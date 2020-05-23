#pragma once

#include "systems/shader_system/shader.hpp"

#include <LinearMath/btIDebugDraw.h>
#include <glad/glad.h>


#include <array>
#include <vector>

namespace aiko
{

    class CDebugDraw : public btIDebugDraw
    {

    public:

        CDebugDraw(Shader&);
        virtual ~CDebugDraw();

        virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);

        virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);

        virtual void reportErrorWarning(const char* warningString);

        virtual void draw3dText(const btVector3& location, const char* textString);

        virtual void setDebugMode(int debugMode);

        virtual int getDebugMode() const;

        void render();

    private:

        Shader& m_shader;
        int m_debugMode;

        GLuint m_vao;
        GLuint m_vbo;
        std::vector<float> vertices;

    };

}
