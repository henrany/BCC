#include "tp2.hpp"

int main(int argc, char *argv[]){
    if(argc < 2){
        return 0;
    }
    int n,value;
    std::string line;
    std::ifstream file(argv[1]);
    if(file.is_open()){
        file>>n;
        Diamonds diamonds(n);
        for(int i=0;i<n;i++){
            file>>value;
            diamonds.addToVector(i,value);
        }
        auto t1 = std::chrono::high_resolution_clock::now();
        diamonds.print(n);
        auto t2 = std::chrono::high_resolution_clock::now();
        //Execution time of the program
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1 ).count();
        std::cout<<duration<<"\n";
        file.close();
    }
    else{
        std::cout<<"No file to be processed now\n";
    }
    return 0;
}