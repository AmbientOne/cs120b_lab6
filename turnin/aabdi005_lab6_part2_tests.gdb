echo ======================================================\n
echo Running all tests..."\n\n



test "PORTB = 0x01"
continue 1
expectPORTB 0x01
checkResult

test "PORTB = 0x02"
continue 1
expectPORTB 0x02
checkResult


test "pause"
setPINA 0x01
continue 1
setPINA 0x00
continue 1
expectPORTB 0x04
checkResult

test "unpause"
setPINA 0x01
continue 1
expectPORTB 0x01
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n