#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>
using namespace std;

class Resource {
    // Each Resource object represents one campus resource.
private:
    string resourceID;
    // Stores the resource ID, such as "R101".
    string resourceName;
    string resourceType;
    string availability;
public:
    Resource(string id, string name, string type, string status);
    // Creates a Resource and gives it its starting information.
    string getResourceID() const;
    // Returns the resource ID.
    string getResourceName() const;
    string getResourceType() const;
    string getAvailability() const;

    void setAvailability(string status);

    void display() const;
    // Displays all information
};

#endif
// Ends the #ifndef/#define section.