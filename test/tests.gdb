# Test file for "cs120b_Lab6"

echo ======================================================\n
echo Running all tests..."\n\n


define timer
	if $argc != 0
		set $i = $arg0
	else
		set $i = 1
	end
	while $i > 0
		set TimerFlag = 1
		continue
		set $i = $i - 1
	end
end

# Tests
test "start"
timer
expect PORTB 0x01
checkResult

test "next"
timer
expect PORTB 0x02
checkResult

test "timer"
timer 2
expect PORTB 0x01
checkResult



# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n