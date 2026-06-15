#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2 {

    private:
        int v[2]; // Array optimization for trivial operator[]

    public:
        // Merged default and parameterized constructor
        vect2(int x = 0, int y = 0);
        // Note: We rely on the compiler's perfect default copy constructor, assignment, and destructor.

        // Accessors
        int& operator[](int index);
        const int& operator[](int index) const;

        // Unary
        vect2 operator-() const;

        // Compound Assignments (Vector)
        vect2& operator+=(const vect2& rhs);
        vect2& operator-=(const vect2& rhs);

        // Compound Assignment (Scalar)
        vect2& operator*=(int scalar);

        // Arithmetic (Vector)
        vect2 operator+(const vect2& rhs) const;
        vect2 operator-(const vect2& rhs) const;

        // Arithmetic (Scalar)
        vect2 operator*(int scalar) const;

        // Increments & Decrements
        vect2& operator++();    // Pre
        vect2 operator++(int);  // Post
        vect2& operator--();    // Pre
        vect2 operator--(int);  // Post

        // Comparisons
        bool operator==(const vect2& rhs) const;
        bool operator!=(const vect2& rhs) const;

};



// Non-member Scalar Multiplication (for 3 * v2)
vect2 operator*(int scalar, const vect2& rhs);

// Non-member Ostream
std::ostream& operator<<(std::ostream& os, const vect2& rhs);

#endif