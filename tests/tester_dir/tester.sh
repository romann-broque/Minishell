#!/bin/bash

RED="\033[31m"
GREEN="\033[32m"
NC="\033[0m"

PROGRAM=./minishell
FOLDER=./tests/tester_dir/
INPUT=${FOLDER}inputs
OUTPUT_REF=${FOLDER}output_ref
OUTPUT=${FOLDER}/output

cat ${INPUT} | ${PROGRAM} &> ${OUTPUT}

if ! diff ${OUTPUT} ${OUTPUT_REF}; then
	echo -e "${RED}KO\n${NC}"
	exit 1
else
	echo -e "${GREEN}OK\n${NC}"
fi
