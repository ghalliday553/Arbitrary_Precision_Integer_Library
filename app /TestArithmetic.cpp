#include <Arithmetic.hpp>
#include <limits.h>
#include <cmath>
#include <stdio.h>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("INITIAL TESTS") {
	/*
	printf("operand1 is %i | operand2 is %i\n", operand1, operand2);
	printf("expected is %s\n", ref.str().c_str());
	printf("output is %s\n", output.str().c_str());
	printf("outputCompound is %s\n", outputCompound.str().c_str());
	
	REQUIRE(!strcmp(output.str().c_str(), ref.str().c_str()));
	*/
}

TEST_CASE("StringToBinary") {
	int i = -1000;
	while(i < 1000) {
		int absolute = abs(i);
		arithmetic ar(std::to_string(i));
		std::string ref;

		const char* beg = reinterpret_cast<const char*>(&absolute);
		for (size_t ind = ar.getSize()-1; ind > 0; --ind) {
			ref = ref + std::bitset<8>(beg[ind]).to_string();
		}
		ref = ref + std::bitset<8>(beg[0]).to_string();

		REQUIRE(ar.bin() == ref);
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

TEST_CASE("IncDec") {
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
			
			arithmetic andRef(std::to_string(operand1 & operand2));
			arithmetic orRef(std::to_string(operand1 | operand2));
			arithmetic notRef(std::to_string(~operand1));

			arithmetic ar1 = std::to_string(operand1);
			arithmetic ar2 = std::to_string(operand2);

			arithmetic notOutput = ~ar1;
			arithmetic orOutput = ar1 | ar2;
			arithmetic andOutput = ar1 & ar2;

			if (operand1 % 200 == 0 && operand2 == 0) {
				printf("operand1 is %i | operand2 is %i\n", operand1, operand2);
			}

			std::string notOutputBin = notOutput.bin();
			std::string notRefBin = notRef.bin();
			notRefBin = notRefBin.substr(notRefBin.size()-notOutputBin.size(), notOutputBin.size());

			std::string andOutputBin = andOutput.bin();
			std::string andRefBin = andRef.bin();
			if (andRefBin.size() > andOutputBin.size()) {
				andRefBin = andRefBin.substr(andRefBin.size()-andOutputBin.size(), andOutputBin.size());
			} else {
				andOutputBin = andOutputBin.substr(andOutputBin.size()-andRefBin.size(), andRefBin.size());
			}

			std::string orOutputBin = orOutput.bin();
			std::string orRefBin = orRef.bin();
			if (orRefBin.size() > orOutputBin.size()) {
				orRefBin = orRefBin.substr(orRefBin.size()-orOutputBin.size(), orOutputBin.size());
			} else {
				orOutputBin = orOutputBin.substr(orOutputBin.size()-orRefBin.size(), orRefBin.size());
			}
			
			REQUIRE(notRefBin == notOutputBin);
			REQUIRE(andRefBin == andOutputBin);
			REQUIRE(orRefBin == orOutputBin);

			ar1 &= ar2;
			std::string ar1Bin = ar1.bin();
			if (andRefBin.size() < ar1Bin.size()) {
				ar1Bin = ar1Bin.substr(ar1Bin.size()-andRefBin.size(), andRefBin.size());
			}
			REQUIRE(ar1Bin == andRefBin);
			ar1 = arithmetic(std::to_string(operand1));

			ar1 |= ar2;
			ar1Bin = ar1.bin();
			if (andRefBin.size() < ar1Bin.size()) {
				ar1Bin = ar1Bin.substr(ar1Bin.size()-orRefBin.size(), orRefBin.size());
			}
			REQUIRE(ar1Bin == orRefBin);

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
		
		std::string ref = std::bitset<16>(operand1).to_string();
		if (ar1.getSize() < 2) {
			ref = ref.substr(8,8);
		}

		REQUIRE(ar1.bin() == ref);

		++operand1;
	}

	printf("PASSED BIN CASES \n");
}

TEST_CASE("Set") {
	int operand1 = -1000;
	arithmetic ar1(std::to_string(operand1));

	while(operand1 <= 1000) {
		ar1.set(std::to_string(operand1+1));
		arithmetic ref(std::to_string(operand1+1));

		REQUIRE(ar1.str() == ref.str());
		REQUIRE(ar1.sign() == ref.sign());
		++operand1;
	}

	printf("PASSED SET CASES \n");
}


