#pragma once

enum class state
{
    empty, full, deleted
};

template<typename T, typename K>
class Item
{
public:
    // Data stored
    T value;
    // Unique key
    K key;
    // Current state of item
    state flag;
    // Default Constructor
    Item();
    // Constructor
    Item(T& Val, K& Key);
    // Copy constructor
    Item(const Item& original);
    // Move constructor
    /*Item(Item&& source);*/
    // Destructor 
    ~Item() = default;
    // Copy assignment
    Item& operator=(Item& target);
    // Equals operator
    bool operator==(const Item& target) const;

};

/* Item functions */
template<typename T, typename K>
Item<T, K>::Item()
{
    flag = state::empty;
}

template<typename T, typename K>
Item<T, K>::Item(T& Val, K& Key)
{
    value = Val;
    key = Key;
    flag = state::full;
}

template<typename T, typename K>
Item<T, K>::Item(const Item& origin)
{
    value = origin.value;
    key = origin.key;
    flag = origin.flag;
}

//template<typename T, typename K>
//Item<T, K>::Item(Item&& source)
//{
//    if (source.value)
//    {
//        value = source.value;
//        source.value = nullptr;
//    }
//    if (source.key)
//    {
//        key = source.key;
//        source.key = nullptr;
//    }
//
//    flag = source.flag;
//}

//template<typename T, typename K>
//Item<T, K>::~Item()
//{
//    if (key)
//    {
//        delete key;
//    }
//    if (value)
//    {
//        delete value;
//    }
//}

template<typename T, typename K>
Item<T, K>& Item<T, K>::operator=(Item& target)
{
    if (this != &target)
    {
       /* if (value)
        {
            delete value;
        }
        if (key)
        {
            delete key;
        }*/

        value = target.value;
        key = target.key;
        flag = target.flag;
    }
    
    return *this;

}

template<typename T, typename K>
bool Item<T, K>::operator==(const Item& target) const
{
    // is the value's pointed by key equal to targets pointer to key's value
    return key == target.key ? true : false;
}

