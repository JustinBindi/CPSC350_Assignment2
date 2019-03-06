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
  bool loop2 = true;
  bool loop3 = true;
  GameLife game(256);
  string printControl;
  string mode;
  string outputFileName;

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
    fileName = "GenerationStart.txt";
  }
  if (config == "F" || config == "f")
  {
    cout << "Name of File?" << endl;
    cin >> fileName;
  }

  cout << "Do you want to go through generations with a pause, by pressing enter, or output to a file" << endl;
  cout << "Type 'P' for pause, 'E' for enter, and 'F' for file" << endl;
  cin >> printControl;
  while (loop2)
  {
    if (printControl == "P" || printControl == "p" || printControl == "F" || printControl == "f" || printControl == "E" || printControl == "e" )
    {
      if (printControl == "f" || printControl == "F")
      {
        cout << "What is the name of the file that you want to output your results to?" << endl;
        cin >> outputFileName;
      }
      loop2 = false;
    }
    else
    {
      cout << "Invalid Input. Please try again." << endl;
      cin >> printControl;
    }
  }

  cout << "What boundary mode do you want to run in?" << endl;
  cout << "Type 'C' for classicMode, 'D' for DoughNutMode, and 'M' for MirrorMode" << endl;
  cin >> mode;
  while (loop3)
  {
    if (mode == "C" || mode == "c" || mode == "D" || mode == "d" || mode == "M" || mode == "m" )
    {
      loop3 = false;
    }
    else
    {
      cout << "Invalid Input. Please try again." << endl;
      cin >> mode;
    }
  }

  if (mode == "c" || mode == "C")
  {
    game.getLineLength(fileName);
    game.readFile(fileName);
    game.printGen0(printControl);
    game.ClassicMode(printControl, outputFileName);
  }

  if (mode == "d" || mode == "D")
  {
    game.getLineLength(fileName);
    game.readFile(fileName);
    game.printGen0(printControl);
    game.DoughNutMode(printControl, outputFileName);
  }

  if (mode == "m" || mode == "M")
  {
    game.getLineLength(fileName);
    game.readFile(fileName);
    game.printGen0(printControl);
    game.MirrorMode(printControl, outputFileName);
  }

  // = argv[1]; //Takes in a user command line argument and
                              // uses it for the name of the file for reading.




  return 0;
};
