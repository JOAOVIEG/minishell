#!/bin/bash

run_test() {
    echo "Running test: $1"
    valgrind --suppressions=../readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt .././minishell -c "$1"
    if grep -q "definitely lost: [1-9]" valgrind-out.txt; then
        echo "$1 caused a definitely lost memory leak. See below for details:" >>leak_tests.txt
        grep -A4 "definitely lost: [1-9]" valgrind-out.txt >>leak_tests.txt
    fi
    if grep -q "indirectly lost: [1-9]" valgrind-out.txt; then
        echo "$1 caused an indirectly lost memory leak. See below for details:" >>leak_tests.txt
        grep -A4 "indirectly lost: [1-9]" valgrind-out.txt >>leak_tests.txt
    fi
    if grep -q "possibly lost: [1-9]" valgrind-out.txt; then
        echo "$1 caused a possibly lost memory leak. See below for details:" >>leak_tests.txt
        grep -A4 "possibly lost: [1-9]" valgrind-out.txt >>leak_tests.txt
    fi
    echo
}

clean_up() {
	find . -type f ! -name "*.sh" -exec rm -f {} \;
}

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
run_test "echo -n"
run_test "echo -n hi"
run_test "echo -n -n hi"
run_test "echo hi -n"
run_test 'echo "-n -n -n" -n hi'
run_test "echo -n $PATH"
run_test "echo -n $NONEXIST"
run_test "echo -n -n -n -n -n -n -n -n -n -n hi"
run_test "echo -n -n -n -n -n -n -n -n -n -n -n -n -n -n -n -n -n -n -n -n hi"


if [ -s leak_tests.txt ]
then
    echo -e "\033[0;31mMemory leaks detected.\033[0m"
    cat leak_tests.txt
else
    echo -e "\033[0;32mNo memory leaks detected.\033[0m"
fi


clean_up
