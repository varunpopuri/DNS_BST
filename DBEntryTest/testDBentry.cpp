/* 
 * File:   testDBentry.cpp
 * Author: Varun
 *
 * Created on November 12, 2012, 11:51 PM
 */

#include <cstdlib>
#include "../DBentry.h"
#include <iostream>

using namespace std;

/*      string name;
	unsigned int IPaddress;
        bool active;
 */

DBentry::DBentry(){
    //name doesn't need to be initialized
    IPaddress = 0;
    active = false;
}
DBentry::DBentry (string _name, unsigned int _IPaddress, bool _active){
    name = _name;
    IPaddress = _IPaddress;
    active = _active;
}
DBentry::~DBentry(){
    //Nothing being dynamically allocated, so we can leave this empty
    cout<<"\tDestroyed a DBentry\n";
}

// sets the domain name, which we will use as a key.
void DBentry::setName(string _name){
    cout<<"\tEntered setName; \n\t";
    name = _name;
    cout<<"\t\tset name to \""<<name<<"\"\n";
}

// sets the IPaddress data.
void DBentry::setIPaddress(unsigned int _IPaddress){
    IPaddress = _IPaddress;
    cout<<"\tEntered setIPaddress;\n"
        <<"\t\tset IPaddress to \""<<IPaddress<<"\"\n";
}

// sets whether or not this entry is active.
void DBentry::setActive (bool _active){
    active = _active;
    cout<<"\tEntered setActive; \n"
        <<"\t\tset active to \""<<active<<"\"\n";
}

// returns the name.
string DBentry::getName() const{
    cout<<"\tEntered getName()"
        <<"\t\treturning name = \""<<name<<"\"\n";
    return name;
}

// returns the IPaddress data.
unsigned int DBentry::getIPaddress() const{
    cout<<"\tEntered getIPaddress(); \n"
        <<"\t\treturning \""<<IPaddress<<"\"\n";
    return IPaddress;
}

// returns whether or not this entry is active.
bool DBentry::getActive() const{
    cout<<"\tEntered getActive();\n"
        <<"\t\treturning \""<<active<<"\"\n";
    return active;
}

// prints the entry in the format 
// name : IPaddress : active  followed by newline
// active is printed as a string (active or inactive)
ostream& operator<< (ostream& out, const DBentry& rhs){
    out<<rhs.getName()<<" : "<<rhs.getIPaddress()<<" : "<<rhs.getActive()<<endl;
    return out;
}
/*
int main(int argc, char** argv) {
    DBentry testDB1;          //Uses the default constructor. name = "", IPaddress = 0, active = false;
    cout<<"printing testDB1 - default constructor: \n\tExpected: \" : 0 : 0\"\n\tHave:    \""<<testDB1<<"\"\n";
    DBentry testDB2("test_second_constructor", 998789850, true);
    cout<<"Printing testDB2 - second constructor: \n\tExpected: \"test_second_constructor : 998789850 : 1\n\tGot:       \""<<testDB2<<"\"\nc";
    
    cout<<"Accessor Function Tests Commencing (on testDB2)...\n";
    string test = testDB2.getName();
    unsigned int testInt = testDB2.getIPaddress();
    bool testActive = testDB2.getActive();
    
    cout<<"Accessor Function Tests completed...\n"
        <<"Commencing Mutator Function Tests (on testDB1)...\n";
    testDB1.setName("testDB1");
    testDB1.setIPaddress(998789850);
    testDB1.setActive(true);
    
    cout<<"Mutator Function Tests completed...\n"
        <<"ALL TESTS COMPLETED!\n";
    return 0;
}
*/
