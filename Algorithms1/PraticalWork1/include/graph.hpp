#ifndef GRAPH_H
#define GRAPH_H

#include<bits/stdc++.h>

class Graph {
  private:
      int nRow;
      int nCol;
      int numOfPlayers;
      //checking if a winner was found;
      int counter;
      int **getMatrix;
      //vector for all the players score, max step and also the the player tag
      std::vector<std::pair<long long, std::pair<double, char>>> players;
  public:
      Graph();
      Graph(int ,int,int);
      //function to get the grid entries
      void addtoMatrix(int, int,int);
      //sort of the average moves made to reach the end point
      static bool sortSecond(const std::pair<int,std::pair<double,char>>&,const std::pair<int,std::pair<double,char>>&);
      //a breadth first search for every player
      void bfs(int,int,int);
      //function for getting the winner
      void getWinner();
      ~Graph();
};
#endif //TP_1