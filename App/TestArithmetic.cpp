#include <Arithmetic.hpp>
#include <limits.h>
#include <stdio.h>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("INITIAL TESTS") {
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
			arithmetic ar3 = ar1+ar2;
			ar1+=ar2;

			std::stringstream output, outputCompound, ref;

			size_t size = ar1.getSize();
			const char* beg = reinterpret_cast<const char*>(&expected);
			for (size_t ind = size-1; ind > 0; --ind) {
				ref<<std::bitset<8>(beg[ind]);
			}
			ref<<std::bitset<8>(beg[0]);

			output<<ar3;
			outputCompound<<ar1;

			REQUIRE(!strcmp(output.str().c_str(), ref.str().c_str()));
			REQUIRE(!strcmp(outputCompound.str().c_str(), ref.str().c_str()));
			++operand2;
		}

		operand2 = 0;
		++operand1;
	}
	/*
	operand1 = 1;
	operand2 = UINT_MAX;

	arithmetic ar3(std::to_string(operand1).c_str());
	arithmetic ar4(std::to_string(operand2).c_str());
	ar3+=ar4;

	std::cout<<"MAX IS: "<<ar4<<"\n";
	std::cout<<"ONE PAST MAX IS: "<<ar3<<"\n";
	*/
	printf("PASSED ADDITION CASES \n");
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
			arithmetic ar3 = ar1-ar2;
			ar1-=ar2;

			std::stringstream output, outputCompound, ref;

			size_t size = ar1.getSize();
			const char* beg = reinterpret_cast<const char*>(&expected);
			for (size_t ind = size-1; ind > 0; --ind) {
				ref<<std::bitset<8>(beg[ind]);
			}
			ref<<std::bitset<8>(beg[0]);

			outputCompound<<ar1;
			output<<ar3;

			REQUIRE(!strcmp(output.str().c_str(), ref.str().c_str()));
			REQUIRE(!strcmp(outputCompound.str().c_str(), ref.str().c_str()));
			++operand2;
		}

		operand2 = 0;
		++operand1;
	}
	printf("PASSED SUBTRACTION CASES \n");
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
			arithmetic ar3 = ar1*ar2;
			ar1*=ar2;

			std::stringstream output, outputCompound, ref;

			size_t size = ar1.getSize();
			const char* beg = reinterpret_cast<const char*>(&expected);
			for (size_t ind = size-1; ind > 0; --ind) {
				ref<<std::bitset<8>(beg[ind]);
			}
			ref<<std::bitset<8>(beg[0]);

			output<<ar3;
			outputCompound<<ar1;

			REQUIRE(!strcmp(output.str().c_str(), ref.str().c_str()));
			REQUIRE(!strcmp(outputCompound.str().c_str(), ref.str().c_str()));
			++operand2;
		}

		operand2 = 0;
		++operand1;
	}

	printf("PASSED MULTIPLICATION CASES \n");
}

TEST_CASE("Shift Left") {
	unsigned int operand1 = 0;
	unsigned int operand2 = 0;
	unsigned int expected = 0;

	while(operand1 <= 10000) {
		while(operand2 <= 8) {
			expected = operand1<<operand2;

			arithmetic ar1 = (std::to_string(operand1).c_str());
			arithmetic ar2 = ar1<<operand2;
			ar1<<=operand2;

			std::stringstream output, outputCompound, ref;

			size_t size = ar1.getSize();
			const char* beg = reinterpret_cast<const char*>(&expected);
			for (size_t ind = size-1; ind > 0; --ind) {
				ref<<std::bitset<8>(beg[ind]);
			}
			ref<<std::bitset<8>(beg[0]);

			output<<ar2;
			outputCompound<<ar1;

			REQUIRE(!strcmp(output.str().c_str(), ref.str().c_str()));
			REQUIRE(!strcmp(outputCompound.str().c_str(), ref.str().c_str()));
			++operand2;
		}

		operand2 = 0;
		++operand1;
	}

	printf("PASSED LEFT SHIFT CASES \n");
}

TEST_CASE("ShiftRight") {
	unsigned int operand1 = 0;
	unsigned int operand2 = 0;
	unsigned int expected = 0;

	while(operand1 <= 10000) {
		while(operand2 <= 8) {
			expected = operand1>>operand2;

			arithmetic ar1 = (std::to_string(operand1).c_str());
			arithmetic ar2 = ar1>>operand2;
			ar1>>=operand2;

			std::stringstream output, outputCompound, ref;

			size_t size = ar1.getSize();
			const char* beg = reinterpret_cast<const char*>(&expected);
			for (size_t ind = size-1; ind > 0; --ind) {
				ref<<std::bitset<8>(beg[ind]);
			}
			ref<<std::bitset<8>(beg[0]);

			output<<ar2;
			outputCompound<<ar1;

			REQUIRE(!strcmp(output.str().c_str(), ref.str().c_str()));
			REQUIRE(!strcmp(outputCompound.str().c_str(), ref.str().c_str()));
			++operand2;
		}

		operand2 = 0;
		++operand1;
	}

	printf("PASSED RIGHT SHIFT CASES \n");
}

TEST_CASE("Comparisons") {
	unsigned int operand1 = 0;
	unsigned int operand2 = 0;
	unsigned int expected = 0;

	while(operand1 <= 1000) {
		while(operand2 <= 1000) {
			bool expected[] = {false, false, false, false, false, false};
			for(int i = 0; i<6; i++) {
				switch(i) {
					case 0: expected[i] = operand1 >= operand2 ? true : false; break;
					case 1: expected[i] = operand1 > operand2 ? true : false; break;
					case 2: expected[i] = operand1 <= operand2 ? true : false; break;
					case 3: expected[i] = operand1 < operand2 ? true : false; break;
					case 4: expected[i] = operand1 == operand2 ? true : false; break;
					case 5: expected[i] = operand1 != operand2 ? true : false; break;
				}
			} 

			arithmetic ar1 = (std::to_string(operand1).c_str());
			arithmetic ar2 = (std::to_string(operand2).c_str());
			
			bool output[] = {false, false, false, false, false, false};
			for(int i = 0; i<6; i++) {
				switch(i) {
					case 0: output[i] = ar1 >= ar2 ? true : false; break;
					case 1: output[i] = ar1 > ar2 ? true : false; break;
					case 2: output[i] = ar1 <= ar2 ? true : false; break;
					case 3: output[i] = ar1 < ar2 ? true : false; break;
					case 4: output[i] = ar1 == ar2 ? true : false; break;
					case 5: output[i] = ar1 != ar2 ? true : false; break;
				}
			}
			
			for(int i = 0; i<6; i++) {
				REQUIRE(output[i] == expected[i]);
			}

			++operand2;
		}

		operand2 = 0;
		++operand1;
	}

	printf("PASSED COMPARISON CASES \n");
}

TEST_CASE("Division") {
	unsigned int operand1 = 3;
	unsigned int operand2 = 1;
	unsigned int expected = 0;

	while(operand1 <= 1000) {
		while(operand2 <= 1000) {
			expected = operand1/operand2;

			arithmetic ar1 = (std::to_string(operand1).c_str());
			arithmetic ar2 = (std::to_string(operand2).c_str());
			arithmetic ar3 = ar1/ar2;
			ar1/=ar2;

			std::stringstream output, outputCompound, ref;

			size_t size = ar1.getSize();
			const char* beg = reinterpret_cast<const char*>(&expected);
			for (size_t ind = size-1; ind > 0; --ind) {
				ref<<std::bitset<8>(beg[ind]);
			}
			ref<<std::bitset<8>(beg[0]);

			output<<ar3;
			outputCompound<<ar1;

			REQUIRE(!strcmp(output.str().c_str(), ref.str().c_str()));
			REQUIRE(!strcmp(outputCompound.str().c_str(), ref.str().c_str()));

			++operand2;
		}

		operand2 = 1;
		++operand1;
	}

	printf("PASSED DIVISION CASES \n");
}




