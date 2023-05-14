all:
	gcc -g -pg -o main libs/src/*.c source/main.c 
run:
	./main
val:
	valgrind --leak-check=full --show-leak-kinds=all ./main
clean:
	rm -f main