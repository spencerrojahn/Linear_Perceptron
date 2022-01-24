
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <random>

using namespace std;

class Perceptron {
private:
    double* weights;

    // make prediction
    double predict(double data_point[4]) {
        double dot_product = 0;
        for (int i = 0; i < 3; i++) {
            dot_product += weights[i]*data_point[i];
        }
        if (dot_product >= 0) {
            return 1.0;
        } else {
            return -1.0;
        }
    }

    // return accuracy
    double accuracy(double data[][4], int n) {
        int correct = 0;
        for (int i = 0; i < n; i++) {
            double pred = predict(data[i]);
            if (pred == data[i][3]) {
                correct++;
            }
        }
        return (double)correct/(double)n;
    }


public:
    Perceptron(int width) {
        weights = new double[width];       // width includes bias (first index)

        random_device rd; 
        mt19937 gen(rd()); 
        uniform_real_distribution<> dis(-1.0,1.0);
        for (int i = 0; i < width; ++i) {
            weights[i] = dis(gen);
        }
    }

    void train(double data[][4], int n, int epochs) {

        double lr = 0.01;
        for (int iter = 0; iter < epochs; iter++) {
            // lr = 1.0/(iter+1.0);
            for (int i = 0; i < n; i++) {
                double pred = predict(data[i]);
                if (pred != data[i][3]) {
                    for (int j = 0; j < 3; j++) {
                        weights[j] += lr * data[i][j] * data[i][3];
                    }
                }
            }
            double acc = accuracy(data, n);
            cout << acc << endl;
            if (acc == 1) {
                break;
            }
        }
    }

    void test(double data[][4], int n) {
        double acc = accuracy(data, n);
        cout << acc << endl;
    }

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


    int n = lines.size();
    double data[n][4];
    int i = 0;

    for (const auto &value : lines) {

        vector<string> d;
        stringstream ss(value);

        while (ss.good()) {
            string substr;
            getline(ss, substr, ',');
            d.push_back(substr);
        }   

        data[i][0] = 1.0;       // 1 for bias
        data[i][1] = stod(d[1]);
        data[i][2] = stod(d[2]);
        data[i][3] = stod(d[0]);
        i++;

    }
    

    Perceptron model(3);

    model.train(data, n, 100);
    model.test(data, n);

    string output_filename(argv[2]);
    ofstream output;
    output.open(output_filename);

    double* wts = model.getWeights();
    for (int i = 0; i < 3; i++) {
        output << "W" << i << ":" << *(wts + i) << "\n";
    }
    output.close();
    return 0;

}