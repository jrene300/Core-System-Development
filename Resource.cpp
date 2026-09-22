#include "Resource.h"
#include <iostream>

using namespace std; 

Resource::Resource(string id, string name, string type, string status)
{

    resourceID = id; 

    // id to resourceID. 

    resourceName = name; 

    // the resource name. 

    resourceType = type; 

    // the resource type. 

    availability = status; 

    // "Available" or "Unavailable". 

} 

string Resource::getResourceID()
const
{

    // returns the resource ID. 

    return resourceID; 

} 

  

string Resource::getResourceName()
const
{

    return resourceName; 

} 

  

string Resource::getResourceType()
const
{

    return resourceType; 

} 

  

string Resource::getAvailability()
const
{

    return availability; 

} 

  

void Resource::setAvailability(string status)
{

    // Changes the availability of the resource. 

    availability = status; 

    // Replaces the old availability with the new status. 

} 

void Resource::display()
const
{

    // Displays all information about one resource. 

    cout << resourceID << " | " 

         << resourceName << " | " 

         << resourceType << " | " 

         << availability << endl; 

    // Prints the availability. 

} 