//
//  main.cpp
//  HW3Q1
//
//  Created by Noela Wheeler on 5/2/21.
//

#include <iostream>
#include <string>
using namespace std;

enum CallType {
    VOICE, TEXT
};

//Medium class
class Medium
{
public:
    Medium(string msg);
    virtual string connect() const=0;
    virtual string transmit(string msg) const;
    string id() const;
    virtual ~Medium();
private:
    string m_ID;
};

//Medium implementation
//destructor
Medium::~Medium()
{}

//constructor
Medium::Medium(string msg)
{
    m_ID=msg;
}

string Medium::id() const
{
    return (m_ID);
}

string Medium::transmit(string msg) const
{
    return("text: "+msg);
}

//TwitterAccount class
class TwitterAccount : public Medium
{
public:
    TwitterAccount(string msg);
    virtual string connect() const;
    virtual ~TwitterAccount();
private:
};

//TwitterAccount implementations

//destructor
TwitterAccount::~TwitterAccount()
{cout<<"Destroying the Twitter account "+id()<<"."<<endl;}

//constructor
TwitterAccount::TwitterAccount(string msg)
: Medium(msg)
{
}

string TwitterAccount::connect() const
{
    return("Tweet");
}

//phone class
class Phone : public Medium
{
public:
    Phone(string msg, CallType type);
    virtual string connect() const;
    string transmit(string msg) const;
    virtual ~Phone();
private:
    CallType TypeofCall;
};

//phone implementations
Phone::~Phone()
{cout<<"Destroying the phone "+id()<<"."<<endl;}

Phone::Phone(string msg, CallType type)
: Medium(msg), TypeofCall(type)
{}

string Phone::connect() const
{
    return("Call");
}

string Phone::transmit(string msg) const
{
    if (TypeofCall==TEXT)
    {return("text: "+msg);}
    return("voice: "+msg);
}

//EmailAccount class
class EmailAccount : public Medium
{
public:
    EmailAccount(string msg);
    virtual string connect() const;
    virtual ~EmailAccount();
private:
};

//EmailAccount implementations
//destructor
EmailAccount::~EmailAccount()
{cout<<"Destroying the email account "+id()<<"."<<endl;}

//constructor
EmailAccount::EmailAccount(string msg)
: Medium(msg)
{}

string EmailAccount::connect() const
{
    return("Email");
}

//send function
void send(const Medium* m, string msg)
{
    cout << m->connect() << " using id " << m->id()
         << ", sending " << m->transmit(msg) << endl;
}

//main routine
int main()
{
    Medium* media[4];
    media[0] = new TwitterAccount("UCLABruinAlert");
      // Phone users may prefer messages to be left as voice or text.
    media[1] = new Phone("(310) 825 3894", VOICE);
    media[2] = new Phone("(213) 389 9060", TEXT);
    media[3] = new EmailAccount("jbroon@ucla.edu");

    cout << "Send the message." << endl;
    for (int k = 0; k < 4; k++)
        send(media[k], "Major power outage in West L.A.");

      // Clean up the media before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete media[k];
}

