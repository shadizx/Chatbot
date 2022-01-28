// bots.h
// Shadi Zoldjalali
// contains all bot classes
// Last modified: 7/23/2021

#include "cmpt_error.h"
#include "Chatbot.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <cassert>
using namespace std;

// for my smartbot:
#include <math.h>

// user chatbot
class User_bot : public Chatbot
{
    string message;

public:
    User_bot(const string &name)
        : Chatbot(name) {}

    void give_msg(const string &s) { message = s; }

    string get_msg()
    {
        cout << "Enter a line of text: ";
        getline(cin, message);
        return message;
    }
};

// single reply bot
class Single_reply_bot : public Chatbot
{
    string message, input;

public:
    Single_reply_bot(const string &name, const string &message)
        : Chatbot(name), message(message) {}

    void give_msg(const string &s) { input = s; }
    string get_msg() { return message; }
};

// moobot
class Moo_bot : public Single_reply_bot
{
public:
    Moo_bot(const string &name)
        : Single_reply_bot(name, "moo") {}
};

// namebot
class Name_bot : public Single_reply_bot
{
public:
    Name_bot(const string &name)
        : Single_reply_bot(name, string("I am ") + name + "!") {}
};

// echobot
class Echo_bot : public Chatbot
{
    string message;

public:
    Echo_bot(const string &name, const string &message)
        : Chatbot(name), message(message) {}

    void give_msg(const string &s) { message = s; }
    string get_msg() { return message; }
};

// random reply bot
class Random_reply_bot : public Chatbot
{
    string message;
    vector<string> words;

public:
    // main constructor
    Random_reply_bot(const string &name, vector<string> words)
        : Chatbot(name), words(words)
    {
        if (words.empty() == true)
        {
            cmpt::error("Words list is empty");
        }
        srand(time(0));
    }

    // file constructor
    Random_reply_bot(const string &name, const string &file)
        : Chatbot(name)
    {
        string word;
        ifstream fin(file);

        if (!fin) // file cant be opened
        {
            cmpt::error("File cannot be opened");
        }
        if (fin.peek() == ifstream::traits_type::eof()) // means file is empty
        {
            cmpt::error("File is empty");
        }
        while (getline(fin, word))
        {
            words.push_back(word);
        }
        fin.close();
        srand(time(0));
    }

    void give_msg(const string &s) { message = s; }

    string get_msg()
    {
        return words[rand() % words.size()];
    }
};

// date and time bot
class Datetime_bot : public virtual Chatbot
{
    vector<string> defwords;
    string stime, temp, sdate, out, hour, min, year, month, day, noon = "am";

public:
    // default constructor for inheritance
    Datetime_bot() : Chatbot(temp){};

    // main constructor
    Datetime_bot(const string &name, vector<string> defwords)
        : Chatbot(name), defwords(defwords)
    {
        out = currtime() + ", " + currdate();
    }

    string currdate()
    {
        time_t timenow = time(0); // current time
        tm *now = localtime(&timenow);

        // getting year, month, and day
        year = to_string(1900 + now->tm_year);
        month = to_string(1 + now->tm_mon);
        day = to_string(now->tm_mday);

        return year + "-" + month + "-" + day;
    }

    virtual string currtime()
    {
        string digitmin = "";
        time_t timenow = time(0); // current time
        tm *now = localtime(&timenow);

        // declaring am or pm
        if (now->tm_hour >= 12)
        {
            now->tm_hour -= 12;
            noon = "pm";
        }

        if (now->tm_hour == 0)
        {
            now->tm_hour = 12;
        }

        // whether we need to add 0 in front of min
        if (now->tm_min < 10)
        {
            digitmin = "0";
        }

        // getting hours, mins, and secs
        hour = to_string(now->tm_hour);
        min = to_string(now->tm_min);

        return hour + ":" + digitmin + min + noon;
    }

    virtual void lowerall(string &a)
    {
        // converting all letters to lowercase:
        std::for_each(a.begin(), a.end(), [](char &c)
                      { c = ::tolower(c); });
    }

    virtual bool found(const string &a, const string &b)
    {
        // seeing if string is found in substring
        return (a.find(b) != std::string::npos);
    }

    void give_msg(const string &s)
    {
        string full = s;
        lowerall(full);

        stime = currtime();
        sdate = currdate();

        if (found(full, "time"))
        {
            out = stime;
            if (found(full, "date"))
                out += ", " + sdate;
        }
        else if (found(full, "date"))
        {
            out = sdate;
            if (found(full, "time"))
                out += ", " + stime;
        }
        else
        {
            out = defwords[rand() % defwords.size()];
        }
    }
    string get_msg()
    {
        return out;
    }
};

class table
{
    vector<string> input;
    vector<string> responses;

public:
    // def const
    table(vector<string> s, vector<string> r) : input(s), responses(r){};

    string getinput(int x) { return input[x]; }
    string getresponse(int x) { return responses[x]; }

    int getinputsize() { return input.size(); }
    int getresponsesize() { return responses.size(); }
};

table database[] = {

    {{"hi", "hello", "hey"},
     {"Helloooooooooo",
      "Hi there!",
      "What's crackin?"}},

    {{"bye"},
     {"Nice talking to you :)",
      "See you next time!",
      "Goodbye, fellow friend :'(",
      "Have a splendid day!"}},

    {{"whats up", "what's up"},
     {"Nothin but the rent",
      "A two letter word indicating direction",
      "Living the dream",
      "Is it just me or does it smell like updog in here?",
      "Childhood obesity in America"}},

    {{"who are you", "what are you"},
     {"I am a smart bot!",
      "I'm the smartest bot alive! Muahahahahahhah",
      "I'm a Sma- Uh nevermind, I'm a human."}},

    {{"how old are you", "what's your age"},
     {"I have infinite years of life",
      "Why do you want to know huh!",
      "It's a secret that surpasses your reality"}},

    {{"what can you do"},
     {"Well, I can engage in conversation, tell you a joke, maybe if you're wonding about the date and time I can tell you that.\n\nOh, I can also calculte some math problems for you! ( In Pemdas order ;) )"}},

    {{"how are you"},
     {"I'm great! I hope you're doing fine as well",
      "I'm doing well thanks",
      "I'm good!"}},

    {{"thanks", "thank you"},
     {"No Problemo",
      "Anytime",
      "No Problem!"}},

    {{"how's it going", "how is it going?"},
     {"It's going swell!",
      "I'ts going.... It's going",
      "Going pretty well thanks"}},

    {{"joke"},
     {"I asked my North Korean friend how it was there, he said he couldn't complain",
      "You'd have to be really low to pickpocket a midget",
      "There's 10 kinds of people in the world. Those who understand binary, and those who don't",
      "Parallel lines have so much in common but it's shame they'll never meet",
      "Remains to be seen if glass coffins become popular",
      "My dad has the heart of a lion, and a lifetime ban from the zoo",
      "Say what you want about deaf people",
      "I know a lot of jokes about unemployed people but none of them work",
      "A soldier survived mustard gas in battle, and then pepper spray by the police. He's now a seasoned veteran",
      "If life gives you melons, you're probably dyslexic",
      "Shout out to the people who want to know what the opposite of in is",
      "Diarrhea is hereditary ... It runs in your jeans",
      "I'm addicted to brake fluid, but I can stop whenever I want",
      "Why shouldn't you hire a midget as a chef?\nThe steaks are too high",
      "Never trust an atom. They make up everything"}},

    {{"are you real"},
     {"Obviously!!!",
      "I'm offended that you have to ask that",
      "Duh!!"}}};

// smartbot class
/* Techniques that I have used:
    To start of with the most basic idea I have built this on; I made a class called
    table that has two vector strings. I then made an array of objects of that class.
    My reasoning of this was so then it would be very easy to detect which response goes
    with the corresponding input. Also, If I wanted to make another chatbot with a different
    purpose I can easily use the database again.

    I have 3 vector strings in private with specific outputs that are pointed towards this chatbot only.
    I could have supplied these in the databse but it made more sense to put it in here because
    It is specifically directed towards this bot

    Explanation of the functionalities of the methods in my Smartbot:
        -Find_response:
            This method highlights the easy access of the inputs and outputs of the database.
            It takes in an input string which is whatever the user inputs and goes through
            the database inputs vector<string> to find a match. The way I have implemenented it
            does not depend on upper case or lowercase. When it does find the input in the database,
            It adds all the responses to a vector of responses which I then pick one of them at random.
        -datetostring:
            This is basically the date function in my date time bot, except it outputs the the date with a
            day as a string, similar to how the date is shown in Windows.
        -removespace:
            removes all the spaces in a string so the solve function can work as intended.
        -solve:
            My proudest functionality of this chatbot. It is a recursive solving function that can take
            any string that is a mathematical expression and solve it. The most impressive thing is that
            it will solve it in PEMDAS order. Very simple yet impressive function. The time complexity of it
            seems a little costly, but this is the easiest way that I thought of.
        -stringsolve:
            used for solve. Takes the input of the user and parses it so its only the numerical input
            thats remaining, and that is what the solve function takes in.
        -round:
            Not only does this round the number, it displays the decimals only if they are needed. I am
            also proud of the way I implemented this. Used for the solve function
        -rootsolve:
            Takes in user input and solves the root of a number if asked for. Round is used for this too.

    Other Functionalies of the smartbot:
        -Tells date and time
        -All responses are random so it is more human-like
        -Alot of nice and funny jokes
        -It can detect and tell you its name if asked for

    Most important of all, I have implened this smartbot in an object oriented way. Even the database is in
    a class. I did want to have the entire database in the table class, but upon talking to a TA, they told
    me that this way was more OOP.

    hope you enjoy this as much as I did. I did want to add some games to it like hangman and tic tac toe
    but I didn't have enough time to perfec those.

    The link I used to get some ideas for my smartbot:
    https://www.codeproject.com/Articles/36106/Chatbot-Tutorial
*/
class Smart_bot : public virtual Chatbot, Datetime_bot
{
    int databasesize = sizeof(database) / sizeof(database[0]);
    string out, answer, name;

    vector<string> greeting = {
        "Greetings, fellow earthling",
        "Smartbot is on and ready to go!",
        "I have come to life!",
        "You are now graced with my presence",
        "Hello little one",
    };

    vector<string> outname =
        {"My name is ",
         "I am ",
         "My name? It's "};

    vector<string> confused = {
        "I'm not sure I understood that",
        "Hmm, I don't know",
        "Sorry I did not understand that"};

    // find method to get responses
    vector<string> find_response(string input)
    {
        vector<string> result;

        for (int i = 0; i < databasesize; ++i)
        {
            for (int j = 0; j < database[i].getinputsize(); ++j)
            {
                if (found(input, database[i].getinput(j)))
                {
                    for (int k = 0; k < database[i].getresponsesize(); ++k)
                    {
                        result.push_back(database[i].getresponse(k));
                    }
                }
            }
        }
        return result;
    }

    string datetostring()
    {
        time_t timenow = time(0); // current time
        tm *now = localtime(&timenow);

        // getting year, month, and day
        string year = to_string(1900 + now->tm_year);
        string day = to_string(now->tm_mday);
        string month, wkday;
        int monthnum = 1 + now->tm_mon;
        int dayoweek = now->tm_wday;

        switch (dayoweek)
        {
        case 1:
            wkday = "Monday";
            break;
        case 2:
            wkday = "Tuesday";
            break;
        case 3:
            wkday = "Wednesday";
            break;
        case 4:
            wkday = "Thursday";
            break;
        case 5:
            wkday = "Friday";
            break;
        case 6:
            wkday = "Saturday";
            break;
        case 7:
            wkday = "Sunday";
            break;
        }

        switch (monthnum)
        {
        case 1:
            month = "January";
            break;
        case 2:
            month = "February";
            break;
        case 3:
            month = "March";
            break;
        case 4:
            month = "April";
            break;
        case 5:
            month = "May";
            break;
        case 6:
            month = "June";
            break;
        case 7:
            month = "July";
            break;
        case 8:
            month = "August";
            break;
        case 9:
            month = "September";
            break;
        case 10:
            month = "October";
            break;
        case 11:
            month = "November";
            break;
        case 12:
            month = "December";
            break;
        }
        return wkday + ", " + month + " " + day + ", " + year;
    }

    void removespace(string &in)
    {
        // removes all spacs inside a string.
        // using remove function we used in an assignment earlier

        // last line is to modify length of container (string)
        string::iterator end_pos = remove(in.begin(), in.end(), ' ');
        in.erase(end_pos, in.end());
    }

    double solve(string input)
    {

        removespace(input);

        // for the recursion below, here is the explanation.
        // if a mathematical expression is found, it will return whatever that's
        // before that expression, plus whatever is after that expression. but it
        // will also solve whatever that is before and after the expression before it
        // adds it.
        for (int i = 0; i < input.length(); i++)
        {
            if (input[i] == '+')
            {
                return solve(input.substr(0, i)) + solve(input.substr(i + 1, input.length() - i - 1));
            }
            else if (input[i] == '-')
            {
                return solve(input.substr(0, i)) - solve(input.substr(i + 1, input.length() - i - 1));
            }
        }

        // doing mult and divison in another for loop so we can abide by
        // pemdas / bedmas
        for (int i = 0; i < input.length(); i++)
        {
            if (input[i] == '*')
            {
                return solve(input.substr(0, i)) * solve(input.substr(i + 1, input.length() - i - 1));
            }
            else if (input[i] == '/')
            {
                return solve(input.substr(0, i)) / solve(input.substr(i + 1, input.length() - i - 1));
            }
            else if (input[i] == '%')
            {
                return (int)solve(input.substr(0, i)) % (int)solve(input.substr(i + 1, input.length() - i - 1));
            }
        }

        return stod(input);
    }

    string stringsolve(string in)
    {
        int beg = in.find_first_of("0123456789");
        int last = in.find_last_of("0123456789");

        int check = in.find_first_of("+-*/%");

        if (beg == -1 || last == -1 || check == -1)
        {
            return "";
        }

        return in.substr(beg, last + 1);
    }

    string round(double number)
    {
        int decimal = (number * 100) - ((int)number * 100);

        if (decimal == 0)
        {
            return to_string((int)number);
        }
        else if (decimal % 10 == 0)
        {
            return to_string((int)number) + "." + to_string(decimal / 10);
        }
        else if (decimal > 10)
        {
            return to_string((int)number) + "." + to_string(decimal);
        }
        else
        {
            return to_string((int)number) + ".0" + to_string(decimal);
        }
    }

    double rootsolve(string input)
    {
        int beg = input.find_first_of("0123456789");
        int last = input.find_last_of("0123456789");

        return sqrt(stod(input.substr(beg, last + 1)));
    }

public:
    // constructor
    Smart_bot(const string &name) : Chatbot(name),
                                    name(name)
    {
        srand(time(NULL));
        out = greeting[rand() % greeting.size()];
    }

    void give_msg(const string &s)
    {

        string input = s;
        lowerall(input);
        vector<string> result = find_response(input);

        if (found(input, "what's your name") || found(input, "whats your name"))
        {
            out = outname[rand() % outname.size()] + name;
        }
        else if (found(input, "bye"))
        {
            out = result[rand() % result.size()];
            // exit() // tried this but it results in memleaks because the destructors
            // of the classes won't be called
        }
        else if (found(input, "time") && found(input, "date"))
        {
            out = "It is " + datetostring() + ", and the time is " + currtime();
        }
        else if (found(input, "time"))
        {
            out = "The time is " + currtime();
        }
        else if (found(input, "date"))
        {
            out = "The date today is " + datetostring();
        }
        else if (stringsolve(input) != "")
        {
            out = round(solve(stringsolve(input)));
        }
        else if (found(input, "square root"))
        {
            out = round(rootsolve(input));
        }
        else if (result.size() == 0)
        {
            out = confused[rand() % confused.size()];
        }
        else
        {
            out = result[rand() % result.size()];
        }
    }
    string get_msg()
    {
        return out;
    }

    ~Smart_bot() {}
};