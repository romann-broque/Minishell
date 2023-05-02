#!/bin/bash

RED="\033[31m"
GREEN="\033[32m"
NC="\033[0m"

CACHE=cache
FOLDERS="srcs/ includes/ libft/"
norminette ${FOLDERS} > ${CACHE}
ret_val=$?
grep -v "OK" ${CACHE}

if [ "${ret_val}" == "0" ]; then
        echo -e "${GREEN}OK\n${NC}"
else
        echo -e "${RED}KO\n${NC}"
fi

rm ${CACHE}
exit ${ret_val}