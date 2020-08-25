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
        for(int i=0;i<players;i++){
            file>>nr>>nc;
            graph.addPlayers(nr,nc);
        }
        std::string show;
        show = "S";
        auto t1 = std::chrono::high_resolution_clock::now();
        graph.bfs(rows,col);
        auto t2 = std::chrono::high_resolution_clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
        //std::cout<<duration<<"\n";
        file.close();
    }
    return 0;
}