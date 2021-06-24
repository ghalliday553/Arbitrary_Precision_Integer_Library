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

arithmetic& arithmetic::operator+=(arithmetic in) {
	if (in.size < size) {
		if (buf[0] & 0x80) {
			grow(size+1);
			in.grow(size);
		} else {
			in.grow(size);
		}
	} else if (in.size > size) {
		if (in.buf[0] & 0x80) {
			grow(in.size+1);
			in.grow(in.size+1);
		} else {
			grow(in.size);
		}
	} else {
		if (buf[0] & 0x80 || in.buf[0] & 0x80) {
			grow(size+1);
			in.grow(size);
		}
	}

	int byteInd = size - 1;
	bool carry = false;
	unsigned short binaryBitMask = 1;

	while (byteInd >= 0) {
		while (binaryBitMask <= 128) {
			if ((binaryBitMask & buf[byteInd]) && (binaryBitMask & in.buf[byteInd])) {
				if(carry) {
					buf[byteInd] |= binaryBitMask;
				} else {
					buf[byteInd] &= ~binaryBitMask;
				}
				carry = true;
			} else if ((binaryBitMask & buf[byteInd]) || (binaryBitMask & in.buf[byteInd])) {
				if (carry) {
					carry = true;
					buf[byteInd] &= ~binaryBitMask;
				} else {
					buf[byteInd] |= binaryBitMask;
					carry = false;
				}
			} else {
				if (carry) {
					buf[byteInd] |= binaryBitMask;
				} else {
					buf[byteInd] &= ~binaryBitMask;
				}
				carry = false;
			}

			binaryBitMask <<= 1;
		}
		binaryBitMask = 1;
		--byteInd;
	}

	return *this;
}

arithmetic& arithmetic::operator-=(arithmetic in) {
	if (in.size < size) {
		in.grow(size);
	} else if (in.size > size) {
		grow(in.size);
	}

	int byteInd = size - 1;
	bool borrow = false;
	unsigned short binaryBitMask = 1;

	while (byteInd >= 0) {
		while (binaryBitMask <= 128) {
			if ((binaryBitMask & buf[byteInd]) >= 1 && (binaryBitMask & in.buf[byteInd]) >= 1) {
				if(borrow) {
					buf[byteInd] |= binaryBitMask;
				} else {
					buf[byteInd] &= ~binaryBitMask;
				}
			} else if ((binaryBitMask & buf[byteInd]) >= 1 && (binaryBitMask & in.buf[byteInd]) == 0) {
				if (borrow) {
					buf[byteInd] &= ~binaryBitMask;
					borrow = false;
				} else {
					buf[byteInd] |= binaryBitMask;
				}
			} else if ((binaryBitMask & buf[byteInd]) == 0 && (binaryBitMask & in.buf[byteInd]) >= 1) {
				if (!borrow) {
					buf[byteInd] |= binaryBitMask;
				} else {
					buf[byteInd] &= ~binaryBitMask;
				}
				borrow = true;
			} else {
				if (borrow) {
					buf[byteInd] |= binaryBitMask;
				} else {
					buf[byteInd] &= ~binaryBitMask;
				}
			}

			binaryBitMask <<= 1;
		}
		binaryBitMask = 1;
		--byteInd;
	}
	return *this;
}

void arithmetic::shiftLeft() {
	size_t prevSize = size;
	if (buf[0] & 0x80) {
		grow(size+1);
		buf[0] |= 1;
	}

	int byteInd = size - prevSize;
	while(byteInd < size-1) {
		buf[byteInd] <<= 1;
		buf[byteInd] |= (buf[byteInd+1] >> 7);
		++byteInd;
	}
	buf[size-1]<<=1;
}


arithmetic& arithmetic::operator<<=(size_t shiftAmount) {
	for(int i = 0; i < shiftAmount; ++i) {
		shiftLeft();
	}
	return *this;
}

arithmetic& arithmetic::operator*=(arithmetic in) {
	if (in.size < size) {
		in.grow(size);
	} else if (in.size > size) {
		grow(in.size);
	}

	arithmetic result;
	int byteInd = size - 1;
	bool borrow = false;
	unsigned short bitMask = 1;
	int bitOffset = 0;

	bool zeroFlag = true;

	while (byteInd >= 0) {
		while (bitMask <= 128) {
			if (in.buf[byteInd] & bitMask) {
				arithmetic temp(*this);
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
		*this = arithmetic();
	} else {
		*this = result;
	}

	return *this;
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
		//printf("%02x", in.buf[i]);
	}
	return outStream;
}