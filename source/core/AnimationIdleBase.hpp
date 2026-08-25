/**
 * This File is a part of Slay_The_Spire Project
 * Extension off the Fall 2026, CSE 498, section 2, course project.
 * @brief A class that manages the animation for Items and entities.
 * @note Status: PROPOSAL
 **/
#pragma once

#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
#include "item/Item.hpp"
#include "../Interfaces/GUI/ImageManager.hpp"
#include "../Interfaces/GUI/ImageGrid.hpp"
#include "WorldPosition.hpp"
#include <string>
#include <math.h>

namespace cse498 {
    enum class AnimationDirection {
        STILL = 0,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    


    constexpr Uint32 kFramesPerSecond = 10;
    constexpr Uint32 kFrameIntereval = 1000 / kFramesPerSecond; //
    constexpr Uint32 kTotal_Frames = 4;

    class Game;
    class PlayerAgent;
    class AgentBase;
    class Enemy;
    class EnemyAgent;
    enum class AgentDirection : int;

    class AnimationIdleBase {
    public:


        AnimationIdleBase(Game& mGame);

        ~AnimationIdleBase() = default;

        /// @brief 
        /// @param agent 
        /// @param direction 
        void CharacterAnimation(AgentBase& agent, const AgentDirection& direction);


        ///
        void SetCounter(int counter_value) { 
            mCounter = counter_value;
        }

        /// @brief 
        /// @return 
        int GetCounter() const { 
            return mCounter;
        }

        void SetValueToSet(int& counter_value) {
            mValueToSet = counter_value;
        }

        Uint32 GetValueToSet() const {
            return mValueToSet;
        }

        /// @brief Overloaded Idle Animation Handler for PlayerAgent
        /// @param player PlayerAgent class
        void IdleHandle(PlayerAgent& player);

        /// @brief Overloaded Idle Animation Handler for Enemy
        /// @param enemy Enemy class
        void IdleHandle(Enemy& enemy);

        /// @brief Overloaded Idle Animation Handler for EnemyAgent
        /// @param enemy EnemyAgent Class
        void IdleHandle(EnemyAgent& enemy);

        /// @brief Overloaded Function Handles the direction the PlayerAgent faces for render
        /// @param test player agent 
        /// @param action_id int value of player movement 
        void DirectionHandle(PlayerAgent& test, size_t action_id);

        /// @brief Overloaded Function Handles the direction the Enemy faces for render
        /// @param enemy enemy class
        /// @param action_id int value of player movement 
        void DirectionHandle(Enemy& enemy, size_t action_id);

        /// @brief Overloaded Function Handles the direction the EnemyAgent faces for render
        /// @param enemy Enemy Agent Class
        /// @param action_id int value of player movement 
        void DirectionHandle(EnemyAgent& enemy, size_t action_id);

        /// @brief Sets direction 
        /// @param agent_direction 
        void SetDirection(AnimationDirection agent_direction) { mAnimationDirection = agent_direction; }

        std::array<AnimationDirection, 5>& GetDirectionalArray() {
            return mDirectionalArray;
        }
    protected: 
        Game& mGame;
    private:

        int mCounter = 0;

        Uint32 mValueToSet = 0;
        AnimationDirection mAnimationDirection = AnimationDirection::RIGHT; // Where the Agent if facing for rendering
        AnimationDirection mAgentDirection; //Where the Agent is facing for interaction 

        std::array<AnimationDirection, 5> mDirectionalArray = { 
            AnimationDirection::STILL,
            AnimationDirection::UP,
            AnimationDirection::DOWN,
            AnimationDirection::LEFT,
            AnimationDirection::RIGHT,
        };

    };


}
