#include <Arithmetic.hpp>
#include <string>
#include <iostream>
#include <stack>
#include <set>

#define INVALID_OPERATION "INVALID OPERATION\n"
#define INSUFFICIENT_MEMORY "INSUFFICIENT MEMORY\n"
#define UNSPECIFIED_ERROR "UNSPECIFIED ERROR\n"

/*
 * Tests if str is a decimal string.
 *
 * INPUTS:
 *	str - Arbitrary size string.
 *	
 * OUTPUTS:	
 * 	Returns true if the string str is a decimal number. Returns false otherwise.
 *
 * PRECONDITIONS:
 *	- none.
 */
bool isNumber(std::string str) {
	if (str.find_first_not_of("0123456789") == std::string::npos) {
		return true;
	}
	if (str[0] == '-') {
		str.erase(0,1);
		if (str.size() > 0 && str.find_first_not_of("0123456789") == std::string::npos) {
			return true;
		}
	}
	return false;
}

/*
 * Performs operations requiring a single operand.
 *
 * INPUTS:
 *	operand1
 *	op - Operation to perform on operand
 *	
 * OUTPUTS:	
 * 	Returns the decimal string result of the operation
 *
 * PRECONDITIONS:
 *	- operand1 must be a decimal string.
 */
std::string performOp1(std::string operand1, std::string op) {
	try {
		arithmetic ar1(operand1);
		arithmetic res;

		char cOp[3];
		strcpy(cOp, op.c_str());

		if(!strcmp(cOp,"~")) {
			res = ~ar1;
		} else if(!strcmp(cOp,"++")) {
			res = ++ar1;
		} else if(!strcmp(cOp,"--")) {
			res = --ar1;
		} else if(!strcmp(cOp,"!")) {
			if (!ar1) {
				return std::string("1");
			} else {
				return std::string("0");
			}
		}

		return res.str();
	} catch (std::bad_alloc e) {
		std::cout<<INSUFFICIENT_MEMORY;
		exit(0); 
	} catch (...) {
		std::cout<<UNSPECIFIED_ERROR;
		exit(0);
	}
}

/*
 * Performs operations requiring two operands.
 *
 * INPUTS:
 *	operand1
 *	operand2
 *	op - Operation to perform on operand
 *	
 * OUTPUTS:	
 * 	Returns the decimal string result of the operation
 *
 * PRECONDITIONS:
 *	- operand1 and operand2 must be decimal strings.
 */
std::string performOp2(std::string operand1, std::string operand2, std::string op) {
	try {
		arithmetic ar1(operand1);
		arithmetic ar2(operand2);
		arithmetic res;

		char cOp[3];
		strcpy(cOp, op.c_str());
		
		if(!strcmp(cOp,"+")) {
			res = ar1 + ar2;
		} else if(!strcmp(cOp,"-")) {
			res = ar1 - ar2;
		} else if(!strcmp(cOp,"*")) {
			res = ar1 * ar2;
		} else if(!strcmp(cOp,"/")) {
			res = ar1 / ar2;
		} else if(!strcmp(cOp,"%")) {
			res = ar1 % ar2;
		} else if(!strcmp(cOp,"^")) {
			res = ar1.pow(ar2);
		} else if(!strcmp(cOp,"<<")) {
			res = ar1 << ar2;
		} else if(!strcmp(cOp,">>")) {
			res = ar1 >> ar2;
		} else if(!strcmp(cOp,"&")) {
			res = ar1 & ar2;
		} else if(!strcmp(cOp,"|")) {
			res = ar1 | ar2;
		} else if (!strcmp(cOp,"&&")) {
			if (ar1 && ar2) {
				return std::string("1");
			} else {
				return std::string("0");
			}
		} else if (!strcmp(cOp,"||")) {
			if (ar1 || ar2) {
				return std::string("1");
			} else {
				return std::string("0");
			}
		} else if (!strcmp(cOp,">")) {
			if (ar1 > ar2) {
				return std::string("1");
			} else {
				return std::string("0");
			}
		} else if(!strcmp(cOp,">=")) {
			if (ar1 >= ar2) {
				return std::string("1");
			} else {
				return std::string("0");
			}
		} else if(!strcmp(cOp,"<")) {
			if (ar1 < ar2) {
				return std::string("1");
			} else {
				return std::string("0");
			}
		} else if(!strcmp(cOp,"<=")) {
			if (ar1 <= ar2) {
				return std::string("1");
			} else {
				return std::string("0");
			}
		} else if(!strcmp(cOp,"==")) {
			if (ar1 == ar2) {
				return std::string("1");
			} else {
				return std::string("0");
			}
		} else if(!strcmp(cOp,"!=")) {
			if (ar1 != ar2) {
				return std::string("1");
			} else {
				return std::string("0");
			}
		}

		return res.str();
	} catch (std::bad_alloc e) {
		std::cout<<INSUFFICIENT_MEMORY;
		exit(0);
	} catch (...) {
		std::cout<<UNSPECIFIED_ERROR;
		exit(0);
	}
}

int main(void) {
	std::string str;
	std::stack<std::string> opStack;
	std::set<std::string> opSet2 = {"+", "-", "*", "/", "%", "^",
		"<<", ">>", "&", "|", "&&", "||", ">", ">=", "<", "<=", "==", "!="};
	std::set<std::string> opSet1 = {"++", "--", "~", "!"};

	// Loop forever
	while(1) {
		std::getline(std::cin, str);

		// Parse line for operands and operators
		size_t pos = str.find(" ");
		if (pos == std::string::npos){
			pos = str.size();
		}
		while (str.size() > 0) {
	        std::string tempStr = str.substr(0, pos);

	        // Check if parsed string is a decimal number
	        if (isNumber(tempStr)) {
	        	if (opStack.size() == 2) {
	        		std::cout<<INVALID_OPERATION;
	        		return 0;
	        	}
	        	opStack.push(tempStr);
	        // Check if parsed string is an operator
	        } else if (opSet2.find(tempStr) != opSet2.end() || opSet1.find(tempStr) != opSet1.end()) {
	        	// Validate that the correct number of decimal numbers are on the stack.
	        	if (opSet1.find(tempStr) != opSet1.end()) {
	        		if (opStack.size() != 1) {
	        			std::cout<<INVALID_OPERATION;
	        			return 0;
	        		}
	        	} else {
	        		if (opStack.size() != 2) {
	        			std::cout<<INVALID_OPERATION;
	        			return 0;
	        		}
	        	}

	        	// Perform operation with the appropriate number of operands
	        	std::string res;
	        	if (opStack.size() == 2) {
	        		std::string operand2 = opStack.top();
		        	opStack.pop();
		        	std::string operand1 = opStack.top();
		        	opStack.pop();
		        	res = performOp2(operand1, operand2, tempStr);
	        	} else if (opStack.size() == 1) {
	        		std::string operand1 = opStack.top();
		        	opStack.pop();
		        	res = performOp1(operand1, tempStr);
	        	} else {
	        		// Shouldnt happen
	        		std::cout<<INVALID_OPERATION;
	        		return 0;
	        	}

	        	// Push result onto stack
	        	opStack.push(res);
	        // Parsed string is neither a decimal string or operator.
	        } else {
	        	std::cout<<INVALID_OPERATION;
	        	return 0;
	        }

	        // Parse next operand/operator
	        str.erase(0, pos + 1);
	        pos = str.find(" ");
	        if (pos == std::string::npos){
				pos = str.size();
			}
    	}

    	// Result is that last value on the stack
    	std::cout<<opStack.top()<<"\n";
    	opStack.pop();
    	str.clear();
	}
}