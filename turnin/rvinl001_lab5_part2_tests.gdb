# Test file for "Lab5_atmegaMicroC"


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

t "PINA: 0x01 => State: Release, 0x08"
set States = Start
setPINA 0x01
continue 5
expect States Hold1
setPINA 0x00
continue 5
expectPORTC 0x08
expect States Release
checkResult

test "PINA: 0x02 => State: Release, 0x06"
set States = Start
setPINA 0x02
continue 5
expect States Hold2
setPINA 0x00
continue 5
expectPORTC 0x06
expect States Release
checkResult

test "PINA: 0x01 twice => State: Release, 0x09"
set States = Start
setPINA 0x01
continue 5
expect States Hold1
setPINA 0x00
continue 5
setPINA 0x01
continue 5
expect States Hold1
setPINA 0x00
continue 5
expectPORTC 0x09
expect States Release
checkResult

test "PINA: 0x02 three times => State: Release, 0x04"
set States = Start
setPINA 0x02
continue 5
expect States Hold2
setPINA 0x00
continue 5
setPINA 0x02
continue 5
expect States Hold2
setPINA 0x00
continue 5
setPINA 0x02
continue 5
expect States Hold2
setPINA 0x00
continue 5
expectPORTC 0x04
expect States Release
checkResult

test "PINA: 0x02 two times then 0x03 => State: init, 0x07"
set States = Start
setPINA 0x02
continue 5
expect States Hold2
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
setPINA 0x03
continue 5
expectPORTC 0x00
expect States Both
checkResult

test "PINA: 0x01 then 0x02 => State: Release, 0x07"
set States = Start
setPINA 0x01
continue 5
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
expectPORTC 0x07
expect States Release
checkResult


# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
