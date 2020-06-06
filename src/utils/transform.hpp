#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace aiko
{

    class Transform
    {
    public:

        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        Transform()
            : position(0.f, 0.f, 0.f)
            , rotation(0.f, 0.f, 0.f)
            , scale(1.f, 1.f, 1.f)
        {

        }

        Transform(glm::vec3 position)
            : position(position)
            , rotation(0.f, 0.f, 0.f)
            , scale (1.f, 1.f, 1.f)
        {

        }

        auto getModelMatrix() const
        {
            auto model = glm::mat4(1.f);
            model = glm::translate(model, position);
            model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, scale);
            return model;
        }

    };

}