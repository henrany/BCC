#ifndef TP2_HPP
#define TP2_HPP
#include<bits/stdc++.h>

class Diamonds{
    private:
        int number;
        int *diaArray;
    public:
        Diamonds(int);
        void addToVector(int,int);
        int BruteForce(int n,int,int);
        int dynamicApproach(int n);
        void print(int);
        ~Diamonds();
};

#endif //TP2_HPP