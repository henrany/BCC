#include "tp2.hpp"

Diamonds::Diamonds(int number){
    this->number = number;
    //initialize the array
    diaArray = new int[number];
    for (int i = 0; i < number; i++){
        diaArray[i] = 0;
    }
}

void Diamonds::addToVector(int index, int value){
    diaArray[index] = value;
}

int Diamonds::BruteForce(int n, int set1, int set2){
    // if list becomes empty, return the absolute
    // difference between two partitions
    if (n < 0){
        return std::abs(set1 - set2);
    }
    // include current item in the subset S1 and do recursion
    // for the remaining items (n - 1)
    int inc = BruteForce(n - 1, set1 + diaArray[n], set2);
    // exclude current item from subset S1 and do recursion
    // for the remaining items (n - 1)
    int exc = BruteForce(n - 1, set1, set2 + diaArray[n]);
    //return the minimum between them
    return std::min(inc, exc);
}

int Diamonds::dynamicApproach(int n){
    // get sum of all the weights
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum += diaArray[i];
    }
    // create a boolean table to store solutions of sub-problems
    bool lookUp[n + 1][sum + 1];
    for (int i = 0; i < n + 1; i++){
        for (int j = 0; j < sum + 1; j++){
            lookUp[i][j] = false;
        }
    }
    // by using the bottom up approach
    for (int i = 0; i <= n; i++){
        //true when elements have sum of 0
        lookUp[i][0] = true;
        for (int j = 1; i > 0 && j <= sum; j++){
            // remove the element from the lookup array
            lookUp[i][j] = lookUp[i - 1][j];
            // include the element in the lookup array 
            if (diaArray[i - 1] <= j){
                //this is done by using bitwise or
                lookUp[i][j] |= lookUp[i - 1][j - diaArray[i - 1]];
            }
        }
    }
    // Find maximum value of j between 0 and sum/2 for which last row is true
    int j = sum / 2;
    while (j >= 0 && !lookUp[n][j]){
        j--;
    }
    return sum - 2 * j;
}

void Diamonds::print(int n){
    std::cout << dynamicApproach(n) << "\n";
    //@Debug
    // for(int i=0;i<n;i++){
    //     std::cout<<diaArray[i]<<" ";
    // }
    // std::cout<<"\n";
}

Diamonds::~Diamonds(){
    delete diaArray;
}
