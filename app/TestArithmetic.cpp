#include <Arithmetic.hpp>
#include <limits.h>
#include <cmath>
#include <stdio.h>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("StringToBinary") {
	// Test value
	int i = -1000;

	while(i < 1000) {
		int absolute = abs(i);
		arithmetic ar(std::to_string(i));
		std::string expected;

		// Generate string of bits corresponding to "abolute"'s magnitude
		const char* beg = reinterpret_cast<const char*>(&absolute);
		for (size_t ind = ar.getSize()-1; ind > 0; --ind) {
			expected = expected + std::bitset<8>(beg[ind]).to_string();
		}
		expected = expected + std::bitset<8>(beg[0]).to_string();

		// Validate
		REQUIRE(ar.bin() == expected);
		if(i >= 0) {
			REQUIRE(ar.sign() == true);
		} else {
			REQUIRE(ar.sign() == false);
		}
		++i;
	}

	printf("PASSED STRING_TO_BINARY CASES\n");
}

TEST_CASE("Addition") {
	int operand1 = -1000;
	int operand2 = -1000;
	int expected = 0;

	while(operand1 <= 1000) {
		while(operand2 <= 1000) {
			expected = operand1 + operand2;

			arithmetic ar1 = (std::to_string(operand1));
			arithmetic ar2 = (std::to_string(operand2));

			arithmetic ar3 = ar1+ar2;
			ar1+=ar2;

			if (operand1 % 50 == 0 && operand2 == 0) {
				printf("operand1 is %i | operand2 is %i\n", operand1, operand2);
			}

			REQUIRE(ar3.str() == std::to_string(expected));
			REQUIRE(ar1.str() == std::to_string(expected));
			REQUIRE(ar3.sign() == (expected >= 0 ? true : false));
			REQUIRE(ar1.sign() == (expected >= 0 ? true : false));
			
			++operand2;
		}

		operand2 = -1000;
		++operand1;
	}
	printf("PASSED ADDITION CASES \n");
}

TEST_CASE("Subtraction") {
	int operand1 = -1000;
	int operand2 = -1000;
	int expected = 0;

	while(operand1 <= 1000) {
		while(operand2 <= 1000) {
			expected = operand1 - operand2;

			arithmetic ar1 = (std::to_string(operand1));
			arithmetic ar2 = (std::to_string(operand2));

			arithmetic ar3 = ar1-ar2;
			ar1-=ar2;

			if (operand1 % 10 == 0 && operand2 == 0) {
				printf("operand1 is %i | operand2 is %i\n", operand1, operand2);
			}

			REQUIRE(ar3.str() == std::to_string(expected));
			REQUIRE(ar1.str() == std::to_string(expected));
			REQUIRE(ar3.sign() == (expected >= 0 ? true : false));
			REQUIRE(ar1.sign() == (expected >= 0 ? true : false));
			
			++operand2;
		}

		operand2 = -1000;
		++operand1;
	}
	printf("PASSED SUBTRACTION CASES \n");
}

TEST_CASE("Multiplication") {
	int operand1 = -1000;
	int operand2 = -1000;
	int expected = 0;

	while(operand1 <= 1000) {
		while(operand2 <= 1000) {
			expected = operand1 * operand2;

			arithmetic ar1 = (std::to_string(operand1));
			arithmetic ar2 = (std::to_string(operand2));

			arithmetic ar3 = ar1*ar2;
			ar1*=ar2;

			if (operand1 % 10 == 0 && operand2 == 0) {
				printf("operand1 is %i | operand2 is %i\n", operand1, operand2);
			}

			REQUIRE(ar3.str() == std::to_string(expected));
			REQUIRE(ar1.str() == std::to_string(expected));
			REQUIRE(ar3.sign() == (expected >= 0 ? true : false));
			REQUIRE(ar1.sign() == (expected >= 0 ? true : false));
			
			++operand2;
		}

		operand2 = -1000;
		++operand1;
	}

	printf("PASSED MULTIPLICATION CASES \n");
}

TEST_CASE("ShiftLeft") {
	int operand1 = -1000;
	int operand2 = 0;
	int expected = 0;

	while(operand1 <= 1000) {
		while(operand2 <= 20) {
			expected = operand1 << operand2;

			arithmetic ar1 = (std::to_string(operand1));
			arithmetic ar2 = (std::to_string(operand2));

			arithmetic ar3 = ar1<<ar2;
			ar1<<=ar2;

			if (operand1 % 10 == 0 && operand2 == 0) {
				printf("operand1 is %i | operand2 is %i\n", operand1, operand2);
			}

			REQUIRE(ar3.str() == std::to_string(expected));
			REQUIRE(ar1.str() == std::to_string(expected));
			REQUIRE(ar3.sign() == (expected >= 0 ? true : false));
			REQUIRE(ar1.sign() == (expected >= 0 ? true : false));
			
			++operand2;
		}

		operand2 = 0;
		++operand1;
	}

	printf("PASSED LEFT SHIFT CASES \n");
}

TEST_CASE("ShiftRight") {
	int operand1 = -1000;
	int operand2 = 0;
	int expected = 0;

	while(operand1 <= 1000) {
		while(operand2 <= 15) {
			expected = operand1 >> operand2;

			arithmetic ar1 = (std::to_string(operand1));
			arithmetic ar2 = (std::to_string(operand2));

			arithmetic ar3 = ar1>>ar2;
			ar1>>=ar2;

			if (operand1 % 10 == 0 && operand2 == 0) {
				printf("operand1 is %i | operand2 is %i\n", operand1, operand2);
			}

			REQUIRE(ar3.str() == std::to_string(expected));
			REQUIRE(ar1.str() == std::to_string(expected));
			REQUIRE(ar3.sign() == (expected >= 0 ? true : false));
			REQUIRE(ar1.sign() == (expected >= 0 ? true : false));
			
			++operand2;
		}

		operand2 = 0;
		++operand1;
	}

	printf("PASSED RIGHT SHIFT CASES \n");
}

TEST_CASE("Comparisons") {
	int operand1 = -1000;
	int operand2 = -1000;
	int expected = 0;

	while(operand1 <= 1000) {
		while(operand2 <= 1000) {
			if (operand1 % 200 == 0 && operand2 == 0) {
				printf("operand1 is %i | operand2 is %i\n", operand1, operand2);
			}

			// Generate array of expected values for each supported comparison operation
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

			arithmetic ar1 = (std::to_string(operand1));
			arithmetic ar2 = (std::to_string(operand2));
			
			// Perform comparison operations on arbitrary precision objects
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
			
			// Validate arrays are equivalent
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
	int operand1 = -1000;
	int operand2 = -1000;
	int expected = 0;

	while(operand1 <= 1000) {
		while(operand2 <= 1000) {
			if (operand2 == 0) {
				expected = 0;
			} else {
				expected = operand1/operand2;
			}

			arithmetic ar1 = (std::to_string(operand1));
			arithmetic ar2 = (std::to_string(operand2));

			arithmetic ar3 = ar1/ar2;
			ar1/=ar2;

			if (operand1 % 10 == 0 && operand2 == 0) {
				printf("operand1 is %i | operand2 is %i\n", operand1, operand2);
			}

			REQUIRE(ar3.str() == std::to_string(expected));
			REQUIRE(ar1.str() == std::to_string(expected));
			REQUIRE(ar3.sign() == (expected >= 0 ? true : false));
			REQUIRE(ar1.sign() == (expected >= 0 ? true : false));
			
			++operand2;
		}

		operand2 = -1000;
		++operand1;
	}

	printf("PASSED DIVISION CASES \n");
}

TEST_CASE("Modulus") {
	int operand1 = -1000;
	int operand2 = -1000;
	int expected = 0;

	while(operand1 <= 1000) {
		while(operand2 <= 1000) {
			if (operand2 == 0) {
				expected = operand1;
			} else {
				expected = operand1%operand2;
			}

			arithmetic ar1 = (std::to_string(operand1));
			arithmetic ar2 = (std::to_string(operand2));

			arithmetic ar3 = ar1%ar2;

			if (operand1 % 10 == 0 && operand2 == 0) {
				printf("operand1 is %i | operand2 is %i\n", operand1, operand2);
			}

			REQUIRE(ar3.str() == std::to_string(expected));
			REQUIRE(ar3.sign() == (expected >= 0 ? true : false));
			
			++operand2;
		}

		operand2 = -1000;
		++operand1;
	}

	printf("PASSED MODULUS CASES \n");
}

TEST_CASE("Pow") {
	long long int operand1 = -9;
	long long int operand2 = -9;
	long long int expected = 0;

	while(operand1 <= 9) {
		while(operand2 <= 9) {
			if (operand1 == 0 && operand2 < 0) {
				expected = 0;
			} else {
				expected = pow(operand1, operand2);
			}
			
			arithmetic ar1 = (std::to_string(operand1));
			arithmetic ar2 = (std::to_string(operand2));

			arithmetic ar3 = ar1.pow(ar2);

			if (operand1 % 10 == 0 && operand2 == 0) {
				printf("operand1 is %lli | operand2 is %lli\n", operand1, operand2);
			}

			REQUIRE(ar3.str() == std::to_string(expected));
			REQUIRE(ar3.sign() == (expected >= 0 ? true : false));
			
			++operand2;
		}

		operand2 = -9;
		++operand1;
	}

	printf("PASSED POW CASES \n");
}

TEST_CASE("Str") {
	int operand1 = -1000;
	std::string expected;

	while(operand1 <= 1000) {
		expected = std::to_string(operand1);

		arithmetic ar1 = (std::to_string(operand1));
		std::stringstream output;
		output<<ar1;

		REQUIRE(expected == ar1.str());
		REQUIRE(expected == output.str());

		++operand1;
	}

	printf("PASSED STR CASES \n");
}

TEST_CASE("IncrementDecrement") {
	int operand1 = -1000;
	int incExpected = 0;
	int decExpected = 0;

	while(operand1 <= 1000) {
		incExpected = ++operand1;
		--operand1;
		decExpected = --operand1; 
		++operand1; 

		arithmetic ar1 = (std::to_string(operand1));

		arithmetic operand1Result = (std::to_string(operand1));
		arithmetic incResult = (std::to_string(incExpected));
		arithmetic decResult = (std::to_string(decExpected));

		REQUIRE((ar1--).str() == operand1Result.str());
		REQUIRE(ar1.str() == decResult.str());
		REQUIRE(ar1.sign() == decResult.sign());

		++ar1;

		REQUIRE((--ar1).str() == decResult.str());
		REQUIRE(ar1.sign() == decResult.sign());

		REQUIRE((ar1++).str() == decResult.str());
		REQUIRE(ar1.str() == operand1Result.str());
		REQUIRE(ar1.sign() == operand1Result.sign());

		REQUIRE((++ar1).str() == incResult.str());
		REQUIRE(ar1.sign() == incResult.sign());

		++operand1;
	}

	printf("PASSED MODULUS CASES \n");
}

TEST_CASE("Logical") {
	arithmetic zero;
	arithmetic one("1");
	arithmetic negOne("-1");

	REQUIRE(!zero == true);
	REQUIRE(!one == false);
	REQUIRE(!negOne == false);

	REQUIRE((zero || zero) == false);
	REQUIRE((one || zero) == true);
	REQUIRE((negOne || zero) == true);
	REQUIRE((one || negOne) == true);

	REQUIRE((zero && zero) == false);
	REQUIRE((one && zero) == false);
	REQUIRE((negOne && zero) == false);
	REQUIRE((one && negOne) == true);
}

TEST_CASE("Bitwise") {
	unsigned int operand1 = 0;
	unsigned int operand2 = 0;

	unsigned int expectedAnd = 0;
	unsigned int expectedOr = 0;
	unsigned int expectedNot = 0;

	while(operand1 <= 1000) {
		while(operand2 <= 1000) {
			
			// Expected values
			arithmetic andExpected(std::to_string(operand1 & operand2));
			arithmetic orExpected(std::to_string(operand1 | operand2));
			arithmetic notExpected(std::to_string(~operand1));

			arithmetic ar1 = std::to_string(operand1);
			arithmetic ar2 = std::to_string(operand2);

			// Output values
			arithmetic notOutput = ~ar1;
			arithmetic orOutput = ar1 | ar2;
			arithmetic andOutput = ar1 & ar2;

			if (operand1 % 200 == 0 && operand2 == 0) {
				printf("operand1 is %i | operand2 is %i\n", operand1, operand2);
			}

			// Get NOT binary strings
			std::string notOutputBin = notOutput.bin();
			std::string notExpectedBin = notExpected.bin();

			// Crop expected length to match string length of output
			notExpectedBin = notExpectedBin.substr(notExpectedBin.size()-notOutputBin.size(), notOutputBin.size());

			// Get AND binary strings
			std::string andOutputBin = andOutput.bin();
			std::string andExpectedBin = andExpected.bin();

			// Make the expected and output string lengths equal
			if (andExpectedBin.size() > andOutputBin.size()) {
				andExpectedBin = andExpectedBin.substr(andExpectedBin.size()-andOutputBin.size(), andOutputBin.size());
			} else {
				andOutputBin = andOutputBin.substr(andOutputBin.size()-andExpectedBin.size(), andExpectedBin.size());
			}

			// Get OR binary strings
			std::string orOutputBin = orOutput.bin();
			std::string orExpectedBin = orExpected.bin();

			// Make the expected and output string lengths equal
			if (orExpectedBin.size() > orOutputBin.size()) {
				orExpectedBin = orExpectedBin.substr(orExpectedBin.size()-orOutputBin.size(), orOutputBin.size());
			} else {
				orOutputBin = orOutputBin.substr(orOutputBin.size()-orExpectedBin.size(), orExpectedBin.size());
			}
			
			// Validate non-assignment bitwise operations
			REQUIRE(notExpectedBin == notOutputBin);
			REQUIRE(andExpectedBin == andOutputBin);
			REQUIRE(orExpectedBin == orOutputBin);

			// Validate assignment bitwise operations
			ar1 &= ar2;
			std::string ar1Bin = ar1.bin();
			if (andExpectedBin.size() < ar1Bin.size()) {
				ar1Bin = ar1Bin.substr(ar1Bin.size()-andExpectedBin.size(), andExpectedBin.size());
			}
			REQUIRE(ar1Bin == andExpectedBin);
			ar1 = arithmetic(std::to_string(operand1));

			ar1 |= ar2;
			ar1Bin = ar1.bin();
			if (andExpectedBin.size() < ar1Bin.size()) {
				ar1Bin = ar1Bin.substr(ar1Bin.size()-orExpectedBin.size(), orExpectedBin.size());
			}
			REQUIRE(ar1Bin == orExpectedBin);

			++operand2;
		}

		operand2 = 0;
		++operand1;
	}

	printf("PASSED BITWISE CASES \n");
}

TEST_CASE("Bin") {
	unsigned int operand1 = 0;

	while(operand1 <= 1000) {
		arithmetic ar1 = (std::to_string(operand1));
		
		std::string expected = std::bitset<16>(operand1).to_string();
		if (ar1.getSize() < 2) {
			expected = expected.substr(8,8);
		}

		REQUIRE(ar1.bin() == expected);

		++operand1;
	}

	printf("PASSED BIN CASES \n");
}

TEST_CASE("Set") {
	int operand1 = -1000;
	arithmetic ar1(std::to_string(operand1));

	while(operand1 <= 1000) {
		ar1.set(std::to_string(operand1+1));
		arithmetic expected(std::to_string(operand1+1));

		REQUIRE(ar1.str() == expected.str());
		REQUIRE(ar1.sign() == expected.sign());
		++operand1;
	}

	printf("PASSED SET CASES \n");
}


