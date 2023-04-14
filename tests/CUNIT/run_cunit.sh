#!/bin/bash

CUNIT_FOLDER=./tests/CUNIT/
CUNIT="$CUNIT_FOLDER"cunit
CACHE="$CUNIT_FOLDER"cache

# Access the command line argument
valgrind="$1"
VALGRIND_FOLDER=./tests/valgrind/
SUPPRESSION_FILE="${VALGRIND_FOLDER}"suppressions.supp
LOG_FILE="${VALGRIND_FOLDER}"valgrind_min.out

# Use the variable in the script
if [[ "$valgrind" == "valgrind" ]]; then
	VALGRIND="valgrind -s --leak-check=full --suppressions=$SUPPRESSION_FILE --log-file=$LOG_FILE --show-leak-kinds=all"
fi

$VALGRIND $CUNIT

if grep -q "ERROR SUMMARY: 0 errors" "$LOG_FILE"; then
	ret_val=0
else
	cat $LOG_FILE
	ret_val=1
fi

exit $ret_val
