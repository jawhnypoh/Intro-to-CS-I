/******************************************************
** Program: hw6.cpp
** Author: Johnny Po
** Date: 3/13/2016
** Description: Plays the Minesweeper Game
** Input: integer numbers
** Output: Game will be played
******************************************************/

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void make_boards(int, int, int);
void fill_boards(char**, char**, int, int, int);
void place_mines(int, int, int, char**);
void draw_boards(char**, char**, int, int, int);
void flag_or_open(int, int, char**, char**, int);
void location_1(char**, char**, int, int, int);
void flag_board(char**, char**, int, int, int, int, int);
void location_2(char**, char**, int, int, int);
void open_board(char**, char**, int, int, int, int, int);
int check_around(char**, char**, int, int, int, int);
int check_surrounding(char**, char**, int, int, int, int, int, int);
int check_surrounding2(char**, char**, int, int, int, int, int, int);
void check_count(char**, char**, int, int, int, int, int, int);
void game_win(char**, int, int);
void game_end(char**, int, int, int);
void play_again(int, int, int);
void repeat(int, int, int);

int main(int argc, char *argv[])
{
  int rows, columns, mines;
  srand(time(NULL));

  if(argc == 7)
  {
    rows = atoi(argv[2]);
    cout <<"Rows: " << rows;

    columns = atoi(argv[4]);
    cout <<"  | Columns: " << columns;

    mines = atoi(argv[6]);
    cout <<"  | Mines: " << mines << endl;

    cout << endl;
    cout <<"Hello! Welcome to Minesweeper! " << endl;
    cout << endl;
  }
  else
  {
    cout <<"Not enough, or too many arguments! " << endl;
    cout <<"Your Arguments: " << argc << ", need 7 Arguments " << endl;
    return 0;
  }

  make_boards(rows, columns, mines);

  return 0;
}

/***********************************************************************************************************
Function: make_boards
Description: Initializes the boards
Return: Nothing
Pre-Conditions: Variables must have something in them, must exist
Post-Conditions: 2D arrays will be created
************************************************************************************************************/
void make_boards(int rows, int columns, int mines)
{
  char **board = new char*[rows];
  for (int i=0; i<rows; i++)
    board[i] = new char[columns];

  char **answer_board = new char*[rows];
  for (int i=0; i<rows; i++)
    answer_board[i] = new char[columns];

  /*for(int i=0; i<r; i++)
    delete[] array[i];
  delete[] array;*/

  fill_boards(board, answer_board, rows, columns, mines);
}

/***********************************************************************************************************
Function: fill_boards
Description: Fills the 2D arrays with stuff
Return: Nothing
Pre-Conditions: Variables must have something, must exist
Post-Conditions: 2D arrays will be filled with stuff
************************************************************************************************************/
void fill_boards(char** board, char** answer_board, int rows, int columns, int mines)
{
  for(int i=0; i<rows; i++)
  {
		for(int j=0; j<columns; j++)
    {
			answer_board[i][j]='O';
			board[i][j]='O';
    }
  }
  place_mines(mines, rows, columns, answer_board);
  draw_boards(board, answer_board, rows, columns, mines);

}

/***********************************************************************************************************
Function: place_mines
Description: Randomly place smines on the 2D array
Return: Nothing
Pre-Conditions: Variables must have something in them, must exit
Post-Conditions: Mines will be randomly placed on the 2D array
************************************************************************************************************/
void place_mines(int mines, int rows, int columns, char** answer_board)
{
  int randr, randc;

  cout <<"There are " << mines << " mines on the board. " << endl;
  cout << endl;

  for(int i = 0; i < mines; i++)
  {
    randr = (rand()%rows); // Randomly assign for Row
    randc = (rand()%columns); // Randomly assign for Columns

    answer_board[randr][randc] = '*';
  }
}

/***********************************************************************************************************
Function: draw_boards
Description: Prints out the boards in the command line
Return: Nothing
Pre-Conditions: Variables must have soemthing in them, must exist
Post-Conditions: 2D arrays will be drawn out
************************************************************************************************************/
void draw_boards(char** board, char** answer_board, int rows, int columns, int mines)
{
  for(int i=0; i<rows; i++)
  {
    for(int j=0; j<columns; j++)
    {
      cout <<" " << board[i][j];
    }
    cout <<" " << endl;
  }
  cout << endl;


  /*cout <<"Answer: " << endl;
  for(int i=0; i<rows; i++)
  {
    for(int j=0; j<columns; j++)
    {
      cout <<" " << answer_board[i][j];
    }
    cout <<" " << endl;
  }
  cout << endl;*/

  flag_or_open(rows, columns, board, answer_board, mines);
}

/***********************************************************************************************************
Function: flag_or_open
Description: Asks user if they want to flag, open, or quit game
Return: Nothing
Pre-Conditions: Variables must have something in them, must exist
Post-Conditions: User will be asked stuff
************************************************************************************************************/
void flag_or_open(int rows, int columns, char** board, char** answer_board, int mines)
{
  int choice;
  cout <<"Would you like to Flag(1), Open(2), or Give Up(3)? " << endl;
  cin >> choice;

  if(choice == 1)
  {
    location_1(board, answer_board, rows, columns, mines);
  }
  else if(choice == 2)
  {
    location_2(board, answer_board, rows, columns, mines);
  }
  else if(choice == 3)
  {
    cout <<"Better luck next time! " << endl;

    repeat(rows, columns, mines);
  }
  else
  {
    while(choice < 1 || choice >= 3)
    {
      cout <<"Invalid Choice! " << endl;
      flag_or_open(rows, columns, board, answer_board, mines);
    }
  }
}

/***********************************************************************************************************
Function: location_1
Description: Finds the location based on user input to flag the board
Return: Nothing
Pre-Conditions: Variables must have something in them, must exist
Post-Conditions: Location to flag on the board will be found
************************************************************************************************************/
void location_1(char** board, char** answer_board, int rows, int columns, int mines)
{
  int row1, column1;

  cout <<"Choose a Row and Column: " << endl;

  cout <<"Row: ";
  cin >> row1;

  cout <<"Column: ";
  cin >> column1;

  flag_board(board, answer_board, row1, column1, rows, columns, mines);
}

/***********************************************************************************************************
Function: flag_board
Description: Flags the board based on user-inputted location
Return: Nothing
Pre-Conditions: Variables must have something in them, must exist
Post-Conditions: Board at location will be flagged
************************************************************************************************************/
void flag_board(char** board, char** answer_board, int row1, int column1, int rows, int columns, int mines)
{
  board[row1][column1] = '!';
  draw_boards(board, answer_board, rows, columns, mines);
}

/***********************************************************************************************************
Function: location_2
Description: Finds the location based on user input to open the board
Return: Nothing
Pre-Conditions: Variables must have something in them, must exist
Post-Conditions: Location to open on the board will be found
************************************************************************************************************/
void location_2(char** board, char** answer_board, int rows, int columns, int mines)
{
  int row2, column2;

  cout <<"Choose a Row and Column: " << endl;

  cout <<"Row: ";
  cin >> row2;

  cout <<"Column: ";
  cin >> column2;

  open_board(board, answer_board, row2, column2, rows, columns, mines);
}

/***********************************************************************************************************
Function: open_board
Description: Check if user-inputted location has a mine in it
Return: Nothing
Pre-Conditions: Variables must have something in them, must exist
Post-Conditions: Check if board at location has a mine
************************************************************************************************************/
void open_board(char** board, char** answer_board, int row2, int column2, int rows, int columns, int mines)
{
  int count;

  if(answer_board[row2][column2] == '*')
  {
    game_end(answer_board, rows, columns, mines);
  }
  else
  {
    //check_around(board, answer_board, row2, column2, rows, columns);
    check_surrounding(board, answer_board, row2, column2, rows, columns, mines, count);
  }
}

/*int check_around(char** board, char** answer_board, int row2, int column2, int rows, int columns)
{
  char count = 48;
  int i, j;

  if(i>0 && j>0 && i<rows && j<columns)
  {
    if(answer_board[i-1][j]=='*') count++;
    if(answer_board[i][j-1]=='*') count++;
    if(answer_board[i+1][j]=='*') count++;
    if(answer_board[i][j+1]=='*') count++;
    if(answer_board[i-1][j-1]=='*') count++;
    if(answer_board[i+1][j+1]=='*') count++;
    if(answer_board[i-1][j+1]=='*') count++;
    if(answer_board[i+1][j-1]=='*') count++;
    if(count > 0) board[i][j] = count;
    if(count == 48) board[i][j] = '0';

    return count;

    check_count(answer_board, board, rows, columns, row2, column2, count);

    //draw_boards(board, answer_board, rows, columns);

  }
}*/

/***********************************************************************************************************
Function: check_surrounding
Description: Checks surrounding 8 spots of user-inputted location on board
Return: Count
Pre-Conditions: Variables must have something in them, must exist
Post-Conditions: Count will be incremented by number of mines around location
************************************************************************************************************/
int check_surrounding(char** board, char** answer_board, int row2, int column2, int rows, int columns, int mines, int count)
{
  if(row2 > 0 && column2 > 0) // Top Left
    if(answer_board[row2 - 1][column2 - 1] == '*')
      count++;

  else if(column2 > 0) // Top
    if(answer_board[row2][column2 - 1] == '*')
      count++;

  else if(row2 < rows - 1 && column2 > 0) // Top Right
    if(answer_board[row2 + 1][column2 - 1] == '*')
      count++;

  else if(row2 > 0) // Left
    if(answer_board[row2 - 1][column2] == '*')
      count++;

  check_surrounding2(board, answer_board, row2, column2, rows, columns, mines, count);

  return count;
}

/***********************************************************************************************************
Function: check_surrounding_2
Description: Checks surrounding 8 spots of user-inputted location on board
Return: Count
Pre-Conditions: Variables must have something in them, must exist
Post-Conditions: Count will be incremented by number of mines around location
************************************************************************************************************/
int check_surrounding2(char** board, char** answer_board, int row2, int column2, int rows, int columns, int mines, int count)
{
  if(row2 < rows - 1) // Right
    if(answer_board[row2 + 1][column2] == '*')
      count++;

  else if(row2 > 0 && column2 < columns - 1) // Bottom Left
    if(answer_board[row2 - 1][column2 + 1] == '*')
      count++;

  else if(column2 < columns - 1) // Bottom
    if(answer_board[row2][column2 + 1])
      count++;

  else if(row2 < rows - 1 && column2 < columns - 1) // Bottom Right
    if(answer_board[row2 + 1][column2 + 1])
      count++;

  check_count(answer_board, board, rows, columns, mines, row2, column2, count);

  return count;
}

/***********************************************************************************************************
Function: check_count
Description: Checks the number of count
Return: Nothing
Pre-Conditions: Count variable must exist
Post-Conditions: Count will be counted up
************************************************************************************************************/
void check_count(char** answer_board, char** board, int rows, int columns, int mines, int row2, int column2, int count)
{
  if(count > 0)
  {
    board[row2][column2] = (char)('0' + count);
    draw_boards(board, answer_board, rows, columns, mines);
  }
  else
  {
    board[row2][column2] = '0';
    draw_boards(board, answer_board, rows, columns, mines);
  }

}

/***********************************************************************************************************
Function: game_win
Description: Tells user they won game
Return: Nothing
Pre-Conditions: Variables must have something in them, must exist
Post-Conditions: Tells user they won the game
************************************************************************************************************/
void game_win(char** answer_board, int rows, int columns)
{
  cout <<"Congratulations, you won! " << endl;

  for(int i=0; i<rows; i++)
  {
    for(int j=0; j<columns; j++)
    {
      cout << answer_board[i][j] << " ";
    }
    cout << endl;
  }

}

/***********************************************************************************************************
Function: game_end
Description: Ends the game
Return: Nothing
Pre-Conditions: Variables must have something in them, must exist
Post-Conditions: Game will be ended
************************************************************************************************************/
void game_end(char** answer_board, int rows, int columns, int mines)
{
  cout <<"Game over! " << endl;
  cout <<"Sorry, you lost. " << endl;

  for(int i=0; i<rows; i++)
  {
    for(int j=0; j<columns; j++)
    {
      cout << answer_board[i][j] << " ";
    }
    cout << endl;
  }

  repeat(rows, columns, mines);
}

/***********************************************************************************************************
Function: play_again
Description: Asks user for row, column, mine input again
Return: Nothing
Pre-Conditions: Must be called upon
Post-Conditions: User will input in new row, column, mine inputs
************************************************************************************************************/
void play_again(int rows, int columns, int mines)
{
  cout <<"Enter your Rows, Columns, and Mines: " << endl;

  cout <<"Rows: ";
  cin >> rows;
  cout << endl;

  cout <<"Columns: ";
  cin >> columns;
  cout << endl;

  cout <<"Mines: ";
  cin >> mines;
  cout << endl;

  make_boards(rows, columns, mines);

}

/***********************************************************************************************************
Function: repeat
Description: Asks user if they want to repeat
Return: Nothing
Pre-Conditions: Game must be ran through
Post-Conditions: User will be asked if they'd like to repeat
************************************************************************************************************/
void repeat(int rows, int columns, int mines)
{
  int again;

  cout <<"Would you like to repeat? (0) No, (1) Yes ";
  cin >> again;

  if(again == 0)
  {
    cout <<"Have a nice day! :) " << endl;
  }
  else if(again == 1)
  {
    play_again(rows, columns, mines);
  }

  while(again < 0 || again > 1)
  {
    cout <<"Bad input, try again! " << endl;
    repeat(rows, columns, mines);
  }
}
