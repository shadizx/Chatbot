// tests.h
// Shadi Zoldjalali
// inlcudes all test functions necessary for main
// Last modified: 7/23/2021

void converse(Chatbot *a, Chatbot *b, int max_turns = 50)
{
    for (int turn = 1; turn <= max_turns; turn++)
    {
        string a_msg = a->get_msg();
        cout << "(" << turn << ") " << a->get_name() << ": " << a_msg << "\n";

        turn++;
        if (turn > max_turns)
            return;

        b->give_msg(a_msg);
        string b_msg = b->get_msg();

        cout << "(" << turn << ") " << b->get_name() << ": " << b_msg << "\n";
        a->give_msg(b_msg);
    } // for
}

void User_bot_test()
{
    User_bot user{"Stan"};
    User_bot user2{"user2"};

    converse(&user, &user2, 10);
}

void Single_reply_bot_test()
{
    User_bot user{"user"};
    Single_reply_bot bot{"tacobot", "I love tacos!"};

    converse(&user, &bot, 10);
}

void Moo_bot_test()
{
    User_bot user{"user"};
    Moo_bot bot{"moobot"};

    converse(&user, &bot, 10);
}

void Name_bot_test()
{
    User_bot user{"user"};
    Name_bot bot{"megabot"};

    converse(&user, &bot, 10);
}

void Echo_bot_test()
{
    User_bot user{"user"};
    Echo_bot bot{"repeato", "repeato is ready to go!"};

    converse(&user, &bot, 10);
}

void Random_reply_bot_test()
{
    User_bot user{"user"};
    Random_reply_bot cat{"Mittens", {"meow", "purrr", "meeeeow"}};

    // Random_reply_bot dog{"Fido", "dog_sounds.txt"}; //file constructor

    converse(&user, &cat, 10);
}

void Datetime_bot_test()
{
    User_bot user{"user"};
    Datetime_bot dt_bot{"deetee", {"Ask me about the date or time!", "I know the date and time!"}};

    converse(&user, &dt_bot, 10);
}

void Smart_bot_test()
{
    User_bot user{"user"};

    Smart_bot smart_bot("Alan");

    converse(&smart_bot, &user, 30);
}
