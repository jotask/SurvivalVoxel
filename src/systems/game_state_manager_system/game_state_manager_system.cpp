#include "systems/game_state_manager_system/game_state_manager_system.hpp"

#include "systems/imgui_system.hpp"

#include "systems/game_state_manager_system/states/test_state.hpp"

#include <imgui.h>
#include <iostream>

namespace aiko
{
    GameStateManagerSystem::GameStateManagerSystem()
        : m_renderImgui(false)
        , m_imguiSystem(nullptr)
        , m_nextState(std::nullopt)
        , m_popLastState(false)
    {

    }

    GameStateManagerSystem::~GameStateManagerSystem()
    {
        while (m_states.empty() == false)
        {
            m_states.pop_back();
        }
    }

    bool GameStateManagerSystem::connect(SystemConnector & connector)
    {
        m_imguiSystem = connector.findSystem<ImguiSystem>();

        return true;
    }

    bool GameStateManagerSystem::init()
    {
        m_imguiSystem->registerSystem("GameStateManager", m_renderImgui);

        changeState<TestState>();

        return true;
    }

    void GameStateManagerSystem::update()
    {

        if (getCurrentState() != nullptr)
        {
            while (getCurrentState()->onUpdate(this) == false);
        }
    }

    void GameStateManagerSystem::postUpdate()
    {
        if (m_nextState != std::nullopt)
        {

            if (getCurrentState() != nullptr)
            {
                while (getCurrentState()->onExit() == false);
            }

            if (m_nextState.value().first == true && m_states.empty() == false)
            {
                m_states.pop_back();
            }

            m_states.push_back(std::move(m_nextState.value().second));
            m_nextState = std::nullopt;

            while (getCurrentState()->onEnter() == false);

        }
        else if (m_popLastState == true)
        {
            m_popLastState = false;

            if (getCurrentState() != nullptr)
            {
                while (getCurrentState()->onExit() == false);
            }

            if (getCurrentState() != nullptr)
            {
                while (getCurrentState()->onEnter() == false);
            }
            else
            {
                std::cout << "No more States!" << std::endl;
            }


        }
    }

    void GameStateManagerSystem::render()
    {
        if (m_renderImgui == true)
        {
            ImGui::Begin("GameStateManager", &m_renderImgui);
            ImGui::End();
        }
    }


    void GameStateManagerSystem::popState()
    {
        m_popLastState = true;
    }

    State * GameStateManagerSystem::getCurrentState()
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

}
