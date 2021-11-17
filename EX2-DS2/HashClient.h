#pragma once
#include "Client.h"
#include "HashTable.h"

class HashClient : public HashTable<Client, int>
{
    typedef Item<Client, int> ClientItem;
    ClientItem* table;
    int size;
    int prime;

public:
    HashClient();
    HashClient(int tableSize);
    HashClient(const HashClient& source);
    HashClient(HashClient&& original) noexcept;
    ~HashClient() override;
    HashClient& operator=(const HashClient& other);
    ClientItem& operator[](int index);
    int H1(const int& key) override;
    int H2(const int& key) override;
    int Hash(const int& key, int i) override;
    void Insert(Client& Client) override;
    int Search(Client& item) override;
    void Delete(Client& item) override;
    int getSize() { return size; }
    ClientItem* getTable() { return table; }
};
