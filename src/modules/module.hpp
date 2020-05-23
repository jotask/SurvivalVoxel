#pragma once

namespace aiko
{
    class Module
    {
    public:

        Module();
        virtual ~Module();

        virtual void initialise();

        virtual void preUpdate();
        virtual void update();
        virtual void postUpdate();

        virtual void preRender();
        virtual void render();
        virtual void postRender();

        virtual void preDebug();
        virtual void debug();
        virtual void postDebug();

    };
}