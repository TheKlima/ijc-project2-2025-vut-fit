#!/bin/bash

# Get the command-line arguments
maxwordcount_type=$1

# Import terminal colors
RED="\e[31m"
GREEN="\e[32m"
LIGHT_GRAY="\e[37m"
PURPLE="\e[35m"
BOLD="\033[1m"
DEFAULT="\e[0m"

# Create variables to keep track of all the different test statistics
test_cnt=0
tests_passed=0

# Test the output code
test_script_output(){
    test_description=$1 # The test description
    test_cnt=$2         # Test count
    test_file=$(pwd)/maxwordcount_tests2025/$3.input  # Program input file
    test_output=$(pwd)/maxwordcount_tests2025/$3.output  # Program output file
    test_type=$4 # Test type (normal or dynamic)

    printf "${LIGHT_GRAY}[Test $test_cnt] – $test_description\n" # Print information about the current test

    # Run the script
    if [ "$test_type" == "dynamic" ]; then
        LD_LIBRARY_PATH="." ../maxwordcount-dynamic <"$test_file" | sort -n > "tmp_file.out"
    else 
        ../maxwordcount <"$test_file" | sort -n > "tmp_file.out"
    fi

    # Check the output
    output=$(cat ./tmp_file.out)
    ref_ouput=$(cat "$test_output" | sort -n)
    
    # Check if the return code and output is matching
    if [ "$output" == "$ref_ouput" ]; then
        echo -e "${GREEN}Test passed ✓ ${DEFAULT}\n"
        # Increase the passed tests count
        tests_passed=$(($tests_passed + 1))
    else
        echo -e "${RED}Test failed ⨯ ${DEFAULT}\n"
    fi

    # Increase the test count
    test_cnt=$(($test_cnt + 1))
}

run_maxwordcount_tests_static(){
    for file in "./maxwordcount_tests2025"/*.input; do
        test_name=$(echo "$file" | rev | cut -d '.' -f2 | cut -d '/' -f1 | rev)
        test_script_output "Testing basic and advanced functionality - $test_name test" $test_cnt "$test_name" ""
    done

    # Check for memory leaks
    printf "${LIGHT_GRAY}[Test $test_cnt] – Testing memory leaks 1\n" # Print information about the current test
    valgrind_result=$(valgrind --leak-check=full ../maxwordcount < ./maxwordcount_tests2025/empty.input 2>&1)

    if echo "$valgrind_result" | grep -q "All heap blocks were freed -- no leaks are possible"; then
        echo -e "${GREEN}Test passed ✓ ${DEFAULT}\n"
        # Increase the passed tests count
        tests_passed=$(($tests_passed + 1))
    else
        echo -e "${RED}Test failed ⨯ ${DEFAULT}\n"
    fi

    # Increase the test count
    test_cnt=$(($test_cnt + 1))

    # Check for memory leaks
    printf "${LIGHT_GRAY}[Test $test_cnt] – Testing memory leaks 2\n" # Print information about the current test
    valgrind_result=$(valgrind --leak-check=full ../maxwordcount < ./maxwordcount_tests2025/random_2.input 2>&1)

    if echo "$valgrind_result" | grep -q "All heap blocks were freed -- no leaks are possible"; then
        echo -e "${GREEN}Test passed ✓ ${DEFAULT}\n"
        # Increase the passed tests count
        tests_passed=$(($tests_passed + 1))
    else
        echo -e "${RED}Test failed ⨯ ${DEFAULT}\n"
    fi

    # Increase the test count
    test_cnt=$(($test_cnt + 1))

    printf "${LIGHT_GRAY}[Test $test_cnt] – Testing memory leaks 3\n" # Print information about the current test
    valgrind_result=$(valgrind --leak-check=full ../maxwordcount < ./maxwordcount_tests2025/seq.input 2>&1)

    if echo "$valgrind_result" | grep -q "All heap blocks were freed -- no leaks are possible"; then
        echo -e "${GREEN}Test passed ✓ ${DEFAULT}\n"
        # Increase the passed tests count
        tests_passed=$(($tests_passed + 1))
    else
        echo -e "${RED}Test failed ⨯ ${DEFAULT}\n"
    fi

    # Increase the test count
    test_cnt=$(($test_cnt + 1))
}

run_maxwordcount_tests_dynamic(){
    for file in "./maxwordcount_tests2025"/*.input; do
        test_name=$(echo "$file" | rev | cut -d '.' -f2 | cut -d '/' -f1 | rev)
        test_script_output "Testing basic and advanced functionality (dynamic) - $test_name test" $test_cnt "$test_name" "dynamic"
    done

    # Check for memory leaks
    printf "${LIGHT_GRAY}[Test $test_cnt] (dynamic) – Testing memory leaks 1\n" # Print information about the current test
    valgrind_result=$(LD_LIBRARY_PATH="." valgrind --leak-check=full ../maxwordcount-dynamic < ./maxwordcount_tests2025/empty.input 2>&1)

    if echo "$valgrind_result" | grep -q "All heap blocks were freed -- no leaks are possible"; then
        echo -e "${GREEN}Test passed ✓ ${DEFAULT}\n"
        # Increase the passed tests count
        tests_passed=$(($tests_passed + 1))
    else
        echo -e "${RED}Test failed ⨯ ${DEFAULT}\n"
    fi

    # Increase the test count
    test_cnt=$(($test_cnt + 1))

    # Check for memory leaks
    printf "${LIGHT_GRAY}[Test $test_cnt] (dynamic) – Testing memory leaks 2\n" # Print information about the current test
    valgrind_result=$(LD_LIBRARY_PATH="." valgrind --leak-check=full ../maxwordcount-dynamic < ./maxwordcount_tests2025/random_2.input 2>&1)

    if echo "$valgrind_result" | grep -q "All heap blocks were freed -- no leaks are possible"; then
        echo -e "${GREEN}Test passed ✓ ${DEFAULT}\n"
        # Increase the passed tests count
        tests_passed=$(($tests_passed + 1))
    else
        echo -e "${RED}Test failed ⨯ ${DEFAULT}\n"
    fi

    # Increase the test count
    test_cnt=$(($test_cnt + 1))

    printf "${LIGHT_GRAY}[Test $test_cnt] (dynamic) – Testing memory leaks 3\n" # Print information about the current test
    valgrind_result=$(LD_LIBRARY_PATH="." valgrind --leak-check=full ../maxwordcount-dynamic < ./maxwordcount_tests2025/seq.input 2>&1)

    if echo "$valgrind_result" | grep -q "All heap blocks were freed -- no leaks are possible"; then
        echo -e "${GREEN}Test passed ✓ ${DEFAULT}\n"
        # Increase the passed tests count
        tests_passed=$(($tests_passed + 1))
    else
        echo -e "${RED}Test failed ⨯ ${DEFAULT}\n"
    fi

    # Increase the test count
    test_cnt=$(($test_cnt + 1))
}

printf "${LIGHT_GRAY}Running maxwordcount tests...\n\n" # Print information about the current test

# Run the output tests
if [ "$maxwordcount_type" == "dynamic" ]; then
    run_maxwordcount_tests_dynamic
elif [ "$maxwordcount_type" == "all" ]; then
    run_maxwordcount_tests_static
    run_maxwordcount_tests_dynamic
else
    run_maxwordcount_tests_static
fi

printf "${BOLD}${PURPLE}Total:\n\tTESTS PASSED = $tests_passed/$test_cnt\n\tTESTS FAILED = $(($test_cnt - $tests_passed))/$test_cnt\n\n"

rm tmp_file.out

if [ $tests_passed -eq $test_cnt ]
then
    xdg-open --version > /dev/null 2>&1
    if [ $? -eq 0 ]
    then
        xdg-open ./tail_tests2025/__/klidecek.jpg > /dev/null 2>&1
    fi
fi

# Author ~ Marek Čupr (xcuprm01)
