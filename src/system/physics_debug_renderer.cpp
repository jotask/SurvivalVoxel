#include "physics_debug_renderer.hpp"

namespace engine
{
    CDebugDraw::CDebugDraw()
        : m_debugMode(btIDebugDraw::DBG_DrawWireframe | btIDebugDraw::DBG_DrawAabb)
        , m_vao(0)
        , m_vbo({ 0, 0 })
    {

    }

    CDebugDraw::~CDebugDraw()
    {

    }

    void CDebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
    {
        LINES.push_back(LINE(from, to));
        COLORS.push_back(COLOR(color));
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

    void CDebugDraw::doDrawing()
    {
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);
        
        glGenBuffers(2, &m_vbo[0]);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, LINES.size() * sizeof(LINE), &LINES[0], GL_STATIC_DRAW);
        glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, COLORS.size() * sizeof(COLOR), &COLORS[0], GL_STATIC_DRAW);
        glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);
        
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    }

    void CDebugDraw::cleanDrawing()
    {
        // delete buffers
        glDeleteBuffers(2, &m_vbo[0]);
        glDeleteBuffers(1, &m_vao);
    }

    void CDebugDraw::clearBuffer()
    {
        // Clear vectors
        LINES.clear();
        COLORS.clear();
    }

    void CDebugDraw::render()
    {
        // cleanDrawing();
        doDrawing();

        // Debug drawing
        glBindVertexArray(m_vao);
        glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(LINES.size()));

    }

}
