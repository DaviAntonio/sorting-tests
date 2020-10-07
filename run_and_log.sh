#!/bin/bash

readonly STACK_SIZE=32768
readonly EXE="./sort_tests.elf"
readonly STDOUT_LOG="test1.log"
readonly STDERR_LOG="test2.log"
readonly TIMING_LOG="test_time.log"

printf 'Increasing stack size to %s kiB...' "${STACK_SIZE}"
if ulimit -Ss ${STACK_SIZE} ; then
	printf 'OK\n'
else
	printf 'FAIL\n'
	exit -1
fi

echo "Executing command..."
tic="$(date --universal '+%s.%N')"
script --command "${EXE} 2>${STDERR_LOG}" --flush --timing="${TIMING_LOG}" "${STDOUT_LOG}"
toc="$(date --universal '+%s.%N')"
elapsed="$(echo "${toc} ${tic} - p" | dc)"
LC_NUMERIC=C.UTF-8 printf 'Done in %.3f seconds\n' "${elapsed}"

exit 0
