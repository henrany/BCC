#include "graph.hpp"

Graph::Graph(){
    this->nRow = 0;
    this->nCol = 0;
    this->numOfPlayers = 0;
    this->counter = 0;
}

Graph::Graph(int nRow, int nCol, int numOfPlayers){
    this->nRow = nRow;
    this->nCol = nCol;
    this->numOfPlayers = numOfPlayers;
    this->counter = 0;

    position = new int *[nRow];
    for (int i = 0; i < nRow; i++){
        position[i] = new int[nCol];
        for (int j = 0; j < nCol; j++){
            position[i][j] = 0;
        }
    }
    getMatrix = new int *[nRow];
    for (int i = 0; i < nRow; i++){
        getMatrix[i] = new int[nCol];
        for (int j = 0; j < nCol; j++){
            getMatrix[i][j] = 0;
        }
    }

    //initializing the vector with null values
    for (int i = 0; i < numOfPlayers; i++){
        players.push_back(std::make_pair(-1, std::make_pair(0, 'A' + i)));
    }
}

void Graph::addtoMatrix(int i, int j, int num){
    getMatrix[i][j] = num;
}

void Graph::addPlayers(int row, int col){
    position[row][col] = 1;
}

bool Graph::sortSecond(const std::pair<int,std::pair<double,char>> &a,const std::pair<int,std::pair<double,char>> &b){ 
    return (a.second.first < b.second.first);
}

void Graph::bfs(int nRow, int nCol){
    //do a bfs for all the players
    //O(n^2)
    for (int i = 0; i < numOfPlayers; i++){
        //values for start rows and columns
        int startRow = 0, endCol = 0;
        //getting the start row and end column
        for(int i=0;i<nRow;i++){
            bool broke = false;
            for(int j=0;j<nCol;j++){
                if(position[i][j] > 0){
                    position[i][j] = 0;
                    startRow = i;
                    endCol = j;
                    broke = true;
                    break;
                }
            }
            if(broke){
                break;
            }
        }
        //values for checking the number of layer and paths taken
        int count = 0, nodesLeftInLayer = 1, nodesInNextLayer = 0;
        //keeping track of every visited nodes
        bool **visited;
        //initialize the bool as false values;
        visited = new bool *[nRow];
        for (int i = 0; i < nRow; i++){
            visited[i] = new bool[nCol];
            for (int j = 0; j < nCol; j++){
                visited[i][j] = false;
            }
        }
        //two queues for tracking the row and columns visited;
        //this is done for efficiency reasons as compared to pair
        std::queue<int> qbR;
        std::queue<int> qbC;
        //initialized the start cell as visited;
        visited[startRow][endCol] = true;
        qbR.push(startRow);
        qbC.push(endCol);
         //get a counter for the all vertices visited
         double max = 0, cu=0,max1 = 0;
         //starting of bfs for the minimum distance
        while (!qbR.empty() || !qbC.empty()){
            //getting the first node of the queues
            cu++;
            int currentRow = qbR.front();
            int currentCol = qbC.front();
            qbR.pop();
            qbC.pop();
            //getting the value of the jump to be done inside the original matrix
            int currentElementNumber = getMatrix[currentRow][currentCol];
            max += currentElementNumber;
            //check whether we are at the end of the matrix
            if (currentRow == nRow - 1 && currentCol == nCol - 1){
                players[i].first = count;
                players[i].second.first = max/cu;
                counter++;
                break;
            }
            //moving downwards
            if (currentRow + currentElementNumber < nRow && visited[currentRow + currentElementNumber][currentCol] == false){
                qbR.push(currentRow + currentElementNumber);
                qbC.push(currentCol);
                visited[currentRow + currentElementNumber][currentCol] = true;
                nodesInNextLayer++;
            }
            //moving in the right direction
            if (currentCol + currentElementNumber < nCol && visited[currentRow][currentCol + currentElementNumber] == false){
                qbR.push(currentRow);
                qbC.push(currentCol + currentElementNumber);
                visited[currentRow][currentCol + currentElementNumber] = true;
                nodesInNextLayer++;
            }

            //moving to the left of the grid;
            if (currentCol - currentElementNumber >= 0 && visited[currentRow][currentCol - currentElementNumber] == false){
                qbR.push(currentRow);
                qbC.push(currentCol - currentElementNumber);
                visited[currentRow][currentCol - currentElementNumber] = true;
                nodesInNextLayer++;
            }

            //moving upwards
            if (currentRow - currentElementNumber >= 0 && visited[currentRow - currentElementNumber][currentCol] == false){
                qbR.push(currentRow - currentElementNumber);
                qbC.push(currentCol);
                visited[currentRow - currentElementNumber][currentCol] = true;
                nodesInNextLayer++;
            }
            nodesLeftInLayer--;
            //getting the movement taken
            if (nodesLeftInLayer == 0){
                nodesLeftInLayer = nodesInNextLayer;
                nodesInNextLayer = 0;
                count++;
            }
        }
        //freeing the allocated memory 
        delete[] visited; 
    }
}

void Graph::getWinner(){
    //sort all the players to get the minimum jumps in the first index
    //time complexity of O(nlogn)
    std::sort(players.begin(),players.end());
    //Remove all losers from the players list
    //time complexity of O(n);
    for(int i=numOfPlayers-1;~i;i--){
        if(players[i].first != players[0].first){
            players.pop_back();
        }
    }
    //in case of a draw
    //sort the max move since the one who reches first may have the least moves
    //time complexity O(nlogn)
    if(players[0].first == players[1].first){
        std::sort(players.begin(),players.end(),sortSecond);
        //remove players with the same max moves 
        //time complexity of O(n)
         for(int i=players.size()-1;~i;i--){
            if(players[i].second.first != players[0].second.first){
            players.pop_back();
            }
        }
    }


    //@Debug
    // for(int i=0;i<players.size();i++){
    //     std::cout<<players[i].first<<" "<<players[i].second.first<<" "<<players[i].second.second<<"\n";
    // }

    //when there is no winner, the counter will be zero
    if(counter<=0){
        std::cout<<"SEM VENCEDORES\n";
    }
    else{
        //what if the max moves is also an impact?
        //think of this one since it can give a very bad output?
        //it should get the last element since it the element closer to reaching first.
        std::cout<<players[players.size()-1].second.second<<"\n";
        std::cout<<players[players.size()-1].first<<"\n";
    }
}

Graph::~Graph(){
    //delete[] adjacencyMatrix;
    delete[] getMatrix;
    delete[] position;
    players.clear();
}