// main.cpp
// Shadi Zoldjalali
// calls bot functions
// Last modified: 7/23/2021

#include "bots.h"
#include "tests.h"
#include <iomanip>
#include <string>

using namespace std;

int main()
{
  string in;

  cout << "Hello and welcome to to my code!\n\n";

  while (true)
  {
    cout << "Please select a number corresponding to the bot you would like to test from the options below\n\n";

    cout << "\tUser_bot"
         << setw(28) << "1\n"
         << "\tSingle_reply_bot"
         << setw(20) << "2\n"
         << "\tMoo_bot"
         << setw(29) << "3\n"
         << "\tName_bot"
         << setw(28) << "4\n"
         << "\tEcho_bot"
         << setw(28) << "5\n"
         << "\tRandom_reply_bot"
         << setw(20) << "6\n"
         << "\tDatetime_bot"
         << setw(24) << "7\n"
         << "\tSmart_bot"
         << setw(28) << "8\n\n"
         << "Enter 0 to exit\n";

    getline(cin, in);

    int x = stoi(in);

    switch (x)
    {
    case 0:
      return 0;
    case 1:
      User_bot_test();
      break;
    case 2:
      Single_reply_bot_test();
      break;
    case 3:
      Moo_bot_test();
      break;
    case 4:
      Name_bot_test();
      break;
    case 5:
      Echo_bot_test();
      break;
    case 6:
      Random_reply_bot_test();
      break;
    case 7:
      Datetime_bot_test();
      break;
    case 8:
      Smart_bot_test();
      break;
    default:
    {
      cout << "Number inputted is out of range (1-8)\n\n";
    }
    }
  }
  return 0;
}