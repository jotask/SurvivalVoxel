#include "component.hpp"

namespace engine
{

    Component::Component(Entity* entity)
        : m_entity(entity)
    {

    }

    Component::~Component()
    {

    }

    void Component::init()
    {

    }

    void Component::update()
    {

    }

    void Component::render()
    {

    }

    Entity* Component::getEntity() const
    {
        return m_entity;
    }

}

