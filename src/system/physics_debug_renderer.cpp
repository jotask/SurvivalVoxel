#include "physics_debug_renderer.hpp"

namespace engine
{
    CDebugDraw::CDebugDraw(Shader& shader)
        : m_shader(shader)
        , m_debugMode(btIDebugDraw::DBG_DrawWireframe | btIDebugDraw::DBG_DrawAabb)
        , m_vao(0)
        , m_vbo(0)
    {
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, nullptr);
        size_t size = 512 * 4 * 4;
        glBufferData(GL_ARRAY_BUFFER, size * sizeof(GL_FLOAT) * 3, nullptr, GL_DYNAMIC_DRAW);
        vertices.reserve(size);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    CDebugDraw::~CDebugDraw()
    {

    }

    void CDebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
    {
        vertices.push_back(from.getX());
        vertices.push_back(from.getY());
        vertices.push_back(from.getZ());
        vertices.push_back(to.getX());
        vertices.push_back(to.getY());
        vertices.push_back(to.getZ());
    }

    void CDebugDraw::drawContactPoint(const btVector3 & PointOnB, const btVector3 & normalOnB, btScalar distance, int lifeTime, const btVector3 & color)
    {
        fprintf(stderr, "Function {drawContactPoint} not implemented \n");
    }

    void CDebugDraw::reportErrorWarning(const char * warningString)
    {
        fprintf(stderr, "Function {reportErrorWarning} not implemented \n");
    }

    void CDebugDraw::draw3dText(const btVector3 & location, const char * textString)
    {
        fprintf(stderr, "Function {draw3dText} not implemented \n");
    }

    void CDebugDraw::setDebugMode(int debugMode)
    {
        m_debugMode = debugMode;
    }

    int CDebugDraw::getDebugMode() const
    {
        return m_debugMode;
    }

    void CDebugDraw::render()
    {
        m_shader.use();
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());

        glDrawArrays(GL_LINES, 0, vertices.size());
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        vertices.clear();
    }

}
