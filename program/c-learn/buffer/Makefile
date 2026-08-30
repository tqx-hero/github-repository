flush: flush.o
	gcc flush.o -o flush
	echo "build success"
flush.o: flush.s
	gcc -c flush.s -o flush.o

flush.s: flush.i
	gcc -S flush.i -o flush.s

flush.i: flush.c
	gcc -E flush.c -o flush.i
