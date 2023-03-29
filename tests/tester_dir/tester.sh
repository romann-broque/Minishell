#!/bin/bash

RED="\033[31m"
GREEN="\033[32m"
NC="\033[0m"

PROGRAM=./minishell
FOLDER=./tests/tester_dir/
IN_FOLDER="${FOLDER}"in/
OUT_FOLDER="${FOLDER}"out/
REF_FOLDER="${FOLDER}"ref/

# Define the input, output, and output reference files

inputs=( "${IN_FOLDER}"basic.in "${IN_FOLDER}"quotes.in)
outputs=( "${OUT_FOLDER}"basic.out "${OUT_FOLDER}"quotes.out )
output_refs=( "${REF_FOLDER}"basic.ref "${REF_FOLDER}"quotes.ref )

# Iterate over the arrays using a for loop

ret_val=0
for i in "${!inputs[@]}"; do

	# Run the program and redirect the output to the corresponding output file
	cat "${inputs[$i]}" | "${PROGRAM}" &> "${outputs[$i]}"
	ret_val+=$?

	# Get the name of the input file without its path
	filename=$(basename "${inputs[$i]}")

	# Compare the output file with the corresponding reference file using diff
	if diff "${outputs[$i]}" "${output_refs[$i]}"; then
		echo -e "${GREEN}${filename} : OK${NC}"
	else
		ret_val+=$?
		echo -e "${RED}${filename} KO${NC}"
	fi
done

# Exit the (ret_val == 0)

echo

if [ "${ret_val}" -eq 0 ]; then
	exit 0
else
	exit 1
fi
