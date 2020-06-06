#include "systems/game_state_manager_system/game_state_manager_system.hpp"

#include "systems/imgui_system.hpp"

#include <imgui.h>

namespace aiko
{
    GameStateManager::GameStateManager()
        : m_renderImgui(false)
        , m_imguiSystem(nullptr)
    {

    }

    GameStateManager::~GameStateManager()
    {
        while (m_states.empty() == false)
        {
            popState();
        }
    }

    bool GameStateManager::connect(SystemConnector & connector)
    {
        m_imguiSystem = connector.findSystem<ImguiSystem>();

        return true;
    }

    bool GameStateManager::init()
    {
        m_imguiSystem->registerSystem("GameStateManager", m_renderImgui);
        return true;
    }

    void GameStateManager::preUpdate()
    {

    }

    void GameStateManager::update()
    {
        if (getCurrentState() != nullptr)
        {
            while (getCurrentState()->onUpdate() == false);
        }
    }

    void GameStateManager::postUpdate()
    {

    }

    void GameStateManager::preRender()
    {

    }

    void GameStateManager::render()
    {
        if (m_renderImgui == true)
        {
            ImGui::Begin("GameStateManager", &m_renderImgui);
            ImGui::End();
        }
    }

    void GameStateManager::postRender()
    {

    }

    State * GameStateManager::getCurrentState()
    {
        if (m_states.empty() == true)
        {
            return nullptr;
        }
        else
        {
            return m_states.back().get();
        }
    }

    void GameStateManager::popState()
    {
        if (getCurrentState() != nullptr)
        {
            while (getCurrentState()->onExit() == false);
            m_states.pop_back();
        }
    }

}
