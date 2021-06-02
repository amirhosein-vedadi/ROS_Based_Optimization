//#include "../include/optimization/BinaryGA.h"
#include "BinaryGA.h"
BinaryGA::BinaryGA(std::string file_path, ros::NodeHandle *nh){

    pub_ = nh->advertise<std_msgs::Float32>("/best_eval", 10); 

    //Read and split optimization parameters from file
    std::fstream file(file_path, std::fstream::in);
    if (!file.is_open()){
        std::cerr << "Error opening file" << std::endl;
        abort();
    }
    std::string line;
    while (std::getline(file, line)){
        this->splitParam(line);
    }
    file.close();

    srand (time(NULL));
}

void BinaryGA::splitParam(std::string line){
/*
    Split and set genetic algorithm parameters from input string.
*/
    int pos = line.find("=");
    std::string param = line.substr(0, pos);
    std::string value = line.substr(pos+1);

    if (param == "n-iter"){
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

void BinaryGA::setInitPop(){
    pop_ = new int*[nPop_]; 
    for (int i = 0; i < nPop_; ++i){
        pop_[i] = new int[nBits_];
        for (int j = 0; j < nBits_; ++j)
            pop_[i][j] = rand() % 2;
    }
}

int BinaryGA::selection(double* scores, int k=3){
/*
    Selection tournament function that returns randomly selected parent for next generation.
*/
    int selected_idx = rand() % nPop_;
    for (int i = 0; i < k-1; ++i){
        int idx = rand() % nPop_;
        if (scores[idx] < scores[selected_idx])
            selected_idx = idx;
    }
    return selected_idx;
}

double BinaryGA::objective(int chrom[]){
    double sum = 0;
    for (int i = 0; i < nBits_; ++i)
        sum += chrom[i];
    return -sum;
}

void BinaryGA::crossover(int* p1, int* p2){
/*
    Implementation of one point crossover operator
*/
    double r = ((double) rand() / (RAND_MAX));
    if (r < rCross_){
        int temp[nBits_];
        for (int i = 0; i < nBits_; ++i){
            temp[i] = p2[i];
        }
        int cros_pt = rand() % (nBits_ - 1) + 1;

        for (int i = cros_pt; i < nBits_; ++i){
            p2[i] = p1[i];
            p1[i] = temp[i];
        }

    }
}

void BinaryGA::mutation(int* p){
/*
    Implementation of mutation operator
*/
    for (int i = 0; i < nBits_; ++i){
        double r = ((double) rand() / (RAND_MAX));
        if(r < rMut_)
            p[i] = 1 - p[i];
    }
}

void BinaryGA::run(){
    this->setInitPop();
    int child[nPop_][nBits_];
    ros::Rate loop_rate(1);
    bestChrom_ = new int[nBits_];
    for (int k = 0; k < nBits_; ++k)
        bestChrom_[k] = pop_[0][k];
    bestEval_ = this->objective(pop_[0]);

    for (int gen_idx = 0; gen_idx < nIter_; ++gen_idx){
        //evaluate population scores
        double scores[nPop_];
        for (int i = 0; i < nPop_; ++i){
            scores[i] = this->objective(pop_[i]);
            if (scores[i] < bestEval_)
            {
                bestEval_ = scores[i];
                for (int k = 0; k < nBits_; ++k)
                    bestChrom_[k] = pop_[0][k];
            }
        }
        //selection tournament
        for (int j = 0; j < nPop_; ++j){
            int selected_idx = this->selection(scores);
            for (int k = 0; k < nBits_; ++k){
                child[j][k] = pop_[selected_idx][k];
            }
        }
        //crossover & mutation operator
        for (int i = 0; i < nPop_; i += 2){
            this->crossover(child[i], child[i+1]);
            this->mutation(child[i]);
            this->mutation(child[i+1]);
        }
        //new generation
        for (int j = 0; j < nPop_; ++j){
            for (int k = 0; k < nBits_; ++k){
                pop_[j][k] = child[j][k];
            }
        }
        loop_rate.sleep();
        std_msgs::Float32 new_msg;
        new_msg.data = bestEval_;
        pub_.publish(new_msg);
        
    }
}

BinaryGA::~BinaryGA(){
    for (int i = 0; i < nPop_; ++i){
        delete[] pop_[i];
    }
    delete[] pop_;
    delete[] bestChrom_;
}

int main(int argc, char* argv[])
{
    ros::init(argc, argv, "optimization_node");
    ros::NodeHandle nh;
    BinaryGA alg(argv[1], &nh);
    alg.run();
    ros::spin();
}

// int main(){
//     BinaryGA alg("GAInput.txt");
//     alg.run();
    //std::cout << r << std::endl;
    // for(int i=0; i < nBits_; i++)
    //     std::cout << child[0][i];
    // std::cout << std::endl;
    // this->mutation(child[0]);
    // for(int i=0; i < nBits_; i++)
    //     std::cout << child[0][i];
// }