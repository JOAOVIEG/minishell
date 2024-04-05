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

run_test "> no_cmd_file"
run_test ">> no_cmd_test"
run_test "echo hola | > filepipe"
run_test "> file_first | > file_second"
run_test "echo hi > file"
run_test "echo hi >> file"
run_test "echo hi > *.txt"
run_test "echo >> file hi"
run_test "echo >> file2 hi"
run_test "> file echo hi"
run_test ">> file echo hi"
run_test "echo hi > file2 > file hi"
run_test "echo hi >> file2 > file hi"
run_test "echo hi > file2 >> file hi"
run_test "echo hi > file2 > file hi"
run_test "echo hi >> file2 >> file hi"
run_test "echo hi>file2>file hi"
run_test "echo hi>>file2>>file hi"
run_test "echo hi > file3 > file2 > file hi"
run_test "echo hi > file3 >> file2 > file hi"
run_test "echo hi > file3 > file2 >> file hi"
run_test "echo hi >> file3 > file2 > file hi"
run_test "echo hi >> file3 > file2 >> file hi"
run_test "echo hi >> file3 >> file2 > file hi"
run_test "echo hi>file3>file2>file hi"
run_test "> file3 echo hi > file2 > file hi"
run_test "> file3 echo hi > file2 >> file hi"
run_test ">> file3 echo hi > file2 > file hi"
run_test "> file3 echo hi >> file2 > file hi"
run_test ">file3 echo hi>file2>file hi"
run_test "echo hi >filea>fileb>filec hi"
run_test "echo hi >filea>>fileb>filec hi"
run_test "echo hi >filea>fileb>>filec hi"
run_test "echo hi >>filea>fileb>filec hi"
run_test "echo hi > \"doble\"quote"
run_test "echo hi >\"doble\"quote"
run_test "echo -n hi >>\"doble\"quote"
run_test "echo hi > 'simple'quote"
run_test "echo hi >'simple'quote"
run_test "echo -n hi >>'simple'quote"
run_test "echo hi > 'with spaces'"
run_test "echo hi >>'with spaces'"
run_test "echo hi > \"mixed\"'file 'name"
run_test "echo hi >> \"mixed\"'file 'name"
run_test "echo hi 0> file"
run_test "4> file"
run_test "echo hi > testfolder"
run_test "echo hi >> testfolder"
run_test "echo hi 2> testfolder"
run_test "echo hi 2>> testfolder"
run_test "echo hi > testfolder"
run_test "echo hi >> testfolder"
run_test "echo hi 2> testfolder"
run_test "echo hi 2>> testfolder"
run_test "echo > file hi"
run_test "echo >> file2 hi"
run_test "> file echo hi"
run_test ">> file3 echo hi"
run_test "cat < file"
run_test "< file cat < file2"
run_test "cat < nonexist"
run_test "cat < $USER"
run_test "cat < file3"
run_test "echo hi 2> error_outp < non_exist"
run_test "echo hi < non_exist > wrong"
run_test "< non_exist echo hi > wrong"
run_test "> correct echo hi < non_exist"


if [ -s leak_tests.txt ]
then
    echo -e "\033[0;31mMemory leaks detected.\033[0m"
    cat leak_tests.txt
else
    echo -e "\033[0;32mNo memory leaks detected.\033[0m"
fi

clean_up
