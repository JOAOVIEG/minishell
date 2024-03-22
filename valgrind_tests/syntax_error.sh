#!/bin/bash

# Define the test function
run_test() {
    echo "Running test: $1"
    valgrind --suppressions=../readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt .././minishell -c "$1"
    echo
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
cat valgrind-out.txt
rm valgrind-out.txt