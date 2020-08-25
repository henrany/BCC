#include "graph.hpp"

Graph::Graph(){
    this->nRow = 0;
    this->nCol = 0;
    this->numOfPlayers = 0;
}

Graph::Graph(int nRow, int nCol, int numOfPlayers){
    this->nRow = nRow;
    this->nCol = nCol;
    this->numOfPlayers = numOfPlayers;

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
}

// int Graph::getNRow(){
//     return this->nRow;
// }

// int Graph::getNCol(){
//     return this->nCol;
// }

// int Graph::getNumOfPlayers(){
//     return this->numOfPlayers;
// }

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
    //vector for all the values;
    std::vector<std::pair<int, std::pair<double, char>>> players;
    //initializing the vector with null values
    int c=0;
    for (int i = 0; i < numOfPlayers; i++){
        players.push_back(std::make_pair(-1, std::make_pair(0, 'A' + i)));
    }
    //do a bfs for all the players
    for (int i = 0; i < numOfPlayers; i++){
        //values for start rows and columns
        int startRow = 0, endCol = 0;
        //getting the start and end row
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
        //initialize the bool as null values;
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
        //if we've reached an answer;
        bool reached = false;
        //initialized the start cell as visited;
        visited[startRow][endCol] = true;
        qbR.push(startRow);
        qbC.push(endCol);
         //get a counter for the all vertices visited
         double max = 0, cu=0;
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
                reached = true;
                c++;
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
            //moving upwards
            if (currentRow - currentElementNumber >= 0 && visited[currentRow - currentElementNumber][currentCol] == false){
                qbR.push(currentRow - currentElementNumber);
                qbC.push(currentCol);
                visited[currentRow - currentElementNumber][currentCol] = true;
                nodesInNextLayer++;
            }
            //moving to the left of the grid;
            if (currentCol - currentElementNumber >= 0 && visited[currentRow][currentCol - currentElementNumber] == false){
                qbR.push(currentRow);
                qbC.push(currentCol - currentElementNumber);
                visited[currentRow][currentCol - currentElementNumber] = true;
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
        delete[] visited; 
    }
    std::sort(players.begin(),players.end());
    if(players[0].first == players[1].first){
        std::sort(players.begin(),players.end(),sortSecond);
    }
    if(c <=0){
        std::cout<<"SEM VENCEDORES\n";
    }
    else{
        std::cout<<players[0].second.second<<"\n";
        std::cout<<players[0].first<<"\n";
    }
}

Graph::~Graph(){
    //delete[] adjacencyMatrix;
    delete[] getMatrix;
    delete[] position;
}