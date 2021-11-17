#include "HashClient.h"


HashClient::HashClient()
{
    table = nullptr;
    size = 0;
    prime = 0;
}

HashClient::HashClient(int TableSize)
{
    size = TableSize;
    prime = NextPrime(TableSize);
    table = new ClientItem[TableSize];
}

HashClient::HashClient(const HashClient& source)
{
    size = source.size;
    prime = source.prime;
    if (table)
    {
        delete[] table;
    }
    table = new ClientItem[size];

    for (int i = 0; i < size; i++)
    {
        table[i] = source.table[i];
    }
}

HashClient::HashClient(HashClient&& original) noexcept
{
    if (this != &original)
    {
        table = original.table;
        size = original.size;
        prime = original.prime;
        original.table = nullptr;
    }
}

HashClient::~HashClient()
{
    if (table)
    {
        delete[] table;
    }
}

HashClient& HashClient::operator=(const HashClient& other)
{
    if (this != &other)
    {
        size = other.size;
        prime = other.prime;

        if (table)
        {
            delete[] table;
        }

        table = new ClientItem[size];

        for (int i = 0; i < size; i++)
        {
            table[i] = other.table[i];
        }
    }

    return *this;
}

Item<Client, int>& HashClient::operator[](int index)
{
    return table[index];
}

int HashClient::H1(const int& key)
{
    return key % size;
}

int HashClient::H2(const int& key)
{
    return (prime - (key % prime));
}

int HashClient::Hash(const int& key, int i)
{
    return (H1(key) + i * H2(key)) % size;
}

void HashClient::Insert(Client& client)
{
    if (!size)
    {
        return;
    }

    int index = 0, i = 0;

    for (i; i < size; i++)
    {
        index = Hash(client.phone, i++);
        if (table[index].flag == state::empty)
        {
            break;
        }
    }

    if (i != size)
    {
        ClientItem *newClient = new ClientItem(client, client.phone);
        table[index] = *newClient;
        cout << "end of insert:" << table[index].value;
    }
}

int HashClient::Search(Client& client)
{
    if (size)
    {
        int i = 0, index = 0;

        for (i; i < size; i++)
        {
            index = Hash(client.phone, i++);
            if (table[index].value.phone == client.phone)
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

void HashClient::Delete(Client& client)
{
    int index = Search(client);

    if (index == -1) // doesn't exist
    {
        return;
    }
    else if (table[index].flag == state::full)
    {
        table[index].flag = state::deleted;
    }
}
