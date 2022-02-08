# Chatbots

Implemented OOP to create an elegant chatbot program, inlcuding my favorite smartbot (Alan).

Some features of the Smartbot:

Techniques that I have used:

    To start of with the most basic idea I have built this on; I made a class called
    table that has two vector strings. I then made an array of objects of that class.
    My reasoning of this was so then it would be very easy to detect which response goes
    with the corresponding input. Also, If I wanted to make another chatbot with a different
    purpose I can easily use the database again.

    I have 3 vector strings in private with specific outputs that are pointed towards this chatbot only.
    I could have supplied these in the database but it made more sense to put them here because
    It is specifically directed towards this bot

    Explanation of the functionalities of the methods in my Smart bot:
        -Find_response:
            This method highlights the easy access of the inputs and outputs of the database.
            It takes in an input string which is whatever the user inputs and goes through
            the database inputs vector<string> to find a match. The way I have implemented it
            does not depend on upper case or lowercase. When it does find the input in the database,
            It adds all the responses to a vector of responses which I then pick one of them at random.
        -datetostring:
            This is the date function in my date time bot, except it outputs the date with a
            day as a string, similar to how the date is shown in Windows.
        -removespace:
            removes all the spaces in a string so the solve function can work as intended.
        -solve:
            My favorite functionality of this chatbot. It is a recursive solving function that can take
            any string that is a mathematical expression and solve it. The most impressive thing is that
            it will solve it in PEMDAS order. Very simple yet impressive function. The time complexity of it
            seems a little costly, but this is the easiest way that I thought of.
        -stringsolve:
            used for solving. Takes the input of the user and parses it so it's only the numerical input
            that's remaining, and that is what the solve function takes in.
        -round:
            Not only does this round the number, but it also displays the decimals only if they are needed. I am
            also proud of the way I implemented this. Used for the solve function
        -rootsolve:
            Takes in user input and solves the root of a number if asked for. Round is used for this too.

    Other Functionalities of the smart bot:
        -Tells date and time
        -All responses are random so it is more human-like
        -A lot of nice and funny jokes
        -It can detect and tell you its name if asked for
