#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
CYAN='\033[0;36m'
NC='\033[0m'
difference=0
FLAG=false

echo -n "Select the number of runs to perform: "
read RUNS

for ((j = 1; j <= $RUNS; j++)); do
    echo -e "${YELLOW}[------------------- RUN NUMBER ${j} -------------------]${NC}"
    for i in {1..15}; do
        echo -e "${YELLOW}[Running test ${i}...]${NC}"
        # start=$(date +%s%N)
        ./a.out < "tests/test${i}.txt" > "temp_result.txt"
        # end=$(date +%s%N)
        # runtime1=$(($end-$start))
        # echo -e "${CYAN}[Parallel Test ${i} finished in ${runtime1} ns]${NC}"
        # start=$(date +%s%N)
        # ./testseq.out < "tests/test${i}.txt" > "temp_result2.txt"
        # end=$(date +%s%N)
        # runtime2=$(($end-$start))
        # differenced=$(($runtime1-$runtime2))
        # difference=$(($difference+$differenced))
        # echo -e "${CYAN}[Sequential Test ${i} finished in ${runtime2} ns]${NC}"
        # echo -e "${CYAN}[Difference: ${differenced} ns]${NC}"

        if diff -q "temp_result.txt" "test_results/result${i}.txt"; then
            echo -e "${GREEN}Test ${i} passed!${NC}"
        else
            FLAG=true
            echo -e "${RED}\nTest ${i} failed! Differences:\n${NC}"
            diff --unified "temp_result.txt" "test_results/result${i}.txt" | grep -E '^(\+|-)[^+-]'
            echo -e "${CYAN}\n^ ['+' ARE REQUIRED RESULT LINES, '-' ARE WRONG LINES PRINTED, REMEMBER TO CHECK FOR SEG FAULTS]\n${NC}"
        fi
    done
    # echo -e "${CYAN}Total difference: sequential was ${difference} ns faster then parallel in this run"
    if $FLAG; then
        echo -e "${RED}\n[------------------- FAILED RUN NUMBER ${j} -------------------]${NC}"
        break
    fi
done
if ! $FLAG; then 
    echo -e "${GREEN}[------------------- ALL TESTS PASSED -------------------]${NC}"
fi


# Remove the temporary result file
rm -f "temp_result.txt temp_result2.txt" 
