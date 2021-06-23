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

arithmetic::~arithmetic(){
	if (buf != nullptr) {
		delete[] buf;
	}
	buf = nullptr;
}

arithmetic& arithmetic::operator+=(const arithmetic &in) {

	arithmetic temp(in);

	if (in.size < size) {
		if (buf[0] & 0x80) {
			grow(size+1);
			temp.grow(size+1);
		} else {
			temp.grow(size);
		}
	} else if (temp.size > size) {
		if (temp.buf[0] & 0x80) {
			grow(temp.size+1);
			temp.grow(temp.size+1);
		} else {
			grow(temp.size);
		}
	} else {
		if (buf[0] & 0x80) {
			grow(size+1);
			temp.grow(size+1);
		}
	}

	int byteInd = size - 1;
	bool carry = false;
	unsigned int binaryBitMask = 1;

	while (byteInd >= 0) {
		while (binaryBitMask <= 128) {
			if ((binaryBitMask & buf[byteInd]) && (binaryBitMask & temp.buf[byteInd])) {
				if(carry) {
					buf[byteInd] |= binaryBitMask;
				} else {
					buf[byteInd] &= ~binaryBitMask;
				}
				carry = true;
			} else if ((binaryBitMask & buf[byteInd]) || (binaryBitMask & temp.buf[byteInd])) {
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