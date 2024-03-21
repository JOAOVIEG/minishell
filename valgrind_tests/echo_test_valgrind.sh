#!/bin/bash

# Define the test function
run_test() {
    echo "Running test: $1"
    valgrind --suppressions=../readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt .././minishell -c "$1"
    echo
}

# Run the tests
run_test "echo"
run_test "echo ñ"
run_test "echo hi"
run_test "/bin/echo hi"
run_test "echo $PATH"
run_test "echo $NONEXIST"
run_test "echoecho"
run_test "echo -n"
run_test "echo -n hi"
run_test "echo --n hi"
run_test "echo -nn hi"
run_test "echo -n -n hi"
run_test "echo hi -n"
run_test 'echo "-n -n -n" -n hi'
run_test "check if launch execve"
run_test "check if builtin is not correct"
run_test "EXECVE THE ECHO?"

# Print the valgrind output
cat valgrind-out.txt
rm valgrind-out.txt
