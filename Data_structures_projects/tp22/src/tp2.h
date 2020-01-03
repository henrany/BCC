#ifndef TP2_H
#define TP2_H

#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>

struct visit{
    int count = 1;
    int time;
    std::string name;
};

class Rick{
    public:
    Rick();
    void add_visit(visit vec[], int n);
    void merge(visit vec[], int beg,int mid, int end);
    void merge_sort(visit vec[], int beg, int end);
    void radix_sort(visit vec[],int n, int length);
    void insertion_sort(visit vec[], int n);
    void sort_visit(visit vec[], int n, int tot_time);
    void print(visit vec[], int n);
    ~Rick();
};

#endif //TP2_H