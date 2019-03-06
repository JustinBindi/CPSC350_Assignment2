#include "GameLife.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <unistd.h>

using namespace std;
vector<char> vectorGrid;
int generationCount = 0;
string output;

GameLife::GameLife()//default constructor
{
  ch = '\0';
  countChar = 0;
  fileName = "";
  generationCount = 0;
};

GameLife::GameLife(int maxSize)//overloaded constructor
{
  ch = '\0';
  countChar = 0;
  fileName = "";
  generationCount = 0;
};

//Gets the length of a row in the first generation.
int GameLife::getLineLength(string fileName)
{
  lineLength = 0;
  ifstream myFileLength (fileName);
  while(myFileLength.get(ch))
  {
    if (ch == '-' || ch == 'X' || ch == 'x')
    {
      getline(myFileLength, line);
      lineLength = line.length()+1;
    }
  }
  myFileLength.close();
  return lineLength;
};

//Reads the first generation into a vector.
int GameLife::readFile(string fileName)
{
  countChar = 0;
  vectorGrid.clear();

  ifstream myFile (fileName);

  while(myFile.get(ch))
  {
    if (ch == '-' || ch == 'X' || ch == 'x')
    {
      countChar++;
      vectorGrid.push_back(ch);
    }
  }
  for (int i = 0; i < lineLength; i++)
  {
    vectorGrid.insert(vectorGrid.begin(),'~');
    vectorGrid.push_back('~');
  }
  countChar+=lineLength*2;

  for (int i = lineLength; i < countChar; i+=lineLength+2)
  {
    vectorGrid.insert(vectorGrid.begin()+i,'~');
    vectorGrid.insert(vectorGrid.begin()+i,'~');
    countChar+=2;
  }

  vectorGrid.insert(vectorGrid.begin(),'~');
  vectorGrid.push_back('~');
  countChar+=2;
  myFile.close();
  return 0;
};

//Prints the first generation to one of the three mediums depending on user input.
int GameLife::printGen0(string printControl)
{
  char* array = &vectorGrid[0];
  charCounter = 0;
  if (printControl == "E" || printControl == "e")
  {
    cin.ignore();
    cout << "" << endl;
    cout << "Generation 0:" << endl;
    for (int i = 0; i < countChar+1; i++)
    {
      if (charCounter == lineLength)
      {
        cout << "" << endl;
        charCounter = 0;
      }

      if (array[i] == 'X' || array[i] == 'x' || array[i] == '-')
      {
        charCounter++;
        cout << array[i] << '\0';

      }
    }
    cin.ignore();
  }

  if (printControl == "F" || printControl == "f")
  {
    output = "";
    output += "Generation 0:";
    output += "\n";
    for (int i = 0; i < countChar+1; i++)
    {
      if (charCounter == lineLength)
      {
        output += "\n";
        charCounter = 0;
      }

      if (array[i] == 'X' || array[i] == 'x' || array[i] == '-')
      {
        charCounter++;
        output += array[i];

      }
    }
  }
  if (printControl == "P" || printControl == "p")
  {
    cout << "" << endl;
    cout << "Generation 0:" << endl;
    for (int i = 0; i < countChar+1; i++)
    {
      if (charCounter == lineLength)
      {
        cout << "" << endl;
        charCounter = 0;
      }

      if (array[i] == 'X' || array[i] == 'x' || array[i] == '-')
      {
        charCounter++;
        cout << array[i] << '\0';
      }
    }
    sleep(2);
  }
  return 0;
};

//Creates a random generation zero with user inputed dimensions and density.
int GameLife::RandomGrid(int dim1, int dim2, double density)
{
  int randomTotal = dim1*dim2;
  int density2 = density*randomTotal;
  string randomStr = "";
  ofstream randomFile ("GenerationStart.txt");
  for (int i = 0; i < density2; i++)
  {
    randomStr += "X";
  }
  int density3 = randomTotal-density2;
  for (int i = 0; i < density3; i++)
  {
    randomStr += "-";
  }
  random_shuffle(randomStr.begin(), randomStr.end());

  if (randomFile.is_open())
  {
    charCounter = 0;
    randomFile << dim1 << '\n';
    randomFile << dim2 << '\n';
    for (int i = 0; i < randomStr.length(); i++)
    {
      if (charCounter == dim2)
      {
        randomFile << "" << endl;
        charCounter = 0;
      }

        charCounter++;
        randomFile << randomStr[i] << '\0';
    }
  }
  randomFile.flush();
  randomFile.close();
  return 0;
};

//Runs classic boundary mode for each of the three mediums depending on user input.
int GameLife::ClassicMode(string printControl, string outputFileName)
{
  generationCount++;
  ofstream classicFile ("classicMode.txt");

  char* array = &vectorGrid[0];
  char classicArray[countChar] = { '\0' };

  for (int i = 0; i < countChar; i++)
  {
    numNeighbors = 0;

    //top left neighbor
    if (array[i-lineLength-3] == '~' || array[i-lineLength-3] == '-')
    {}
    if (array[i-lineLength-3] == 'x' || array[i-lineLength-3] == 'X')
    {
      numNeighbors++;
    }
    //top neighbor
    if (array[i-lineLength-2] == '~' || array[i-lineLength-2] == '-')
    {}
    if (array[i-lineLength-2] == 'x' || array[i-lineLength-2] == 'X')
    {
      numNeighbors++;
    }
    //top right neighbor
    if (array[i-lineLength-1] == '~' || array[i-lineLength-1] == '-')
    {}
    if (array[i-lineLength-1] == 'x' || array[i-lineLength-1] == 'X')
    {
      numNeighbors++;
    }
    //left neighbor
    if (array[i-1] == '~' || array[i-1] == '-')
    {}
    if (array[i-1] == 'x' || array[i-1] == 'X')
    {
      numNeighbors++;
    }
    //right neighbor
    if (array[i+1] == '~' || array[i+1] == '-')
    {}
    if (array[i+1] == 'x' || array[i+1] == 'X')
    {
      numNeighbors++;
    }
    //bottom left neighbor
    if (array[i+lineLength+1] == '~' || array[i+lineLength+1] == '-')
    {}
    if (array[i+lineLength+1] == 'x' || array[i+lineLength+1] == 'X')
    {
      numNeighbors++;
    }
    //bottom neighbor
    if (array[i+lineLength+2] == '~' || array[i+lineLength+2] == '-')
    {}
    if (array[i+lineLength+2] == 'x' || array[i+lineLength+2] == 'X')
    {
      numNeighbors++;
    }
    //bottom right neighbor
    if (array[i+lineLength+3] == '~' || array[i+lineLength+3] == '-')
    {}
    if (array[i+lineLength+3] == 'x' || array[i+lineLength+3] == 'X')
    {
      numNeighbors++;
    }

    if (array[i] == '-')
    {
      if (numNeighbors == 3)
      {
        classicArray[i] = 'X';
      }
      else
      {
        classicArray[i] = '-';
      }
    }
    if (array[i] == 'X' || array[i] == 'x')
    {
      if (numNeighbors <= 1)
      {
        classicArray[i] = '-';
      }
      if (numNeighbors == 2)
      {
        classicArray[i] = 'X';
      }
      if (numNeighbors == 3)
      {
        classicArray[i] = 'X';
      }
      if (numNeighbors >= 4)
      {
        classicArray[i] = '-';
      }
    }
    if (array[i] == '~')
    {
      classicArray[i] = '~';
    }
  }

  string strArray = array;
  string strClassicArray = classicArray;

  if (printControl == "E" || printControl == "e")
  {
    if (strArray == strClassicArray)
    {
      cout << "The simulation is now stable. Please press 'enter'/'return' to exit." << endl;
      cin.ignore();
      return 0;
    }
    if (classicFile.is_open())
    {
      charCounter = 0;
      cout << "" << endl;
      cout << "Generation " << generationCount << ":" << endl;
      for (int i = 0; i < countChar+1; i++)
      {
        if (charCounter == lineLength)
        {
          classicFile << "" << endl;
          cout << "" << endl;
          charCounter = 0;
        }

        if (classicArray[i] == 'X' || classicArray[i] == 'x' || classicArray[i] == '-')
        {
          charCounter++;
          classicFile << classicArray[i] << '\0';
          cout << classicArray[i] << '\0';
        }
      }
    }
    cin.ignore();
    classicFile.flush();
    classicFile.close();
    readFile("classicMode.txt");
    ClassicMode(printControl, outputFileName);
  }

  if (printControl == "f" || printControl == "F")
  {
    if (strArray == strClassicArray)
    {
      return 0;
    }
    if (classicFile.is_open())
    {
      charCounter = 0;
      output += "Generation ";
      output += to_string(generationCount);
      output += ":";
      output += "\n";
      for (int i = 0; i < countChar+1; i++)
      {
        if (charCounter == lineLength)
        {
          classicFile << "" << endl;
          output += "\n";
          charCounter = 0;
        }

        if (classicArray[i] == 'X' || classicArray[i] == 'x' || classicArray[i] == '-')
        {
          charCounter++;
          classicFile << classicArray[i] << '\0';
          output += classicArray[i];

        }
      }
    }
    classicFile.flush();
    classicFile.close();
    ofstream outputFile (outputFileName);
    outputFile << output;
    outputFile.flush();
    outputFile.close();
    readFile("classicMode.txt");
    ClassicMode(printControl, outputFileName);
  }

  if (printControl == "P" || printControl == "p")
  {
    if (strArray == strClassicArray)
    {
      cout << "The simulation is now stable. Please press 'enter'/'return' to exit." << endl;
      cin.ignore();
      return 0;
    }
    if (classicFile.is_open())
    {
      charCounter = 0;
      cout << "" << endl;
      cout << "Generation " << generationCount << ":" << endl;
      for (int i = 0; i < countChar+1; i++)
      {
        if (charCounter == lineLength)
        {
          classicFile << "" << endl;
          cout << "" << endl;
          charCounter = 0;
        }

        if (classicArray[i] == 'X' || classicArray[i] == 'x' || classicArray[i] == '-')
        {
          charCounter++;
          classicFile << classicArray[i] << '\0';
          cout << classicArray[i] << '\0';
        }
      }
    }
    sleep(2);
    classicFile.flush();
    classicFile.close();
    readFile("classicMode.txt");
    ClassicMode(printControl, outputFileName);
  }

  return 0;
};

//Runs doughnut boundary mode for each of the three mediums depending on user input.
int GameLife::DoughNutMode(string printControl, string outputFileName)
{
  generationCount++;
  ofstream doughnutFile ("doughnutMode.txt");

  char* array = &vectorGrid[0];
  char doughnutArray[countChar] = { '\0' };
  string fixArray1(array);
  fixArray1.erase(remove(fixArray1.begin(), fixArray1.end(), '~'), fixArray1.end());

  int fixArray1Length = fixArray1.length();
  int fixArray1Rows = fixArray1Length/lineLength;

  string fixArray2 = fixArray1;
  if (fixArray1[fixArray1Length-1] == 'x' || fixArray1[fixArray1Length-1] == 'X')
  {
    fixArray2.insert(0, 1, 'W');
  }
  if (fixArray1[fixArray1Length-1] == '-')
  {
    fixArray2.insert(0, 1, 'L');
  }
  for (int i = fixArray1Length-1; i > fixArray1Length-lineLength-1; i--)
  {
    if (fixArray1[i] == 'x' || fixArray1[i] == 'X')
    {
      fixArray2.insert(1, 1, 'W');
    }
    if (fixArray1[i] == '-')
    {
      fixArray2.insert(1, 1, 'L');
    }
  }

  if (fixArray1[fixArray1Length-lineLength-1] == 'x' || fixArray1[fixArray1Length-lineLength-1] == 'X')
  {
    fixArray2.insert(lineLength+1, 1, 'W');
  }
  if (fixArray1[fixArray1Length-lineLength-1] == '-')
  {
    fixArray2.insert(lineLength+1, 1, 'L');
  }

  for (int i = 1; i < fixArray1Rows+1; i++)
  {
    if (fixArray1[i*lineLength-1] == 'x' || fixArray1[i*lineLength-1] == 'X')
    {
      fixArray2.insert(i*(lineLength+2), 1, 'W');
    }
    if (fixArray1[i*lineLength-1] == '-')
    {
      fixArray2.insert(i*(lineLength+2), 1, 'L');
    }
    if (fixArray1[i*lineLength-lineLength] == 'x' || fixArray1[i*lineLength-lineLength] == 'X')
    {
      fixArray2.insert(i*(lineLength+2)+lineLength+1, 1, 'W');
    }
    if (fixArray1[i*lineLength-lineLength] == '-')
    {
      fixArray2.insert(i*(lineLength+2)+lineLength+1, 1, 'L');
    }
  }

  if (fixArray1[lineLength-1] == 'x' || fixArray1[lineLength-1] == 'X')
  {
    fixArray2.insert(fixArray2.end(), 1, 'W');
  }
  if (fixArray1[lineLength-1] == '-')
  {
    fixArray2.insert(fixArray2.end(), 1, 'L');
  }

  for (int i = 0; i < lineLength; i++)
  {
    if (fixArray1[i] == 'x' || fixArray1[i] == 'X')
    {
      fixArray2.insert(fixArray2.end(), 1, 'W');
    }
    if (fixArray1[i] == '-')
    {
      fixArray2.insert(fixArray2.end(), 1, 'L');
    }
  }

  if (fixArray1[0] == 'x' || fixArray1[0] == 'X')
  {
    fixArray2.insert(fixArray2.end(), 1, 'W');
  }
  if (fixArray1[0] == '-')
  {
    fixArray2.insert(fixArray2.end(), 1, 'L');
  }

  for (int i = 0; i < countChar; i++)
  {
    numNeighbors = 0;

    //top left neighbor
    if (fixArray2[i-lineLength-3] == 'L' || fixArray2[i-lineLength-3] == '-')
    {}
    if (fixArray2[i-lineLength-3] == 'x' || fixArray2[i-lineLength-3] == 'X' || fixArray2[i-lineLength-3] == 'W')
    {
      numNeighbors++;
    }
    //top neighbor
    if (fixArray2[i-lineLength-2] == 'L' || fixArray2[i-lineLength-2] == '-')
    {}
    if (fixArray2[i-lineLength-2] == 'x' || fixArray2[i-lineLength-2] == 'X' || fixArray2[i-lineLength-2] == 'W')
    {
      numNeighbors++;
    }
    //top right neighbor
    if (fixArray2[i-lineLength-1] == 'L' || fixArray2[i-lineLength-1] == '-')
    {}
    if (fixArray2[i-lineLength-1] == 'x' || fixArray2[i-lineLength-1] == 'X'|| fixArray2[i-lineLength-1] == 'W')
    {
      numNeighbors++;
    }
    //left neighbor
    if (fixArray2[i-1] == 'L' || fixArray2[i-1] == '-')
    {}
    if (fixArray2[i-1] == 'x' || fixArray2[i-1] == 'X'|| fixArray2[i-1] == 'W')
    {
      numNeighbors++;
    }
    //right neighbor
    if (fixArray2[i+1] == 'L' || fixArray2[i+1] == '-')
    {}
    if (fixArray2[i+1] == 'x' || fixArray2[i+1] == 'X' || fixArray2[i+1] == 'W')
    {
      numNeighbors++;
    }
    //bottom left neighbor
    if (fixArray2[i+lineLength+1] == 'L' || fixArray2[i+lineLength+1] == '-')
    {}
    if (fixArray2[i+lineLength+1] == 'x' || fixArray2[i+lineLength+1] == 'X' || fixArray2[i+lineLength+1] == 'W')
    {
      numNeighbors++;
    }
    //bottom neighbor
    if (fixArray2[i+lineLength+2] == 'L' || fixArray2[i+lineLength+2] == '-')
    {}
    if (fixArray2[i+lineLength+2] == 'x' || fixArray2[i+lineLength+2] == 'X' || fixArray2[i+lineLength+2] == 'W')
    {
      numNeighbors++;
    }
    //bottom right neighbor
    if (fixArray2[i+lineLength+3] == 'L' || fixArray2[i+lineLength+3] == '-')
    {}
    if (fixArray2[i+lineLength+3] == 'x' || fixArray2[i+lineLength+3] == 'X' || fixArray2[i+lineLength+3] == 'W')
    {
      numNeighbors++;
    }

    if (fixArray2[i] == '-')
    {
      if (numNeighbors == 3)
      {
        doughnutArray[i] = 'X';
      }
      else
      {
        doughnutArray[i] = '-';
      }
    }
    if (fixArray2[i] == 'X' || fixArray2[i] == 'x')
    {
      if (numNeighbors <= 1)
      {
        doughnutArray[i] = '-';
      }
      if (numNeighbors == 2)
      {
        doughnutArray[i] = 'X';
      }
      if (numNeighbors == 3)
      {
        doughnutArray[i] = 'X';
      }
      if (numNeighbors >= 4)
      {
        doughnutArray[i] = '-';
      }
    }
    if (fixArray2[i] == 'W' || fixArray2[i] == 'L')
    {
      doughnutArray[i] = '~';
    }
  }

  string strArray = array;
  string strdoughnutArray = doughnutArray;

  if (printControl == "E" || printControl == "e")
  {
    if (strArray == strdoughnutArray)
    {
      cout << "The simulation is now stable. Please press 'enter'/'return' to exit." << endl;
      cin.ignore();
      return 0;
    }
    if (doughnutFile.is_open())
    {
      charCounter = 0;
      cout << "Generation " << generationCount << ":" << endl;
      cout << "" << endl;
      for (int i = 0; i < countChar+1; i++)
      {
        if (charCounter == lineLength)
        {
          doughnutFile << "" << endl;
          cout << "" << endl;
          charCounter = 0;
        }

        if (doughnutArray[i] == 'X' || doughnutArray[i] == 'x' || doughnutArray[i] == '-')
        {
          doughnutFile << doughnutArray[i] << '\0';
          charCounter++;
          cout << doughnutArray[i] << '\0';

        }
      }
    }
    cin.ignore();
    doughnutFile.flush();
    doughnutFile.close();
    readFile("doughnutMode.txt");
    DoughNutMode(printControl, outputFileName);
  }

  if (printControl == "f" || printControl == "F")
  {
    if (strArray == strdoughnutArray)
    {
      return 0;
    }
    if (doughnutFile.is_open())
    {
      charCounter = 0;
      output += "Generation ";
      output += to_string(generationCount);
      output += ":";
      output += "\n";
      for (int i = 0; i < countChar+1; i++)
      {
        if (charCounter == lineLength)
        {
          doughnutFile << "" << endl;
          output += "\n";
          charCounter = 0;
        }

        if (doughnutArray[i] == 'X' || doughnutArray[i] == 'x' || doughnutArray[i] == '-')
        {
          charCounter++;
          doughnutFile << doughnutArray[i] << '\0';
          output += doughnutArray[i];
        }
      }
    }
    doughnutFile.flush();
    doughnutFile.close();
    ofstream outputFile (outputFileName);
    outputFile << output;
    outputFile.flush();
    outputFile.close();
    readFile("doughnutMode.txt");
    DoughNutMode(printControl, outputFileName);
  }

  if (printControl == "P" || printControl == "p")
  {
    if (strArray == strdoughnutArray)
    {
      cout << "The simulation is now stable. Please press 'enter'/'return' to exit." << endl;
      cin.ignore();
      return 0;
    }
    if (doughnutFile.is_open())
    {
      charCounter = 0;
      cout << "Generation " << generationCount << ":" << endl;
      cout << "" << endl;
      for (int i = 0; i < countChar+1; i++)
      {
        if (charCounter == lineLength)
        {
          doughnutFile << "" << endl;
          cout << "" << endl;
          charCounter = 0;
        }

        if (doughnutArray[i] == 'X' || doughnutArray[i] == 'x' || doughnutArray[i] == '-')
        {
          doughnutFile << doughnutArray[i] << '\0';
          charCounter++;
          cout << doughnutArray[i] << '\0';

        }
      }
    }
    sleep(2);
    doughnutFile.flush();
    doughnutFile.close();
    readFile("doughnutMode.txt");
    DoughNutMode(printControl, outputFileName);
  }
  return 0;
};

//Runs mirror boundary mode for each of the three mediums depending on user input.
int GameLife::MirrorMode(string printControl, string outputFileName)
{
  generationCount++;
  ofstream mirrorFile ("mirrorMode.txt");
  char* array = &vectorGrid[0];
  char mirrorArray[countChar] = { '\0' };
  string fixArray1(array);
  fixArray1.erase(remove(fixArray1.begin(), fixArray1.end(), '~'), fixArray1.end());

  int fixArray1Length = fixArray1.length();
  int fixArray1Rows = fixArray1Length/lineLength;

  string fixArray2 = fixArray1;
  if (fixArray1[0] == 'x' || fixArray1[0] == 'X')
  {
    fixArray2.insert(0, 1, 'W');
  }
  if (fixArray1[0] == '-')
  {
    fixArray2.insert(0, 1, 'L');
  }

  for (int i = lineLength-1; i > -1; i--)
  {
    if (fixArray1[i] == 'x' || fixArray1[i] == 'X')
    {
      fixArray2.insert(1, 1, 'W');
    }
    if (fixArray1[i] == '-')
    {
      fixArray2.insert(1, 1, 'L');
    }
  }

  if (fixArray1[lineLength-1] == 'x' || fixArray1[lineLength-1] == 'X')
  {
    fixArray2.insert(lineLength+1, 1, 'W');
  }
  if (fixArray1[lineLength-1] == '-')
  {
    fixArray2.insert(lineLength+1, 1, 'L');
  }

  for (int i = 1; i < fixArray1Rows+1; i++)
  {
    if (fixArray1[i*lineLength-lineLength] == 'x' || fixArray1[i*lineLength-lineLength] == 'X')
    {
      fixArray2.insert(i*(lineLength+2), 1, 'W');
    }
    if (fixArray1[i*lineLength-lineLength] == '-')
    {
      fixArray2.insert(i*(lineLength+2), 1, 'L');
    }
    if (fixArray1[i*lineLength-1] == 'x' || fixArray1[i*lineLength-1] == 'X')
    {
      fixArray2.insert(i*(lineLength+2)+lineLength+1, 1, 'W');
    }
    if (fixArray1[i*lineLength-1] == '-')
    {
      fixArray2.insert(i*(lineLength+2)+lineLength+1, 1, 'L');
    }
  }

  if (fixArray1[fixArray1Length-lineLength-1] == 'x' || fixArray1[fixArray1Length-lineLength-1] == 'X')
  {
    fixArray2.insert(fixArray2.end(), 1, 'W');
  }
  if (fixArray1[fixArray1Length-lineLength-1] == '-')
  {
    fixArray2.insert(fixArray2.end(), 1, 'L');
  }

  for (int i = fixArray1Length-lineLength; i < fixArray1Length; i++)
  {
    if (fixArray1[i] == 'x' || fixArray1[i] == 'X')
    {
      fixArray2.insert(fixArray2.end(), 1, 'W');
    }
    if (fixArray1[i] == '-')
    {
      fixArray2.insert(fixArray2.end(), 1, 'L');
    }
  }
  if (fixArray1[fixArray1Length-1] == 'x' || fixArray1[fixArray1Length-1] == 'X')
  {
    fixArray2.insert(fixArray2.end(), 1, 'W');
  }
  if (fixArray1[fixArray1Length-1] == '-')
  {
    fixArray2.insert(fixArray2.end(), 1, 'L');
  }

  for (int i = 0; i < countChar; i++)
  {
    numNeighbors = 0;

    //top left neighbor
    if (fixArray2[i-lineLength-3] == 'L' || fixArray2[i-lineLength-3] == '-')
    {}
    if (fixArray2[i-lineLength-3] == 'x' || fixArray2[i-lineLength-3] == 'X' || fixArray2[i-lineLength-3] == 'W')
    {
      numNeighbors++;
    }
    //top neighbor
    if (fixArray2[i-lineLength-2] == 'L' || fixArray2[i-lineLength-2] == '-')
    {}
    if (fixArray2[i-lineLength-2] == 'x' || fixArray2[i-lineLength-2] == 'X' || fixArray2[i-lineLength-2] == 'W')
    {
      numNeighbors++;
    }
    //top right neighbor
    if (fixArray2[i-lineLength-1] == 'L' || fixArray2[i-lineLength-1] == '-')
    {}
    if (fixArray2[i-lineLength-1] == 'x' || fixArray2[i-lineLength-1] == 'X'|| fixArray2[i-lineLength-1] == 'W')
    {
      numNeighbors++;
    }
    //left neighbor
    if (fixArray2[i-1] == 'L' || fixArray2[i-1] == '-')
    {}
    if (fixArray2[i-1] == 'x' || fixArray2[i-1] == 'X'|| fixArray2[i-1] == 'W')
    {
      numNeighbors++;
    }
    //right neighbor
    if (fixArray2[i+1] == 'L' || fixArray2[i+1] == '-')
    {}
    if (fixArray2[i+1] == 'x' || fixArray2[i+1] == 'X' || fixArray2[i+1] == 'W')
    {
      numNeighbors++;
    }
    //bottom left neighbor
    if (fixArray2[i+lineLength+1] == 'L' || fixArray2[i+lineLength+1] == '-')
    {}
    if (fixArray2[i+lineLength+1] == 'x' || fixArray2[i+lineLength+1] == 'X' || fixArray2[i+lineLength+1] == 'W')
    {
      numNeighbors++;
    }
    //bottom neighbor
    if (fixArray2[i+lineLength+2] == 'L' || fixArray2[i+lineLength+2] == '-')
    {}
    if (fixArray2[i+lineLength+2] == 'x' || fixArray2[i+lineLength+2] == 'X' || fixArray2[i+lineLength+2] == 'W')
    {
      numNeighbors++;
    }
    //bottom right neighbor
    if (fixArray2[i+lineLength+3] == 'L' || fixArray2[i+lineLength+3] == '-')
    {}
    if (fixArray2[i+lineLength+3] == 'x' || fixArray2[i+lineLength+3] == 'X' || fixArray2[i+lineLength+3] == 'W')
    {
      numNeighbors++;
    }

    if (fixArray2[i] == '-')
    {
      if (numNeighbors == 3)
      {
        mirrorArray[i] = 'X';
      }
      else
      {
        mirrorArray[i] = '-';
      }
    }
    if (fixArray2[i] == 'X' || fixArray2[i] == 'x')
    {
      if (numNeighbors <= 1)
      {
        mirrorArray[i] = '-';
      }
      if (numNeighbors == 2)
      {
        mirrorArray[i] = 'X';
      }
      if (numNeighbors == 3)
      {
        mirrorArray[i] = 'X';
      }
      if (numNeighbors >= 4)
      {
        mirrorArray[i] = '-';
      }
    }
    if (fixArray2[i] == 'W' || fixArray2[i] == 'L')
    {
      mirrorArray[i] = '~';
    }
  }

  string strArray = array;
  string strmirrorArray = mirrorArray;

  if (printControl == "E" || printControl == "e")
  {
    if (strArray == strmirrorArray)
    {
      cout << "The simulation is now stable. Please press 'enter'/'return' to exit." << endl;
      cin.ignore();
      return 0;
    }
    if (mirrorFile.is_open())
    {
      charCounter = 0;

      cout << "Generation " << generationCount << ":" << endl;
      cout << "" << endl;
      for (int i = 0; i < countChar+1; i++)
      {
        if (charCounter == lineLength)
        {
          mirrorFile << "" << endl;
          cout << "" << endl;
          charCounter = 0;
        }

        if (mirrorArray[i] == 'X' || mirrorArray[i] == 'x' || mirrorArray[i] == '-')
        {
          mirrorFile << mirrorArray[i] << '\0';
          charCounter++;
          cout << mirrorArray[i] << '\0';

        }
      }
    }
    cin.ignore();
    mirrorFile.flush();
    mirrorFile.close();
    readFile("mirrorMode.txt");
    MirrorMode(printControl, outputFileName);
  }

  if (printControl == "f" || printControl == "F")
  {
    if (strArray == strmirrorArray)
    {
      return 0;
    }
    if (mirrorFile.is_open())
    {
      charCounter = 0;
      output += "Generation ";
      output += to_string(generationCount);
      output += ":";
      output += "\n";
      for (int i = 0; i < countChar+1; i++)
      {
        if (charCounter == lineLength)
        {
          mirrorFile << "" << endl;
          output += "\n";
          charCounter = 0;
        }

        if (mirrorArray[i] == 'X' || mirrorArray[i] == 'x' || mirrorArray[i] == '-')
        {
          charCounter++;
          mirrorFile << mirrorArray[i] << '\0';
          output += mirrorArray[i];

        }
      }
    }
    mirrorFile.flush();
    mirrorFile.close();
    ofstream outputFile (outputFileName);
    outputFile << output;
    outputFile.flush();
    outputFile.close();
    readFile("mirrorMode.txt");
    MirrorMode(printControl, outputFileName);
  }

  if (printControl == "P" || printControl == "p")
  {
    if (strArray == strmirrorArray)
    {
      cout << "The simulation is now stable. Please press 'enter'/'return' to exit." << endl;
      cin.ignore();
      return 0;
    }
    if (mirrorFile.is_open())
    {
      charCounter = 0;

      cout << "Generation " << generationCount << ":" << endl;
      cout << "" << endl;
      for (int i = 0; i < countChar+1; i++)
      {
        if (charCounter == lineLength)
        {
          mirrorFile << "" << endl;
          cout << "" << endl;
          charCounter = 0;
        }

        if (mirrorArray[i] == 'X' || mirrorArray[i] == 'x' || mirrorArray[i] == '-')
        {
          mirrorFile << mirrorArray[i] << '\0';
          charCounter++;
          cout << mirrorArray[i] << '\0';

        }
      }
    }
    sleep(2);
    mirrorFile.flush();
    mirrorFile.close();
    readFile("mirrorMode.txt");
    MirrorMode(printControl, outputFileName);
  }

  return 0;
};
