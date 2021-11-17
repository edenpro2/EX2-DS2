#include "HashVolunteer.h"

HashVolunteer::HashVolunteer()
{
    table = nullptr;
    size = 0;
    prime = 0;
}

HashVolunteer::HashVolunteer(int TableSize)
{
    size = TableSize;
    prime = NextPrime(TableSize);
    table = new VolItem[TableSize];
}

HashVolunteer::HashVolunteer(const HashVolunteer& source)
{
    if (this != &source)
    {
        size = source.size;
        prime = source.prime;
        table = new VolItem[size];

        for (int i = 0; i < size; i++)
        {
            table[i] = source.table[i];
        }
    }
}

HashVolunteer::HashVolunteer(HashVolunteer&& original)
{
    if (original.size && this != &original)
    {
        table = original.table;
        size = original.size;
        prime = original.prime;
        original.table = nullptr;
    }
}

HashVolunteer::~HashVolunteer()
{
    if (table)
    {
        delete[] table;
    }
}

HashVolunteer& HashVolunteer::operator=(const HashVolunteer& other)
{
    if (this != &other)
    {
        size = other.size;
        prime = other.prime;

        if (table)
        {
            delete[] table;
        }

        table = new VolItem[size];

        for (int i = 0; i < size; i++)
        {
            table[i] = other.table[i];
        }
    }

    return *this;
}

Item<Volunteer, string>& HashVolunteer::operator[](int index)
{
    return table[index];
}

int HashVolunteer::computeKey(const string& strKey)
{
    int key = 0;
    for (size_t i = 0; i < strKey.length(); ++i)
    {
        key += strKey[i];
    }
    return key;
}

int HashVolunteer::H1(const string& strKey)
{
    return (this->computeKey(strKey) % size);
}

int HashVolunteer::H2(const string& strKey)
{
    return (prime - (this->computeKey(strKey) % prime));
}

int HashVolunteer::Hash(const string& strKey, int i)
{
    return ((H1(strKey) + i * H2(strKey)) % size);
}

void HashVolunteer::Insert(Volunteer& volunteer)
{
    if (!size)
    {
        return;
    }

    int index = Search(volunteer);
    if (index != -1) // doesn't exist
    {
        return;
    }

    int i = 0;

    for (i; i < size; i++)
    {
        index = Hash(volunteer.name, i++);
        if (table[index].flag == state::empty)
        {
            break;
        }
    }

    if (i != size)
    {
        VolItem* newVolItem = new VolItem(volunteer, volunteer.name);
        table[index] = *newVolItem;
    }
}

int HashVolunteer::Search(Volunteer& volunteer)
{
    if (size)
    {
        int i = 0, index = 0;

        for (i; i < size; i++)
        {
            index = Hash(volunteer.name, i++);

            if (table[index].value.name == volunteer.name)
            {
                break;
            }
        }

        if (i != size && table[index].flag == state::full)
        {
            return index;
        }
    }

    return -1;
}

void HashVolunteer::Delete(Volunteer& volunteer)
{
    int index = Search(volunteer);

    if (index == -1) // doesn't exist
    {
        return;
    }
    else if (table[index].flag == state::full)
    {
        table[index].flag = state::deleted;
    }
}
