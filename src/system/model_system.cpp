#include "system/model_system.hpp"

#include "system/camera_system.hpp"
#include "system/shader_system.hpp"
#include "utils/utilities.hpp"

#include <algorithm>

namespace engine
{
    ModelSystem::ModelSystem()
        : m_cameraSystem(nullptr)
        , m_shaderSystem(nullptr)
    {

    }

    bool ModelSystem::init()
    {

        // TODO : Move this to a assets class maybe, but definetly not here
        unsigned int texture = utils::loadBMPTexture("crate.bmp");

        constexpr auto testName = "test";
        m_models.insert({ testName, std::make_unique<model::Model>() });
        m_models.at(testName)->setProgram(m_shaderSystem->getShader("cubeShader"));
        m_models.at(testName)->setTexture("Crate", texture);
        m_models.at(testName)->create();
        
        return true;
    }

    bool ModelSystem::connect(SystemConnector & connector)
    {
        m_cameraSystem = connector.findSystem<CameraSystem>();
        m_shaderSystem = connector.findSystem<ShaderSystem>();
        return true;
    }

    void ModelSystem::preUpdate()
    {

    }

    void ModelSystem::update()
    {
        for (const auto& model : m_models)
        {
            model.second->update();
        }
    }

    void ModelSystem::postUpdate()
    {

    }

    void ModelSystem::preRender()
    {
        
    }

    void ModelSystem::render()
    {
        for (const auto& model : m_models)
        {

            const auto programId = model.second->getProgram();

            // Map shader variables
            glUseProgram(programId);

            // Bind Texture
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, model.second->getTextureId("Crate"));
            unsigned int textureLocation = glGetUniformLocation(programId, "texture1");
            glUniform1i(textureLocation, 0);

            const auto& rotation_sin = model.second->rotation_sin;
            glUniform3f(glGetUniformLocation(programId, "rotation"), rotation_sin.x, rotation_sin.y, rotation_sin.z);
            glUniformMatrix4fv(glGetUniformLocation(programId, "view_matrix"), 1, false, &(m_cameraSystem->getViewMatrix())[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(programId, "projection_matrix"), 1, false, &m_cameraSystem->getProjectionMatrix()[0][0]);
            glBindVertexArray(model.second->getVao());
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }
    }

    void ModelSystem::postRender()
    {

    }

}
