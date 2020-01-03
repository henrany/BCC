#include"tp2.h"
#include<iostream>
#include<cstdio>
#include<string>
#include<cstdlib>

int main(){
    //calling the function created
    Rick rick;
    int time, planet,length;
    //asking for user input
    std::cin>>time>>planet>>length;
    visit vec[planet];
    //add to vector
    rick.add_visit(vec,planet);
    //sort the time and assign them to months
    rick.sort_visit(vec,planet,time);
    //sort individual alphabets
    rick.radix_sort(vec,planet,length);
    //sort the months
    rick.insertion_sort(vec,planet);
    rick.print(vec,planet);
    return 0;
}