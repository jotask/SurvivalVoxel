#pragma once

#include "systems/post_processor_system/effects/effect.hpp"

namespace aiko
{
    class Shader;
    namespace postprocessing
    {
        class ShakeFx : public Effect
        {
        public:
            ShakeFx();

            virtual void init(Shader* shader);
            virtual void use(Shader* shader);

            virtual void updateSettings() override;

        private:

            float m_strength;

        };
    }
}
