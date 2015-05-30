// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under LGPLv3, see LICENSE.txt for details.

#ifndef ES_WORLD_H
#define ES_WORLD_H

#include "es/internal/core.h"
#include "es/entity.h"

namespace es
{

/*
A wrapper class around Core and Entity.
Creates instances of Entity by constructing it with ID and Core&.
*/
class World
{
    public:

        World() {}


        // Creating entities =================================================

        // Creates an empty entity and returns it
        Entity create(const std::string& name = "");

        // Creates an entity with the specified components
        // TODO: Determine if this should deal with components

        // Creates an entity from a prototype
        Entity copy(const std::string& prototypeName, const std::string& name = "");


        // Creates a new entity if needed ====================================

        // Get entity by name
        Entity operator[](const std::string& name);


        // Returns an invalid Entity if it doesn't exist =====================

        // Get entity by ID
        Entity operator[](ID id);

        // Get entity by name
        Entity get(const std::string& name);

        // Get entity by ID
        Entity get(ID id);


        // Remove entities ===================================================

        // Removes all entities
        void clear();


        // Query entities ====================================================

        using EntityList = std::vector<Entity>;

        // Returns all entities
        EntityList query();

        // Returns entities with specified component types
        template <typename T, typename... Args>
        EntityList query();

        // Returns entities with specified component names
        template <typename... Args>
        EntityList query(const std::string& name, Args&&... args);


        // Iterate through all entities ======================================

        // TODO: Add begin/end and const versions
            // This should iterate through the entities safely and return an
            // Entity handle each time.


        // Miscellaneous =====================================================

        operator Core&();

        // Returns true if the component name is valid
        static bool validName(const std::string& compName);

        static World prototypes;

    private:

        Core core;

};

template <typename T, typename... Args>
World::EntityList World::query()
{
    EntityList entities;
    for (const auto& id: core.entities.getIndex())
    {
        Entity ent {core, id.first};
        if (ent.has<T, Args...>())
            entities.push_back(ent);
    }
    return entities;
}

template <typename... Args>
World::EntityList World::query(const std::string& name, Args&&... args)
{
    EntityList entities;
    for (const auto& id: core.entities.getIndex())
    {
        Entity ent {core, id.first};
        if (ent.has(name, args...))
            entities.push_back(ent);
    }
    return entities;
}

}

#endif
