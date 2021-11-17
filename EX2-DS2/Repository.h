#pragma once
#include "HashClient.h"
#include "HashVolunteer.h"


class Repository
{
    HashVolunteer* VolunteerTable; // by name
    HashClient* CallerTable; // by phone

public:
    /// @brief Constructor
    Repository() : VolunteerTable(new HashVolunteer(100)), CallerTable(new HashClient(100)) {}

    /// @brief Destructor
    ~Repository();

    /// @brief Add volunteer to table
    /// @param volunteer 
    void addVolunteer(Volunteer& volunteer);

    /// @brief Add client to the table
    /// @param caller 
    void addClient(Client& caller);

    /// @brief Delete volunteer from table
    /// @param volunteer 
    void delVolunteer(Volunteer& volunteer);

    /// @brief Delete client from table
    /// @param caller 
    void delClient(Client& caller);

    /// @brief Add bidirectional association (client helped by volunteer) between the client and volunteer and vice versa
    /// @param volunteer 
    /// @param caller 
    void addVolunteerToClient(Volunteer& volunteer ,Client& caller);
    
    /// @brief Print list of Volunteers who helped given caller
    /// @param caller 
    void listOfVolunteers(Client& caller);

    /// @brief Print list of Clients who given volunteer helped
    /// @param volunteer 
    void listOfClients(Volunteer& volunteer);
 
    // for manual checker
    void printHashTables();
};


