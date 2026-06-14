#include "bigint.hpp"
#include <sstream>
#include <algorithm>
#include <cstdlib>

// --- Helpers & Constructors ---
void bigint::trim(){
    size_t i = 0;
    while (i < val.length() - 1 && val[i] == '0'){
        i++;
    }
    val = val.substr(i);
}

bigint::bigint() : val("0"){}

bigint::bigint(unsigned int n){
    std::stringstream ss;
    ss << n;
    val = ss.str();
}

bigint::bigint(std::string s) : val(s){
    trim();
}

int bigint::toInt() const{
    return std::atoi(val.c_str());
}

std::string bigint::getVal() const{
    return val;
}

// --- Addition ---
bigint bigint::operator+(const bigint& rhs) const{
    std::string res = "";
    int carry = 0;
    int i = val.length() - 1;
    int j = rhs.val.length() - 1;

    // The smart loop: runs until all digits AND the carry are exhausted
    while (i >= 0 || j >= 0 || carry){
        int sum = carry;
        if (i >= 0) sum += val[i--] - '0';
        if (j >= 0) sum += rhs.val[j--] - '0';

        res += (sum % 10) + '0';
        carry = sum / 10;
    }

    std::reverse(res.begin(), res.end());
    return bigint(res);
}

bigint& bigint::operator+=(const bigint& rhs){
    *this = *this + rhs;
    return *this;
}

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

// --- Shifts (Int) ---
bigint bigint::operator<<(unsigned int n) const{
    if (val == "0") return *this; // Prevent "0000"
    std::string res = val;
    res.append(n, '0');
    return bigint(res);
}

bigint bigint::operator>>(unsigned int n) const{
    if (n >= val.length()) return bigint("0"); // Prevent out of range
    return bigint(val.substr(0, val.length() - n));
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
bigint bigint::operator<<(const bigint& rhs) const{ return *this << rhs.toInt(); }
bigint bigint::operator>>(const bigint& rhs) const{ return *this >> rhs.toInt(); }
bigint& bigint::operator<<=(const bigint& rhs){ *this = *this << rhs.toInt(); return *this; }
bigint& bigint::operator>>=(const bigint& rhs){ *this = *this >> rhs.toInt(); return *this; }

// --- Comparisons ---
bool bigint::operator==(const bigint& rhs) const{
    return val == rhs.val;
}

bool bigint::operator<(const bigint& rhs) const{
    // Since we aggressively trimmed leading zeros, length comparison is safe
    if (val.length() != rhs.val.length())
        return val.length() < rhs.val.length();
    return val < rhs.val; // Lexicographical matches numeric if lengths equal
}

// The rest are smartly derived from == and <
bool bigint::operator!=(const bigint& rhs) const{ return !(*this == rhs); }
bool bigint::operator>(const bigint& rhs) const{ return rhs < *this; }
bool bigint::operator<=(const bigint& rhs) const{ return !(rhs < *this); }
bool bigint::operator>=(const bigint& rhs) const{ return !(*this < rhs); }

// --- Ostream ---
std::ostream& operator<<(std::ostream& os, const bigint& obj){
    os << obj.getVal();
    return os;
}
