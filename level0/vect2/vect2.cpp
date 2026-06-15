#include "vect2.hpp"

// --- Constructor ---
vect2::vect2(int x, int y) {
    v[0] = x;
    v[1] = y;
}

// --- Accessors ---
int& vect2::operator[](int index) { return v[index]; }
const int& vect2::operator[](int index) const { return v[index]; }

// --- Unary ---
vect2 vect2::operator-() const { return vect2(-v[0], -v[1]); }

// --- Compound Assignments ---
vect2& vect2::operator+=(const vect2& rhs) {
    v[0] += rhs[0];
    v[1] += rhs[1];
    return *this;
}

vect2& vect2::operator-=(const vect2& rhs) {
    v[0] -= rhs[0];
    v[1] -= rhs[1];
    return *this;
}

vect2& vect2::operator*=(int scalar) {
    v[0] *= scalar;
    v[1] *= scalar;
    return *this;
}

// --- Arithmetic --- (Smartly reusing compound assignments)
vect2 vect2::operator+(const vect2& rhs) const {
    vect2 tmp(*this);
    tmp += rhs;
    return tmp;
}

vect2 vect2::operator-(const vect2& rhs) const {
    vect2 tmp(*this);
    tmp -= rhs;
    return tmp;
}

vect2 vect2::operator*(int scalar) const {
    vect2 tmp(*this);
    tmp *= scalar;
    return tmp;
}

// --- Increments & Decrements ---
vect2& vect2::operator++() {
    v[0]++; v[1]++;
    return *this;
}

vect2 vect2::operator++(int) {
    vect2 tmp(*this);
    ++(*this);
    return tmp;
}

vect2& vect2::operator--() {
    v[0]--; v[1]--;
    return *this;
}

vect2 vect2::operator--(int) {
    vect2 tmp(*this);
    --(*this);
    return tmp;
}

// --- Comparisons ---
bool vect2::operator==(const vect2& rhs) const {
    return (v[0] == rhs[0] && v[1] == rhs[1]);
}

bool vect2::operator!=(const vect2& rhs) const {
    return !(*this == rhs); // Smart reuse
}



// --- Non-Member Functions ---
vect2 operator*(int scalar, const vect2& rhs) {
    return rhs * scalar; // Smart reuse of member operator*(int)
}

std::ostream& operator<<(std::ostream& os, const vect2& rhs) {
    os << "{" << rhs[0] << ", " << rhs[1] << "}"; // Fixed bug, uses os
    return os;
}