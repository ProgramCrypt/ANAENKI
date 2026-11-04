//----------------------------------------------------------------
//
// Author(s): McKendree Springer
// Project: ANÆNKI engine
// Purpose: This class represents a basic "object" within the simulation. Attched components give it properties.
// Copyright © McKendree Springer
//
//----------------------------------------------------------------

#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>

#include "component/component.h"

// Forward declarations
class Stream;

class Entity
{
    public:
    //////// Public Functions ////////
    // Constructors
    Entity();

    // Deconstructor
    ~Entity();

    private:
    //////// Private Functions ////////
    
    //////// Private Variables ////////
    std::string name;

    std::vector<Component*> components;
};

#endif  // ENTITY_H