all:
	gcc -pg -g -Wall -o main libs/implementation/*.c source/main.c -lm
run:
	./main
val:
	valgrind --leak-check=full --show-leak-kinds=all ./main
profile:
	./main
	gprof main gmon.out > analysis.txt
clean:
	rm -f main
	rm -f gmon.out
	rm -f analysis.txt