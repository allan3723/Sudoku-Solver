// ache; Cheng, Allan

#include <list>
#include <stack>
#include <iostream>
#include <set>
using namespace std;
#include <cctype>
#include <stdlib.h>
#include <stdio.h>

class Table
{
  private:
    set<char>::iterator it;
    Table* copy;
    stack<char> numstack;
    int i;
  public:
  int row, col, area, count;
  char num;
  set<char> choice;

  void push()
  {
  }

  void pop()
  {
//    choice = choicestack.top();
//    num = numstack.top();
//    choicestack.pop();
//    numstack.pop();
  }

  void print() //temporary - use to print out possibilities
  { 
    for (it = choice.begin(); it != choice.end(); i++)
      cout << " " << *it;
    cout << endl;
  }
};

set<int> emptyCell;
list<Table*> solutions;
bool solutionFound = false;
bool guessed = false;
int areaZero[] = {0, 1, 2, 9, 10, 11, 18, 19, 20}, //3x3 grids
    areaOne[] = {3, 4, 5, 12, 13, 14, 21, 22, 23},
    areaTwo[] = {6, 7, 8, 15, 16, 17, 24, 25, 26},
    areaThree[] = {27, 28, 29, 36, 37, 38, 45, 46, 47},
    areaFour[] = {30, 31, 32, 39, 40, 41, 48, 49, 50},
    areaFive[] = {33, 34, 35, 42, 43, 44, 51, 52, 53},
    areaSix[] = {54, 55, 56, 63, 64, 65, 72, 73, 74},
    areaSeven[] = {57, 58, 59, 66, 67, 68, 75, 76, 77},
    areaEight[] = {60, 61, 62, 69, 70, 71, 78, 79, 80};
void read_input();
void setSeen(Table* puzzle, int i);
void findSimplifications(Table* puzzle);
bool findDecidableCell(Table* puzzle);
bool hiddenSingles(Table* puzzle, int cell);
void guess(Table* puzzle);
bool check(Table* puzzle);
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
      cout << "ERROR: expected <value> got " << inp[i] << endl;
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
        emptyCell.insert(i);
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
    cout << "ERROR: expected <eof> got " << temp << endl;
    exit(1);
  }

  findSimplifications(puzzle);
//  printTable();
}
void findSimplifications(Table* puzzle)
{
  int i;
  set<char>::iterator it;
  char temp[81];

  for (i = 0; i < 81; i++)
    setSeen(puzzle, i);

  while ((findDecidableCell(puzzle) == true) && emptyCell.size() != 0)
  {
    for (i = 0; i < 81; i++)
      setSeen(puzzle,i);
  }

  if (emptyCell.size() != 0)
    guess(puzzle);
  else
    if (!guessed && check(puzzle))
      printTable(puzzle);
    
}

void setSeen(Table* puzzle, int i)
{
  int j;

        if (!isdigit(puzzle[i].num))
        {
          for (j = 0; j < 9; j++)
          {
            puzzle[i].choice.erase(puzzle[puzzle[i].col + (j*9)].num);
            puzzle[i].choice.erase(puzzle[(puzzle[i].row * 9) + j].num);  
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
              {
                puzzle[i].choice.erase(puzzle[areaThree[j]].num); 
              }
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

}

bool findDecidableCell(Table* puzzle)
{
  int i;
  set<char>::iterator it;

  for (i = 0; i < 81; i++)
  {
    if (puzzle[i].choice.size() == 1) //hidden single
    {
      it = puzzle[i].choice.begin();
      puzzle[i].num = *it;
      puzzle[i].choice.clear();
      emptyCell.erase(i);
      return true;
    }
    else
      if (puzzle[i].choice.size() > 1)
        if(hiddenSingles(puzzle, i) == true)
          return true; 
  } //end for

  return false;
}

bool hiddenSingles(Table* puzzle, int cell)
{
  int i, j;
  set<char>::iterator it;
  set<char>::iterator sec;
  bool repeat = false;

  for (it = puzzle[cell].choice.begin(); it != puzzle[cell].choice.end(); it++)
  {
    for (i = 1; ((cell + i) < 81) && puzzle[cell + i].row == puzzle[cell].row; i++)
    {
      for(sec = puzzle[cell + i].choice.begin(); sec != puzzle[cell + i].choice.end(); sec++)
      {
        if (*sec == *it)
        {
          repeat = true;
          break;
        } //if
        
        if (repeat == true)
          break;
      } //for
    } //for

    for (i = 1; ((cell - i) >= 0) && puzzle[cell - i].row == puzzle[cell].row; i++)
    {
      for(sec = puzzle[cell - i].choice.begin(); sec != puzzle[cell - i].choice.end(); sec++)
      {
        if (*sec == *it)
        {
          repeat = true;
          break;
        } //if

        if (repeat == true)
          break;
      } //for
    } //for -- ROW BACKWARDS

    if (repeat == false)
    {
      puzzle[cell].num = *it;
      puzzle[cell].choice.clear();
      emptyCell.erase(cell);
      return true;
    }
    else
      repeat = false; //no H.S in row so check col

    for(i = 1; (cell + (i * 9)) < 81; i++)
    {
      for(sec = puzzle[cell + (i * 9)].choice.begin(); sec != puzzle[cell + (i * 9)].choice.end(); sec++)
      {
        if (*sec == *it)
        {
          repeat = true;
          break;
        } //if

        if (repeat == true)
          break;
      } //for
    } //for - COL FORWARD

    for (i = 1; (cell - (i * 9)) >= 0; i++)
    {
      for(sec = puzzle[cell - (i * 9)].choice.begin(); sec != puzzle[cell - (i * 9)].choice.end(); sec++)
      {
        if (*sec == *it)
        {
          repeat = true;
          break;
        }

        if (repeat == true)
          break;
      } // for 
    } //for - COL BACKWARDS

    if (repeat == false)
    {
      puzzle[cell].num = *it;
      puzzle[cell].choice.clear();
      emptyCell.erase(cell);
      return true;
    }
    else
      repeat = false; //no H.S. in col so check unit

    switch(puzzle[cell].area)
    {
      case 0:
        for (i = 0; i < 9; i++)
        {
          if (cell == areaZero[i])
            continue;
          else
            for (sec = puzzle[areaZero[i]].choice.begin(); sec != puzzle[areaZero[i]].choice.end(); sec++)
              if (*it == *sec)
              {
                repeat = true;
                break;
              }
          if (repeat == true)
            break;
        } //for
          break;
      case 1:
        for (i = 0; i < 9; i++)
        {
          if (cell == areaOne[i])
            continue;
          else
            for (sec = puzzle[areaOne[i]].choice.begin(); sec != puzzle[areaOne[i]].choice.end(); sec++)
              if (*it == *sec)
              {
                repeat = true;
                break;
              }
          if (repeat == true)
            break;
        } //for
          break;
      case 2:
        for (i = 0; i < 9; i++)
        {
          if (cell == areaTwo[i])
            continue;
          else
            for (sec = puzzle[areaTwo[i]].choice.begin(); sec != puzzle[areaTwo[i]].choice.end(); sec++)
              if (*it == *sec)
              {
                repeat = true;
                break;
              }
          if (repeat == true)
            break;
        } //for
          break;
      case 3:
        for (i = 0; i < 9; i++)
        {
          if (cell == areaThree[i])
            continue;
          else
            for (sec = puzzle[areaThree[i]].choice.begin(); sec != puzzle[areaThree[i]].choice.end(); sec++)
              if (*it == *sec)
              {
                repeat = true;
                break;
              }
          if (repeat == true)
            break;
        } //for
          break;
      case 4:
        for (i = 0; i < 9; i++)
        {
          if (cell == areaFour[i])
            continue;
          else
            for (sec = puzzle[areaFour[i]].choice.begin(); sec != puzzle[areaFour[i]].choice.end(); sec++)
              if (*it == *sec)
              {
                repeat = true;
                break;
              }
          if (repeat == true)
            break;
        } //for
          break;
      case 5:
        for (i = 0; i < 9; i++)
        {
          if (cell == areaFive[i])
            continue;
          else
            for (sec = puzzle[areaFive[i]].choice.begin(); sec != puzzle[areaFive[i]].choice.end(); sec++)
              if (*it == *sec)
              {
                repeat = true;
                break;
              }
          if (repeat == true)
            break;
        } //for
          break;
      case 6:
        for (i = 0; i < 9; i++)
        {
          if (cell == areaSix[i])
            continue;
          else
            for (sec = puzzle[areaSix[i]].choice.begin(); sec != puzzle[areaSix[i]].choice.end(); sec++)
              if (*it == *sec)
              {
                repeat = true;
                break;
              }
          if (repeat == true)
            break;
        } //for
          break;
      case 7:
        for (i = 0; i < 9; i++)
        {
          if (cell == areaSeven[i])
            continue;
          else
            for (sec = puzzle[areaSeven[i]].choice.begin(); sec != puzzle[areaSeven[i]].choice.end(); sec++)
              if (*it == *sec)
              {
                repeat = true;
                break;
              }
          if (repeat == true)
            break;
        } //for
          break;
      case 8:
        for (i = 0; i < 9; i++)
        {
          if (cell == areaEight[i])
            continue;
          else
            for (sec = puzzle[areaEight[i]].choice.begin(); sec != puzzle[areaEight[i]].choice.end(); sec++)
              if (*it == *sec)
              {
                repeat = true;
                break;
              }
          if (repeat == true)
            break;
        } //for
          break;
    }        

    if (repeat == false)
    {
      puzzle[cell].num = *it;
      puzzle[cell].choice.clear();
      emptyCell.erase(cell);
      return true;
    }
  } //for - THE WHOLE FOR

  return false;
} //end function

void guess(Table* puzzle)
{
  set<int>::iterator it;
  stack <set<int> > empty;
  set<char>::iterator cit;
  stack<Table> alternatives;
  stack< set<char> > test;
  int cell, size, i = 0, j, k = 0, size2;
  Table temp[81];
  guessed = true;
printTable(puzzle);
  if (emptyCell.size() == 0 && !alternatives.empty()) //no alts, no cell to try anymore
  {
    if (solutionFound = false) //didn't find any solutions at all
    {
      cout << "No solution!\n";
      exit(1);
    }
    return;
  }
  
  size2 = emptyCell.size();
  int cells[size2];

  for (it = emptyCell.begin(); it != emptyCell.end(); it++) //goes through all empty Cell
  {
    cells[k] = *it;
    k++;
  }

  for (k = 0; k < size2; k++)
  {
    cell = cells[k];
//cout << "cell = " << cell << endl;
    size = puzzle[cell].choice.size();
    char array[size];

//cout << "puzzle[ce]].choice.size = " << puzzle[cell].choice.size() << endl;
//cout << "cell = " << cell << endl;
//printTable(puzzle);
    if (puzzle[cell].choice.size() == 0) //not a solution so return;
      return;

    emptyCell.erase(cell);     //since current cell will be filled, erase from list.
    for (cit = puzzle[cell].choice.begin(); cit != puzzle[cell].choice.end(); cit++) //all poss of cell
    { 
      array[i] = *cit;
      i++;
    } 

    for (i = 0; i < size; i++)
    {
      empty.push(emptyCell);
//cout << "on top, puzzle[0] = " << puzzle[0].num << endl;
      for (j = 0; j < 81; j++)
        alternatives.push(puzzle[j]); //saves the entire board
//printTable(puzzle);
      puzzle[cell].num = array[i];  // fills current pos in the empty cell
//cout << "puzzle[cell].num = " << puzzle[cell].num << endl;
//cout << "cell = " << cell << endl;
//printTable(puzzle);
//      puzzle[cell].choice.clear();
      findSimplifications(puzzle);  //tries to solve this guess

      if (check(puzzle) == true)
      {
        for (k = 0; k < 81; k++)
          cout << puzzle[k].num;
        cout << endl;
      }
        for (j = 80; j >= 0; j--)
        {
          puzzle[j] = alternatives.top();
          alternatives.pop();
        }
        emptyCell = empty.top();
        empty.pop(); 
//cout << "bottom, puzzle[50] = " << puzzle[50].num << endl;
//cout << "# of choices = " << puzzle[50].choice.size() << endl;
//cout << "# of emptys = " << emptyCell.size() << endl;
//cout << "alternatives = " << alternatives.size() << endl;
    } //for

      emptyCell.insert(cell); //inserts back into empty list
  } // big for
} //end guess

bool check(Table* puzzle)
{
  int i;
     
  for (i = 0; i < 81; i++)
    if (puzzle[i].num == '.' && puzzle[i].choice.size() == 0)
      return false;
  return true;
}

void printTable(Table* puzzle)
{
  int i;
//  list<Table*>::iterator it;
//  char *solution;

 // solutions.unique();
//  cout << solutions.size() << endl;
//  for (it = solutions.begin(); it != solutions.end(); it++) 
  {
    for (i = 0; i < 81; i++)
      cout << puzzle[i].num;
//    solutions.pop_front();
//  for (i = 0; i < 81; i++)
//    cout << solutions.front(); 
  cout << endl;
//  solutions.pop_front();
  } 
  
}
