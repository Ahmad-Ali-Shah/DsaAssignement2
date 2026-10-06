#include<iostream>
using namespace std;


template <class Type>
class queueType 
{

    //////////////////////////////

    // Array

    //////////////////////////////


    Type* circularArray;

    int maxSize;

    int queueFront;

    int queueRear;

    int count;

public:

 void initializeQueue(){
  
    queueFront = -1;

    queueRear = -1;

    count = 0;

 } // make the queue empty

 bool isEmptyQueue() const{

    return count==0;

 }

 bool isFullQueue() const{

    return (count==maxSize);

 }

 Type front() const{

    if(isEmptyQueue()){

        cout<<"[Empty Queue] \n";

        return Type();
         // it returns a generic type 
    }

    return circularArray[queueFront];

 } // queue must not be empty

 Type back() const{

    if(isEmptyQueue()){

        cout<<"[Empty Queue] \n";

        return Type(); // it returns a generic type

    }
    
    return circularArray[queueRear];

 } // queue must not be empty

 void addQueue(const Type& queueElement){

    if(isFullQueue()){

        cout<<"[Queue is Full]\n";

        return;

    }

    // first add then move circularly
    if(isEmptyQueue()){
        queueFront = 0;
        queueRear = 0;
    }
    else{
        queueRear = (queueRear + 1) % maxSize;
    }

    this->circularArray[queueRear] = queueElement;

    count++;

 }

 void deleteQueue(){

    // queue must not be empty

    if(isEmptyQueue()){

        cout<<"[QUEUE IS EMPTY GNG]\n";

        return;

    }

    // else move front 
    count--;

    if(count == 0){
        queueFront = -1;
        queueRear = -1;
    }
    else{
        queueFront = (queueFront + 1) % maxSize;
    }

 }

 int size() const{

    return count; // return the current number of elements

 }

 int capacity() const{

    return maxSize; // return the max capacity of the array

 }

 // Read-only function to inspect element at logical position (0 = front, count-1 = back)
 Type getAt(int index) const{
    if(index < 0 || index >= count){
        return Type();
    }
    int actualIndex = (queueFront + index) % maxSize;
    return circularArray[actualIndex];
 }

 // Read-only function to display all queue elements from front to rear
 void print() const{
    if(isEmptyQueue()){
        cout<<"[Empty Queue]\n";
        return;
    }
    for(int i = 0; i < count; i++){
        int actualIndex = (queueFront + i) % maxSize;
        cout << circularArray[actualIndex] << " ";
    }
    cout << "\n";
 }

 queueType(int queueSize = 100){
    //////////////////////////////

    // initializing all values of queue

    /////////////////////////////////

    this->maxSize = queueSize;

    if(maxSize<=0){

        maxSize = 100; // same as stack

    }

    ////////////////////////////

    // initially both front and rear be at -1

    ////////////////////////////////

    queueFront = -1;
    queueRear = -1;
    count = 0;

    circularArray = new Type[maxSize];
 }

 ~queueType(){
    delete[] circularArray;
    circularArray = nullptr;
 }

 queueType(const queueType<Type>& otherQueue){

    this->maxSize = otherQueue.maxSize;

    this->count = otherQueue.count;

    this->queueFront = otherQueue.queueFront;

    this->queueRear = otherQueue.queueRear;

    this->circularArray = new Type[this->maxSize];

    for(int i = 0; i < this->maxSize; i++){

        this->circularArray[i] = otherQueue.circularArray[i];

    }

 }

 const queueType<Type>& operator=(const queueType<Type>& otherQueue){
    if(this != &otherQueue){
    
        delete[] this->circularArray;

        this->maxSize = otherQueue.maxSize;

        this->count = otherQueue.count;

        this->queueFront = otherQueue.queueFront;

        this->queueRear = otherQueue.queueRear;

        this->circularArray = new Type[this->maxSize];

        for(int i = 0; i < this->maxSize; i++){

            this->circularArray[i] = otherQueue.circularArray[i];

        }
    }
    
    return *this;
 }
};