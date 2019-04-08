#ifndef PERCEPTRON_H
#define PERCEPTRON_H
#include <vector>

class Perceptron
{
    public:
        Perceptron();
        Perceptron(int numInput);
        int ComputeOutput(std::vector<double> xValues);
        std::vector<double> train(std::vector<std::vector<double>> trainData, double alpha, int maxEpochs);
        // make sure this train function works after the use poiter use
        // because i have never use this in this manner before
        ~Perceptron();

    protected:

    private:
        // Data members
        int numInput; // i/p for perceptron which is two
        /*
        double *inputs;
        double *weights;
        */
        std::vector<double> inputs;
        std::vector<double> weights;
        double bias;
        int output;
        // Data functons
        void initializeWeight();
        int Activation(double v);
        void Shuffle(std::vector<int> &sequence);
        void Update(int computed, int desired, double alpha);
};

#endif // PERCEPTRON_H
