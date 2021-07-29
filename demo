import subprocess
import os

initialDir = os.path.dirname(os.path.realpath(__file__))
cmd = os.path.join(initialDir, "ap_calculator");

# Due to limitations for communicate(), a new subprocess must be created for each input
def runComp(comp):
	proc = subprocess.Popen([cmd], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	ret = proc.communicate(input=bytes(comp + "\n", 'utf-8'))
	print(comp + " -> " + str(ret[0].decode('utf-8')))
	proc.kill()

print("---------------------------")
print("Arbitrary-Precision Calculator Demo")
print("---------------------------")
print("\n")

print("----------")
print("Addition")
print("----------")

print("\nsanity:\n")
runComp("1 1 +")
runComp("1 -1 +")
runComp("-1 1 +")
runComp("-1 -1 +")

print("\nmulti:\n")
runComp("1 1 + 1 +")
runComp("1 1 + -1 +")

print("\nunary:\n")
runComp("1 ++")
runComp("1 1 + ++")

print("\nlarge:\n")
runComp("18446744073709551615 18446744073709551615 +")
runComp("-18446744073709551615 -18446744073709551615 +")

print("----------")
print("Subtraction")
print("----------")

print("\nsanity:\n")
runComp("1 1 -")
runComp("1 -1 -")
runComp("-1 1 -")
runComp("-1 -1 -")

print("\nmulti:\n")
runComp("1 1 - 1 -")
runComp("1 1 - -1 -")

print("\nunary:\n")
runComp("1 --")
runComp("1 1 - --")

print("\nlarge:\n")
runComp("18446744073709551615 18446744073709551615 -")
runComp("-18446744073709551615 -18446744073709551615 -")
runComp("18446744073709551615 -18446744073709551615 -")
runComp("-18446744073709551615 18446744073709551615 -")

print("----------")
print("Multiplication")
print("----------")

print("\nsanity:\n")
runComp("1 2 *")
runComp("1 -2 *")
runComp("-1 2 *")
runComp("-1 -2 *")

print("\nmulti:\n")
runComp("1 2 * 1 *")
runComp("1 2 * -1 *")

print("\nlarge:\n")
runComp("18446744073709551615 18446744073709551615 *")
runComp("-18446744073709551615 -18446744073709551615 *")
runComp("18446744073709551615 -18446744073709551615 *")
runComp("-18446744073709551615 18446744073709551615 *")

print("----------")
print("Division")
print("----------")

print("\nsanity:\n")
runComp("10 2 /")
runComp("10 -2 /")
runComp("-10 2 /")
runComp("-10 -2 /")
runComp("10 3 /")
runComp("10 -3 /")
runComp("-10 3 /")
runComp("-10 -3 /")

print("\ndivision by 0:\n")
runComp("10 0 /")

print("\nmulti:\n")
runComp("10 2 / 2 /")
runComp("10 2 / -2 /")

print("\nlarge:\n")
runComp("340282366920938463426481119284349108225 5 /")
runComp("-340282366920938463426481119284349108225 -5 /")
runComp("340282366920938463426481119284349108225 -5 /")
runComp("-340282366920938463426481119284349108225 5 /")

print("----------")
print("Modulus")
print("----------")

runComp("10 2 %")
runComp("10 -2 %")
runComp("-10 2 %")
runComp("-10 -2 %")
runComp("10 3 %")
runComp("10 -3 %")
runComp("-10 3 %")
runComp("-10 -3 %")

print("\ndivision by 0:\n")
runComp("10 0 %")

print("\nmulti:\n")
runComp("10 3 % 2 %")
runComp("10 3 % -2 %")

print("\nlarge:\n")
runComp("340282366920938463426481119284349108225 6 %")
runComp("-340282366920938463426481119284349108225 -6 %")
runComp("340282366920938463426481119284349108225 -6 %")
runComp("-340282366920938463426481119284349108225 6 %")

print("----------")
print("Exponentiation")
print("----------")

print("\nsanity:\n")
runComp("2 3 ^")
runComp("-2 3 ^")
runComp("2 -3 ^")
runComp("2 0 ^")

print("\nmulti:\n")
runComp("2 3 ^ 2 ^")

print("\nlarge:\n")
runComp("18446744073709551615 3 ^")
runComp("-18446744073709551615 3 ^")

print("----------")
print("Comparisions")
print("----------")

print("\nless-than:\n")
runComp("2 3 <")
runComp("-2 3 <")
runComp("2 -3 <")
runComp("-2 -3 <")

print("\ngreater-than:\n")
runComp("2 3 >")
runComp("-2 3 >")
runComp("2 -3 >")
runComp("-2 -3 >")

print("\nequal-to:\n")
runComp("2 2 ==")
runComp("-2 2 ==")
runComp("2 2 <=")
runComp("2 2 >=")
runComp("2 2 !=")
runComp("-2 2 !=")

print("----------")
print("Shift Operations")
print("----------")

print("\nshift-right:\n")
runComp("16 2 >>")
runComp("16 5 >>")
runComp("-16 2 >>")
runComp("-17 2 >>")

print("\nshift-left:\n")
runComp("2 4 <<")
runComp("2 128 <<")
runComp("-2 2 <<")


print("----------")
print("Logical Operations")
print("----------")

print("\nAND:\n")
runComp("1 1 &&")
runComp("1 0 &&")

print("\nOR:\n")
runComp("1 1 ||")
runComp("1 0 ||")
runComp("0 0 ||")

print("\nNOT:\n")
runComp("1 !")
runComp("0 !")

print("----------")
print("Bitwise Operations")
print("----------")

print("\nAND:\n")
runComp("2 2 &")
runComp("-2 2 &")
runComp("2 -2 &")
runComp("2 1 &")
runComp("-2 1 &")
runComp("2 -1 &")

print("\nOR:\n")
runComp("2 1 |")
runComp("-2 1 |")
runComp("2 -1 |")

print("\nNOT:\n")
runComp("1 ~")
runComp("-1 ~")
runComp("255 ~")
runComp("-255 ~")

print("----------")
print("Error Handling")
print("----------")

print("\nincorrect number of operands:\n")
runComp("1 +")
runComp("1 1 1+")
runComp("1 1 + 1 1 +")
runComp("1 1 ++")
runComp("++")

print("\ninvalid operand:\n")
runComp("a 1 +")
runComp("1a 1 +")
runComp("-a 1 +")
runComp("-1a 1 +")
runComp("1 1 + a +")
runComp("1 1 + 1a +")
runComp("1 1 + -a +")
runComp("1 1 + -1a +")

print("\ninvalid operator:\n")
runComp("1 1 $")
runComp("1 1 +++")
runComp("1 1 + 1 $")
runComp("1 1 + 1 +++")

print("\nsanitization\n")
runComp("0001 1 +")


print("\n")
print("---------------------------")
print("Arbitrary-Precision Calculator Demo Completed")
print("---------------------------")

