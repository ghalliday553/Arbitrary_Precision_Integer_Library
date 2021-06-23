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
	arithmetic();
	arithmetic(const char *str);
	arithmetic(const arithmetic &in);
	~arithmetic();

	arithmetic& operator+=(const arithmetic &in);
	size_t getSize() const;

	friend std::ostream& operator<<(std::ostream& outStream, const arithmetic &in);
private:
	void grow(size_t newSize);

	unsigned char *buf;
	size_t size;
};

std::ostream& operator<<(std::ostream& outStream, const arithmetic &in);