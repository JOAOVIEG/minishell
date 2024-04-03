#!/bin/bash

# Define the test function
run_test() {
	echo "Running test: $1"
	valgrind --suppressions=../readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt .././minishell -c "$1"
	if grep -q "definitely lost: [1-9]" valgrind-out.txt; then
		echo "$1 caused a memory leak. See below for details:" >>leak_tests.txt
		grep -A4 "definitely lost: [1-9]" valgrind-out.txt >>leak_tests.txt
	fi
	echo
}

clean_up() {
	find . -type f ! -name "*.sh" -exec rm -f {} \;
}

run_test "export TMPENVVAR"
run_test "export TMPENVVAR=echo"
run_test "export TMPENVVAR=\"-n\""
run_test "export TMPENVVAR=echo hi"
run_test "export TMPENVVAR=echo hi hi"
run_test "export TMPENVVAR=echo hi hi hi"
run_test "export TMPENVVAR=echo hi hi hi hi"
run_test "export TMPENVVAR=echo hi hi hi hi hi"
run_test "export TMPENVVAR=echo hi hi hi hi hi hi"
run_test "export 1A=value"
run_test "export 1=value"
run_test "export A1=value"
run_test "export /A=value"
run_test "export 'A=value'"
run_test "export ' A=value'"
run_test "export 'A =value'"
run_test "export TEST=tes"

echo "Tests that caused memory leaks:"
cat leak_tests.txt

clean_up
