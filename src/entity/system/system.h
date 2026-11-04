//----------------------------------------------------------------
//
// Author(s): McKendree Springer
// Project: ANÆNKI engine
// Purpose: This is the base class for systems that interact with an entity's components to update and/or render them.
// Copyright © McKendree Springer
//
//----------------------------------------------------------------

#ifndef SYSTEM_H
#define SYSTEM_H

// Forward declarations
class Stream;

class System
{
    public:
    //////// Special Member Functions ////////
    
    // Constructors
    System();

    // Deconstructor
    virtual ~System(void) = 0;

    //////// Public Functions ////////

    // Initializes the system
    virtual bool initialize() {return true;}

    // Updates the system
    virtual void update(float dt) {}

    // Renders the system
    virtual void render() const {}

    virtual void read(Stream& stream) {}

    private:
    //////// Private Functions ////////
    
    //////// Private Variables ////////

};

#endif  // SYSTEM_H