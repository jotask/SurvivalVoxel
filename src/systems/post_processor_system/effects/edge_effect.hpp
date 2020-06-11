#pragma once

#include "systems/post_processor_system/effects/effect.hpp"

namespace aiko
{
    class Shader;
    namespace postprocessing
    {
        class EdgeFx : public Effect
        {
        public:
            EdgeFx();

            virtual void init(Shader* shader);
            virtual void use(Shader* shader);

        };
    }
}
