#include <Arithmetic.hpp>

/*
 * Divides a decimal string by 2. 
 *
 * INPUTS:
 *	str - Arbitrary size string consisting only of decimal numbers.
 *	
 * OUTPUTS:	
 * 	str - Output is written in place.
 *
 * PRECONDITIONS:
 *	- str must contain only decimal numbers.
 */
static void divStringByTwo(std::string &str) {
	int add = 0;

	// Loop through string
	for(std::string::iterator it = str.begin(); it != str.end(); ++it) {
		int digit = *it - '0';
		digit /= 2;
		digit += add;
		switch(*it) {
			case '1':
			case '3':
			case '5':
			case '7':
			case '9':
				add = 5;
				break;
			default:
				add = 0;
				break;
		}
		*it = digit + '0';
	}

	// Erase front padded zeros
	str.erase(0, std::min(str.find_first_not_of('0'), str.size() - 1));
}

/*
 * Converts a positive string of decimal numbers to its binary equivalent using an array of unsigned chars.
 * The concatination of array members forms the unsigned magnitude binary representation of the provided number. 
 *
 * INPUTS:
 *	inputStr - Input string consisting of a decimal number with arbitrary size
 *	outputBufSize - Size of the provided buffer to hold the binary equivalent
 *	
 * OUTPUTS:	
 * 	binaryOutputBuf - buffer to hold the binary equivalent
 *
 * PRECONDITIONS:
 *	- inputStr must contain only decimal numbers.
 * 	- outputBufSize must be able to hold the binary representation of the provided decimal number.
 */
static void stringToBinary(const char *inputStr, unsigned char *binaryOutputBuf, size_t outputBufSize) {
	std::string tempString = inputStr;
	std::queue<unsigned short> outputQueue;
	unsigned int binaryBitMask = 1;
	unsigned char currentByte = 0x00;
	size_t byteInd = outputBufSize-1;
	int len;

	// Look while the decimal string is not "0"
	while(tempString.find_first_not_of('0') != std::string::npos) {
		// Push 1 onto a queue if least significant digit is odd. Push a 0 otherwise.
		switch(tempString[tempString.size()-1]) {
			case '1':
			case '3':
			case '5':
			case '7':
			case '9':
				outputQueue.push(1);
				break;
			default:
				outputQueue.push(0);
				break;
		}
		divStringByTwo(tempString);
	}
	
	// Write queue to binaryOutputBuffer, moving from LSB to MSB.
	while(!outputQueue.empty()) {
		if (binaryBitMask <= 128) {
			if (outputQueue.front() == 1) {
				currentByte |= binaryBitMask;
			}
			outputQueue.pop();
			binaryBitMask <<= 1;
		} else {
			binaryBitMask = 1;
			binaryOutputBuf[byteInd] = currentByte;
			--byteInd;
			currentByte = 0x00;
		}
	}

	if (binaryBitMask > 1) {
		binaryOutputBuf[byteInd] = currentByte;
	}
}

/*
 * Performs binary addition on the magnitude of two arithmetic objects.
 * The returned object size will be the minimum needed to represent the addition result.
 *
 * INPUTS:
 *	operand1
 *	operand2
 *	
 * OUTPUTS:	
 * 	returns an object holding the addition result
 *
 * PRECONDITIONS:
 *	- operand1 and operand2 must both be positive.
 */
arithmetic add(arithmetic operand1, arithmetic operand2) {
	// Grow operands if needed
	// Operands must be the same size
	if (operand2.size < operand1.size) {
		if (operand1.buf[0] & 0x80) {
			operand1.grow(operand1.size+1);
			operand2.grow(operand1.size);
		} else {
			operand2.grow(operand1.size);
		}
	} else if (operand2.size > operand1.size) {
		if (operand2.buf[0] & 0x80) {
			operand1.grow(operand2.size+1);
			operand2.grow(operand2.size+1);
		} else {
			operand1.grow(operand2.size);
		}
	} else {
		if (operand1.buf[0] & 0x80 || operand2.buf[0] & 0x80) {
			operand1.grow(operand1.size+1);
			operand2.grow(operand1.size);
		}
	}

	size_t byteInd = operand1.getSize() - 1;
	bool carry = false;
	unsigned short binaryBitMask = 1;

	// Perform binary addition
	while (1) {
		while (binaryBitMask <= 128) {
			if ((binaryBitMask & operand1.buf[byteInd]) && (binaryBitMask & operand2.buf[byteInd])) {
				if(carry) {
					operand1.buf[byteInd] |= binaryBitMask;
				} else {
					operand1.buf[byteInd] &= ~binaryBitMask;
				}
				carry = true;
			} else if ((binaryBitMask & operand1.buf[byteInd]) || (binaryBitMask & operand2.buf[byteInd])) {
				if (carry) {
					carry = true;
					operand1.buf[byteInd] &= ~binaryBitMask;
				} else {
					operand1.buf[byteInd] |= binaryBitMask;
					carry = false;
				}
			} else {
				if (carry) {
					operand1.buf[byteInd] |= binaryBitMask;
				} else {
					operand1.buf[byteInd] &= ~binaryBitMask;
				}
				carry = false;
			}

			binaryBitMask <<= 1;
		}
		binaryBitMask = 1;

		if(byteInd == 0) {
			break;
		} else {
			--byteInd;
		}
	}

	return operand1;
}


/*
 * Performs binary subtraction on the magnitude of two arithmetic objects.
 * The returned object size will be the same as operand1.
 *
 * INPUTS:
 *	operand1
 *	operand2 - value to subtract from operand 1
 *	
 * OUTPUTS:	
 * 	returns an object holding the subtraction result
 *
 * PRECONDITIONS:
 *	- operand1 must be equal or greater than operand 2.
 */
arithmetic sub(arithmetic operand1, arithmetic operand2) {
	// Grow operands if needed
	// Operands must be the same size
	if (operand2.size < operand1.size) {
		operand2.grow(operand1.size);
	}

	size_t byteInd = operand1.size - 1;
	bool borrow = false;
	unsigned short binaryBitMask = 1;

	// Perform binary subtraction
	while (1) {
		while (binaryBitMask <= 128) {
			if ((binaryBitMask & operand1.buf[byteInd]) >= 1 && (binaryBitMask & operand2.buf[byteInd]) >= 1) {
				if(borrow) {
					operand1.buf[byteInd] |= binaryBitMask;
				} else {
					operand1.buf[byteInd] &= ~binaryBitMask;
				}
			} else if ((binaryBitMask & operand1.buf[byteInd]) >= 1 && (binaryBitMask & operand2.buf[byteInd]) == 0) {
				if (borrow) {
					operand1.buf[byteInd] &= ~binaryBitMask;
					borrow = false;
				} else {
					operand1.buf[byteInd] |= binaryBitMask;
				}
			} else if ((binaryBitMask & operand1.buf[byteInd]) == 0 && (binaryBitMask & operand2.buf[byteInd]) >= 1) {
				if (!borrow) {
					operand1.buf[byteInd] |= binaryBitMask;
				} else {
					operand1.buf[byteInd] &= ~binaryBitMask;
				}
				borrow = true;
			} else {
				if (borrow) {
					operand1.buf[byteInd] |= binaryBitMask;
				} else {
					operand1.buf[byteInd] &= ~binaryBitMask;
				}
			}

			binaryBitMask <<= 1;
		}
		binaryBitMask = 1;
		if(byteInd == 0) {
			break;
		} else {
			--byteInd;
		}
	}

	return operand1;
}

/*
 * Performs binary multiplication on the magnitude of two arithmetic objects.
 * The returned object size will be the minumum needed to hold the multiplication result.
 *
 * INPUTS:
 *	operand1
 *	operand2
 *	
 * OUTPUTS:	
 * 	returns an object holding the multiplcation result
 *
 * PRECONDITIONS:
 *	- operand1 and operand2 must be positive.
 */
arithmetic mult(arithmetic operand1, arithmetic operand2) {
	// Grow operands if needed
	// Operands must be the same size
	if (operand2.size < operand1.size) {
		operand2.grow(operand1.size);
	} else if (operand2.size > operand1.size) {
		operand1.grow(operand2.size);
	}

	arithmetic result;
	size_t byteInd = operand1.size - 1;
	bool borrow = false;
	unsigned short bitMask = 1;
	int bitOffset = 0;

	bool zeroFlag = true;

	// Perform multiplication
	while (1) {
		while (bitMask <= 128) {
			if (operand2.buf[byteInd] & bitMask) {
				arithmetic temp(operand1);
				temp <<= arithmetic(std::to_string(bitOffset));
				result += temp;
				if (zeroFlag) {
					zeroFlag = false;
				}
			}

			++bitOffset;
			bitMask <<= 1;
		}

		bitMask = 1;
		if(byteInd == 0) {
			break;
		} else {
			--byteInd;
		}
	}

	if (zeroFlag) {
		operand1 = arithmetic();
	} else {
		operand1 = result;
	}

	return operand1;
}

/*
 * Performs binary division on the magnitude of two arithmetic objects.
 * The returned object size will be the size of the larger operand.
 *
 * INPUTS:
 *	operand1
 *	operand2 - value operand1 will be divided by
 *	
 * OUTPUTS:	
 * 	returns an object holding the division result
 *
 * PRECONDITIONS:
 *	- operand1 and operand2 must be positive.
 *
 * NOTES:
 *	- The result of a division by 0 is defined as 0.
 */
arithmetic div(arithmetic operand1, arithmetic operand2) {
	// Division by 0 is defined as 0
	if(!operand2) {
		return arithmetic();
	}

	// Grow operands if needed
	// Operands must be the same size
	if (operand2.size < operand1.size) {
		operand2.grow(operand1.size);
	} else if (operand2.size > operand1.size) {
		operand1.grow(operand2.size);
	}

	arithmetic temp;
	arithmetic res;
	temp.grow(operand1.size);
	res.grow(operand1.size);

	size_t byteInd = 0;
	unsigned short bitInd = 0;
	unsigned short bitMask = 128;

	// Perform division
	while (byteInd < operand1.size) {
		while(bitMask > 0) {
			temp = (operand1 >> arithmetic(std::to_string((8*operand1.size - (8*byteInd + bitInd + 1)))));
			if (operand2 <= temp) {
				break;
			}
			bitMask>>=1;
			++bitInd;
		}

		if (operand2 <= temp) {
			res.buf[byteInd] |= (bitMask);

			size_t numberOfShifts = ((operand1.size-(byteInd+1))*8 + 7-bitInd);
		
			operand1 = sub(operand1, (operand2 << arithmetic(std::to_string(numberOfShifts))));
			temp = arithmetic();
		}

		if (bitMask == 0){
			++byteInd;
			bitMask = 128;
			bitInd = 0;
		}
	}

	return res;
}

/*
 * Performs a single left shift operation on the magnitude of an arithmetic object.
 * The size of the provided object may grow by 1 byte if required.
 *
 * INPUTS:
 *	in
 *	
 * OUTPUTS:	
 * 	in
 *
 * PRECONDITIONS:
 *	- none.
 */
void shiftLeft(arithmetic &in) {
	size_t prevSize = in.size;
	if (in.buf[0] & 0x80) {
		in.grow(in.size+1);
		in.buf[0] |= 1;
	}

	size_t byteInd = in.size - prevSize;
	while(byteInd < in.size-1) {
		in.buf[byteInd] <<= 1;
		in.buf[byteInd] |= (in.buf[byteInd+1] >> 7);
		++byteInd;
	}
	in.buf[in.size-1]<<=1;
}

/*
 * Performs a single right shift operation on the magnitude of an arithmetic object.
 * The provided object size will not be modified.
 *
 * INPUTS:
 *	in
 *	
 * OUTPUTS:	
 * 	in
 *	returns a boolean indicating if the lost bit was a 1 (true) or 0 (false).
 *
 * PRECONDITIONS:
 *	- none.
 */
bool shiftRight(arithmetic &in) {
	size_t byteInd = 0;
	unsigned int newTemp = 0;
	unsigned int prevTemp = 0;
	bool remainder = in.buf[in.getSize()-1] & 1;

	while(byteInd < in.size) {
		prevTemp = newTemp;
		newTemp = (in.buf[byteInd] & 1);
		in.buf[byteInd] >>= 1;
		in.buf[byteInd] |= (prevTemp<<7);

		++byteInd;
	}

	return remainder;
}

/*
 * Performs a comparison between two arithmetic objects, factoring in the sign.
 *
 * INPUTS:
 *	operand1
 *	operand2
 *	
 * OUTPUTS:	
 * 	returns +1 if operand1 > operand2
 *	returns -1 if operand2 > operand1
 *	returns 0 if the operands are equal
 *
 * PRECONDITIONS:
 *	- none.
 */
int compare(arithmetic operand1, arithmetic operand2) {
	// Grow operands if needed
	// Operands must be the same size
	if (operand2.size < operand1.size) {
		operand2.grow(operand1.size);
	} else if (operand2.size > operand1.size) {
		operand1.grow(operand2.size);
	}

	unsigned int bitMask = 128;
	size_t byteInd = 0;
	bool operand1IsGreater = false;
	bool operand2IsGreater = false;

	// Determine which magnitude is larger
	while(byteInd < operand1.size) {
		while (bitMask >= 1) {
			if ((operand1.buf[byteInd] & bitMask) && !(operand2.buf[byteInd] & bitMask)) {
				operand1IsGreater = true;
				break;
			} else if ((operand2.buf[byteInd] & bitMask) && !(operand1.buf[byteInd] & bitMask)) {
				operand2IsGreater = true;
				break;
			}
			bitMask >>= 1;
		}

		if (operand2IsGreater || operand1IsGreater) {
			break;
		}

		bitMask = 128;
		++byteInd;
	}

	// Account for operand signs	
	if (operand1IsGreater) {
		if (operand1.sign()) {
			return 1;
		} else {
			return -1;
		}
	} else if(operand2IsGreater) {
		if (operand2.sign()) {
			return -1;
		} else {
			return 1;
		}
	}
	else {
		if(operand1.sign() == operand2.sign()){
			return 0;
		} else {
			return operand1.sign()? 1 : -1;
		}
	}
	return 0;
}

/*
 *	Default constructor
 *	
 *	Initializes to +0 with a size of 1.
 */
arithmetic::arithmetic() {
	buf = new unsigned char[1]();
	negative = false;
	size = 1;
}

/*
 * Copy constructor
 */
arithmetic::arithmetic(const arithmetic &in) {
	size = in.size;
	buf = new unsigned char[size]();
	negative = in.negative;
	memcpy(buf, in.buf, size);
}

/*
 * Constructor accepting a decimal string.
 *
 * PRECONDITIONS:
 *	- The string must only contain decimal numbers, except for the first character 
 *		which may be a '-' sign indicating the value is negative.
 */
arithmetic::arithmetic(std::string str){
	if (str.front() == '-') {
		negative = true;
		str.erase(0,1);
	} else {
		negative = false;
	}

	// Find the max number of bytes needed to hold the binary representation of a decimal string with a certain length.
	size_t requiredBufSize = (floor(str.length()*log2(10))+1)/8.0 + 1;

	buf = new unsigned char[requiredBufSize]();
	size = requiredBufSize;
	stringToBinary(str.c_str(), buf, requiredBufSize);
	shrink();
}

/*
 * Move constructor
 *
 * The value of the moved object is set to +0 with a size of 1.
 */
arithmetic::arithmetic(arithmetic &&in) {
	size = in.getSize();
	buf = in.buf;
	negative = in.negative;

	in.buf = new unsigned char[1]();
	in.size = 1;
	in.negative = false;
}

/*
 * Copy assignment
 */
arithmetic& arithmetic::operator=(const arithmetic &in){
	delete[] buf;
	buf = new unsigned char[in.size]();
	size = in.size;
	negative = in.negative;
	memcpy(buf, in.buf, size);

	return *this;
}

/*
 * Move Assignment
 *
 * The value of the moved object is set to +0 with a size of 1.
 */
arithmetic& arithmetic::operator=(arithmetic &&in) {
	delete[] buf;

	size = in.getSize();
	buf = in.buf;
	negative = in.negative;

	in.buf = new unsigned char[1]();
	in.size = 1;
	in.negative = false;

	return *this;
}

/*
 * Destructor
 */ 
arithmetic::~arithmetic(){
	if (buf != nullptr) {
		delete[] buf;
	}
	buf = nullptr;
}

/*
 * Compound addition.
 *
 * The modified arithmetic object size will be the minimum needed to represent the addition result.
 */
arithmetic& arithmetic::operator+=(const arithmetic &in) {
	if (this->sign() != in.sign()){
		if (this->abs() < in.abs()) {
			*this = sub(in, *this);
		} else {
			*this = sub(*this, in);
			if (!(*this) && this->negative) {
				this->negative = false;
			}
		}
	} else {
		*this = add(*this, in);
	}
	shrink();
	return *this;
}

/*
 * Binary addition.
 *
 * The returned object size will be the minimum needed to represent the addition result.
 */
arithmetic arithmetic::operator+(arithmetic in) const {
	arithmetic temp = *this;
	arithmetic res;
	if (temp.sign() != in.sign()){
		if (temp.abs() < in.abs()) {
			res = sub(in, temp);
			res.negative = !temp.negative;
		} else {
			res = sub(temp, in);
			if (!res) {
				res.negative = false;
			} else {
				res.negative = temp.negative;
			}
		}
	} else {
		res = add(temp, in);
		res.negative = this->negative;
	}
	res.shrink();
	return res;
}

/*
 * Pre-increment.
 *
 * The modified arithmetic object size will be the minimum needed to represent the addition result.
 */
arithmetic& arithmetic::operator++() {
	return *this += arithmetic("1");
}

/*
 * Post-increment.
 *
 * The modified arithmetic object size will be the minimum needed to represent the addition result.
 */
arithmetic arithmetic::operator++(int) {
	arithmetic temp = *this;
	*this += arithmetic("1");
	return temp;
}

/*
 * Compound subtraction.
 *
 * The modified arithmetic object size will be the minimum needed to represent the subtraction result.
 */
arithmetic& arithmetic::operator-=(const arithmetic &in) {
	if (this->sign() == in.sign()){
		if (this->abs() < in.abs()) {
			*this = sub(in, *this);
			this->negative = !(this->negative);
		} else {
			*this = sub(*this, in);
			if (!(*this) && this->negative) {
				this->negative = false;
			}
		}
	} else {
		*this = add(*this, in);
	}
	shrink();
	return *this;
}

/*
 * Binary subtraction.
 *
 * The returned object size will be the minimum needed to represent the subtraction result.
 */
arithmetic arithmetic::operator-(arithmetic in) const {
	arithmetic temp = *this;
	arithmetic res;
	if (temp.sign() == in.sign()){
		if (temp.abs() < in.abs()) {
			res = sub(in, temp);
			res.negative = !(temp.negative);
		} else {
			res = sub(temp, in);
			if (!res) {
				res.negative = false;
			} else {
				res.negative = temp.negative;
			}
		}
	} else {
		res = add(temp, in);
		res.negative = temp.negative;
	}
	res.shrink();
	return res;
}

/*
 * Pre-decrement.
 *
 * The modified arithmetic object size will be the minimum needed to represent the subtraction result.
 */
arithmetic& arithmetic::operator--() {
	return *this -= arithmetic("1");
}

/*
 * Post-decrement.
 *
 * The modified arithmetic object size will be the minimum needed to represent the subtraction result.
 */
arithmetic arithmetic::operator--(int) {
	arithmetic temp = *this;
	*this -= arithmetic("1");
	return temp;
}

/*
 * Compound multiplication.
 *
 * The modified arithmetic object size will be the minimum needed to represent the multiplication result.
 */
arithmetic& arithmetic::operator*=(const arithmetic &in) {
	bool negative = (this->negative ^ in.negative);
	*this = mult(this->abs(), in);
	if(!(*this)) {
		this->negative = false;
	} else {
		this->negative = negative;
	}
	return *this;
}

/*
 * Binary multiplication.
 *
 * The returned arithmetic object size will be the minimum needed to represent the multiplication result.
 */
arithmetic arithmetic::operator*(arithmetic in) const {
	arithmetic temp = mult(this->abs(), in);
	if(!temp) {
		temp.negative = false;
	} else {
		temp.negative = (this->negative ^ in.negative);
	}
	return temp;
}

/*
 * Compound division.
 *
 * The result of a division by 0 is defined as 0.
 * The modified arithmetic object size will be the minimum needed to represent the division result.
 */
arithmetic& arithmetic::operator/=(const arithmetic &in) {
	bool negative = (this->negative ^ in.negative);
	*this = div(this->abs(), in.abs());
	if(!(*this)) {
		this->negative = false;
	} else {
		this->negative = negative;
	}
	shrink();
	return *this;
}

/*
 * Binary division
 *
 * The result of a division by 0 is defined as 0.
 * The returned arithmetic object size will be the minimum needed to represent the division result.
 */
arithmetic arithmetic::operator/(arithmetic in) const{
	arithmetic temp = div(this->abs(), in.abs());
	if(!temp) {
		temp.negative = false;
	} else {
		temp.negative = (this->negative ^ in.negative);
	}
	temp.shrink();
	return temp;
}

/*
 * Modulus
 * 
 * Returns an arithmetic object corresponding the modulus result.
 * The result of a modulus operation with a divisor of 0 is defined to be the dividend.
 * The returned arithmetic object size will be the minimum needed to represent the modulus result.
 */
arithmetic arithmetic::operator%(const arithmetic &in) const {
	arithmetic res = *this/in;
	return (*this - res*in);
}

/*
 * Left shift assignment
 *
 * The returned arithmetic object size will be the minimum needed to represent the modulus result.
 */
arithmetic& arithmetic::operator<<=(arithmetic shiftAmount) {
	for(; !(!shiftAmount); --shiftAmount) {
		shiftLeft(*this);
	}
	return *this;
}

/*
 * Left shift
 */ 
arithmetic arithmetic::operator<<(arithmetic shiftAmount) {
	arithmetic temp = *this;
	for(; !(!shiftAmount); --shiftAmount) {
		shiftLeft(temp);
	}
	return temp;
}

/*
 * Right shift
 * 
 * The returned object will be equivalent to a right shift operation on a two's-compliment value.
 */
arithmetic arithmetic::operator>>(arithmetic shiftAmount) {
	arithmetic temp = *this;
	bool remainderFlag = false;

	for(; !(!shiftAmount); --shiftAmount) {
		bool tempRemainderFlag = shiftRight(temp);
		if (tempRemainderFlag && !remainderFlag) {
			remainderFlag = true;
		}
	}
	
	if(!temp.sign() && remainderFlag) {
		temp--;
	}
	
	temp.shrink();
	return temp;
}

/*
 * Right shift assignment
 * 
 * The modified object will be equivalent to a right shift operation on a two's-compliment value.
 */
arithmetic& arithmetic::operator>>=(arithmetic shiftAmount) {
	bool remainderFlag = false;
	for(; !(!shiftAmount); --shiftAmount) {
		bool tempRemainderFlag = shiftRight(*this);
		if (tempRemainderFlag && !remainderFlag) {
			remainderFlag = true;
		}
	}
	
	if(!this->sign() && remainderFlag) {
		(*this)--;
	}
	
	shrink();
	return *this;
}

/*
 * Greater than or equal to
 *
 * Returns true if *this is equal or greater than in, or false otherwise.
 */
bool arithmetic::operator>=(const arithmetic &in) const {
	int comp = compare(*this, in);
	if (comp >= 0) {
		return true;
	} else {
		return false;
	}
}

/*
 * Greater than
 *
 * Returns true if *this is greater than in, or false otherwise.
 */
bool arithmetic::operator>(const arithmetic &in) const {
	int comp = compare(*this, in);
	if (comp > 0) {
		return true;
	} else {
		return false;
	}
}

/*
 * Less than or equal to
 *
 * Returns true if *this is less than or equal to in, or false otherwise.
 */
bool arithmetic::operator<=(const arithmetic &in) const {
	int comp = compare(*this, in);
	if (comp <= 0) {
		return true;
	} else {
		return false;
	}
}

/*
 * Less than
 *
 * Returns true if *this is less than in, or false otherwise.
 */
bool arithmetic::operator<(const arithmetic &in) const {
	int comp = compare(*this, in);
	if (comp < 0) {
		return true;
	} else {
		return false;
	}
}

/*
 * Equal to
 *
 * Returns true if *this is equal to in, or false otherwise.
 */
bool arithmetic::operator==(const arithmetic &in) const {
	int comp = compare(*this, in);
	if (comp == 0) {
		return true;
	} else {
		return false;
	}
}

/*
 * Not equal to
 *
 * Returns true if *this not equal to in, or false otherwise.
 */
bool arithmetic::operator!=(const arithmetic &in) const {
	int comp = compare(*this, in);
	if (comp != 0) {
		return true;
	} else {
		return false;
	}
}

/*
 * Exponentation
 *
 * Returns an object corresponding to *this raised to the power of exp.
 * The returned arithmetic object size will be the minimum needed to represent the exponentiation result.
 */
arithmetic arithmetic::pow(const arithmetic exp) const {
	arithmetic one = arithmetic("1");
	arithmetic temp = *this;

	if (!exp) {
		return one;
	} else if (!exp.sign() && temp.abs() > one){
		return arithmetic();
	}
	
	arithmetic expTemp = exp.abs() - one;
	while (!(!expTemp)) {
		temp*=(*this);
		expTemp -= one;
	}
	return temp;
}

/*
 * Logical NOT
 *
 * Returns true if the object magnitude is non-0, or false otherwise.
 */
bool arithmetic::operator!() const {
	unsigned int bitMask = 128;
	size_t byteInd = 0;

	while(byteInd < this->size) {
		while (bitMask >= 1) {
			if ((bitMask & this->buf[byteInd]) != 0) {
				return false;
			}
			bitMask >>= 1;
		}

		bitMask = 128;
		++byteInd;
	}
	return true;;
}

/*
 * Logical OR
 *
 * Returns true if either *this or in is non-0, or false otherwise.
 */
bool arithmetic::operator||(const arithmetic &in) const {
	return (!(!*this) || !(!in));
}

/*
 * Logical AND
 *
 * Returns true if *this and in are non-0, or false otherwise.
 */
bool arithmetic::operator&&(const arithmetic &in) const { 
	return (!(!*this) && !(!in));
}

/*
 * Bitwise NOT
 *
 * Returns an arithemtic object with the same sign and every *this magnitude bit inverted.
 * The sign of *this will remain unchanged.
 */
arithmetic arithmetic::operator~() const {
	arithmetic ret = *this;
	for (size_t i = 0; i < this->getSize(); ++i) {
		unsigned char temp = this->buf[i];
		ret.buf[i] = ~temp;
	}
	return ret;
}

/*
 * Bitwise AND
 *
 * Returns an arithemtic object corresponding to the bitwise AND between the magnitudes of *this and in.
 * The returned object sign will be equivalent to *this.
 * The returned object size will be the larger of either *this or in.
 */
arithmetic arithmetic::operator&(const arithmetic &in) const {
	arithmetic tempIn = in;
	arithmetic tempSelf = *this;

	if (tempSelf.getSize() < tempIn.getSize()) {
		tempSelf.grow(tempIn.getSize());
	} else if (tempIn.getSize() < tempSelf.getSize()) {
		tempIn.grow(tempSelf.getSize());
	}

	for (size_t i = 0; i < tempSelf.getSize(); ++i) {
		tempSelf.buf[i] &= tempIn.buf[i];
	}
	return tempSelf;
}

/*
 * Bitwise AND assignment
 *
 * Sets *this to the bitwise AND between the magnitdues of *this and in.
 * The sign of *this will remain unchanged.
 * The modified object size will be the larger of either *this or in.
 */
arithmetic& arithmetic::operator&=(const arithmetic &in) {
	arithmetic tempIn = in;

	if (this->getSize() < tempIn.getSize()) {
		this->grow(tempIn.getSize());
	} else if (tempIn.getSize() < this->getSize()) {
		tempIn.grow(this->getSize());
	}

	for (size_t i = 0; i < this->getSize(); ++i) {
		this->buf[i] &= tempIn.buf[i];
	}
	return *this;
}


/*
 * Bitwise OR
 *
 * Returns an arithemtic object corresponding to the bitwise OR between the magnitudes of *this and in.
 * The returned object sign will be equivalent to *this.
 * The returned object size will be the larger of either *this or in.
 */
arithmetic arithmetic::operator|(const arithmetic &in) const {
	arithmetic tempIn = in;
	arithmetic tempSelf = *this;

	if (tempSelf.getSize() < tempIn.getSize()) {
		tempSelf.grow(tempIn.getSize());
	} else if (tempIn.getSize() < tempSelf.getSize()) {
		tempIn.grow(tempSelf.getSize());
	}

	for (size_t i = 0; i < tempSelf.getSize(); ++i) {
		tempSelf.buf[i] |= tempIn.buf[i];
	}
	return tempSelf;
}

/*
 * Bitwise OR assignment
 *
 * Sets *this to the bitwise OR between the magnitdues of *this and in.
 * The sign of *this will remain unchanged.
 * The modified object size will be the larger of either *this or in.
 */
arithmetic& arithmetic::operator|=(const arithmetic &in) {
	arithmetic tempIn = in;

	if (this->getSize() < tempIn.getSize()) {
		this->grow(tempIn.getSize());
	} else if (tempIn.getSize() < this->getSize()) {
		tempIn.grow(this->getSize());
	}

	for (size_t i = 0; i < this->getSize(); ++i) {
		this->buf[i] |= tempIn.buf[i];
	}
	return *this;
}

/*
 * Returns the size of the buffer used to hold the magnitude of *this
 */
size_t arithmetic::getSize() const {
	return size;
}

/*
 * Returns true if the value is positive, or false if the value is negative.
 *
 * The value of 0 is defined as being positive.
 */
bool arithmetic::sign() const {
	return !negative;
}

/*
 * Returns a string containing the decimal equivalent of the artithmetic object.
 *
 * A "-" will preceed the string if the object is negative.
 */
std::string arithmetic::str() const {
	bool negative = !this->sign();
	arithmetic temp = this->abs();
	arithmetic ten("10");
	std::string str;
	if (!temp) {
		str.push_back('0');
		return str;
	}
	if (!(this->sign())) {
		str.push_back('-');
	}
	while (!(!temp)){
		arithmetic remainder = temp - (temp/ten)*ten;
		char remainderChar = remainder.buf[remainder.getSize()-1] + 48;
		if (negative) {
			str.insert(str.begin()+1, remainderChar);
		} else {
			str.insert(str.begin(), remainderChar);
		}
		temp/=ten;
	}

	return str;  
}

/*
 * Returns a string containing the binary representation of the magnitude of the artithmetic object.
 */
std::string arithmetic::bin() const {
	std::stringstream ret;
	for (int i = 0; i<this->getSize(); i++) {
		ret << (std::bitset<8>(this->buf[i]));
	}
	return ret.str();
}

/*
 * Returns the absolute value of the arithmetic object.
 */
arithmetic arithmetic::abs() const {
	arithmetic temp = *this;
	temp.negative = false;
	return temp;
}

/*
 * Sets the arithmetic object to the provided string.
 *
 * PRECONDITIONS:
 * 	the string must only contain decimal numbers, except for the first character 
 *		which may be a '-' sign indicating the value is negative.
 */
void arithmetic::set(std::string str) {
	delete[] this->buf;

	if (str.front() == '-') {
		negative = true;
		str.erase(0,1);
	} else {
		negative = false;
	}

	size_t requiredBufSize = (floor(str.length()*log2(10))+1)/8.0 + 1;

	buf = new unsigned char[requiredBufSize]();
	size = requiredBufSize;
	stringToBinary(str.c_str(), buf, requiredBufSize);
	shrink();
}

/*
 * Private function used to grow the buffer holding the magnitude of the binary number.
 */ 
void arithmetic::grow(size_t newSize) {
	unsigned char *oldBuf = buf;

	buf = new unsigned char[newSize]();

	memcpy(buf+(newSize-size), oldBuf, size);
	size = newSize;

	delete[] oldBuf;
}

/*
 * Private function used to shrink the object buffer to the	minimum size needed to represent the stored number.
 */ 
void arithmetic::shrink() {
	unsigned char *oldBuf = buf;

	size_t bytesToShrink = 0;
	size_t byteInd = 0;
	while(byteInd < this->getSize() && (buf[byteInd] == 0)) {
		++bytesToShrink;
		++byteInd;
	}

	size_t newSize = size - bytesToShrink;

	if (newSize == 0){
		++newSize;
		--bytesToShrink;
	}

	buf = new unsigned char[newSize]();

	memcpy(buf, oldBuf+bytesToShrink, newSize);
	size = newSize;

	delete[] oldBuf;
}

/*
 * Stream inserter
 *
 * Writes the decimal equivalent of the binary number to the provided stream.
 * A "-" will preceed the string if the object is negative.
 * 
 */
std::ostream& operator<<(std::ostream& outStream, const arithmetic &in) {
	outStream<<in.str();
	return outStream;
}