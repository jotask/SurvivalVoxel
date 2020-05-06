#pragma once

namespace engine
{

    class Entity;

    class Component
    {
    public:
        Component(Entity*);
        virtual ~Component();

        virtual void init();
        virtual void update();
        virtual void render();

        Entity* getEntity() const;

    private:

        Entity* m_entity;
    };
}
