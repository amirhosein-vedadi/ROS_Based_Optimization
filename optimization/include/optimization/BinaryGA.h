#pragma once

#include "fstream"
#include "iostream"
#include "math.h"
#include <stdlib.h>
#include <time.h>
#include <vector>

class BinaryGA{
/*
    Implementation of a Simple Binary Genetic Algorithm. Inspired by:
    Jason Brownlee, Machine Learning Algorithms in Python, Machine Learning Mastery, 
    Available from https://machinelearningmastery.com/simple-genetic-algorithm-from-scratch-in-python/.
*/
    public:
        BinaryGA(std::string filePath);
        void splitParam(std::string line);


    private:
        //std::string filePath_;
        int nIter_;
        int nBits_;
        int nPop_;
        double rCross_;
        double rMut_;

};