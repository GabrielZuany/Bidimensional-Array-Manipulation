all:
	@gcc -pg -g -Wall -o main libs/implementation/*.c source/main.c -lm
	@echo "Building main..."
run:
	@./main
	@echo "Running main..."
generate:
	@python3 generator/generator.py
	@echo "Building random matrix..."
val:
	@valgrind --leak-check=full --show-leak-kinds=all ./main
	@echo "Running valgrind..."
profile:
	@./main
	@gprof main gmon.out > AlgorithmAnalysis/analysis.txt
	@echo "Running gprof..."
shared_lib:
	@gcc -fPIC -shared -o matrix.so libs/implementation/*.c	
	@echo "Building shared library for wrapper..."
clean:
	@rm -f main
	@rm -f gmon.out
	@echo "Cleaning..."