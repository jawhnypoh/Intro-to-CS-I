#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

void message_hidden(string);
void players(int, string);
void play_game(int, string);
bool spin(int, int, string);
void guess_letter(string, int);
void guess_vowel(string, int);
bool solve(string, int);
bool buy(int, int, string);
int round_money(int);
void money_bank(int);


void message_hidden(string og_message)
{
  int i = 0;

  for(i=0; i<og_message.length(); i++)
  {
    if(og_message.at(i) == ' ')
    {
      cout <<"    ";
    }
    else if(og_message.at(i) != ' ')
    {

      cout <<" _ ";

    }

  }

  cout << endl;

}

void players(int player_num, string message)
{
  for(int i=1; i<=player_num; i++)
  {
    play_game(player_num, message);
  }
}


void play_game(int player_num, string message)
{

  bool repeat = true;
  while (repeat)
  {

    int user_gain;
    user_gain = 0;

    int player_money;
    player_money = 20;

    cout <<"Player " << player_num << endl;

    // Player Choice
    int choice_play;

    cout <<"Do you want to Spin(1), Solve the Puzzle(2), or Buy a vowel(3)? " << endl;
    cin >> choice_play;
    cin.ignore();

    switch(choice_play)
    {
      case 1:
        cout <<"You chose to Spin. " << endl;
        cout << endl;

        repeat = spin(user_gain, player_money, message);

        break;

      case 2:
        cout <<"You chose to Solve the Puzzle. " << endl;
        cout << endl;

        repeat = solve(message, player_num);

        break;

      case 3:
        cout <<"You chose to Buy a vowel. " << endl;
        cout << endl;

        repeat = buy(player_money, user_gain, message);

        break;
    }
  }
}

bool spin(int user_gain, int player_money, string message)
{
    srand(time(NULL)); // Initializes Random Seed

    int spin_num;
    spin_num = rand()%22; // Generate Number between 0 - 21

    cout <<"Your wheel landed on " << spin_num << endl;
    cout << endl;

    if(spin_num == 0)
    {
      cout <<"Sorry, you lost all your money for the round. " << endl;
      player_money = 0;

      return false;

    }
    else if(spin_num == 21)
    {
      cout <<"Your turn has ended. " << endl;

      return false;
    }
    else
    {
      guess_letter(message, user_gain);

      return true;
    }

}


void guess_letter(string message, int user_gain)
{

  char letter_guess;
  cout <<"Guess a letter: " << endl;
  cin >> letter_guess;
  cin.ignore();

    int i=0;

    char message_array[i];

    int num_match = 0;

    int new_money;
    for(int i=0; i<message.length(); i++)
    {
      if(message.at(i) == letter_guess)
      {
        message_array[i] = 'x';
        num_match++;

        new_money = num_match += user_gain;
      }
    }
    cout <<"Number of matches: " << num_match << endl;
    cout <<"Total Money: " << new_money << endl;


    if(num_match == 0)
    {
      cout <<"Nothing, sorry " << endl;
      cout << new_money << endl;
    }

    for(int i=0; i<message.length(); i++)
    {
      if(message_array[i] == 'x')
      {
        cout << message.at(i);
      }
      else
      {
        cout << " _ ";
      }
    }

    cout << endl;

}


bool solve(string message, int player_num)
{

  string message_guess;
  cout <<"Guess the Message: " << endl;
  getline(cin, message_guess);

  if(message_guess == message)
  {
    cout <<"Correct! You guessed the right Message! " << endl;
    cout <<"Player " << player_num << " wins this Round. " << endl;

    return false;
  }
  else
  {
    cout <<"Sorry, your guess is incorrect. " << endl;

    return false;
  }

}

bool buy(int player_money, int user_gain, string message)
{
  int buy_money;

  buy_money = player_money - 10;

  cout <<"You bought a Vowel. (-$10)" << endl;
  cout <<"Total Money Left: " << buy_money << endl;
  cout << endl;

  if(buy_money < 10)
  {
    cout <<"You don't have enough money! " << endl;

    return false;
  }
  else
  {

    guess_vowel(message, user_gain);

    return true;
  }

}

void guess_vowel(string message, int user_gain)
{
  int i=0;

  char vowel_guess;
  cout <<"Guess a Vowel: " << endl;
  cin >> vowel_guess;
  cin.ignore();

  char message_array[i];

  int vowel_match = 0;

  int new_money;
  for(int i=0; i<message.length(); i++)
  {
    if(message.at(i) == vowel_guess)
    {
      message_array[i] = 'x';
      vowel_match++;

      new_money = vowel_match += user_gain;
    }
  }
  cout <<"Number of matches: " << vowel_match << endl;
  cout <<"Total Money: " << new_money << endl;


  if(vowel_match == 0)
  {
    cout <<"Nothing, sorry " << endl;
    cout << new_money << endl;
  }

  for(int i=0; i<message.length(); i++)
  {
    if(message_array[i] == 'x')
    {
      cout << message.at(i);
    }
    else
    {
      cout << " _ ";
    }
  }

  cout << endl;


}

/*int round_money(int player_money, int user_gain, int spin_num)
{


}*/

void money_bank(int player_money, int user_gain)
{
  player_money += user_gain;

}

int main()
{

  cout <<"Welcome to the Wheel of Fortune! " << endl;


  string og_message; // Takes in Message for the players to guess

  cout <<"Enter the Message you want to guess: " << endl;
  getline(cin, og_message);

  cout << endl;

  int player_num;
  cout <<"How many Players are there? (1-3) " << endl;
  cin >> player_num;
  cin.ignore();

  cout << endl;

  int round_num;
  cout <<"How many rounds for winning? " << endl;
  cin >> round_num;
  cin.ignore();

  /* Player Round Numbers */
  int rounds = 1;
  bool game_run = true;

  while (round_num > rounds)
  {
    for(int i=1; i<=round_num; i++)
    {

      while (game_run)
      {
        play_game(player_num, og_message);
      }

    }
  }

  return 0;
}
