#include <iostream>

using namespace std;

class GameLife
{
  public:
    GameLife();//constructor
    GameLife(int maxSize);//overloaded constructor
    ~GameLife();//destructor

    //void push(char d);
    void readFile();
    //char peek();//aka top()

    int getSize();
    bool isEmpty();
    bool isFull();

    char ch;
    int countChar;

    char *myArray;
};
