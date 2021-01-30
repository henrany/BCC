#include<bits/stdc++.h>
#include <unistd.h>
#include<pthread.h>
int cnt;
bool rajActive = false;
int reset;
int rajCounter = 0;
pthread_mutex_t wantOven = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t useOven = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t usingOven = PTHREAD_COND_INITIALIZER;

std::vector<int> waitingList; // for getting the users who wants to use the oven 
std::list<int> finishedUsingOven; // finished using the oven
std::list<int> work; // when they are done eating

std::string persons(int n){
    switch (n){
    case 1: return "Sheldon";
    case 2: return "Amy";
    case 3: return "Howard";
    case 4: return "Bernadette";
    case 5: return "Leonard";
    case 6: return "Penny";
    case 7: return "Stuart";
    case 8: return "Kripke";
    default: return "";
    }
}

int randomVal(int min, int max){
    int randomSleep = min + rand() % max;
    return randomSleep;
}

bool isOnDeadlockList(int id){
    std::vector<int>::iterator it;
    it = std::find (waitingList.begin(), waitingList.end(), id);
    if (it == waitingList.end()){
        return false;
    }else{
        return true;
    }
}

bool marriedDeadlock(){
    return ((isOnDeadlockList(1) && isOnDeadlockList(2)) && (isOnDeadlockList(3) && isOnDeadlockList(4)) &&
        (isOnDeadlockList(5) && isOnDeadlockList(6)));
}

bool singlePersonDeadlock(){
    return (isOnDeadlockList(1) || isOnDeadlockList(2)) && (isOnDeadlockList(3) || isOnDeadlockList(4)) &&
           (isOnDeadlockList(5) || isOnDeadlockList(6));
}

bool hasMarriedCouple(){
     return ((isOnDeadlockList(1) && isOnDeadlockList(2)) || (isOnDeadlockList(3) && isOnDeadlockList(4)) ||
    (isOnDeadlockList(5) && isOnDeadlockList(6)));
}

bool hasDeadLock(){
    if(marriedDeadlock()){
        return true;
    }
    else if(singlePersonDeadlock() && !hasMarriedCouple()){
        return true;
    }
    else{
        return false;
    }
}

void deleteFromWaitingList(int n){
    std::vector<int>::iterator it;
    it = std::find(waitingList.begin(),waitingList.end(),n);
    if(it != waitingList.end()){
        waitingList.erase(it);
    }
}

int findMin(){
    int minElement = *std::min_element(waitingList.begin(), waitingList.end());
    return minElement;
}

void insertIntoWaitingList(int n){
    waitingList.push_back(n);
}

//get the priority of the person to use the oven
int getPriority(){
    int element = 0;
    //check if there is only  one person waiting to use oven
    //if so, then that person can use the oven
    //if not, get the person with higher priority
    if(waitingList.size() > 1){
        if(waitingList[0] == 5 || waitingList[0] == 6){
            element = waitingList[0];
        }else{
        element = findMin();
        }
    }else{
        element = waitingList[0];
    }
    return element;
}

int resetPriority(int n){
    std::cout<<"Raj detectou um deadlock, liberando "<<persons(n)<<"\n";
    return n;
}

void getPerson(int n){
    pthread_mutex_lock(&wantOven);
    insertIntoWaitingList(n);
    std::cout<<persons(n)<<" quer usar o forno\n";
    pthread_mutex_unlock(&wantOven);
}

void heatSomething(int n){
    pthread_mutex_lock(&wantOven);
    std::cout<<persons(n)<<" começa a esquentar algo\n";
    pthread_mutex_unlock(&wantOven);
    sleep(1);
}

void getNextToHeat(){
    int n = 0;
    //if waiting list is 0 , wait for more users 
    n = getPriority();
    while(waitingList.size() == 0){
        if (rajActive){
            n = reset;
            reset = 0;
            break;
        }
        pthread_cond_wait(&usingOven, &wantOven);
    }
    deleteFromWaitingList(n);
    finishedUsingOven.push_back(n);
    work.push_back(n);
    heatSomething(n);
}

void eat(){
    int n = finishedUsingOven.front();
    finishedUsingOven.pop_front();
    std::cout<<persons(n)<<" vai comer\n";
    sleep(randomVal(3,6));
}

void goToWork(){
    int n = work.front();
    work.pop_front();
    std::cout<<persons(n)<<" voltou para o trabalho\n";
    sleep(randomVal(3,6));
}

void *runner(void *params){
    int n =*reinterpret_cast<int*>(params);
    for(int i=0;i<cnt;i++){
        getPerson(n);
        pthread_mutex_lock(&useOven);
        getNextToHeat();
        pthread_mutex_unlock(&useOven);
        pthread_cond_signal(&usingOven);
        eat();
        goToWork();
    }
    rajCounter++;
    pthread_exit(NULL);
}

void *rajDetect(void *params){
    int n = *reinterpret_cast<int*>(params);
    int randomUser = randomVal(1,6);
    while(rajCounter < n){
        sleep(5);
        if(!rajActive && hasDeadLock()){
            rajActive = true;
            reset = resetPriority(randomUser);
            pthread_cond_broadcast(&usingOven);
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){

    if(argc != 2){
       fprintf(stderr,"usage: %s",argv[0]);
    }

    cnt = std::stoi(argv[1]);
    int num = 8;
    srand(time(NULL));
    pthread_t threads[8];
    pthread_t rajThread;
    pthread_mutex_init(&wantOven,NULL);
    pthread_mutex_init(&useOven,NULL);
    pthread_cond_init(&usingOven,NULL);
    std::vector<int> threadList;
    for(int i=0;i<8;i++){
        threadList.push_back(i+1);
    }

    for(int i=0;i<8;i++){
        pthread_create(&threads[i],NULL,runner,&threadList[i]);
    }
    pthread_create(&rajThread,NULL,rajDetect,&num);

    for(int i=0;i<8;i++){
        pthread_join(threads[i],NULL);
    }
    pthread_join(rajThread,NULL);
    pthread_mutex_destroy(&wantOven);
    pthread_mutex_destroy(&useOven);
    pthread_cond_destroy(&usingOven);
}