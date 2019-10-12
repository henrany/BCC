#include<iostream>
#include<cmath>
#include<cstdlib>
#include "tp1.h"


int main(){
  Rick rick;
  int containers; // for each container to be entered
  std::string carac; //the caracter for whether we will be performing inclusion, exclusion or an operation
  //time complexity of O(n);
  while(std::cin>>containers>>carac){ //getting the user input for the program 
  //inclusion when we encounter the i caracter
    if(carac == "i"){
      rick.insert_container(containers);
    }
    //removing the container from the list when we enter r
    if(carac == "r"){
      rick.remove_container(containers);
    }
    //the getting the minimum number of operations when when we type p
    if(carac == "p"){
      rick.operations(containers);
    }
  }
  //rick.print();
  return 0;
}