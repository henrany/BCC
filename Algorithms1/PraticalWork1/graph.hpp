#ifndef GRAPH_H
#define GRAPH_H

#include<bits/stdc++.h>

class Graph {
  private:
      int nRow;
      int nCol;
      int numOfPlayers;
      int **getMatrix;
      int **position;
  public:
      Graph();
      Graph(int ,int,int);
    //   int getNRow();
    //   int getNCol();
    //   int getNumOfPlayers();
      void addtoMatrix(int, int,int);
      void addPlayers(int,int);
      static bool sortSecond(const std::pair<int,std::pair<double,char>>&,const std::pair<int,std::pair<double,char>>&);
      void bfs(int,int);
      void play(int,int);
      ~Graph();
};
#endif //TP_1