#!/bin/bash

# Access the command line argument
valgrind="$1"
VALGRIND_FOLDER=./tests/valgrind/
SUPPRESSION_FILE="${VALGRIND_FOLDER}"suppressions.supp
LOG_FILE="${VALGRIND_FOLDER}"valgrind_min.out

# Use the variable in the script
if [[ "$valgrind" == "valgrind" ]]; then
	VALGRIND="valgrind -s --leak-check=full --suppressions=$SUPPRESSION_FILE --log-file=$LOG_FILE --show-leak-kinds=all"
fi

RED="\033[31m"
GREEN="\033[32m"
BLUE="\033[34m"
NC="\033[0m"

PROGRAM=./minishell
FOLDER=./tests/tester_folder/
IN_FOLDER="${FOLDER}"in/
OUT_FOLDER="${FOLDER}"out/
REF_FOLDER="${FOLDER}"ref/
REF_BASH_FOLDER="${FOLDER}"ref_bash/

# Define the input, output, and output reference files

inputs=( "${IN_FOLDER}"basic.in)
outputs=( "${OUT_FOLDER}"basic.out)
output_refs=( "${REF_FOLDER}"basic.ref)

# Iterate over the arrays using a for loop

ret_val=0
for i in "${!inputs[@]}"; do

	# Run the program and redirect the output to the corresponding output file
	cat "${inputs[$i]}" | $VALGRIND "${PROGRAM}" &> "${outputs[$i]}"
	ret_val+=$?

	# Get the name of the input file without its path
	filename=$(basename "${inputs[$i]}")

	# Compare the output file with the corresponding reference file using diff
	if diff -a "${outputs[$i]}" "${output_refs[$i]}"; then
		echo -e "${GREEN}${filename} : OK${NC}"
	else
		ret_val+=$?
		echo -e "${RED}${filename} KO${NC}"
		if [[ -n "$VALGRIND" ]]; then
			cat $LOG_FILE
		fi
	fi
done

# BASH COMPARAISON

# echo -e "${BLUE}\n<====  BASH  ====>\n${NC}"

# output_ref_bash=( "${REF_BASH_FOLDER}"basic.refb "${REF_BASH_FOLDER}"expand.refb "${REF_BASH_FOLDER}"quotes.refb "{REF_BASH_FOLDER}"var.refb)

# ret_val=0
# for i in "${!inputs[@]}"; do
# 	# Run the program and redirect the output to the corresponding output file
# 	cat "${inputs[i]}" | bash &> "${output_ref_bash[i]}"
# 	ret_val+=$?

# 	# Get the name of the input file without its path
# 	filename=$(basename "${inputs[i]}")

# 	# Compare the output file with the corresponding reference file using diff
# 	if diff -a "${output_ref_bash[i]}" "${outputs[i]}"; then
# 		echo -e "${GREEN}${filename} : OK${NC}"
# 	else
# 		ret_val+=$?
# 		echo -e "${RED}${filename} KO${NC}"
# 	fi
# done

# Exit the (ret_val == 0)

echo

if [ "${ret_val}" -eq 0 ]; then
	exit 0
else
	exit 1
fi
