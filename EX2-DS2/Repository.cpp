#include "Repository.h"

Repository::~Repository()
{
    if (VolunteerTable)
    {
        delete[] VolunteerTable;
    }
    if (CallerTable)
    {
        delete[] CallerTable;
    }
}

void Repository::addVolunteer(Volunteer& volunteer)
{
    VolunteerTable->Insert(volunteer);
}

void Repository::addClient(Client& caller)
{
    CallerTable->Insert(caller);
}

void Repository::delVolunteer(Volunteer& volunteer)
{
    VolunteerTable->Delete(volunteer);
}

void Repository::delClient(Client& caller)
{
    CallerTable->Delete(caller);
}

void Repository::addVolunteerToClient(Volunteer& volunteer, Client& caller)
{
    int volIndex = VolunteerTable->Search(volunteer), callerIndex = CallerTable->Search(caller);
    if (volIndex == -1 || callerIndex == -1)
    {
        return;
    }
    
    bool exists = false;


    // search for volunteer in client, if doesn't exist, add volunteer to client.
    list<Volunteer*>** listOfResponders = &(*CallerTable)[callerIndex].value.listOfResponders;

    if (listOfResponders)
    {
        list<Volunteer*>::iterator it;
        for (it = (*listOfResponders)->begin(); it != (*listOfResponders)->end(); it++)
        {
            if ((*it)->name == volunteer.name)
            {
                exists = true;
                break;
            }
        }

        if (!exists)
        {
            (*listOfResponders)->push_back(&(*VolunteerTable)[volIndex].value);
        }
    }

    cout << "after searching listofresponders: " << (*VolunteerTable)[volIndex].value << endl;


    list<Client*>** listOfCallers = &(*VolunteerTable)[volIndex].value.listOfHelpedClients;

    if (listOfCallers)
    {
        list<Client*>::iterator it;

        for (it = (*listOfCallers)->begin(); it != (*listOfCallers)->end(); it++)
        {
            if((*it)->phone == caller.phone)
            {   
                exists = true;
                break;
            }
        }
        cout << "after searching list of callers:" << (*CallerTable)[callerIndex].value;

        if (!exists)
        {
            (*listOfCallers)->push_back(&(*CallerTable)[callerIndex].value);
        }

    }

    


}

void Repository::listOfVolunteers(Client& caller)
{
    int index = CallerTable->Search(caller);
    if (index != -1)
    {
        Client* callPtr = &(*CallerTable)[index].value;

        for (auto it = (callPtr)->listOfResponders->begin(); it != (callPtr)->listOfResponders->end(); it++)
        {
            cout << **it;
        }
    }
}

void Repository::listOfClients(Volunteer& volunteer)
{
    int index = VolunteerTable->Search(volunteer);
    if (index != -1)
    {
        Volunteer* volPtr = &(*VolunteerTable)[index].value;

        for (auto it = (volPtr)->listOfHelpedClients->begin(); it != (volPtr)->listOfHelpedClients->end(); it++)
        {
            cout << **it;
        }
    }
}

void Repository::printHashTables()
{
    cout << "Printing Volunteer Table:" << endl;
    for (int i = 0; i < 100; i++)
    {
        if ((*VolunteerTable)[i].flag == state::full)
        {
            cout << (*VolunteerTable)[i].value;
        }
    }

    cout << "Printing Caller Table:" << endl;
    for (int i = 0; i < 100; i++)
    {
        if ((*CallerTable)[i].flag == state::full)
        {
            cout << (*CallerTable)[i].value;
        }
    }

    
}
