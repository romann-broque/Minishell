#!/bin/bash

RED="\033[31m"
GREEN="\033[32m"
NC="\033[0m"

PROGRAM=./minishell
FOLDER=./tests/tester_dir/
INPUT=${FOLDER}inputs
OUTPUT_REF=${FOLDER}output_ref
OUTPUT=${FOLDER}/output

cat ${INPUT} | ${PROGRAM} &> ${OUTPUT}; diff ${OUTPUT} ${OUTPUT_REF}

ret_val=$?

if [ "${ret_val}" == "0" ]; then
	echo -e "${GREEN}OK\n${NC}"
else
	cat ${CACHE}
	echo -e "${RED}KO\n${NC}"
fi
