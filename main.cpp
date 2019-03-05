//#include "GameLife.h"
#include "GameLife.cpp"
#include <iostream>

using namespace std;

int main (int argc, char **argv)
{
  string fileName;
  string config;
  int dim1;
  int dim2;
  float density;
  bool loop = true;
  GameLife game(256);

  cout << "Random configuration Or a Flat-File configuration?" << endl;
  cout << "Type 'R' for random and 'F' for flat-file" << endl;
  cin >> config;
  while (loop)
  {
    if (config == "R" || config == "r" || config == "F" || config == "f")
    {
      loop = false;
    }
    else
    {
      cout << "Invalid Input. Please try again." << endl;
      cin >> config;
    }
  }
  if (config == "r" || config == "R")
  {
    cout << "Enter 1st Dimension of World:" << endl;
    cin >> dim1;
    cout << "Enter 2nd Dimension of World:" << endl;
    cin >> dim2;
    cout << "Enter Density of Population (between 0 and 1):" << endl;
    cin >> density;
    cout << dim1 << dim2 << density<< endl;
    game.RandomGrid(dim1,dim2,density);
  }
  if (config == "F" || config == "f")
  {
    cout << "Name of File?" << endl;
    cin >> fileName;
  }
  // = argv[1]; //Takes in a user command line argument and
                              // uses it for the name of the file for reading.

  game.getLineLength(fileName);
  game.readFile(fileName);
  game.printGen0();
  game.MirrorMode();


  return 0;
}
