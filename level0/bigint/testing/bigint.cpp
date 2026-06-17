#include "bigint.hpp"
#include <sstream>
#include <algorithm>
#include <cstdlib>

// --- Helpers & Constructors ---
void bigint::_trim(){
    size_t i = 0;
    while (i + 1 < _val.length() && _val[i] == '0'){
        i++;
    }
    _val = _val.substr(i);
}

bigint::bigint() : _val("0"){}

bigint::bigint(unsigned int n){
    std::stringstream ss;
    ss << n;
    _val = ss.str();
}

bigint::bigint(std::string str) : _val(str){
    _trim();
}


// --- Addition ---
bigint bigint::operator+(const bigint& other) const{
    std::string res = "";
    int carry = 0;
    int i = _val.length() - 1;
    int j = other._val.length() - 1;

    // The smart loop: runs until all digits AND the carry are exhausted
    while (i >= 0 || j >= 0 || carry){
        int sum = carry;
        if (i >= 0) sum += _val[i--] - '0';
        if (j >= 0) sum += other._val[j--] - '0';

        res += (sum % 10) + '0';
        carry = sum / 10;
    }

    std::reverse(res.begin(), res.end());
    return bigint(res);
}

bigint& bigint::operator+=(const bigint& other){
    *this = *this + other;
    return *this;
}




// --- Shifts (Int) ---
bigint bigint::operator<<(unsigned int n) const{
    if (_val == "0") return *this; // Prevent "0000"
    std::string res = _val;
    res.append(n, '0');
    return bigint(res);
}

bigint bigint::operator>>(unsigned int n) const{
    if (n >= _val.length()) return bigint("0"); // Prevent out of range
    return bigint(_val.substr(0, _val.length() - n));
}

bigint& bigint::operator<<=(unsigned int n){
    *this = *this << n;
    return *this;
}

bigint& bigint::operator>>=(unsigned int n){
    *this = *this >> n;
    return *this;
}



// --- Shifts (Bigint reuse) ---
int bigint::toInt() const{
    return std::atoi(_val.c_str());
}

bigint bigint::operator<<(const bigint& other) const{ return *this << other.toInt(); }
bigint bigint::operator>>(const bigint& other) const{ return *this >> other.toInt(); }
bigint& bigint::operator<<=(const bigint& other){ *this = *this << other.toInt(); return *this; }
bigint& bigint::operator>>=(const bigint& other){ *this = *this >> other.toInt(); return *this; }




// --- Comparisons ---
bool bigint::operator==(const bigint& other) const{
    return _val == other._val;
}

bool bigint::operator<(const bigint& other) const{
    // Since we aggressively _trimmed leading zeros, length comparison is safe
    if (_val.length() != other._val.length())
        return _val.length() < other._val.length();
    return _val < other._val; // Lexicographical matches numeric if lengths equal
}

// The rest are smartly derived from == and <
bool bigint::operator!=(const bigint& other) const{ return !(*this == other); }
bool bigint::operator>(const bigint& other) const{ return other < *this; }
bool bigint::operator<=(const bigint& other) const{ return !(other < *this); }
bool bigint::operator>=(const bigint& other) const{ return !(*this < other); }





// --- Increments ---
bigint& bigint::operator++(){
    *this += bigint(1);
    return *this;
}

bigint bigint::operator++(int){
    bigint tmp(*this);
    ++(*this);
    return tmp;
}





std::string bigint::getVal() const{
    return _val;
}

// --- Ostream ---
std::ostream& operator<<(std::ostream& os, const bigint& obj){
    os << obj.getVal();
    return os;
}



