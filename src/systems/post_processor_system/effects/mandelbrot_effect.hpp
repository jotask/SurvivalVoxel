#pragma once

#include "systems/post_processor_system/effects/effect.hpp"

namespace aiko
{
    namespace postprocessing
    {
        class MandelbrotFx : public Effect
        {
        public:
            MandelbrotFx();

            virtual void init(Shader* shader);
            virtual void use(Shader* shader);

            virtual void updateSettings() override;

        private:

        };
    }
}
