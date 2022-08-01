#!/bin/bash

cd $(dirname $0)
#make

run() {
	tst_exec=$1
	result=$2
	ok=1

	echo === Test $tst_exec ===
	rm -f tst
	if ! ./$tst_exec ; then
		echo "Exec failed"
		ok=0
	fi

	if ! cmp --silent tst $result ; then
		echo Invalid file content
		ok=0
	fi

	[ "$ok" == "1" ] && echo OK
}

for x in capitalize_*; do
	run $x capitalize.out
done

for x in unload_*; do
    run $x unload.out
done

