#!/bin/bash

NAME="   ___ _     _ _         _____          _            
  / _ \ |__ (_) | ___   /__   \___  ___| |_ ___ _ __ 
 / /_)/ '_ \| | |/ _ \    / /\/ _ \/ __| __/ _ \ '__|
/ ___/| | | | | | (_) |  / / |  __/\__ \ ||  __/ |   
\/    |_| |_|_|_|\___/   \/   \___||___/\__\___|_|   
                                                           "

LIGHT_RED='\033[1;31m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
ORANGE='\033[0;33m'
NC='\033[0m'
USAGE="Usage: ./test.sh <path_to_executable philo>"
MESSAGE="\nThis test does not test for memory leaks only for correct behavior\n"
TIME_TO_TEST=10
echo -e "${LIGHT_RED}$NAME${NC}"
echo -e "${CYAN}$MESSAGE${NC}"
if [ "$#" -ne 1 ]; then
	echo -e "${LIGHT_RED}Error:${NC} Invalid number of arguments."
	echo "$USAGE"
	exit 1
fi

EXECUTABLE=$1

if [ ! -f "$EXECUTABLE" ] || [ ! -x "$EXECUTABLE" ]; then
	echo -e "${LIGHT_RED}Error:${NC} '$EXECUTABLE' is not a valid executable file."
	exit 1
fi

color_percentage(){
	if [ $1 -ge 90 ]; then
		echo -e "PASSED: ${GREEN}$1% ($2 out of $TIME_TO_TEST)${NC}"
	elif [ $1 -ge 70 ]; then
		echo -e "PASSED: ${ORANGE}$1% ($2 out of $TIME_TO_TEST)${NC}"
	else
		echo -e "PASSED: ${LIGHT_RED}$1% ($2 out of $TIME_TO_TEST)${NC}"
	fi
}

test1(){
	echo -e "Running test 1 with 1 800 200 200. Should die\n"
	PASSED=0
	for i in $(seq 1 $TIME_TO_TEST); do
		OUTPUT=$(timeout 1s ./$EXECUTABLE 1 800 200 200)
		if echo "$OUTPUT" | grep -q "died"; then
			echo -e "${GREEN}Test 1 - Iteration $i: Passed${NC}"
			((PASSED++))
		else
			echo -e "${LIGHT_RED}Test 1 - Iteration $i: Failed${NC}"
		fi
	done
	PERCENTAGE=$((PASSED * 100 / TIME_TO_TEST))
	color_percentage $PERCENTAGE $PASSED
}

test2(){
	echo -e "\nRunning test 2 with  2 800 100 100. Should live\n"
	PASSED=0
	for i in $(seq 1 $TIME_TO_TEST); do
		OUTPUT=$(timeout 3s ./$EXECUTABLE 2 800 100 100)
		if echo "$OUTPUT" | grep -q "died"; then
			echo -e "${LIGHT_RED}Test 2 - Iteration $i: Failed${NC}"
		else
			echo -e "${GREEN}Test 2 - Iteration $i: Passed${NC}"
			((PASSED++))
		fi
	done
	PERCENTAGE=$((PASSED * 100 / TIME_TO_TEST))
	color_percentage $PERCENTAGE $PASSED
}

test3(){
	echo -e "\nRunning test 3 with 3 800 100 100. Should live\n"
	PASSED=0
	for i in $(seq 1 $TIME_TO_TEST); do
		OUTPUT=$(timeout 3s ./$EXECUTABLE 3 800 100 100)
		if echo "$OUTPUT" | grep -q "died"; then
			echo -e "${LIGHT_RED}Test 3 - Iteration $i: Failed${NC}"
		else
			echo -e "${GREEN}Test 3 - Iteration $i: Passed${NC}"
			((PASSED++))
		fi
	done
	PERCENTAGE=$((PASSED * 100 / TIME_TO_TEST))
	color_percentage $PERCENTAGE $PASSED
}

nb_eaten(){
    local output=$1
    local required=$2
    local nb_philo=$3
    local i
    
    i=1
    while [ $i -le $nb_philo ]; do
		local eaten=$(echo "$output" | grep -c "$i is eating")
        if [ $eaten -lt $required ]; then
            return 1
        fi
        ((i++))
    done
    return 0
}

test4(){
	echo -e "\nRunning test 4 with 5 800 200 200 5. Should live\n"
	PASSED=0
	for i in $(seq 1 $TIME_TO_TEST); do
		OUTPUT=$(timeout 7s ./$EXECUTABLE 5 800 200 200 5)
		if echo "$OUTPUT" | grep -q "died"; then
			echo -e "${LIGHT_RED}Test 4 - Iteration $i: Failed${NC}"
		elif ! nb_eaten "$OUTPUT" 5 5; then
			echo -e "${LIGHT_RED}Test 4 - Iteration $i: Failed${NC}"
		else
			echo -e "${GREEN}Test 4 - Iteration $i: Passed${NC}"
			((PASSED++))
		fi
	done
	PERCENTAGE=$((PASSED * 100 / TIME_TO_TEST))
	color_percentage $PERCENTAGE $PASSED
}

test5(){
	echo -e "\nRunning test 5 with 6 800 200 200 5. Should live\n"
	PASSED=0
	for i in $(seq 1 $TIME_TO_TEST); do
		OUTPUT=$(timeout 7s ./$EXECUTABLE 6 800 200 200 5)
		if echo "$OUTPUT" | grep -q "died"; then
			echo -e "${LIGHT_RED}Test 5 - Iteration $i: Failed${NC}"
		elif ! nb_eaten "$OUTPUT" 5 6; then
			echo -e "${LIGHT_RED}Test 5 - Iteration $i: Failed${NC}"
		else
			echo -e "${GREEN}Test 5 - Iteration $i: Passed${NC}"
			((PASSED++))
		fi
	done
	PERCENTAGE=$((PASSED * 100 / TIME_TO_TEST))
	color_percentage $PERCENTAGE $PASSED
}

test6(){
	echo -e "\nRunning test 6 with 4 410 200 200 2. Should live\n"
	PASSED=0
	for i in $(seq 1 $TIME_TO_TEST); do
		OUTPUT=$(timeout 7s ./$EXECUTABLE 5 410 200 200 2)
		if echo "$OUTPUT" | grep -q "died"; then
			echo -e "${LIGHT_RED}Test 6 - Iteration $i: Failed${NC}"
		elif ! nb_eaten "$OUTPUT" 2 5; then
			echo -e "${LIGHT_RED}Test 6 - Iteration $i: Failed${NC}"
		else
			echo -e "${GREEN}Test 6 - Iteration $i: Passed${NC}"
			((PASSED++))
		fi
	done
	PERCENTAGE=$((PASSED * 100 / TIME_TO_TEST))
	color_percentage $PERCENTAGE $PASSED
}

test7(){
	echo -e "\nRunning test 7 with 21 800 100 100 5. Should live\n"
	PASSED=0
	for i in $(seq 1 $TIME_TO_TEST); do
		OUTPUT=$(timeout 10s ./$EXECUTABLE 21 800 100 100 5)
		if echo "$OUTPUT" | grep -q "died"; then
			echo -e "${LIGHT_RED}Test 7 - Iteration $i: Failed${NC}"
		elif ! nb_eaten "$OUTPUT" 5 21; then
			echo -e "${LIGHT_RED}Test 7 - Iteration $i: Failed${NC}"
		else
			echo -e "${GREEN}Test 7 - Iteration $i: Passed${NC}"
			((PASSED++))
		fi
	done
	PERCENTAGE=$((PASSED * 100 / TIME_TO_TEST))
	color_percentage $PERCENTAGE $PASSED
}

test1
test2
test3
test4
test5
test6
test7
