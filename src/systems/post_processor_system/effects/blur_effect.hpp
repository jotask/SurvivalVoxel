#pragma once

#include "systems/post_processor_system/effects/effect.hpp"

namespace aiko
{
    namespace postprocessing
    {
        class BlurFx : public Effect
        {
        public:
            BlurFx();

            virtual void init(Shader* shader);
            virtual void use(Shader* shader);

        };
    }
}
