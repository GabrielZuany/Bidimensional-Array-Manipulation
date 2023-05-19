all:
	gcc -g -Wall -pg -o main libs/src/*.c source/main.c -lm
run:
	./main
val:
	valgrind --leak-check=full --show-leak-kinds=all ./main
clean:
	rm -f main