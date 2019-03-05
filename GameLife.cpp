#include "GameLife.h"
#include <iostream>
#include <fstream> //Using this for reading and writing files.
#include <vector>
#include <algorithm> //
#include <string>

using namespace std;
vector<char> vectorGrid;
int generationCount = 0;

GameLife::GameLife()//default constructor
{
  //initialize variabble to default values
  //myvectorGrid = new char[256];
  ch = '\0';
  countChar = 0;
  fileName = "";
  generationCount = 0;
}

GameLife::GameLife(int maxSize)//overloaded constructor
{
  //myvectorGrid = new char[maxSize];
  ch = '\0';
  countChar = 0;
  fileName = "";
  generationCount = 0;
}

GameLife::~GameLife()//destructor
{}

int GameLife::getLineLength(string fileName)
{
  lineLength = 0;
  ifstream myFileLength (fileName); //Makes the file "fileName" available for reading.
  while(myFileLength.get(ch)) //A while function that continues on the end of file.
  {
    //getline(myFile, line); //Reads the file line by line.
    if (ch == '-' || ch == 'X' || ch == 'x')
    {
      getline(myFileLength, line); //Reads the file's first line.
      //cout << line << endl;
      lineLength = line.length()+1; //Set a value of lineLength to the line's length.
    }
  }
  myFileLength.close();
  //cout << lineLength << endl;
  return lineLength;
}

int GameLife::readFile(string fileName)
{
  countChar = 0;
  vectorGrid.clear();

  ifstream myFile (fileName); //Makes the file "fileName" available for reading.

  while(myFile.get(ch)) //A while function that continues on the end of file.
  {
    //getline(myFile, line); //Reads the file line by line.
    if (ch == '-' || ch == 'X' || ch == 'x')
    {
      countChar++;
      //cout << countChar << endl;
      //cout << ch << endl;
      //cout << "" << endl;
      vectorGrid.push_back(ch);
    }
  }//cout << vectorGrid << endl;
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

  /*numberRows = countChar/lineLength;
  countChar+=numberRows*2;*/

  vectorGrid.insert(vectorGrid.begin(),'~');
  vectorGrid.push_back('~');
  countChar+=2;
      /*for (vector<char>::const_iterator i = vectorGrid.begin(); i != vectorGrid.end(); ++i)
      {
        cout << *i << ' ';
      }
      cout << '\0' << endl;*/
myFile.close();

  return 0;
}

int GameLife::printGen0()
{
  char* array = &vectorGrid[0];
  charCounter = 0;
  //classicFile << "" << endl;
  cout << "" << endl;
  cout << "Generation 0:" << endl;
  for (int i = 0; i < countChar+1; i++) //For each item in the array.
  {
    if (charCounter == lineLength)
    {
      //classicFile << "" << endl;
      cout << "" << endl;
      charCounter = 0;
    }

    if (array[i] == 'X' || array[i] == 'x' || array[i] == '-')
    {
      //classicFile << array[i] << '\0';
      charCounter++;
      cout << array[i] << '\0';

    }
  }
  return 0;
}

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

  if (randomFile.is_open()) //If the new file created is open.
  {
    charCounter = 0;
    //classicFile << "" << endl;
    randomFile << dim1 << '\n';
    randomFile << dim2 << '\n';
    for (int i = 0; i < randomStr.length(); i++) //For each item in the array.
    {
      if (charCounter == dim2)
      {
        randomFile << "" << endl;
        //cout << "" << endl;
        charCounter = 0;
      }

        charCounter++;
        randomFile << randomStr[i] << '\0';
    }
  }
  randomFile.flush();
  randomFile.close();
  //cout << randomStr << endl;
}

int GameLife::ClassicMode()
{
  generationCount++;
  ofstream classicFile ("classicMode.txt"); //Writes to/creates new file named
                                         // classicMode.txt.
  char* array = &vectorGrid[0];
  char classicArray[countChar] = { '\0' };

  for (int i = 0; i < countChar; i++) //For each item in the array.
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

    //cout << array[i] << ' ';
    //cout << "neighbors: " << numNeighbors << endl;
  }

  /*for (int i = 0; i < countChar+1; i++) //For each item in the array.
  {
    cout << classicArray[i] << ' ';
  }
  cout << "" << endl;*/

  string strArray = array;
  string strClassicArray = classicArray;

  //cout << strArray << endl;
  //cout << strClassicArray << endl;

  if (strArray == strClassicArray)
  {
    cout << "The simulation is now stable. Please press 'enter'/'return' to exit." << endl;
    cin.ignore();
    return 0;
  }
  if (classicFile.is_open()) //If the new file created is open.
  {
    charCounter = 0;
    //classicFile << "" << endl;
    cout << "" << endl;
    cout << "Generation " << generationCount << ":" << endl;
    for (int i = 0; i < countChar+1; i++) //For each item in the array.
    {
      if (charCounter == lineLength)
      {
        classicFile << unitbuf << "" << endl;
        cout << "" << endl;
        charCounter = 0;
      }

      if (classicArray[i] == 'X' || classicArray[i] == 'x' || classicArray[i] == '-')
      {
        charCounter++;
        classicFile << unitbuf << classicArray[i] << '\0';
        cout << classicArray[i] << '\0';

      }
    }
  }
  classicFile.flush();
  classicFile.close();
  readFile("classicMode.txt");
  ClassicMode();
  return 0;
}

/*int GameLife::ClassicModeRepeat()
{
  char* arrayC = &classicArray[0];

  char classicArrayC[countChar] = { '\0' };

  for (int i = 0; i < countChar; i++) //For each item in the array.
  {
    numNeighbors = 0;

    //top left neighbor
    if (arrayC[i-lineLength-3] == '~' || arrayC[i-lineLength-3] == '-')
    {}
    if (arrayC[i-lineLength-3] == 'x' || arrayC[i-lineLength-3] == 'X')
    {
      numNeighbors++;
    }
    //top neighbor
    if (arrayC[i-lineLength-2] == '~' || arrayC[i-lineLength-2] == '-')
    {}
    if (arrayC[i-lineLength-2] == 'x' || arrayC[i-lineLength-2] == 'X')
    {
      numNeighbors++;
    }
    //top right neighbor
    if (arrayC[i-lineLength-1] == '~' || arrayC[i-lineLength-1] == '-')
    {}
    if (arrayC[i-lineLength-1] == 'x' || arrayC[i-lineLength-1] == 'X')
    {
      numNeighbors++;
    }
    //left neighbor
    if (arrayC[i-1] == '~' || arrayC[i-1] == '-')
    {}
    if (arrayC[i-1] == 'x' || arrayC[i-1] == 'X')
    {
      numNeighbors++;
    }
    //right neighbor
    if (arrayC[i+1] == '~' || arrayC[i+1] == '-')
    {}
    if (arrayC[i+1] == 'x' || arrayC[i+1] == 'X')
    {
      numNeighbors++;
    }
    //bottom left neighbor
    if (arrayC[i+lineLength+1] == '~' || arrayC[i+lineLength+1] == '-')
    {}
    if (arrayC[i+lineLength+1] == 'x' || arrayC[i+lineLength+1] == 'X')
    {
      numNeighbors++;
    }
    //bottom neighbor
    if (arrayC[i+lineLength+2] == '~' || arrayC[i+lineLength+2] == '-')
    {}
    if (arrayC[i+lineLength+2] == 'x' || arrayC[i+lineLength+2] == 'X')
    {
      numNeighbors++;
    }
    //bottom right neighbor
    if (arrayC[i+lineLength+3] == '~' || arrayC[i+lineLength+3] == '-')
    {}
    if (arrayC[i+lineLength+3] == 'x' || arrayC[i+lineLength+3] == 'X')
    {
      numNeighbors++;
    }

    if (arrayC[i] == '-')
    {
      if (numNeighbors == 3)
      {
        classicArrayC[i] = 'X';
      }
      else
      {
        classicArrayC[i] = '-';
      }
    }
    if (arrayC[i] == 'X' || arrayC[i] == 'x')
    {
      if (numNeighbors <= 1)
      {
        classicArrayC[i] = '-';
      }
      if (numNeighbors == 2)
      {
        classicArrayC[i] = 'X';
      }
      if (numNeighbors == 3)
      {
        classicArrayC[i] = 'X';
      }
      if (numNeighbors >= 4)
      {
        classicArrayC[i] = '-';
      }
    }
    if (arrayC[i] == '~')
    {
      classicArrayC[i] = '~';
    }

    //cout << array[i] << ' ';
    //cout << "neighbors: " << numNeighbors << endl;
  }

  //for (int i = 0; i < countChar+1; i++) //For each item in the array.
  //{
    cout << classicArrayC[0] << ' ';
  //}
  return 0;
}*/

int GameLife::DoughNutMode()
{
  generationCount++;
  ofstream doughnutFile ("doughnutMode.txt"); //Writes to/creates new file named
                                         // classicMode.txt.
  char* array = &vectorGrid[0];
  char doughnutArray[countChar] = { '\0' };
  //char fixArray[countChar] = { '\0' };
  string fixArray1(array);
  fixArray1.erase(remove(fixArray1.begin(), fixArray1.end(), '~'), fixArray1.end());
  //cout << fixArray1 << endl;

  int fixArray1Length = fixArray1.length();
  int fixArray1Rows = fixArray1Length/lineLength;
  //cout << fixArray1Length << endl;
  //cout << fixArray1Rows << endl;

  string fixArray2 = fixArray1;
  if (fixArray1[fixArray1Length-1] == 'x' || fixArray1[fixArray1Length-1] == 'X')
  {
    fixArray2.insert(0, 1, 'W');
  }
  if (fixArray1[fixArray1Length-1] == '-')
  {
    fixArray2.insert(0, 1, 'L');
  }
//cout << fixArray2 << endl;
  for (int i = fixArray1Length-1; i > fixArray1Length-lineLength-1; i--) //For each item in the array.
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
  //cout << fixArray2 << endl;

  if (fixArray1[fixArray1Length-lineLength-1] == 'x' || fixArray1[fixArray1Length-lineLength-1] == 'X')
  {
    fixArray2.insert(lineLength+1, 1, 'W');
  }
  if (fixArray1[fixArray1Length-lineLength-1] == '-')
  {
    fixArray2.insert(lineLength+1, 1, 'L');
  }

//cout << fixArray2 << endl;

  for (int i = 1; i < fixArray1Rows+1; i++) //For each item in the array.
  {
    //cout << "1" << fixArray2[i*(lineLength+2)] << endl;
    //cout << "2" << fixArray1[i*lineLength-1] << endl;
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
    //cout << fixArray2 << endl;
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

  //for (char part : tildaRemoval)
  //{

  //}

  /*for (int i = 0; i < countChar; i++) //For each item in the array.
  {
    if (array[i] == '~')
    {}
    else
    {
      fixArray[i] = array[i];
    }
  }*/

  //cout << fixArray2 << endl;

  for (int i = 0; i < countChar; i++) //For each item in the array.
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

    //cout << array[i] << ' ';
    //cout << "neighbors: " << numNeighbors << endl;
  }

  /*for (int i = 0; i < countChar+1; i++) //For each item in the array.
  {
    cout << doughnutArray[i] << ' ';
  }
  cout << "" << endl;*/

  string strArray = array;
  string strdoughnutArray = doughnutArray;

  //cout << strArray << endl;
  //cout << strdoughnutArray << endl;

  if (strArray == strdoughnutArray)
  {
    cout << "The simulation is now stable. Please press 'enter'/'return' to exit." << endl;
    cin.ignore();
    return 0;
  }
  if (doughnutFile.is_open()) //If the new file created is open.
  {
    charCounter = 0;
    //classicFile << "" << endl;

    cout << "Generation " << generationCount << ":" << endl;//printing wrong
    cout << "" << endl;
    for (int i = 0; i < countChar+1; i++) //For each item in the array.
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
  doughnutFile.close();
  readFile("doughnutMode.txt");
  DoughNutMode();
  return 0;
}

int GameLife::MirrorMode()
{
  generationCount++;
  ofstream mirrorFile ("mirrorMode.txt"); //Writes to/creates new file named
                                         // classicMode.txt.
  char* array = &vectorGrid[0];
  char mirrorArray[countChar] = { '\0' };
  //char fixArray[countChar] = { '\0' };
  string fixArray1(array);
  fixArray1.erase(remove(fixArray1.begin(), fixArray1.end(), '~'), fixArray1.end());
  //cout << fixArray1 << endl;

  int fixArray1Length = fixArray1.length();
  int fixArray1Rows = fixArray1Length/lineLength;
  //cout << fixArray1Length << endl;
  //cout << fixArray1Rows << endl;

  string fixArray2 = fixArray1;
  if (fixArray1[0] == 'x' || fixArray1[0] == 'X')
  {
    fixArray2.insert(0, 1, 'W');
  }
  if (fixArray1[0] == '-')
  {
    fixArray2.insert(0, 1, 'L');
  }
  //cout << fixArray2 << endl;

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
  //cout << fixArray2 << endl;

  if (fixArray1[lineLength-1] == 'x' || fixArray1[lineLength-1] == 'X')
  {
    fixArray2.insert(lineLength+1, 1, 'W');
  }
  if (fixArray1[lineLength-1] == '-')
  {
    fixArray2.insert(lineLength+1, 1, 'L');
  }

  //cout << fixArray2 << endl;

  for (int i = 1; i < fixArray1Rows+1; i++) //For each item in the array.
  {
    //cout << "1" << fixArray2[i*(lineLength+2)] << endl;
    //cout << "2" << fixArray1[i*lineLength-1] << endl;
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
    //cout << fixArray2 << endl;
  }

  if (fixArray1[fixArray1Length-lineLength-1] == 'x' || fixArray1[fixArray1Length-lineLength-1] == 'X')
  {
    fixArray2.insert(fixArray2.end(), 1, 'W');
  }
  if (fixArray1[fixArray1Length-lineLength-1] == '-')
  {
    fixArray2.insert(fixArray2.end(), 1, 'L');
  }

  for (int i = fixArray1Length-lineLength; i < fixArray1Length; i++) //For each item in the array.
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
  //LLLLWLLWWL---X--XWL-X--X--LL-----XXWWX-X-X--LL-----XXWLWWLLLLL
  //LLLLWLLWWL---X--XWL-X--X--LL-----XXWWX-X-X--LL-----XXWLLLLLLLW
  //LLLLWLLWWL---X--XWL-X--X--LL-----XXWWX-X-X--LL-----XXWLLLLLLW
  //LLLLWLLWWL---X--XWL-X--X--LL-----XXWWX-X-X--LL-----XXWLLLLLLWW
//cout << fixArray2 << endl;
//cout << fixArray1[fixArray1Length-1] << endl;
  if (fixArray1[fixArray1Length-1] == 'x' || fixArray1[fixArray1Length-1] == 'X')
  {
    fixArray2.insert(fixArray2.end(), 1, 'W');
  }
  if (fixArray1[fixArray1Length-1] == '-')
  {
    fixArray2.insert(fixArray2.end(), 1, 'L');
  }
//cout << fixArray2 << endl;
  //for (char part : tildaRemoval)
  //{

  //}

  /*for (int i = 0; i < countChar; i++) //For each item in the array.
  {
    if (array[i] == '~')
    {}
    else
    {
      fixArray[i] = array[i];
    }
  }*/

  //cout << fixArray2 << endl;

  for (int i = 0; i < countChar; i++) //For each item in the array.
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

    //cout << array[i] << ' ';
    //cout << "neighbors: " << numNeighbors << endl;
  }

  /*for (int i = 0; i < countChar+1; i++) //For each item in the array.
  {
    cout << mirrorArray[i] << ' ';
  }

  string strArray = array;
  string strdoughnutArray = doughnutArray;

  //cout << strArray << endl;
  //cout << strdoughnutArray << endl;

  if (strArray == strdoughnutArray)
  {
  cout << "" << endl;*/

  string strArray = array;
  string strmirrorArray = mirrorArray;

  //cout << strArray << endl;
  //cout << strmirrorArray << endl;

  if (strArray == strmirrorArray)
  {
    cout << "The simulation is now stable. Please press 'enter'/'return' to exit." << endl;
    cin.ignore();
    return 0;
  }
  if (mirrorFile.is_open()) //If the new file created is open.
  {
    charCounter = 0;
    //classicFile << "" << endl;

    cout << "Generation " << generationCount << ":" << endl;//printing wrong
    cout << "" << endl;
    for (int i = 0; i < countChar+1; i++) //For each item in the array.
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
  if (strArray == strmirrorArray)
  {
    cout << "The simulation is now stable. Please press 'enter'/'return' to exit." << endl;
    cin.ignore();
    return 0;
  }
  mirrorFile.close();
  readFile("mirrorMode.txt");
  MirrorMode();
  return 0;
}
