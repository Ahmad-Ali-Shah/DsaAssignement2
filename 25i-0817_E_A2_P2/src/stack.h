#pragma once
#include <iostream>
using namespace std;

template <class Type>
class stackType 
{


    //implementing array wise


Type* array;
int maxStackSize;
int stackTop;

public:
void initializeStack(){
    stackTop = 0;
    // you just put the starting index as 0

} // make the stack empty

bool isEmptyStack() const{

    if(stackTop<=0){

        cout<<"[empty]\n";
        return true;
    }
    return false;
}

bool isFullStack() const{

    if(stackTop>= maxStackSize){
        cout<<"[Stack is Full]\n";
        return true;   
    }
    else{
        cout<<"[There is Space]\n";
        return false;
    }
}

void push(const Type& newItem){
    

    // making that dynamic stack via array 


    if (isFullStack()) {
        

        int newSize = maxStackSize * 2; 

        Type* newArray = new Type[newSize];

        for (int i = 0; i < stackTop; i++) {

            newArray[i] = array[i];

        }

        delete[] array;

        array = newArray;

        maxStackSize = newSize;

    }

    array[stackTop] = newItem;

    stackTop++;
}

Type top() const{

    if(isEmptyStack()){

        cout<<"[Empty Stack]\n";

        return Type();// return default value for only that case

    }

    else{

        return array[stackTop - 1];

    }
}

void pop(){
    if(stackTop<=0){
        /////////////////////////////////////

        // since its gui and console base so cout else no needed

        /////////////////////////////////////////


        cout<<"[Stack Underflow]\n";
        stackTop = 0;
    }
    else{
        stackTop--;
    }
}

int size() const{
    return this->stackTop;
}

Type getAt(int index) const{
    if(index < 0 || index >= stackTop){
        return Type();
    }
    return array[index];
}

void print() const{
    if(isEmptyStack()){
        cout<<"[Empty Stack]\n";
        return;
    }
    for(int i = stackTop - 1; i >= 0; i--){
        cout<<array[i]<<" ";
    }
    cout<<"\n";
}


    // Phase 2: Memory-Aware History bottom eviction (Section 7.1)
    Type removeBottom() {
        if (stackTop <= 0) {
            return Type();
        }
        Type bottomVal = array[0];
        for (int i = 1; i < stackTop; i++) {
            array[i - 1] = array[i];
        }
        stackTop--;
        return bottomVal;
    }

    // Phase 2: Batched Push Operation (Section 7.4)
    void pushBatch(const Type items[], int n) {
        if (n <= 0 || !items) return;
        if (stackTop + n > maxStackSize) {
            int newSize = maxStackSize * 2;
            if (newSize < stackTop + n) {
                newSize = stackTop + n + 10;
            }
            Type* newArray = new Type[newSize];
            for (int i = 0; i < stackTop; i++) {
                newArray[i] = array[i];
            }
            delete[] array;
            array = newArray;
            maxStackSize = newSize;
        }
        for (int i = 0; i < n; i++) {
            array[stackTop + i] = items[i];
        }
        stackTop += n;
    }

    // Phase 2: Batched Pop Operation (Section 7.4)
    void popBatch(int n) {
        if (n <= 0) return;
        if (n >= stackTop) {
            stackTop = 0;
        } else {
            stackTop -= n;
        }
    }

stackType(int stackSize = 100){
    if (stackSize <= 0)
        stackSize = 100; // for 0 its default 100

    this->maxStackSize = stackSize;

    array = new Type[stackSize];

    stackTop = 0;

}

~stackType(){
    delete[] array;
    array = nullptr;
}

stackType(const stackType<Type>& otherStack){ 

    this->maxStackSize = otherStack.maxStackSize;

    this->stackTop = otherStack.stackTop;

    this->array = new Type[this->maxStackSize];

    for(int i = 0; i < this->stackTop; i++){

        this->array[i] = otherStack.array[i];

    }

}

const stackType<Type>& operator=(const stackType<Type>& otherStack){
    
    if(this != &otherStack){ // different objects

        delete[] this->array;

        this->maxStackSize = otherStack.maxStackSize;

        this->stackTop = otherStack.stackTop;

        this->array = new Type[this->maxStackSize];

        for(int i = 0; i < this->stackTop; i++){

            this->array[i] = otherStack.array[i];

        }

    }

    return *this;

    // copy constructor by = value 
}

};
