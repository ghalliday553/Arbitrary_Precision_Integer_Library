#include <Arithmetic.hpp>
#include <limits.h>
#include <stdio.h>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("INITIAL TESTS") {
	/*
	arithmetic ar1("160");
	arithmetic ar2("130");
	ar1+=ar2;

	std::cout<<"INITIAL res is: "<<ar1<<"\n";
	*/
}

TEST_CASE("String to Binary") {
	unsigned int i = 0;
	//while(i < 1000000) {
	while(i < 1000) {
		std::string s = std::to_string(i);
		arithmetic ar(s.c_str());

		std::stringstream output, ref;

		size_t size = ar.getSize();

		const char* beg = reinterpret_cast<const char*>(&i);
		for (size_t ind = size-1; ind > 0; --ind) {
			ref<<std::bitset<8>(beg[ind]);
		}
		ref<<std::bitset<8>(beg[0]);
		
		output<<ar;

		REQUIRE(!strcmp(output.str().c_str(), ref.str().c_str()));
		++i;
	}
}

TEST_CASE("Test Add") {

	unsigned int operand1 = 0;
	unsigned int operand2 = 0;
	unsigned int expected = 0;

	while(operand1 <= 1000) {
		while(operand2 <= 1000) {
			expected = operand1 + operand2;

			arithmetic ar1 = (std::to_string(operand1).c_str());
			arithmetic ar2 = (std::to_string(operand2).c_str());
			ar1+=ar2;

			std::stringstream output, ref;

			size_t size = ar1.getSize();
			const char* beg = reinterpret_cast<const char*>(&expected);
			for (size_t ind = size-1; ind > 0; --ind) {
				ref<<std::bitset<8>(beg[ind]);
			}
			ref<<std::bitset<8>(beg[0]);

			output<<ar1;

			REQUIRE(!strcmp(output.str().c_str(), ref.str().c_str()));
			++operand2;
		}

		operand2 = 0;
		++operand1;
	}

	operand1 = 1;
	operand2 = UINT_MAX;

	arithmetic ar3(std::to_string(operand1).c_str());
	arithmetic ar4(std::to_string(operand2).c_str());
	ar3+=ar4;

	std::cout<<"MAX IS: "<<ar4<<"\n";
	std::cout<<"ONE PAST MAX IS: "<<ar3<<"\n";
}

TEST_CASE("Subtract") {
	unsigned int operand1 = 0;
	unsigned int operand2 = 0;
	unsigned int expected = 0;

	while(operand1 <= 1000) {
		while(operand2 <= operand1) {
			expected = operand1 - operand2;

			arithmetic ar1 = (std::to_string(operand1).c_str());
			arithmetic ar2 = (std::to_string(operand2).c_str());
			ar1-=ar2;

			std::stringstream output, ref;

			size_t size = ar1.getSize();
			const char* beg = reinterpret_cast<const char*>(&expected);
			for (size_t ind = size-1; ind > 0; --ind) {
				ref<<std::bitset<8>(beg[ind]);
			}
			ref<<std::bitset<8>(beg[0]);

			output<<ar1;

			REQUIRE(!strcmp(output.str().c_str(), ref.str().c_str()));
			++operand2;
		}

		operand2 = 0;
		++operand1;
	}
}

TEST_CASE("Multiply") {
	unsigned int operand1 = 0;
	unsigned int operand2 = 0;
	unsigned int expected = 0;

	while(operand1 <= 1000) {
		while(operand2 <= 1000) {
			expected = operand1*operand2;

			arithmetic ar1 = (std::to_string(operand1).c_str());
			arithmetic ar2 = (std::to_string(operand2).c_str());
			ar1*=ar2;

			std::stringstream output, ref;

			size_t size = ar1.getSize();
			const char* beg = reinterpret_cast<const char*>(&expected);
			for (size_t ind = size-1; ind > 0; --ind) {
				ref<<std::bitset<8>(beg[ind]);
			}
			ref<<std::bitset<8>(beg[0]);

			output<<ar1;

			REQUIRE(!strcmp(output.str().c_str(), ref.str().c_str()));
			++operand2;
		}

		operand2 = 0;
		++operand1;
	}
}




