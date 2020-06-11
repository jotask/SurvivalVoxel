#pragma once

#include "systems/post_processor_system/effects/effect.hpp"

namespace aiko
{
    namespace postprocessing
    {
        class InvertColorsFx : public Effect
        {
        public:
            InvertColorsFx();

            virtual void init(Shader* shader);
            virtual void use(Shader* shader);

        };
    }
}
