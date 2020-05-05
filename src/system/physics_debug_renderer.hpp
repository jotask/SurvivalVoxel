#pragma once

#include <LinearMath/btIDebugDraw.h>
#include <glad/glad.h>

#include <array>
#include <vector>

namespace engine
{

    class CDebugDraw : public btIDebugDraw
    {

    public:

        struct LINE
        {

            LINE(btVector3 f, btVector3 t) {
                from = f;
                to = t;
            }

            btVector3 from;
            btVector3 to;

        };

        struct COLOR
        {

            COLOR(btVector3 c) {
                col = c;
            }

            btVector3 col;
        };

        CDebugDraw();
        virtual ~CDebugDraw();

        std::vector<LINE> LINES;
        std::vector<COLOR> COLORS;

        virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);

        virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);

        virtual void reportErrorWarning(const char* warningString);

        virtual void draw3dText(const btVector3& location, const char* textString);

        virtual void setDebugMode(int debugMode);

        virtual int getDebugMode() const;

        void doDrawing();
        void render();
        void cleanDrawing();
        void clearBuffer();

    private:


        int m_debugMode;

        GLuint m_vao;
        std::array<GLuint, 2> m_vbo;

    };

}
