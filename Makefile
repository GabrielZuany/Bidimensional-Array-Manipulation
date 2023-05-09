all:
	gcc -pg -o main libs/src/*.c source/main.c 
clean:
	rm -f main