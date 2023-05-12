all:
	gcc -g -pg -o main libs/src/*.c source/main.c 
clean:
	rm -f main