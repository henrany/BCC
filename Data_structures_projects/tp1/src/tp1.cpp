#include"tp1.h"

// constructor to be used in the main
Rick::Rick(){
  _head = NULL;
  _tail = NULL;
  _container = 0;
  _count = 0;
}

//constructor for initializing the attributes
Rick::Rick(int container, int count){
  _head = NULL;
  _tail = NULL;
  _container = container;
  _count = count;
}

Node* Rick::get_head(){
  return _head;
}

Node* Rick::get_tail(){
  return _tail;
}

int Rick::get_container(){
  return _container;
}

int Rick::get_count(){
  return _count;
}

void Rick::set_container(int container){
  _container = container;
}

void Rick::set_head(Node *head){
  _head = head;
}

void Rick::set_tail(Node *tail){
  _tail = tail;
}

//function to get inert item into the list
//insertion is actually done at the end of the list
// time complexity of O(1)
void Rick::insert_container(int container){
  Node *temp = new Node();
  //getting the new container
  temp->data = container;
  temp->next = NULL;
  if(_head == NULL){
    //atualizing the head to point to the new node
    _head = temp;
    _tail = temp;
    _count++;
  }
  else{
    //inserting at the end of the list
    _tail->next = temp;
    _tail = _tail->next;
    _count++;
  }
  //std::cout<<_count<<std::endl;
}

//function where the insertion of the manipulated values are stored
//time complexity of O(n)
void Rick::insert_new_container(int container, int count){
  Node *temp = new Node();
  //getting the new container
  // and the counter
  temp->data = container;
  temp->count = count;
  temp->next = NULL;
  if(_head == NULL){
    //atualizing the head to point to the new node
    _head = temp;
    _tail = temp;
    _count++;
  }
  else{
    //inserting at the end of the list
    _tail->next = temp;
    _tail = _tail->next;
    _count++;
  }
}

//function to remove a specific node from the list
void Rick::remove_container(int container){
  //set if equal to the head

    Node *prev = _head;
    //when the data to be removed is the head 
    if(_head->data == container){//time complexity of O(1), when the item is at the head
      _head = prev->next;
      delete prev;
      _count--;
      //decrement the counter each time an item is removed;
      return ;
    }
    // setting the current to the beginning of the list
    Node *current = _head->next; 
    // run through the list 
    //time complexity of O(n), since we run through the whole list
    while(current!=NULL){ 
      if(current->data == container){
        //when  the item to be removed is at  the end of the list
        if(current == _tail){
          _tail = prev;
        }
        prev->next = current->next; 
        _count--;
        delete current;
        break;
      }
      // atualize the list
      prev = current;
      current = current->next;
    }
  }

   //time complexity of O(n^2)
  int Rick::operations(int container){
    //operation to get the alreadu created list
    Node *opera = new Node();
    opera = get_head();
    //variable for the manipulation of the list
    int quant,cnt;
    int sum = 0,sub = 0;
    //create a new list
    Rick measure = Rick();
    //insert nodes into the list
    //this list take 0 as the initial element of the list
    measure.insert_new_container(0,0);
    //new node to get the head of the new created list
    Node *measure_node = measure.get_head();
    for(int i=0;i<measure.get_count();i++){
      //initialize quant to the data in the new list
      quant = measure_node->data;
      //pass counter to count the steps
      cnt = measure_node->count;
      //a loop to get each container in the original list
      while (opera!=NULL){
        //addition and subtraction of values;
        sum = quant + opera->data;
        sub = quant - opera->data;
        //we insert the sum in the new list
        measure.insert_new_container(sum,cnt + 1);
        //not inserting if we get negative values
        if(sub>0){
          measure.insert_new_container(sub,cnt + 1);
        }
        //return when we get the desired operation
        if(sum == container || sub == container){
          //print out the minimum operation
          std::cout<<cnt + 1<<std::endl;
          //delete [] measure;
          return cnt + 1;
        }
        // next of the head
        opera = opera->next;
      }
      //starting again at the beginning of the list
      opera = get_head();
      measure_node = measure_node->next;
    }
    return 0;
  }

//para imprimir o que ta os resultados
void Rick::print(){
  Node *temp = new Node();
  temp = get_head();
  //time complexity of O(n)
  while(temp!=NULL){
    std::cout<<temp->data<<" ";
    temp = temp->next;
  }
}

//destructor for freeing the memory used to avoid memory leaks
Rick::~Rick(){
  Node* next = _head;
    Node* cur = NULL;
    //time complexity of O(n)
    while (next != NULL) {
        cur = next;
        next = next->next;
        delete cur;
    }      
}