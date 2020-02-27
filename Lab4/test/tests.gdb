# Test file for "Lab3"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Example test:
#test "PINA: 0x00, PINB: 0x00 => PORTC: 0"
# Set inputs
#setPINA 0x00
#setPINB 0x00
# Continue for several ticks
#continue 2
# Set expect values
#expectPORTC 0
# Check pass/fail
#checkResult

#Each test we write should:
#Initialize the context to some known starting state
#(gdb) set state = waitA0
#Apply stimulus (input)
#(gdb) setPINA 0x01
#...
#Observe output
#(gdb) expectPORTB 0xF0
#(gdb) expect state pressA1

# Add tests below
#
#
#
# # Test sequence from waitA0: A0, !A0, A1 => PORTB: 1
test "PINA: 0x01, 0x00, 0x02 => PORTB: 1, state: pressA1"
set currentState = wait
set counter = 0x07
set prevButton = 0x00
print currentState

# increment 2x
test "Increment\n"
setPINA 0x01
continue 5
expect PORTC 0x08
checkResult
print currentState
print counter
#decrease x2
test "decrement\n"
setPINA 0x02
continue 5
expect PORTC 0x07
checkResult
print currentState
print counter
#reset
test "Reset\n"
print counter
setPINA 0x3
continue 5
setPINA 0x00
continue 5
expect PORTC 0x00
checkResult
print currentState
print counter






# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
