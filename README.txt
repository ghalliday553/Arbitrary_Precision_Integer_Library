--------------------------------------
Arbitrary-Precision Integer Calculator
--------------------------------------

USAGE:

The calculator uses the reverse polish notation and accepts a string of arguments through the standard input consisting of both operators and operands, separated by spaces. Intermediate operation results will be used as an operand for the following operation, whereas the final operation result will be written to the standard output.

An example is as follows:

<operand_1> <operand_2> <operator_1> <operand_3> <operator_2>

The calculator will compute the first intermediate result of <operand_1> and <operand_2> through the application of <operator_1> and use the result within the next calculation involving <operand_3> and <operator_2>.

INPUT:

All operands must be a string of decimal numbers, optionally preceded by a negative sign. Usage of non-decimal numbers will cause the program to exit with an "INVALID OPERATION" message.

A list of supported operators is as follows:
{"+", "++", "-", "--", "*", "/", "%", "^", "<<", ">>", "&", "|", "&&", "||", ">", ">=", "<", "<=", "==", "!=", "~", "!"'}

Usage of any unsupported operators or using the incorrect number of operands will cause the program to exit with an "INVALID OPERATION" message.

Notes:
- All bitwise operations will equivalent to that of a twos-compliment system
- All logical operators will produce either a value of "1" or "0"
