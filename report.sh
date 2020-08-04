#! /bin/bash

./deque.bin  > /dev/null

lcov -t "report" -d Build/ -c -o "report.info"

genhtml -o report report.info

exit 0
