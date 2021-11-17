#pragma once
#include "Volunteer.h"

class Client
{
    string address;
public:
    string name;
    int phone;
    list<Volunteer*> *listOfResponders;

    Client(string name = "", int phone = 0, string address = "") 
        : name(name), phone(phone), address(address), listOfResponders(new list<Volunteer*>) {}
    Client(const Client& source);
    Client(Client&& source) noexcept;
    ~Client() = default;
    Client operator=(const Client& target);
    friend istream& operator>>(istream& input, Client& v);
    friend ostream& operator<<(ostream& output, const Client& v);
    bool operator==(Client& v);
 
};


inline Client::Client(const Client& source)
{
    name = source.name;
    phone = source.phone;
    address = source.address;
    if (source.listOfResponders)
    {
        for (auto it = source.listOfResponders->begin(); it != source.listOfResponders->end(); it++)
        {
            listOfResponders->push_back(*it);
        }
    }
}

inline Client::Client(Client&& source) noexcept
{
    if (this != &source)
    {
        name = source.name;
        phone = source.phone;
        address = source.address;
        listOfResponders = source.listOfResponders;
        source.listOfResponders = nullptr;
    }

}


inline Client Client::operator=(const Client& target)
{
    if (this != &target)
    {
        name = target.name;
        phone = target.phone;
        address = target.address;
        if (target.listOfResponders)
        {
            listOfResponders->clear();
            for (auto it = target.listOfResponders->begin(); it != target.listOfResponders->end(); it++)
            {
                listOfResponders->push_back(*it);
            }
        }
    }
    return *this;
}

inline istream& operator>>(istream& input, Client& c)
{
    input >> c.name >> c.phone >> c.address;
    return input;
}

inline ostream& operator<<(ostream& output, const Client& c)
{
    output << c.name << ":caller name = " << c.name << " phone = " <<
        c.phone << " address = " << c.address << endl;

    return output;
}

inline bool Client::operator== (Client& c)
{
    return (phone == c.phone) ? true : false;
}