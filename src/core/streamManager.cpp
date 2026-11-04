#include "streamManager.h"
#include "entity/entity.h"
#include <fstream>


//////// Special Member Functions ////////
// Constructors
Stream::Stream(std::string_view filepath)
{
    open(filepath);
}

// Deconstructor
Stream::~Stream(void)
{

}

//////// Public Functions ////////
// Returns if the given key can be found in the current tree node
bool Stream::contains(std::string_view key)
{
    return dataNode->contains(key);
}

// Move dataNode ptr to the json file object of respective key (within the current tree location)
void Stream::pushNode(std::string_view key)
{
    if (contains(key))
    {
        dataStack.push_back(dataNode);
        dataNode = &dataNode->at(key);
    }
}

// Moves up the dataStack by one, setting the dataNode to point at the last element of the dataStack while removing said element from the dataStack
void Stream::popNode()
{
    dataNode = dataStack.back();
    dataStack.pop_back();
}

// Reads an entity's data from the current json file location
void Stream::readEntity(std::string_view entityName, Entity* entity)
{

}

//////// Private Functions ////////
    
// Opens a stream to the given filepath
bool Stream::open(std::string_view filepath)
{
    isValid = false;
    
    // opens json file
    std::ifstream file(filepath.data());
    if (!file.is_open())
    {
        LogManager::log('E', "streamManager", "Could not open filepath.");
        return isValid;
    }

    // parses json file into json object
    try
    {
        file >> jsonData;
    }
    catch(const json::parse_error& exception)
    {
        LogManager::log('E', "streamManager", "Failed to parse JSON file.");
        return isValid;
    }
    
    // if json file was read and parsed successfully
    isValid = true;
    dataNode = &jsonData;
    return isValid;
}