#pragma once
/* Hashing Table */
#include "Item.h"

template<typename T, typename K>
class HashTable
{
    /// @brief Pointer to table of items
    Item<T, K>* table;
    /// @brief size of table
    int size;
    /// @brief prime number to use for hashing function
    int prime;

public:

    // default destructor
    virtual ~HashTable() = default;

    /// @brief calculates the hash function position in table
    /// @param key 
    /// @return position in table
    virtual int H1(const K& key) = 0;
    
    /// @brief collision resolution function to further reduce clustering
    /// @param key 
    /// @return added complexity
    virtual int H2(const K& key) = 0;

    /// @brief total Hash function that combines H1 and H2 with a probe step i
    /// @param key - unique key of object
    /// @param i - probe step
    /// @return index in the table
    virtual int Hash(const K& key, int i) = 0;

    /// @brief insert the object into table
    /// @param t object
    virtual void Insert(T& t) = 0;

    /// @brief searcg for the object in table
    /// @param t object
    virtual int Search(T& t) = 0;

    /// @brief delete the object from table
    /// @param t object
    virtual void Delete(T& t) = 0;

    /// @brief Checks if a number is prime
    /// @param num to check
    /// @return true or false if the number is prime
    bool isPrime(int num);

    /// @brief Function to return the smallest prime number greater than N
    /// @param number (input number)
    /// @return smallest contiguous prime number
    int NextPrime(int number);
};

template<typename T, typename K>
inline bool HashTable<T, K>::isPrime(int num)
{
    bool flag = true;
    for (int i = 2; i <= num / 2; i++)
    {
        if (num % i == 0)
        {
            flag = false;
            break;
        }
    }
    return flag;
}

template<typename T, typename K>
inline int HashTable<T, K>::NextPrime(int number)
{
    // Base case
    if (number <= 1)
        return 2;

    int prime = number;
    bool found = false;

    // Loop continuously until isPrime returns
    // true for a number greater than n
    while (!found)
    {
        prime++;

        if (isPrime(prime))
            found = true;
    }

    return prime;
}