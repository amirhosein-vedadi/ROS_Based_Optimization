#include "../include/optimization/BinaryGA.h"

BinaryGA::BinaryGA(std::string file_path){
    //Read and split optimization parameters from file
    std::fstream file(file_path, std::fstream::in);
    if(!file.is_open()){
        std::cerr << "Error opening file" << std::endl;
    }
    std::string line;
    while(std::getline(file, line)){
        this->splitParam(line);
    }
    file.close();
}

void BinaryGA::splitParam(std::string line){

    int pos = line.find("=");
    std::string param = line.substr(0, pos);
    std::string value = line.substr(pos+1);

    if(param == "n-iter"){
        nIter_ = std::stoi(value);
    }else if (param == "n-bits")
    {
        nBits_ = std::stoi(value);
    }else if (param == "n-pop")
    {
        nPop_ = std::stoi(value);
    }else if (param == "r-cross")
    {
        rCross_ = std::stod(value);
    }else if (param == "r-mut")
    {
        rMut_ = std::stod(value);
    }
}

int main(){
    srand (time(NULL));
    int iSecret = rand();
    std::string binary = "0101111";
    BinaryGA alg("GAInput.txt");
    //std::cout << binary;
}