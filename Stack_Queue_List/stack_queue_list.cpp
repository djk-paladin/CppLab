#include <iostream>
#include <typeinfo>

template <typename T>
class Stack
{   
    protected:
        int maxSize;
        T *array;
        int lastPoint;

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

        ~Stack(){
            delete [] array;
        }

    public:
        
                
    Stack(T typeData, int maxSize){
        this -> maxSize = maxSize;
        this -> array = new T[maxSize];
        this -> lastPoint = -1;
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

};

template <typename T>
class Queue
{

    protected:

        int maxSize;
        T *array;
        //bool firstAdd;
        int point;

        void shiftPoint(){
            for(int i = 0; i < point - 1; i++)
            {
                array[i] = array[i+1];
            }
        }

        void setPoint(bool next){

            if(next)
            {
                point ++;
            }
            else
            {
                point --;
            }

        }

    public:

        Queue(int size){
            this -> maxSize = size;
            //this -> firstAdd = true;
            this -> point = 0;
            this -> array = new T[maxSize];
        }

        bool isFull(){

            bool checkFull = point >= maxSize;
            return checkFull;

        }

        bool isEmpty(){

            bool chekEmpty = point <=0;
            return chekEmpty;
        }

        int size(){

            if(!isEmpty)
            {
                return point-1;
            }
            else{
                throw "array is empty!";
            }

        }

        void enqueu(T data){
            // if(firstAdd)
            // {

            //     array = new T[maxSize];

            //     firstAdd = false;

            // }

            if(!isFull())
            {

                array[point] = data;
                setPoint(true);

            }
            else{
                throw "array is full!";
            }

        }

        void dequeue(){

            if(!isEmpty())
            {
                shiftPoint();
                setPoint(false);
            }
            else
            {
                throw "array is empty!";
            }

        }

        T peek(){

            if(!isEmpty())
            {
                return array[0];
            }
            else{
                throw "array is empty!";
            }

        }

};


// Now main is using for tests

int main()
{

    //test for Queue

    Queue<int> qut(4);

    for(int i = 1; i <= 4; i++)
    {
        try
        {
            std::cout << "is emty?" << qut.isEmpty() << std::endl;
            qut.enqueu(i);
            std::cout << "added " << i << std::endl;
            std::cout << "is full?" << qut.isFull() << std::endl;
        }
        catch(const char* e)
        {
            std::cerr << e << '\n';
        }
    }

    for(int i = 1; i <= 4; i++)
    {
        try
        {
            std::cout << "must dequed " << qut.peek() << std::endl;
            qut.dequeue();
        }
        catch(const char* e)
        {
            std::cerr << e << '\n';
        }
        
        
    }

}