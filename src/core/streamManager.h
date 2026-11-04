//----------------------------------------------------------------
//
// Author(s): McKendree Springer
// Project: ANÆNKI engine
// Purpose: Creates and manages a stream to read and write data from files.
// Copyright © McKendree Springer
//
//----------------------------------------------------------------

#ifndef STREAMMANAGER_H
#define STREAMMANAGER_H

#include "nlohmann/json.hpp"
#include <string>
#include <vector>

#include "logManager.h"

using json = nlohmann::json;

// Forward declarations
class Entity;

class Stream
{
    public:
    //////// Special Member Functions ////////

    // Constructors
    Stream(std::string_view filepath);

    // Deconstructor
    ~Stream(void);

    //////// Public Functions ////////

    bool isValid() const {return isValid;}

    // Returns if the given key can be found in the current tree node
    bool contains(std::string_view key);

    // Move dataNode ptr to the json file object of respective key (within the current tree location)
    void pushNode(std::string_view key);

    // Moves up the dataStack by one, setting the dataNode to point at the last element of the dataStack while removing said element from the dataStack
    void popNode();

    // Attempts to read the json value associated with the given key into the given memory location
    template <typename T> bool Read(const char* key, T& loc) const
    {
        // exit if stream is not valid
        if (!isValid) return false;

        try
        {
            loc = dataNode->at(key).get<T>();
        }
        catch(const json::out_of_range& exception)
        {
            LogManager::log('D', "streamManager", "Could not read key from node.");
            return false;
        }
        
        return true;
    }

    // Reads an entity's data from the current json file location
    void readEntity(std::string_view entityName, Entity* entity);

    private:
    //////// Private Functions ////////
    
    // Opens a stream to the given filepath
    bool open(std::string_view filepath);

    //////// Private Variables ////////

    // Flag that indicates if stream is valid
    bool isValid = false;

    // Hierarchical tree that represents part of the json file
    json jsonData{};

    // Ptr to json node currently being accessed
    const json* dataNode{nullptr};

    // Stack used to traverse the hierarchical tree
    std::vector<const json*> dataStack;
};

#endif  // STREAMMANAGER_H