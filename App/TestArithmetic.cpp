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
	//while(i < 1000000) {
	while(i < 1000) {
		std::string s = std::to_string(i);
		arithmetic ar(s);

		std::stringstream output, ref;

		size_t size = ar.getSize();

		int absolute = abs(i);

		const char* beg = reinterpret_cast<const char*>(&absolute);
		for (size_t ind = size-1; ind > 0; --ind) {
			ref<<std::bitset<8>(beg[ind]);
		}
		ref<<std::bitset<8>(beg[0]);
		
		output<<ar;

		REQUIRE(!strcmp(output.str().c_str(), ref.str().c_str()));
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
			arithmetic result = (std::to_string(expected));

			arithmetic ar3 = ar1+ar2;
			ar1+=ar2;

			std::stringstream output, outputCompound, ref;

			ref<<result;

			output<<ar3;
			outputCompound<<ar1;

			if (operand1 % 200 == 0 && operand2 == 0) {
				printf("operand1 is %i | operand2 is %i\n", operand1, operand2);
			}

			REQUIRE(output.str() == ref.str());
			REQUIRE(outputCompound.str() == ref.str());
			REQUIRE(ar3.sign() == result.sign());
			REQUIRE(ar1.sign() == result.sign());
			
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

TEST_CASE("Subtraction") {
	int operand1 = -1000;
	int operand2 = -1000;
	int expected = 0;

	while(operand1 <= 1000) {
		while(operand2 <= 1000) {
			expected = operand1 - operand2;

			arithmetic ar1 = (std::to_string(operand1));
			arithmetic ar2 = (std::to_string(operand2));
			arithmetic result = (std::to_string(expected));

			arithmetic ar3 = ar1-ar2;
			ar1-=ar2;

			std::stringstream output, outputCompound, ref;

			ref<<result;
			outputCompound<<ar1;
			output<<ar3;

			if (operand1 % 200 == 0 && operand2 == 0) {
				printf("operand1 is %i | operand2 is %i\n", operand1, operand2);
			}

			REQUIRE(output.str() == ref.str());
			REQUIRE(outputCompound.str() == ref.str());
			REQUIRE(ar3.sign() == result.sign());
			REQUIRE(ar1.sign() == result.sign());
			++operand2;
		}

		operand2 = 0;
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
			expected = operand1*operand2;

			arithmetic ar1 = (std::to_string(operand1));
			arithmetic ar2 = (std::to_string(operand2));
			arithmetic result = (std::to_string(expected));

			arithmetic ar3 = ar1*ar2;
			ar1*=ar2;

			std::stringstream output, outputCompound, ref;

			ref<<result;
			outputCompound<<ar1;
			output<<ar3;

			if (operand1 % 200 == 0 && operand2 == 0) {
				printf("operand1 is %i | operand2 is %i\n", operand1, operand2);
			}

			REQUIRE(output.str() == ref.str());
			REQUIRE(outputCompound.str() == ref.str());
			REQUIRE(ar3.sign() == result.sign());
			REQUIRE(ar1.sign() == result.sign());
			++operand2;
		}

		operand2 = 0;
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
			expected = operand1<<operand2;

			arithmetic ar1 = (std::to_string(operand1));
			arithmetic result = (std::to_string(expected));

			arithmetic ar2 = ar1<<operand2;
			ar1<<=operand2;

			std::stringstream output, outputCompound, ref;

			ref<<result;
			outputCompound<<ar1;
			output<<ar2;

			if (operand1 % 200 == 0 && operand2 == 0) {
				printf("operand1 is %i | operand2 is %i\n", operand1, operand2);
			}

			REQUIRE(output.str() == ref.str());
			REQUIRE(outputCompound.str() == ref.str());
			REQUIRE(ar2.sign() == result.sign());
			REQUIRE(ar1.sign() == result.sign());
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
			expected = operand1>>operand2;

			arithmetic ar1 = (std::to_string(operand1));
			arithmetic result = (std::to_string(expected));

			arithmetic ar2 = ar1>>operand2;
			ar1>>=operand2;

			std::stringstream output, outputCompound, ref;

			ref<<result;
			outputCompound<<ar1;
			output<<ar2;

			if (operand1 % 200 == 0 && operand2 == 0) {
				printf("operand1 is %i | operand2 is %i\n", operand1, operand2);
			}

			REQUIRE(output.str() == ref.str());
			REQUIRE(outputCompound.str() == ref.str());
			REQUIRE(ar2.sign() == result.sign());
			REQUIRE(ar1.sign() == result.sign());
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
			arithmetic result = (std::to_string(expected));

			arithmetic ar3 = ar1/ar2;
			ar1/=ar2;

			std::stringstream output, outputCompound, ref;

			ref<<result;
			outputCompound<<ar1;
			output<<ar3;

			if (operand1 % 200 == 0 && operand2 == 0) {
				printf("operand1 is %i | operand2 is %i\n", operand1, operand2);
			}

			REQUIRE(output.str() == ref.str());
			REQUIRE(outputCompound.str() == ref.str());
			REQUIRE(ar3.sign() == result.sign());
			REQUIRE(ar1.sign() == result.sign());
			++operand2;
		}

		operand2 = 0;
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
			arithmetic result = (std::to_string(expected));

			arithmetic ar3 = ar1%ar2;

			std::stringstream output, outputCompound, ref;

			ref<<result;
			output<<ar3;

			if (operand1 % 200 == 0 && operand2 == 0) {
				printf("operand1 is %i | operand2 is %i\n", operand1, operand2);
			}

			REQUIRE(output.str() == ref.str());
			REQUIRE(ar3.sign() == result.sign());
			++operand2;
		}

		operand2 = 0;
		++operand1;
	}

	printf("PASSED MODULUS CASES \n");
}

TEST_CASE("Pow") {
	long long int operand1 = -10;
	long long int operand2 = -10;
	long long int expected = 0;

	while(operand1 <= 9) {
		while(operand2 <= 9) {
			
			expected = pow(operand1, operand2);

			arithmetic ar1 = (std::to_string(operand1));
			arithmetic ar2 = (std::to_string(operand2));
			arithmetic ar3 = ar1.pow(ar2);

			std::stringstream output, outputCompound, ref;

			int absolute = abs(expected);

			size_t size = ar3.getSize();
			const char* beg = reinterpret_cast<const char*>(&absolute);
			for (size_t ind = size-1; ind > 0; --ind) {
				ref<<std::bitset<8>(beg[ind]);
			}
			ref<<std::bitset<8>(beg[0]);

			output<<ar3;

			REQUIRE(!strcmp(output.str().c_str(), ref.str().c_str()));
			if(expected >= 0) {
				REQUIRE(ar3.sign() == true);
			} else if(expected < 0) {
				REQUIRE(ar3.sign() == false);
			}

			++operand2;
		}

		operand2 = 1;
		++operand1;
	}

	printf("PASSED POW CASES \n");
}


