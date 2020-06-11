#pragma once

#include "systems/post_processor_system/effects/effect.hpp"

namespace aiko
{
    namespace postprocessing
    {
        class ChaosFx : public Effect
        {
        public:
            ChaosFx();

            virtual void init(Shader* shader);
            virtual void use(Shader* shader);

            virtual void updateSettings() override;

        private:

            float m_strength;

        };
    }
}
