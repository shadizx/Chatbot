// Chatbot.h
// Shadi Zoldjalali
// main chatbot class
// Last modified: 7/23/2021

#include <string>

using namespace std;

class Chatbot
{
	string name;

public:
	Chatbot(const string &name)
		: name(name)
	{
	}

	// Name of this Chatbot
	string get_name() const
	{
		return name;
	}

	// Give a string to this chatbot.
	virtual void give_msg(const string &s) = 0;

	// Get a string from this chatbot.
	virtual string get_msg() = 0;

	// virtual destructor
	virtual ~Chatbot() {}
}; // class Chatbot
