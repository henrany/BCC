#include "graph.hpp"

int main(int argc, char *argv[]){
    if(argc < 2){
        return 0;
    }
    int rows=0,col=0,players=0, num=0;
    std::string line;
    std::ifstream file(argv[1]);
    if(file.is_open()){
        file>>rows>>col;
        file>>players;
        Graph graph(rows,col,players);
        for(int i=0;i<rows;i++){
            for(int j=0;j<col;j++){
                file>>num;
                graph.addtoMatrix(i,j,num);
            }
        }
        int nr=0,nc=0;
        auto t1 = std::chrono::high_resolution_clock::now();
        for(int i=0;i<players;i++){
            file>>nr>>nc;
            graph.bfs(nr,nc,i);
        }
        // graph.bfs(rows,col);
        graph.getWinner();
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