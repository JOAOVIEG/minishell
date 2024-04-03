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

# Run the tests
run_test "echo $?"
run_test "echo '$ '"
run_test "echo $USER"
run_test "echo $NONEXIST"
run_test "echo $USER$PATH$PWD"
run_test "echo \"$USER$PATH$PWD\""
run_test "echo '$USER$PATH$PWD'"
run_test "echo '$USER\",\"\$PATH,\$PWD'"
run_test "$NONEXIST"
run_test "$NONEXIST $NONEXIST"
run_test "VAR: export TMPENVVAR"
run_test "VAR: export TMPENVVAR=echo"
run_test "VAR: export TMPENVVAR=\"-n\""
run_test "echo '|$USER|'"
run_test "echo '|$USE|'"
run_test "echo '|$USER_|'"
run_test "'echo' hi"
run_test "'''echo' hi"
run_test "'echo' 'hi'"
run_test "'echo' 'hi'''"
run_test "\"echo\" hi"
run_test "\"\"\"echo\" hi"
run_test "\"echo\" \"hi\""
run_test "\"echo\" \"hi\"\"\""
run_test "echo '\"\"\"\"\"\"\"\"\"\"\"\"'"
run_test "echo '\"$\"'"
run_test "echo \"|$USER|\""
run_test "echo \"|$USE|\""
run_test "\" echo\""
run_test "' echo'"
run_test "\"\"echo"
run_test "\" \"echo"
run_test "''echo"
run_test "' 'echo"
run_test "''''''''''echo hi"
run_test "\"\"\"\"\"\"\"\"\"\"echo hi"
run_test "EcHo hi"
run_test "ECHO hi"
run_test "\"ECHO\" hi"
run_test "'ECHO' hi"
run_test "echo    t  hi   t"
run_test "echo \"   t  hi   t    \""
run_test "echo '   t  hi   t    '"
run_test "echo $\"   t  hi   t    \""
run_test "echo $'   t  hi   t    '"
run_test "echo $'   r  hi   t    '"
run_test "echo hi~"
run_test "echo ~$USER"
run_test "echo ~false"
run_test "echo ~$USER/sdfsfsfsfdsfs"
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
run_test "echo hi >< file"

echo "Tests that caused memory leaks:"
cat leak_tests.txt

clean_up
