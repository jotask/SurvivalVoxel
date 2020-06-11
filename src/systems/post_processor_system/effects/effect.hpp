#pragma once

#include <string>

namespace aiko
{
    class Shader;
    namespace postprocessing
    {
        class Effect
        {
        public:
            Effect(const std::string& name);
            virtual ~Effect() = default;

            virtual void init(Shader* shader) = 0;
            virtual void use(Shader* shader) = 0;
            virtual void updateSettings() {};

            const std::string& getName() const;
            bool& isEnabled();

        private:

            const std::string m_name;

            bool m_enabled;

        };
    }
}
