#!/bin/bash

# Define the test function
run_test() {
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

# Run the tests
run_test "test"
run_test "|test"
run_test "||test"
run_test "|< | test"
run_test "|<< | test"
run_test "|> | test"
run_test "|>> | test"
run_test "|| < test"
run_test "|| << test"
run_test "|| > test"
run_test "|| >> test"
run_test "|| test"
run_test "test | >"
run_test "test | >>"
run_test "test | <"
run_test "echo hiecho hi"
run_test "echo hi|echo hi"
run_test "echo hi |echo hi"
run_test "echo hi| echo hi"
run_test "echo hi | | echo hi"
run_test "echo hi ||| echo hi"
run_test "echo >"
run_test "echo >>"
run_test "echo <"
run_test "echo >>>"
run_test "echo <<<"
run_test "echo hi >< file"

# Print the valgrind output
echo "Tests that caused memory leaks:"
cat leak_tests.txt

clean_up
