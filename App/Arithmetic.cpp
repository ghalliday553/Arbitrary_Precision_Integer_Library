#include <Arithmetic.hpp>

/*
 * Helper function for stringToBits()
 */
static void divStringByTwo(char *buf) {
	int add = 0;
	for (char *it = buf; *it != '\0'; ++it) {
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

	int zeroOffset = 0;
	for(char *it = buf; *it == '0'; ++it) {
		++zeroOffset;
	}
	memmove(buf, buf+zeroOffset, strlen(buf)-zeroOffset+1);
}

/*
 * Converts a string of decimal numbers to both its binary string and binary equivalents
 *
 * Input: inputBuf
 *	- Input string consisting of a decimal number of arbitrary size
 *
 * Output: stringOutputBuf, binaryOutputBuf
 *	- Output buffers where the equivalent binary string and binary representations are written
 *
 * Note: stringOutputBuf and binaryOutputBuf must be large enough to hold the largest needed numbers.
 * 		 Their sizes must be defined using ARITHMETIC_STRING_BUFF_LEN and ARITHMETIC_BINARY_BUFF_LEN.
 */
static bool stringToBinary(const char *inputBuf, size_t inputBufSize, unsigned char *binaryOutputBuf, size_t outputBufSize) {
	char *stringTempBuf = new char[inputBufSize]();
	std::queue<unsigned short> outputQueue;
	unsigned int binaryBitMask = 1;
	unsigned char currentByte = 0x00;
	size_t byteInd = outputBufSize-1;
	int counter = 0;
	int len;

	// Convert decimal string to binary string
	strcpy(stringTempBuf, inputBuf);

	while(strlen(stringTempBuf)) {
		switch(stringTempBuf[strlen(stringTempBuf)-1]) {
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
		divStringByTwo(stringTempBuf);
		counter++;
	}
	
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

	delete[] stringTempBuf;
	return true;
}

arithmetic add(arithmetic operand1, arithmetic operand2) {
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

arithmetic sub(arithmetic operand1, arithmetic operand2) {
	if (operand2.size < operand1.size) {
		operand2.grow(operand1.size);
	}

	size_t byteInd = operand1.size - 1;
	bool borrow = false;
	unsigned short binaryBitMask = 1;

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

arithmetic mult(arithmetic operand1, arithmetic operand2) {
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

	while (1) {
		while (bitMask <= 128) {
			if (operand2.buf[byteInd] & bitMask) {
				arithmetic temp(operand1);
				temp <<= bitOffset;
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

arithmetic div(arithmetic operand1, arithmetic operand2) {
	if(!operand2) {
		return arithmetic();
	}

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

	while (byteInd < operand1.size) {
		while(bitMask > 0) {
			temp = (operand1 >> (8*operand1.size - (8*byteInd + bitInd + 1)));
			if (operand2 <= temp) {
				break;
			}
			bitMask>>=1;
			++bitInd;
		}

		if (operand2 <= temp) {
			res.buf[byteInd] |= (bitMask);

			size_t numberOfShifts = ((operand1.size-(byteInd+1))*8 + 7-bitInd);
		
			operand1 = sub(operand1, (operand2 << numberOfShifts));
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

int compare(arithmetic operand1, arithmetic operand2) {
	if (operand2.size < operand1.size) {
		operand2.grow(operand1.size);
	} else if (operand2.size > operand1.size) {
		operand1.grow(operand2.size);
	}

	unsigned int bitMask = 128;
	size_t byteInd = 0;
	bool operand1IsGreater = false;
	bool operand2IsGreater = false;

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

arithmetic::arithmetic() {
	buf = new unsigned char[1]();
	negative = false;
	size = 1;
}

arithmetic::arithmetic(const arithmetic &in) {
	size = in.size;
	buf = new unsigned char[size]();
	negative = in.negative;
	memcpy(buf, in.buf, size);
}

arithmetic::arithmetic(std::string str){
	if (str.front() == '-') {
		negative = true;
		str.erase(0,1);
	} else {
		negative = false;
	}

	size_t requiredBufSize = (floor(str.length()*log2(10))+1)/8.0 + 1;

	buf = new unsigned char[requiredBufSize]();
	size = requiredBufSize;
	stringToBinary(str.c_str(), str.length()+1, buf, requiredBufSize);
	shrink();
}

arithmetic& arithmetic::operator=(const arithmetic &in){
	delete[] buf;
	buf = new unsigned char[in.size]();
	size = in.size;
	negative = in.negative;
	memcpy(buf, in.buf, size);

	return *this;
}

arithmetic::~arithmetic(){
	if (buf != nullptr) {
		delete[] buf;
	}
	buf = nullptr;
}

arithmetic& arithmetic::operator+=(const arithmetic &in) {
	if (this->sign() != in.sign()){
		if (this->abs() < in) {
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

arithmetic arithmetic::operator+(arithmetic in) const {
	arithmetic temp = *this;
	arithmetic res;
	if (temp.sign() != in.sign()){
		if (temp.abs() < in) {
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

arithmetic& arithmetic::operator-=(const arithmetic &in) {
	if (this->sign() == in.sign()){
		if (this->abs() < in) {
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

arithmetic arithmetic::operator-(arithmetic in) const {
	arithmetic temp = *this;
	arithmetic res;
	if (temp.sign() == in.sign()){
		if (temp.abs() < in) {
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

arithmetic arithmetic::operator*(arithmetic in) const {
	arithmetic temp = mult(this->abs(), in);
	if(!temp) {
		temp.negative = false;
	} else {
		temp.negative = (this->negative ^ in.negative);
	}
	return temp;
}

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

arithmetic arithmetic::operator%(const arithmetic &in) const {
	arithmetic res = *this/in;
	return (*this - res*in);
}

arithmetic& arithmetic::operator<<=(size_t shiftAmount) {
	for(int i = 0; i < shiftAmount; ++i) {
		shiftLeft(*this);
	}
	return *this;
}

arithmetic arithmetic::operator<<(size_t shiftAmount) {
	arithmetic temp = *this;
	for(int i = 0; i < shiftAmount; ++i) {
		shiftLeft(temp);
	}
	return temp;
}

arithmetic arithmetic::operator>>(size_t shiftAmount) {
	arithmetic temp = *this;
	bool remainderFlag = false;

	for(int i = 0; i < shiftAmount; ++i) {
		bool tempRemainderFlag = shiftRight(temp);
		if (tempRemainderFlag && !remainderFlag) {
			remainderFlag = true;
		}
	}
	
	if(!temp.sign() && remainderFlag) {
		temp -= arithmetic("1");
	}
	
	temp.shrink();
	return temp;
}

arithmetic& arithmetic::operator>>=(size_t shiftAmount) {
	bool remainderFlag = false;
	for(int i = 0; i < shiftAmount; ++i) {
		bool tempRemainderFlag = shiftRight(*this);
		if (tempRemainderFlag && !remainderFlag) {
			remainderFlag = true;
		}
	}
	
	if(!this->sign() && remainderFlag) {
		*this -= arithmetic("1");
	}
	
	shrink();
	return *this;
}

bool arithmetic::operator>=(const arithmetic &in) const {
	int comp = compare(*this, in);
	if (comp >= 0) {
		return true;
	} else {
		return false;
	}
}

bool arithmetic::operator>(const arithmetic &in) const {
	int comp = compare(*this, in);
	if (comp > 0) {
		return true;
	} else {
		return false;
	}
}

bool arithmetic::operator<=(const arithmetic &in) const {
	int comp = compare(*this, in);
	if (comp <= 0) {
		return true;
	} else {
		return false;
	}
}

bool arithmetic::operator<(const arithmetic &in) const {
	int comp = compare(*this, in);
	if (comp < 0) {
		return true;
	} else {
		return false;
	}
}

bool arithmetic::operator==(const arithmetic &in) const {
	int comp = compare(*this, in);
	if (comp == 0) {
		return true;
	} else {
		return false;
	}
}

bool arithmetic::operator!=(const arithmetic &in) const {
	int comp = compare(*this, in);
	if (comp != 0) {
		return true;
	} else {
		return false;
	}
}

arithmetic arithmetic::pow(const arithmetic exp) const {
	if (!exp) {
		return arithmetic("1");
	} else if(!exp.sign()) {
		return arithmetic();
	}

	arithmetic temp = *this;
	arithmetic expTemp = exp - arithmetic("1");
	while (!(!expTemp)) {
		temp*=(*this);
		expTemp -= arithmetic("1");
	}
	return temp;
}

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

size_t arithmetic::getSize() const {
	return size;
}

bool arithmetic::sign() const {
	return !negative;
}

arithmetic arithmetic::abs() const {
	arithmetic temp = *this;
	temp.negative = false;
	return temp;
}

void arithmetic::grow(size_t newSize) {
	unsigned char *oldBuf = buf;

	buf = new unsigned char[newSize]();

	memcpy(buf+(newSize-size), oldBuf, size);
	size = newSize;

	delete[] oldBuf;
}

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

std::ostream& operator<<(std::ostream& outStream, const arithmetic &in) {
	for (int i = 0; i<in.size; i++) {
		outStream<<std::bitset<8>(in.buf[i]);
	}
	return outStream;
}