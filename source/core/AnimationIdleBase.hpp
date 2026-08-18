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

    constexpr Uint32 kFramesPerSecond = 10;
    constexpr Uint32 kFrameIntereval = 1000 / kFramesPerSecond; //
    constexpr Uint32 kTotal_Frames = 4;

    class Game;
    class PlayerAgent;
    class AgentBase;
    class Enemy;
    class EnemyAgent;

    class AnimationIdleBase {
    public:


        AnimationIdleBase(Game& mGame);

        ~AnimationIdleBase() = default;

        /// @brief 
        /// @param agent 
        /// @param tile_width static_cast<int>(mOverworldGrid->GetTileWidth());
        /// @param tile_height static_cast<int>(mOverworldGrid->GetTileHeight());
        /// @param camX mCamX
        /// @param camY mCamY
        void CharacterAnimation(AgentBase& agent);


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

        /// @brief 
        /// @param player 
        void Handle(PlayerAgent& player);

        void Handle(Enemy& enemy);
        void Handle(EnemyAgent& enemy);
    protected: 
        Game& mGame;
    private:

        int mCounter = 0;
        Uint32 mValueToSet = 0;



    };


}
