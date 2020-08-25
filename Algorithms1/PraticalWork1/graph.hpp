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
      int **position;
      //vector for all the players score, max step and also the the player tag
      std::vector<std::pair<int, std::pair<double, char>>> players;
  public:
      Graph();
      Graph(int ,int,int);
      void addtoMatrix(int, int,int);
      void addPlayers(int,int);
      static bool sortSecond(const std::pair<int,std::pair<double,char>>&,const std::pair<int,std::pair<double,char>>&);
      void bfs(int,int);
      void getWinner();
      ~Graph();
};
#endif //TP_1