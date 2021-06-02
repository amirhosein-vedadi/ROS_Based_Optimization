#pragma once

#include <cstdlib>
#include "fstream"
#include "iostream"
#include "math.h"
#include <stdlib.h>
#include <time.h>
#include <vector>

#include <ros/ros.h>
#include <std_msgs/Float32.h>

class BinaryGA{
/*
    Implementation of a Simple Binary Genetic Algorithm. Inspired by:
    Jason Brownlee, Machine Learning Algorithms in Python, Machine Learning Mastery, 
    Available from https://machinelearningmastery.com/simple-genetic-algorithm-from-scratch-in-python/.
*/
    public:
        BinaryGA(std::string filePath, ros::NodeHandle *nh);
        ~BinaryGA();
        void splitParam(std::string line);
        void setInitPop();
        void run();
        double objective(int chrom[]);
        int selection(double* scores, int k);
        void crossover(int* p1, int* p2);
        void mutation(int* p);


    private:
        //std::string filePath_;
        int nIter_;
        int nBits_;
        int nPop_;
        double rCross_;
        double rMut_;
        int** pop_;
        double bestEval_;
        int* bestChrom_;

        ros::Publisher pub_;
};