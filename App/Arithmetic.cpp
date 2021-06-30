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
	unsigned int byteInd = outputBufSize-1;
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

arithmetic& add(arithmetic &operand1, arithmetic &operand2) {
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

	int byteInd = operand1.size - 1;
	bool carry = false;
	unsigned short binaryBitMask = 1;

	while (byteInd >= 0) {
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
		--byteInd;
	}

	return operand1;
}

arithmetic& sub(arithmetic &operand1, arithmetic &operand2) {
	if (operand2.size < operand1.size) {
		operand2.grow(operand1.size);
	} else if (operand2.size > operand1.size) {
		operand1.grow(operand2.size);
	}

	int byteInd = operand1.size - 1;
	bool borrow = false;
	unsigned short binaryBitMask = 1;

	while (byteInd >= 0) {
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
		--byteInd;
	}
	return operand1;
}

arithmetic& mult(arithmetic &operand1, arithmetic &operand2) {
	if (operand2.size < operand1.size) {
		operand2.grow(operand1.size);
	} else if (operand2.size > operand1.size) {
		operand1.grow(operand2.size);
	}

	arithmetic result;
	int byteInd = operand1.size - 1;
	bool borrow = false;
	unsigned short bitMask = 1;
	int bitOffset = 0;

	bool zeroFlag = true;

	while (byteInd >= 0) {
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
		--byteInd;
	}

	if (zeroFlag) {
		operand1 = arithmetic();
	} else {
		operand1 = result;
	}

	return operand1;
}

arithmetic& div(arithmetic &operand1, arithmetic &operand2) {
	if (operand2.size < operand1.size) {
		operand2.grow(operand1.size);
	} else if (operand2.size > operand1.size) {
		operand1.grow(operand2.size);
	}

	arithmetic temp;
	arithmetic res;
	temp.grow(operand1.size);
	res.grow(operand1.size);

	unsigned short byteInd = 0;
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
			operand1 -= (operand2 << ((operand1.size-(byteInd+1))*8 + 7-bitInd));
			temp = arithmetic();
		}

		if (bitMask == 0){
			++byteInd;
			bitMask = 128;
			bitInd = 0;
		}
	}

	operand1 = res;
	return operand1;
}

void shiftLeft(arithmetic &in) {
	size_t prevSize = in.size;
	if (in.buf[0] & 0x80) {
		in.grow(in.size+1);
		in.buf[0] |= 1;
	}

	int byteInd = in.size - prevSize;
	while(byteInd < in.size-1) {
		in.buf[byteInd] <<= 1;
		in.buf[byteInd] |= (in.buf[byteInd+1] >> 7);
		++byteInd;
	}
	in.buf[in.size-1]<<=1;
}

void shiftRight(arithmetic &in) {
	unsigned int byteInd = 0;
	unsigned int newTemp = 0;
	unsigned int prevTemp = 0;

	while(byteInd < in.size) {
		prevTemp = newTemp;
		newTemp = (in.buf[byteInd] & 1);
		in.buf[byteInd] >>= 1;
		in.buf[byteInd] |= (prevTemp<<7);

		++byteInd;
	}
}

int compare(arithmetic operand1, arithmetic operand2) {
	if (operand2.size < operand1.size) {
		operand2.grow(operand1.size);
	} else if (operand2.size > operand1.size) {
		operand1.grow(operand2.size);
	}

	unsigned int bitMask = 128;
	int byteInd = 0;

	while(byteInd < operand1.size) {
		while (bitMask >= 1) {
			if ((operand1.buf[byteInd] & bitMask) && !(operand2.buf[byteInd] & bitMask)) {
				return 1;
			} else if ((operand2.buf[byteInd] & bitMask) && !(operand1.buf[byteInd] & bitMask)) {
				return -1;
			}
			bitMask >>= 1;
		}

		bitMask = 128;
		++byteInd;
	}
	return 0;
}

arithmetic::arithmetic() {
	buf = new unsigned char[1]();
	size = 1;
}

arithmetic::arithmetic(const arithmetic &in) {
	size = in.size;
	buf = new unsigned char[size]();
	memcpy(buf, in.buf, size);
}

arithmetic::arithmetic(const char *str){
	size_t requiredBufSize = (floor(strlen(str)*log2(10))+1)/8.0 + 1;

	buf = new unsigned char[requiredBufSize]();
	size = requiredBufSize;
	stringToBinary(str, strlen(str)+1, buf, requiredBufSize);
}

arithmetic& arithmetic::operator=(const arithmetic &in){
	delete[] buf;
	buf = new unsigned char[in.size]();
	size = in.size;
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
	arithmetic temp = in;
	return add(*this, temp);
}

arithmetic arithmetic::operator+(arithmetic in) const {
	arithmetic temp = *this;
	return add(temp, in);
}

arithmetic& arithmetic::operator-=(const arithmetic &in) {
	arithmetic temp = in;
	return sub(*this, temp);
}

arithmetic arithmetic::operator-(arithmetic in) const {
	arithmetic temp = *this;
	return sub(temp, in);
}

arithmetic& arithmetic::operator*=(const arithmetic &in) {
	arithmetic temp = in;
	return mult(*this, temp);
}

arithmetic arithmetic::operator*(arithmetic in) const {
	arithmetic temp = *this;
	return mult(temp, in);
}

arithmetic& arithmetic::operator/=(const arithmetic &in) {
	arithmetic temp = in;
	return div(*this, temp);
}

arithmetic arithmetic::operator/(arithmetic in) const{
	arithmetic temp = *this;
	return div(temp, in);
}

arithmetic& arithmetic::operator<<=(unsigned int shiftAmount) {
	for(int i = 0; i < shiftAmount; ++i) {
		shiftLeft(*this);
	}
	return *this;
}

arithmetic arithmetic::operator<<(unsigned int shiftAmount) {
	arithmetic temp = *this;
	for(int i = 0; i < shiftAmount; ++i) {
		shiftLeft(temp);
	}
	return temp;
}

arithmetic arithmetic::operator>>(unsigned int shiftAmount) {
	arithmetic temp = *this;
	for(int i = 0; i < shiftAmount; ++i) {
		shiftRight(temp);
	}
	return temp;
}

arithmetic& arithmetic::operator>>=(unsigned int shiftAmount) {
	for(int i = 0; i < shiftAmount; ++i) {
		shiftRight(*this);
	}
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

size_t arithmetic::getSize() const {
	return size;
}

void arithmetic::grow(size_t newSize) {
	unsigned char *oldBuf = buf;

	buf = new unsigned char[newSize]();

	memcpy(buf+(newSize-size), oldBuf, size);
	size = newSize;

	delete[] oldBuf;
}

std::ostream& operator<<(std::ostream& outStream, const arithmetic &in) {
	for (int i = 0; i<in.size; i++) {
		outStream<<std::bitset<8>(in.buf[i]);
	}
	return outStream;
}