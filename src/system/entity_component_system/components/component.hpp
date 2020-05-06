#pragma once

namespace engine
{

    class Entity;

    class Component
    {
    public:
        Component();
        virtual ~Component();

        virtual void init();
        virtual void update();
        virtual void render();

        Entity* m_entity;
    };
}
