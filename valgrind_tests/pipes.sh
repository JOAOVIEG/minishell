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

run_test "echo | /bin/cat"
run_test "echo hi | /bin/cat"
run_test "cat /etc/shells | head -c 10"
run_test "cat -e /etc/shells | head -c 10"
run_test "cat -e /etc/shells | cat -e | head -c 10"
run_test "cat -e /etc/shells | cat -e | cat -e | head -c 10"
run_test "echo hola | cat"
run_test "echo hola | cat -e"
run_test "echo hola | cat -e | cat -n"
run_test "echo hola with many pipes cat -e"
run_test "ls | cat -e"
run_test "ls -l | cat -e"
run_test "ls -l | cat -e | cat | cat | cat"
run_test "ls -l | cat -e | cat -e | cat -e | cat -e"
run_test "echo hola | asdf"
run_test "asdf | echo hola"
run_test "sleep 1 | ls | cat -n"
run_test "cd folder | pwd"
run_test "ls pipes (255)"
run_test "ls pipes (256)"
run_test "ls pipes (257)"
run_test "ls pipes (258)"
run_test "ls pipes (259)"
run_test "ls -l | grep .sh | wc -l"
run_test "echo 'Hello, World!' | wc -c"
run_test "cat /etc/passwd | grep root"
run_test "find . -name '*.sh' | wc -l"
run_test "ps aux | grep bash"
run_test "ls -l | awk '{print $9}'"
run_test "date | cut -d' ' -f1"
run_test "whoami | tr -d '\n'"
run_test "ls -l | sort -r"
run_test "ls -l | sort | uniq"
run_test "echo 'This is a test' | ls"
run_test "ls -l | head -n 5"
run_test "ls -l | tail -n 5"
run_test "ls -l | sed 's/^.*$/Test passed/'"
run_test "ls -l | grep '^d'"
run_test "ls -l | awk '{print $1}' | sort | uniq -c"
run_test "ls -l | awk '{print $3}' | sort | uniq -c"
run_test "ls -l | awk '{print $5}' | sort -n"
run_test "ls -l | awk '{print $5}' | sort -nr | head -n 5"
run_test "ls -l | awk '{print $5}' | sort -nr | tail -n 5"

if [ -s leak_tests.txt ]
then
    echo -e "\033[0;31mMemory leaks detected.\033[0m"
    cat leak_tests.txt
else
    echo -e "\033[0;32mNo memory leaks detected.\033[0m"
fi


clean_up

