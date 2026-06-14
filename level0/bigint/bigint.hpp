#ifndef BIGINT_HPP
#define BIGINT_HPP

# include <iostream>
# include <string>

class bigint{
    private:
        std::string val;
        void trim(); // Helper to remove leading zeros

    public:
        // Constructors (Rely on Rule of Zero for Copy/Assign/Destructor)
        bigint();
        bigint(unsigned int n);
        bigint(std::string s);

        // Helper for shift logic
        int toInt() const;

        // Addition
        bigint operator+(const bigint &rhs) const;
        bigint& operator+=(const bigint &rhs);

        // Increments
        bigint& operator++();    // Pre
        bigint operator++(int);  // Post

        // Shifts (with int)
        bigint operator<<(unsigned int n) const;
        bigint operator>>(unsigned int n) const;
        bigint& operator<<=(unsigned int n);
        bigint& operator>>=(unsigned int n);

        // Shifts (with bigint)
        bigint operator<<(const bigint &rhs) const;
        bigint operator>>(const bigint &rhs) const;
        bigint& operator<<=(const bigint &rhs);
        bigint& operator>>=(const bigint &rhs);

        // Comparisons (Write < and ==, derive the rest)
        bool operator==(const bigint &rhs) const;
        bool operator!=(const bigint &rhs) const;
        bool operator<(const bigint &rhs) const;
        bool operator>(const bigint &rhs) const;
        bool operator<=(const bigint &rhs) const;
        bool operator>=(const bigint &rhs) const;

        // Getter for ostream
        std::string getVal() const;
};

std::ostream& operator<<(std::ostream& os, const bigint& obj);

#endif
