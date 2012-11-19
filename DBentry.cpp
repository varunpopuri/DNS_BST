#include "DBentry.h"
#include <iostream>

using namespace std;

/*      string name;
	unsigned int IPaddress;
        bool active;
 */

DBentry::DBentry(){
    //name doesn't need to be initialized
    name = "\0";
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
}

// sets the domain name, which we will use as a key.
void DBentry::setName(string _name){
    name = _name;
}

// sets the IPaddress data.
void DBentry::setIPaddress(unsigned int _IPaddress){
    IPaddress = _IPaddress;
}

// sets whether or not this entry is active.
void DBentry::setActive (bool _active){
    active = _active;
}

// returns the name.
string DBentry::getName() const{
        return name;
}

// returns the IPaddress data.
unsigned int DBentry::getIPaddress() const{
        return IPaddress;
}

// returns whether or not this entry is active.
bool DBentry::getActive() const{
    return active;
}

// prints the entry in the format 
// name : IPaddress : active  followed by newline
// active is printed as a string (active or inactive)
ostream& operator<< (ostream& out, const DBentry& rhs){
    cout<<"Printing Entry \""<<rhs.getName()<<"\"\n";
    out<<rhs.getName()<<" : "<<rhs.getIPaddress()<<" : "<<rhs.getActive()<<endl;
    return out;
}

ostream& operator<< (ostream& out, DBentry *rhs){
 cout<<"Printing Entry \""<<rhs->getName()<<"\"\n";
    out<<rhs->getName()<<" : "<<rhs->getIPaddress()<<" : "<<rhs->getActive()<<endl;
    return out;   
}