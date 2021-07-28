#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <sstream> 
#include <stdlib.h>
#include <queue>
#include <cmath>
#include <ios>
#include <iomanip> 
#include <iostream>

/*
 * Class providing arbitrary-precision integer functionality.
 *
 * Class member functions may throw std::bad_alloc if insufficient memory is available.
 */
class arithmetic {
public:
	// CONSTRUCTORS

	/*
	 *	Default constructor
	 *	
	 *	Initializes to +0 with a size of 1.
	 */
	arithmetic();

	/*
	 * Constructor accepting a decimal string.
	 *
	 * PRECONDITIONS:
	 *	- The string must only contain decimal numbers, except for the first character 
	 *		which may be a '-' sign indicating the value is negative.
	 */
	arithmetic(const arithmetic &in);

	/*
	 * Copy constructor
	 */
	arithmetic(std::string str);

	/*
	 * Move constructor
	 *
	 * The value of the moved object is set to +0 with a size of 1.
	 */
	arithmetic(arithmetic &&in);


	// ASSIGNMENTS

	/*
	 * Copy assignment
	 */
	arithmetic& operator=(const arithmetic &in);

	/*
	 * Move Assignment
	 *
	 * The value of the moved object is set to +0 with a size of 1.
	 */
	arithmetic& operator=(arithmetic &&in);

	// DESTRUCTOR

	/*
	 * Destructor
	 */ 
	~arithmetic();


	// ARITHMETIC

	/*
	 * Compound addition.
	 *
	 * The modified arithmetic object size will be the minimum needed to represent the addition result.
	 */
	arithmetic& operator+=(const arithmetic &in);

	/*
	 * Binary addition.
	 *
	 * The returned object size will be the minimum needed to represent the addition result.
	 */
	arithmetic operator+(arithmetic in) const;

	/*
	 * Pre-increment.
	 *
	 * The modified arithmetic object size will be the minimum needed to represent the addition result.
	 */
	arithmetic& operator++();

	/*
	 * Post-increment.
	 *
	 * The modified arithmetic object size will be the minimum needed to represent the addition result.
	 */
	arithmetic operator++(int);

	/*
	 * Compound subtraction.
	 *
	 * The modified arithmetic object size will be the minimum needed to represent the subtraction result.
	 */
	arithmetic& operator-=(const arithmetic &in);

	/*
	 * Binary subtraction.
	 *
	 * The returned object size will be the minimum needed to represent the subtraction result.
	 */
	arithmetic operator-(arithmetic in) const;

	/*
	 * Pre-decrement.
	 *
	 * The modified arithmetic object size will be the minimum needed to represent the subtraction result.
	 */
	arithmetic& operator--();

	/*
	 * Post-decrement.
	 *
	 * The modified arithmetic object size will be the minimum needed to represent the subtraction result.
	 */
	arithmetic operator--(int);

	/*
	 * Compound multiplication.
	 *
	 * The modified arithmetic object size will be the minimum needed to represent the multiplication result.
	 */
	arithmetic& operator*=(const arithmetic &in);

	/*
	 * Binary multiplication.
	 *
	 * The returned arithmetic object size will be the minimum needed to represent the multiplication result.
	 */
	arithmetic operator*(arithmetic in) const;

	/*
	 * Compound division.
	 *
	 * The result of a division by 0 is defined as 0.
	 * The modified arithmetic object size will be the minimum needed to represent the division result.
	 */
	arithmetic& operator/=(const arithmetic &in);

	/*
	 * Binary division
	 *
	 * The result of a division by 0 is defined as 0.
	 * The returned arithmetic object size will be the minimum needed to represent the division result.
	 */
	arithmetic operator/(arithmetic in) const;

	/*
	 * Modulus
	 * 
	 * Returns an arithmetic object corresponding the modulus result.
	 * The result of a modulus operation with a divisor of 0 is defined to be the dividend.
	 * The returned arithmetic object size will be the minimum needed to represent the modulus result.
	 */
	arithmetic operator%(const arithmetic &in) const;

	/*
	 * Exponentation
	 *
	 * Returns an object corresponding to *this raised to the power of exp.
	 * The returned arithmetic object size will be the minimum needed to represent the exponentiation result.
	 */
	arithmetic pow(const arithmetic exp) const;

	/*
	 * Left shift assignment
	 *
	 * The returned arithmetic object size will be the minimum needed to represent the modulus result.
	 */
	arithmetic& operator<<=(arithmetic shiftAmount);

	/*
	 * Left shift
	 */ 
	arithmetic operator<<(arithmetic shiftAmount);

	/*
	 * Right shift
	 * 
	 * The returned object will be equivalent to a right shift operation on a two's-compliment value.
	 */
	arithmetic& operator>>=(arithmetic shiftAmount);

	/*
	 * Right shift assignment
	 * 
	 * The modified object will be equivalent to a right shift operation on a two's-compliment value.
	 */
	arithmetic operator>>(arithmetic shiftAmount);


	// COMPARISONS

	/*
	 * Greater than or equal to
	 *
	 * Returns true if *this is equal or greater than in, or false otherwise.
	 */
	bool operator>=(const arithmetic &in) const;

	/*
	 * Greater than
	 *
	 * Returns true if *this is greater than in, or false otherwise.
	 */
	bool operator>(const arithmetic &in) const;

	/*
	 * Less than or equal to
	 *
	 * Returns true if *this is less than or equal to in, or false otherwise.
	 */
	bool operator<=(const arithmetic &in) const;

	/*
	 * Less than
	 *
	 * Returns true if *this is less than in, or false otherwise.
	 */
	bool operator<(const arithmetic &in) const;

	/*
	 * Equal to
	 *
	 * Returns true if *this is equal to in, or false otherwise.
	 */
	bool operator==(const arithmetic &in) const;

	/*
	 * Not equal to
	 *
	 * Returns true if *this not equal to in, or false otherwise.
	 */
	bool operator!=(const arithmetic &in) const;


	// LOGICAL OPERATORS

	/*
	 * Logical NOT
	 *
	 * Returns true if the object magnitude is non-0, or false otherwise.
	 */
	bool operator!() const;

	/*
	 * Logical OR
	 *
	 * Returns true if either *this or in is non-0, or false otherwise.
	 */
	bool operator||(const arithmetic &in) const;

	/*
	 * Logical AND
	 *
	 * Returns true if *this and in are non-0, or false otherwise.
	 */
	bool operator&&(const arithmetic &in) const;

	// BITWISE OPERATORS

	/*
	 * Bitwise NOT
	 *
	 * Returns an arithemtic object with the same sign and every *this magnitude bit inverted.
	 * The sign of *this will remain unchanged.
	 */
	arithmetic operator~() const;

	/*
	 * Bitwise AND assignment
	 *
	 * Sets *this to the bitwise AND between the magnitdues of *this and in.
	 * The sign of *this will remain unchanged.
	 * The modified object size will be the larger of either *this or in.
	 */
	arithmetic& operator&=(const arithmetic &in);

	/*
	 * Bitwise AND
	 *
	 * Returns an arithemtic object corresponding to the bitwise AND between the magnitudes of *this and in.
	 * The returned object sign will be equivalent to *this.
	 * The returned object size will be the larger of either *this or in.
	 */
	arithmetic operator&(const arithmetic &in) const;

	/*
	 * Bitwise OR assignment
	 *
	 * Sets *this to the bitwise OR between the magnitdues of *this and in.
	 * The sign of *this will remain unchanged.
	 * The modified object size will be the larger of either *this or in.
	 */
	arithmetic& operator|=(const arithmetic &in);

	/*
	 * Bitwise OR
	 *
	 * Returns an arithemtic object corresponding to the bitwise OR between the magnitudes of *this and in.
	 * The returned object sign will be equivalent to *this.
	 * The returned object size will be the larger of either *this or in.
	 */
	arithmetic operator|(const arithmetic &in) const;


	// OTHER MEMBER FUNCTIONS

	/*
	 * Returns the size of the buffer used to hold the magnitude of *this
	 */
	size_t getSize() const;

	/*
	 * Returns true if the value is positive, or false if the value is negative.
	 *
	 * The value of 0 is defined as being positive.
	 */
	bool sign() const;

	/*
	 * Returns the absolute value of the arithmetic object.
	 */
	arithmetic abs() const;

	/*
	 * Returns a string containing the decimal equivalent of the artithmetic object.
	 *
	 * A "-" will preceed the string if the object is negative.
	 */
	std::string str() const;

	/*
	 * Returns a string containing the binary representation of the magnitude of the artithmetic object.
	 */
	std::string bin() const;

	/*
	 * Sets the arithmetic object to the provided string.
	 *
	 * PRECONDITIONS:
	 * 	the string must only contain decimal numbers, except for the first character 
	 *		which may be a '-' sign indicating the value is negative.
	 */
	void set(std::string str);

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
