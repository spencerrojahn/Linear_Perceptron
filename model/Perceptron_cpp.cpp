#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <random>

#define NUM_FEATURES 3

using namespace std;

class Perceptron {
private:
    double* weights;

    // make prediction
    double predict(double data_point[NUM_FEATURES+1]) {
        double dot_product = 0;
        for (int i = 0; i < NUM_FEATURES; i++) {
            dot_product += weights[i]*data_point[i];
        }
        if (dot_product >= 0) {
            return 1.0;
        } else {
            return -1.0;
        }
    }

    // return accuracy
    double accuracy(double data[][NUM_FEATURES+1], int n) {
        int correct = 0;
        for (int i = 0; i < n; i++) {
            double pred = predict(data[i]);
            if (pred == data[i][NUM_FEATURES]) {
                correct++;
            }
        }
        return (double)correct/(double)n;
    }


public:
    Perceptron(int width) {
        weights = new double[width];       // width includes bias (first index)

        // produce random weights between 0 and 1
        random_device rd; 
        mt19937 gen(rd()); 
        uniform_real_distribution<> dis(0,1.0);
        for (int i = 0; i < width; ++i) {
            weights[i] = dis(gen);
        }
    }

    // train the model with specific number of epochs (steps)
    void train(double data[][NUM_FEATURES+1], int n, int epochs) {
        cout << "\nTraining model for " << epochs << " epochs\n" << endl;

        // learning rate is 0.01 for now (proabably will incorpote other types of learning rates)
        double lr = 0.01;
        for (int iter = 0; iter < epochs; iter++) {
            // lr = 1.0/(iter+1.0);
            for (int i = 0; i < n; i++) {
                double pred = predict(data[i]);
                if (pred != data[i][NUM_FEATURES]) {
                    for (int j = 0; j < NUM_FEATURES; j++) {
                        weights[j] += lr * data[i][j] * data[i][3];
                    }
                }
            }
            double acc = accuracy(data, n);
            cout << "Epoch #" << (iter+1) << " ----- accuracy: " << (acc*100.0) << "%" << endl;
            if (acc == 1) {
                break;
            }
        }
        cout << endl;
    }

    // function to test current accuracy with given weights
    void test(double data[][NUM_FEATURES+1], int n) {
        double acc = accuracy(data, n);
        cout << "Model TEST: " << (acc*100.0) << "%\n" << endl;
    }

    // return the weights
    double* getWeights() {
        return weights;
    }
};


int main (int argc, char** argv) {
    string input_filename(argv[1]);
    ifstream input_file(input_filename);
    vector<string> lines;
    string line;

    while (getline(input_file, line)){
        lines.push_back(line);
    }
    input_file.close();

    // int num_features = 3;           // includes bias

    int n = lines.size();
    // double data[n][4];
    double data[n][NUM_FEATURES+1];
    int i = 0;

    // get input  attributes and target values
    for (const auto &value : lines) {
        vector<string> d;
        stringstream ss(value);

        while (ss.good()) {
            string substr;
            getline(ss, substr, ',');
            d.push_back(substr);
        }   

        
        data[i][0] = 1.0;           // 1 for bias
        for (int j = 1; j < NUM_FEATURES; j++) {
            data[i][j] = stod(d[j]);
        }
        data[i][NUM_FEATURES] = stod(d[0]);
        i++;
    }
    
    // create the perceptron model
    Perceptron model(NUM_FEATURES);

    // train the model and then test
    model.train(data, n, 100);
    model.test(data, n);

    // print the weights to file for plotting (done in python)
    string output_filename(argv[2]);
    ofstream output;
    output.open(output_filename);

    double* wts = model.getWeights();
    for (int i = 0; i < NUM_FEATURES; i++) {
        output << "W" << i << ":" << *(wts + i) << "\n";
    }
    output.close();
    return 0;
}


