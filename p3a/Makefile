default:
	gcc -c -Wall -Werror -fpic mem1.c -O
	gcc -shared -Wall -o libmem1.so mem1.o -O
	gcc -c -Wall -Werror -fpic mem2.c -O
	gcc -shared -Wall -o libmem2.so mem2.o -O
	gcc -c -Wall -Werror -fpic mem3.c -O
	gcc -shared -Wall -o libmem3.so mem3.o -O
contest_t:
	gcc -c -Wall -Werror -fpic mem_contest_t.c -O
	gcc -shared -Wall -o libcontest1.so mem_contest_t.o -O
	gcc time.c -Wall -o contest_t -lcontest1 -L.
contest_n:
	gcc -c -Wall -Werror -fpic mem_contest_n.c -O
	gcc -shared -Wall -o libcontest2.so mem_contest_n.o -O
	gcc space.c -Wall -o contest_n -lcontest2 -L.
test:
	gcc -lmem1 -L. -o test test.c -Wall -Werror
clean:
	rm -rf mem1.o libmem1.so mem2.o libmem2.so mem3.o libmem3.so libcontest1.so libcontest2.so mem_contest_t.o mem_contest_n.o contest_t contest_n
