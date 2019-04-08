#include "Perceptron.h"
#include <cstdlib>
#include <iostream>
//#include <algorithm>
#include "myHeader.h"

Perceptron::Perceptron()
{
    //ctor
}

Perceptron::Perceptron(int numInput)
{
    this->numInput = numInput;
    inputs.reserve(numInput);
    weights.reserve(numInput);

    initializeWeight();
}

int Perceptron::                                                                                                                                                                                                                                                       Activation(double v){
    if(v >= 0.0)
        return +1;
    else
        return -1;
}

int Perceptron::ComputeOutput(std::vector<double> xValues){
    try{
        if(xValues.size() != this->numInput)
            throw 1;
        for(int i=0; i<xValues.size(); ++i)
            this->inputs[i] = xValues[i];
        double sum = 0.0;
        for(int i=0; i<numInput; ++i)
            sum += this->inputs[i] * this->weights[i];
        sum += this->bias;
        int result = Activation(sum);
        this->output = result;
        return result;
    }
    catch(int x){
        std::cout << "! xValues doesnot match with number of inputs (numInputs)";
    }
}

std::vector<double> Perceptron::train(std::vector<std::vector<double>> trainData, double alpha, int maxEpochs){
    int epoch = 0;
    //double *xValues = new double[numInput];
    std::vector<double> xValues; // initialize with 0
    xValues.reserve(numInput);
    int desired = 0;

    //int *sequence = new int[trainData.size()];
    std::vector<int> sequence; // initialize with 0
    sequence.reserve(trainData.size());

    for(int i=0; i<getArrSize(sequence); ++i)
        sequence[i] = i;

    while(epoch < maxEpochs){
        Shuffle(sequence);
        for(int i=0; i<trainData.size(); ++i){
            int idx = sequence[i];
            //copy_n(trainData[idx], numInput, xValues); // copy trainData to xValues numInput times
            for (int i=idx; i<numInput; i++) // alternate to copy
                xValues.push_back(trainData[i][0]);

            desired = (int)trainData[idx][numInput]; // -1 or +1
            int computed = ComputeOutput(xValues);
            Update(computed, desired, alpha); // modify the weights and bias values
        }
        ++epoch;
    }

    //double *result = new double[numInput + 1];
    std::vector<double> result;
    result.reserve(numInput + 1);
    //copy_n(this->weights, numInput, result); // copy weights to result numInput times
    for (int i=0; i<numInput; i++) // alternate to copy
        result.push_back(this->weights[i]);

    result[getArrSize(result) - 1] = bias;
    return result;
}

void Perceptron::initializeWeight(){
    double lo = -0.01;
    double hi = 0.01;
    for(int i = 0; i < getArrSize(weights); ++i)
        weights[i] = lo + static_cast<float>(rand())/(static_cast<float>(RAND_MAX/(hi-lo)));
    bias = lo + static_cast<float>(rand())/(static_cast<float>(RAND_MAX/(hi-lo)));
}

void Perceptron::Shuffle(std::vector<int> &sequence){
    for(int i=0; i<sequence.size(); ++i){
        int r = rand()%sequence.size(); // no need to add 1 as it will starts from 0
        int temp = sequence[r];
        sequence[r] = sequence[i];
        sequence[i] = temp;
    }
}

void Perceptron::Update(int computed, int desired, double alpha){
    if(computed == desired)
        return; // we are good here
    int delta = computed - desired; // if computed > desired, delta is +

    for(int i=0; i<this->weights.size(); ++i){ // each input-weight pair
        if(computed > desired && inputs[i] >= 0.0) // need to reduce weights
            weights[i] = weights[i] - (alpha * delta * inputs[i]); // delta is +, input is +
        else if(computed > desired && inputs[i] < 0.0) // need to reduce weights
            weights[i] = weights[i] + (alpha * delta * inputs[i]); // delta is +, input is -
        else if(computed < desired && inputs[i] >= 0.0) // need to increase weights
            weights[i] = weights[i] - (alpha * delta * inputs[i]); // delta is -, input is +
        else if(computed < desired && inputs[i] < 0.0) // need to increase weights
            weights[i] = weights[i] + (alpha * delta * inputs[i]); // delta is -, input is -
    } // each weight
    bias = bias - (alpha * delta);
}

Perceptron::~Perceptron()
{
    //dtor
}
