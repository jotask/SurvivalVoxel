#pragma once

#include "system//shader.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <map>

namespace engine
{

    namespace model
    {

        class Model
        {

        public:

            Model(Shader& shader);
            virtual ~Model();

            virtual void create();

            void setTexture(const std::string& textureName, GLuint textureId);
            GLuint getTextureId(const std::string& texture) const;
            GLuint getVao() const;
            std::vector<GLuint> getVbos() const;
            void destroy();

            void update();

            glm::vec3 rotation, rotation_speed;
            glm::vec3 rotation_sin;

        private:

            GLuint m_vao;
            std::vector<GLuint> m_vbos;
            std::map<std::string, GLuint> m_textures;


        };
    }
}

