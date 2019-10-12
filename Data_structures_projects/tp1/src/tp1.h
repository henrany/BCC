#ifndef TP1_H
#define TP1_H
#include<iostream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include<cmath>

//struct node for the data, next and count 
struct Node{
    Node *next;
    int data;
    int count;
};

class Rick{
    private:
    Node *_head; 
    Node *_tail;
    int _count;
    int _container;

    public:
    Rick();
    Rick(int container,int count);
    Node *get_head();//getting the head of th list
    Node *get_tail();//getting the tail of the list
    int get_container();//the containers to be used
    int get_count(); // getting the total number of insertion
    void set_container(int container);//setting the container
    void set_head(Node* head);
    void set_tail(Node* tail);
    void insert_container(int container);//funciton to create a new list
    void insert_new_container(int container, int count); //the function for the insertion of containers
    void remove_container(int container); //funciton for the removal of a container from the list
    int operations(int container); // function for th minimum operation
    void print();//function to print the list
    ~Rick();//destructor to free the memory
};

#endif//TP1_H