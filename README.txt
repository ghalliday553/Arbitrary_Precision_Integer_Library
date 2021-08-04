--------------------------------------
Arbitrary-Precision Integer Calculator
--------------------------------------

To demonstrate the use of the developed arbitrary-precision integer library, a reverse polish calculator has been provided.

Some library functions are not applicable to a calculator, and therefore have not been included within the calculator's list of supported operations. These commands includes:
- Pre increment/decrement
- getSize()
- sign()
- abs()
- bin()
- set()

Validation of these commands can instead be accomplished through the /app/TestArithmetic.cpp file, which makes use of the Catch2 library. To compile the validation program, uncomment the appropriate lines within CMakeLists.txt.

Note that the full test suite requires a substantial amount of time to complete. Therefore, it is recommended to test individual Catch2 test cases.



USAGE:

The calculator uses the reverse polish notation and accepts a string of arguments through the standard input
consisting of both operators and operands, separated by spaces. Intermediate operation results will be used as an
operand for the following operation, and the final operation result will be written to the standard output.

An example is as follows:

<operand_1> <operand_2> <operator_1> <operand_3> <operator_2>

The calculator will compute the first intermediate result of <operand_1> and <operand_2> through the application of
<operator_1> and use the result within the next calculation involving <operand_3> and <operator_2>.




INPUT:

All operands must be a string of decimal numbers, optionally preceded by a negative sign. Usage of non-decimal numbers will cause the program to exit with an "INVALID OPERATION" message.

A list of supported operators is as follows:
{"+", "++", "-", "--", "*", "/", "%", "^", "<<", ">>", "&", "|", "&&", "||", ">", ">=", "<", "<=", "==", "!=", "~", "!"'}

Usage of any unsupported operators or using the incorrect number of operands will cause the program to exit with an
"INVALID OPERATION" message.

Notes:
- All shift operations will be equivalent to that of a two's-compliment system.
- All logical operators will produce either a value of "1" or "0".
- The sign of all bitwise operations will be determined from the first operand.
- Division by 0 is defined as 0.
- Modulus by 0 is defined as the dividend.




DEMO:

The demo python program contains a series of tests used to display and validate example calculator inputs.


