default:
	gcc -c -Wall -Werror -fpic mem_contest_t.c -O4
	gcc -shared -Wall -o libcontest1.so mem_contest_t.o -O4
	gcc -c -Wall -Werror -fpic mem_contest_n.c -O4
	gcc -shared -Wall -o libcontest2.so mem_contest_n.o -O4
clean:
	rm -rf mem1.o libmem1.so mem2.o libmem2.so mem3.o libmem3.so libcontest1.so libcontest2.so mem_contest_t.o mem_contest_n.o contest_t contest_n
