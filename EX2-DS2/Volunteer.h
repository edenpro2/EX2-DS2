#pragma once
#include <string>
#include <iostream>
#include <list>
using namespace std;

//forward declaration
class Client;

class Volunteer
{
    string address;
    string city;

public:
    string name;
    int phone;
    list<Client*> *listOfHelpedClients;

    Volunteer(string name = "", string address = "", int phone = 0, string city = "") :
        name(name), address(address), phone(phone), city(city), listOfHelpedClients(new list<Client*>) {}

    Volunteer(const Volunteer& source);
    Volunteer(Volunteer&& source) noexcept;
    ~Volunteer() = default;
    Volunteer& operator=(const Volunteer& target);
    friend istream& operator>>(istream& input, Volunteer& v);
    friend ostream& operator<<(ostream& output, const Volunteer& v);
    bool operator==(Volunteer& v);

};

//Copy Constructor
inline Volunteer::Volunteer(const Volunteer& source)
{
    if (this != &source)
    {
        name = source.name;
        address = source.address;
        phone = source.phone;
        city = source.city;
        if (source.listOfHelpedClients)
        {
            for (auto it = source.listOfHelpedClients->begin(); it != source.listOfHelpedClients->end(); it++)
            {
                listOfHelpedClients->push_back(*it);
            }
        }
    }

}

inline Volunteer::Volunteer(Volunteer&& source) noexcept
{
    if (this != &source)
    {
        name = source.name;
        address = source.address;
        phone = source.phone;
        city = source.city;
        if (source.listOfHelpedClients)
        {
            listOfHelpedClients->clear();
            for (auto it = source.listOfHelpedClients->begin(); it != source.listOfHelpedClients->end(); it++)
            {
                listOfHelpedClients->push_back(*it);
            }
        }
    }
}

//Assignment Operator
inline Volunteer& Volunteer::operator=(const Volunteer& target)
{
    if (this != &target)
    {
        name = target.name;
        address = target.address;
        phone = target.phone;
        city = target.city;
        if (target.listOfHelpedClients)
        {
            listOfHelpedClients->clear();
            for (auto it = target.listOfHelpedClients->begin(); it != target.listOfHelpedClients->end(); it++)
            {
                listOfHelpedClients->push_back(*it);
            }
        }
    }
    return *this;
}

//input operator
inline istream& operator>>(istream& input, Volunteer& v)
{
    input >> v.name >> v.phone >> v.city;
    return input;
}

//output operator
inline ostream& operator<<(ostream& output, const Volunteer& v)
{
    output << v.name << ":volunteer name = " << v.name
        << " phone = " << v.phone << " address = " << v.city << endl;
    return output;
}

//Equality Operator: Compares te names of volunteers
inline bool Volunteer::operator==(Volunteer& v)
{
    return (name == v.name) ? true : false;
}