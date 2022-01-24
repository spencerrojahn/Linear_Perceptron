
run: compile
	@./model/exec data-linear.txt weights.txt

compile:
	@g++ -std=c++20 -o model/exec model/Perceptron_cpp.cpp