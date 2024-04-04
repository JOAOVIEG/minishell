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

run_test "echo $?"
run_test "\" \""
run_test "echo $?"
run_test "echo $?"
run_test "cat < noexiste"
run_test "echo $?"
run_test "echo hola > noperm"
run_test "echo $?"
run_test "echo hola < noperm"
run_test "echo $?"
run_test "sleep 1 | ls | cat -n"
run_test "echo $?"
run_test "sleep 1 | dddd"
run_test "echo $?"
run_test "nonexistcmd"
run_test "echo $?"
run_test "nonexistcmd | echo hi"
run_test "echo $?"
run_test "echo hi | nonexistcmd"
run_test "echo $?"
run_test "echo hi < nofile | nonexistcmd"
run_test "echo $?"
run_test "echo hi < nofile | echo hii"
run_test "echo $?"
run_test "/Users/nonexist/directory"
run_test "echo $?"
run_test "cat /Users/nonexist/directory"

if [ -s leak_tests.txt ]
then
    echo -e "\033[0;31mMemory leaks detected.\033[0m"
    cat leak_tests.txt
else
    echo -e "\033[0;32mNo memory leaks detected.\033[0m"
fi

clean_up
