#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <cmath>
#include <ios>
#include <iomanip> 
#include <iostream>

class arithmetic {
public:
	// Constructors
	arithmetic();
	arithmetic(const char *str);
	arithmetic(const arithmetic &in);

	// Assignments
	arithmetic& operator=(const arithmetic &in);

	// Destructor
	~arithmetic();

	// Arithmetic
	arithmetic& operator+=(const arithmetic &in);
	arithmetic operator+(arithmetic in) const;

	arithmetic& operator-=(const arithmetic &in);
	arithmetic operator-(arithmetic in) const;

	arithmetic& operator*=(const arithmetic &in);
	arithmetic operator*(arithmetic in) const;

	arithmetic& operator/=(const arithmetic &in);
	arithmetic operator/(arithmetic in) const;

	arithmetic& operator<<=(unsigned int shiftAmount);
	arithmetic operator<<(unsigned int shiftAmount);

	arithmetic& operator>>=(unsigned int shiftAmount);
	arithmetic operator>>(unsigned int shiftAmount);

	// Comparisons
	bool operator>=(const arithmetic &in) const;
	bool operator>(const arithmetic &in) const;

	bool operator<=(const arithmetic &in) const;
	bool operator<(const arithmetic &in) const;

	bool operator==(const arithmetic &in) const;
	bool operator!=(const arithmetic &in) const;

	size_t getSize() const;

	friend std::ostream& operator<<(std::ostream& outStream, const arithmetic &in);
	friend arithmetic& add(arithmetic &operand1, arithmetic &operand2);
	friend arithmetic& sub(arithmetic &operand1, arithmetic &operand2);
	friend arithmetic& mult(arithmetic &operand1, arithmetic &operand2);
	friend arithmetic& div(arithmetic &operand1, arithmetic &operand2);
	friend void shiftLeft(arithmetic &in);
	friend void shiftRight(arithmetic &in);
	friend int compare(arithmetic operand1, arithmetic operand2);
private:
	void grow(size_t newSize);

	unsigned char *buf;
	size_t size;
};
