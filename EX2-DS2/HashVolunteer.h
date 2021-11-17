#pragma once
#include "Volunteer.h"
#include "HashTable.h"

class HashVolunteer : public HashTable<Volunteer, string>
{
    typedef Item<Volunteer, string> VolItem;
    VolItem* table;
    int size;
    int prime;

public:
    HashVolunteer();
    HashVolunteer(int tableSize);
    HashVolunteer(const HashVolunteer& source);
    HashVolunteer(HashVolunteer&& original);
    ~HashVolunteer() override;
    HashVolunteer& operator=(const HashVolunteer& other);
    VolItem& operator[](int index);
    int computeKey(const string& strKey);
    int H1(const string& strKey) override;
    int H2(const string& strKey) override;
    int Hash(const string& strKey, int i) override;
    void Insert(Volunteer& volunteer) override;
    int Search(Volunteer& volunteer) override;
    void Delete(Volunteer& volunteer) override;

    int getSize() { return size; }
    VolItem* getTable() { return table; }
};
