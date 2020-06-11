#pragma once

#include "systems/post_processor_system/effects/effect.hpp"

namespace aiko
{
    class Shader;
    namespace postprocessing
    {
        class ConfuseFx : public Effect
        {
        public:
            ConfuseFx();

            virtual void init(Shader* shader);
            virtual void use(Shader* shader);

        };
    }
}
