
run: compile
	@./model/exec data-linear.txt weights.txt
	@python3 plot.py

compile:
	@g++ -std=c++20 -o model/exec model/Perceptron_cpp.cpp


	