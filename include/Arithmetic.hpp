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
	arithmetic(std::string str);
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

	arithmetic operator%(const arithmetic &in) const;

	arithmetic pow(const arithmetic exp) const;

	arithmetic& operator<<=(size_t shiftAmount);
	arithmetic operator<<(size_t shiftAmount);

	arithmetic& operator>>=(size_t shiftAmount);
	arithmetic operator>>(size_t shiftAmount);

	// Comparisons
	bool operator>=(const arithmetic &in) const;
	bool operator>(const arithmetic &in) const;

	bool operator<=(const arithmetic &in) const;
	bool operator<(const arithmetic &in) const;

	bool operator==(const arithmetic &in) const;
	bool operator!=(const arithmetic &in) const;

	// Logical Operators
	bool operator!() const;

	size_t getSize() const;
	bool sign() const;
	arithmetic abs() const;

	friend std::ostream& operator<<(std::ostream& outStream, const arithmetic &in);
	friend arithmetic add(arithmetic operand1, arithmetic operand2);
	friend arithmetic sub(arithmetic operand1, arithmetic operand2);
	friend arithmetic mult(arithmetic operand1, arithmetic operand2);
	friend arithmetic div(arithmetic operand1, arithmetic operand2);
	friend void shiftLeft(arithmetic &in);
	friend bool shiftRight(arithmetic &in);
	friend int compare(arithmetic operand1, arithmetic operand2);
private:
	void grow(size_t newSize);
	void shrink();

	unsigned char *buf;
	size_t size;
	bool negative;
};
