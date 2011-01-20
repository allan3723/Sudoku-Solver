// ache; Cheng, Allan

#include <iostream>
#include <set>
using namespace std;
#include <cctype>
#include <stdlib.h>
#include <stdio.h>

class Table
{
  private:
    set<char>::iterator i;
  public:
  int row, col, area, count;
  char num;
  set<char> choice;

  void print()
  { 
    for (i = choice.begin(); i != choice.end(); i++)
      cout << " " << *i;
    cout << endl;
  }
};

int emptyCellCount = 0;
void read_input();
void setSeen(Table* puzzle, int i);
bool findDecidableCell(Table* puzzle);
void printTable(Table* puzzle);

int main()
{
  read_input();
}

void read_input()
{
  char temp, inp[82]; //9x9 sudo puzzle + \n
  int i, j, areacount, areamult;
  Table puzzle[81];

  fgets(inp, 83, stdin);

  areacount = -1;

  for(i = 0; i < 81; i++) //check for error input
  {
    if (!isdigit(inp[i]) && inp[i] != '.' && inp[i] == '0')
    {
      cout << "ERROR: expected {value} got " << inp[i] << endl;
      exit(1);
    }
    
    puzzle[i].num = inp[i];
    if (inp[i] == '.')
    {
        puzzle[i].choice.insert('1');
        puzzle[i].choice.insert('2');
        puzzle[i].choice.insert('3');
        puzzle[i].choice.insert('4');
        puzzle[i].choice.insert('5');
        puzzle[i].choice.insert('6');
        puzzle[i].choice.insert('7');
        puzzle[i].choice.insert('8');
        puzzle[i].choice.insert('9');
        emptyCellCount++;
    }

    j = i / 9;  // row number from row 0->8
    puzzle[i].row = j;

    j = i % 9; // col num from 0->8
    puzzle[i].col = j;

    if ((i%3) == 0) //3x3 location of the num
      areacount++;

    areamult = (i / 27) * 3;

    if (areacount >= 3)
      areacount = 0;

    puzzle[i].area = areacount + areamult;
  }

  if (inp[81] != '\n')
  {
    cout << "ERROR: expected \\n got " << inp[81] << endl;
    exit(1);
  }

  temp = fgetc(stdin);
  if (!feof(stdin))
  {
    cout << "ERROR: expected EOF got " << temp << endl;
    exit(1);
  }

  for (i = 0; i < 81; i++)
    setSeen(puzzle, i);

  while (findDecidableCell(puzzle) == true && emptyCellCount != 0)
  {
    for (i = 0; i < 81; i++)
      setSeen(puzzle,i);
  }

  if (emptyCellCount == 0)
    printTable(puzzle);
}

void setSeen(Table* puzzle, int i)
{
  int areaZero[] = {0, 1, 2, 9, 10, 11, 18, 19, 20},
      areaOne[] = {3, 4, 5, 12, 13, 14, 21, 22, 23},
      areaTwo[] = {6, 7, 8, 15, 16, 17, 24, 25, 26},
      areaThree[] = {27, 28, 29, 36, 37, 38, 45, 46, 47},
      areaFour[] = {30, 31, 32, 39, 40, 41, 48, 49, 50},
      areaFive[] = {33, 34, 35, 42, 43, 44, 51, 52, 53},
      areaSix[] = {54, 55, 56, 63, 64, 65, 72, 73, 74},
      areaSeven[] = {57, 58, 59, 66, 67, 68, 75, 76, 77},
      areaEight[] = {60, 61, 62, 69, 70, 71, 78, 79, 80},
      j;

//      for (i = 0; i < 81; i++)
//      {
        if (!isdigit(puzzle[i].num))
        {
          for (j = 1; j < 10; j++)
          {
            puzzle[i].choice.erase(puzzle[puzzle[i].col + (j*9)].num);
            puzzle[i].choice.erase(puzzle[(puzzle[i].row * 9) + j - 1].num);   
          }

          switch(puzzle[i].area)
          {
            case 0:
              for (j = 0; j < 9; j++)
                puzzle[i].choice.erase(puzzle[areaZero[j]].num);
              break;
            case 1:
              for (j = 0; j < 9; j++)
                puzzle[i].choice.erase(puzzle[areaOne[j]].num);
              break;
            case 2:
              for (j = 0; j < 9; j++)
                puzzle[i].choice.erase(puzzle[areaTwo[j]].num);
              break; 
            case 3:
              for (j = 0; j < 9; j++)
                puzzle[i].choice.erase(puzzle[areaThree[j]].num);
              break;
            case 4:
              for (j = 0; j < 9; j++)
                puzzle[i].choice.erase(puzzle[areaFour[j]].num);
              break;
            case 5:
              for (j = 0; j < 9; j++)
                puzzle[i].choice.erase(puzzle[areaFive[j]].num);
              break;
            case 6:
              for (j = 0; j < 9; j++)
                puzzle[i].choice.erase(puzzle[areaSix[j]].num);
              break;
            case 7:
              for (j = 0; j < 9; j++)
                puzzle[i].choice.erase(puzzle[areaSeven[j]].num);
              break;
            case 8:
              for (j = 0; j < 9; j++)
                puzzle[i].choice.erase(puzzle[areaEight[j]].num);
              break;
          }        
        }
//      }
}

bool findDecidableCell(Table* puzzle)
{
  int i;
  set<char>::iterator it;

  for (i = 0; i < 81; i++)
  {
    if (puzzle[i].choice.size() == 1)
    {
      it = puzzle[i].choice.begin();
      puzzle[i].num = *it;
      puzzle[i].choice.clear();
      emptyCellCount--;
      return true;
    }
  }

  return false;
}

void printTable(Table* puzzle)
{
  int i;

  for (i = 0; i < 81; i++)
    cout << puzzle[i].num;

  cout << endl;
}
