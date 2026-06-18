#include "vect2.hpp"

// --- Constructor ---
vect2::vect2(int x, int y){
    v[0] = x;
    v[1] = y;
}

// --- Accessors ---
int& vect2::operator[](int index) { return v[index]; }
const int& vect2::operator[](int index) const { return v[index]; }



// --- Compound Assignments ---
vect2& vect2::operator+=(const vect2& other){
    v[0] += other[0];
    v[1] += other[1];
    return *this;
}

vect2& vect2::operator-=(const vect2& other){
    v[0] -= other[0];
    v[1] -= other[1];
    return *this;
}

// (Smartly reusing compound assignments)
vect2 vect2::operator+(const vect2& other) const{
    vect2 tmp(*this);
    tmp += other;
    return tmp;
}

vect2 vect2::operator-(const vect2& other) const{
    vect2 tmp(*this);
    tmp -= other;
    return tmp;
}



vect2& vect2::operator*=(int scalar){
    v[0] *= scalar;
    v[1] *= scalar;
    return *this;
}

vect2 vect2::operator*(int scalar) const{
    vect2 tmp(*this);
    tmp *= scalar;
    return tmp;
}



// --- Increments & Decrements ---
vect2& vect2::operator++(){
    v[0]++; v[1]++;
    return *this;
}

vect2 vect2::operator++(int){
    vect2 tmp(*this);
    ++(*this);
    return tmp;
}

vect2& vect2::operator--(){
    v[0]--; v[1]--;
    return *this;
}

vect2 vect2::operator--(int){
    vect2 tmp(*this);
    --(*this);
    return tmp;
}



// --- Unary ---
vect2 vect2::operator-() const{ return vect2(-v[0], -v[1]); }



// --- Comparisons ---
bool vect2::operator==(const vect2& other) const{
    return (v[0] == other[0] && v[1] == other[1]);
}

bool vect2::operator!=(const vect2& other) const{
    return !(*this == other); // Smart reuse
}



// --- Non-Member Functions ---
vect2 operator*(int scalar, const vect2& other){
    return other * scalar; // Smart reuse of member operator*(int)
}

std::ostream& operator<<(std::ostream& os, const vect2& other){
    os << "{" << other[0] << ", " << other[1] << "}"; // Fixed bug, uses os
    return os;
}
