#include <iostream>
#include <typeinfo>

template <typename T>
class Stack
{   
    protected:
        int maxSize;
        T *array;

    public:
        int lastPoint;
                
    Stack(T typeData, int maxSize){
        this -> maxSize = maxSize;
        this -> array = new T[maxSize];
        this -> lastPoint = -1;
    }

    ~Stack(){
        delete [] array;
    }

    void push(T data){

        if(getLastPoint() + 1 < getMaxSize())
        {
            setLastPoint(false);
            array[getLastPoint()] = data;
        }
    }

    T pop(){
        
        if(lastPoint < 0)
        {
            throw;
        }

        T delItm;
        delItm = array[getLastPoint()];

        setLastPoint(true);

        return delItm;

        
    }

    void setLastPoint(bool minus){

        if(lastPoint == 0 && minus) return;

        lastPoint = lastPoint > 0 && minus ? lastPoint-1 : lastPoint+1; 

    }

    int getLastPoint(){

        return lastPoint;

    }

    int getMaxSize(){

        return maxSize;

    }

};

// Now main is using for tests

int main()
{

    // Stack stk(1, 4);
    // //Stack arr("s", 3);

    // stk.push(1);
    // stk.push(2);
    // stk.push(8);
    // stk.push(4);

    // std::cout << stk.pop() << std::endl
    //             << stk.pop() << std::endl
    //             << stk.pop() << std::endl
    //             << stk.pop() << std::endl;

}