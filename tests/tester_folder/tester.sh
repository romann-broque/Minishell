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
ENV=./tests/env/env.sh
IN_FOLDER="${FOLDER}"in/
OUT_FOLDER="${FOLDER}"out/
REF_FOLDER="${FOLDER}"ref/
REF_BASH_FOLDER="${FOLDER}"ref_bash/

# Define the input, output, and output reference files

# inputs=( "${IN_FOLDER}"basic.in)
# outputs=( "${OUT_FOLDER}"basic.out)
# output_refs=( "${REF_FOLDER}"basic.ref)

# # Iterate over the arrays using a for loop

# ret_val=0
# for i in "${!inputs[@]}"; do

# 	# Run the program and redirect the output to the corresponding output file
# 	source $ENV; cat "${inputs[$i]}" | $VALGRIND "${PROGRAM}" &> "${outputs[$i]}"
# 	ret_val+=$?

# 	# Get the name of the input file without its path
# 	filename=$(basename "${inputs[$i]}")

# 	# Compare the output file with the corresponding reference file using diff
# 	if diff -a "${outputs[$i]}" "${output_refs[$i]}"; then
# 		echo -e "${GREEN}${filename} : OK${NC}"
# 	else
# 		ret_val+=$?
# 		echo -e "${RED}${filename} KO${NC}"
# 		if [[ -n "$VALGRIND" ]]; then
# 			cat $LOG_FILE
# 		fi
# 	fi
# done

function put_format()
{
	local folder="$1"
	local suffix="$2"
	local files=("${@:3}")

	for (( i=0; i<${#files[@]}; i++ )); do
		files[$i]="${folder}${files[$i]}${suffix}"
	done
	echo "${files[@]}"
}

# BASH COMPARAISON

 echo -e "${BLUE}\n<====  BASH  ====>\n${NC}"

files=( "basic" "builtin_cwd" "echo_builtin" "expansion" "assign" "exit_builtin" "export_builtin" "unset")

inputs=($(put_format "$IN_FOLDER" ".in" "${files[@]}"))
outputs=($(put_format "$OUT_FOLDER" ".out" "${files[@]}"))
output_ref_bash=($(put_format "$REF_BASH_FOLDER" ".refb" "${files[@]}"))

source $ENV
 for i in "${!inputs[@]}"; do
 	# Run the program and redirect the output to the corresponding output file
 	cat "${inputs[i]}" | bash --posix &> "${output_ref_bash[i]}"
 	cat "${inputs[i]}" | ./minishell &> "${outputs[i]}"
 	ret_val+=$?
	# Replace Error of each line with minishell
	sed -i -e 's/^bash: line [0-9]*: /minishell: /g' "${output_ref_bash[i]}"
	sed -i '/^minishell /d' "${outputs[i]}"
	sed -i '/^minishell /d' "${output_ref_bash[i]}"
	while grep -c "minishell " "${outputs[i]}" > /dev/null; do
		sed -i -n '/minishell \$/!{p;d}; N; s/minishell \$.*\n//; P; D' "${outputs[i]}"
	done
	sed -i '/^exit/d' "${outputs[i]}"
	sed -i '/^exit/d' "${output_ref_bash[i]}"

 	# Get the name of the input file without its path
 	filename=$(basename "${inputs[i]}")

 	# Compare the output file with the corresponding reference file using diff
 	if diff -a "${output_ref_bash[i]}" "${outputs[i]}"; then
 		echo -e "${GREEN}${filename} : OK${NC}"
 	else
 		ret_val+=$?
 		echo -e "${RED}${filename} KO${NC}"
		if [[ -n "$VALGRIND" ]]; then
			cat $LOG_FILE
		fi
 	fi
 done

# Exit the (ret_val == 0)

echo

if [ "${ret_val}" -eq 0 ]; then
	exit 0
else
	exit 1
fi
