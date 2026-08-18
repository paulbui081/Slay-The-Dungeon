/**
 * This File is a part of Slay_The_Spire Project
 * Extension off the Fall 2026, CSE 498, section 2, course project.
 * @brief A class that manages the basic, generic animation for Entities.
 * @note Status: PROPOSAL
 **/


#include "AnimationIdleBase.hpp"
#include "../Interfaces/GUI/interface/Game.hpp"
#include "AgentBase.hpp"
#include "../Agents/Classic/Enemy.hpp"
#include "../Agents/AI/EnemyAgent.hpp"

namespace cse498 {

    enum DirectionalState {
        LEFT,
        RIGHT
    };

    AnimationIdleBase::AnimationIdleBase(Game& mGame) : mGame(mGame) {};
    
    /// @brief 
    /// @param agent 
    /// @param tile_width static_cast<int>(mOverworldGrid->GetTileWidth());
    /// @param tile_height static_cast<int>(mOverworldGrid->GetTileHeight());
    /// @param camX mCamX
    /// @param camY mCamY
    void AnimationIdleBase::CharacterAnimation(AgentBase& agent) {
        const WorldPosition& pos = agent.GetLocation().AsWorldPosition();
        auto tw = mGame.GetDungeonGrid()->GetTileWidth();
        auto th = mGame.GetDungeonGrid()->GetTileHeight();

        int screen_x = (int(pos.CellX()) - mGame.GetDungeonCamX()) * tw;
        int screen_y = (int(pos.CellY()) - mGame.GetDungeonCamY()) * th;

        int vector_list_size = agent.GetAgentAnimations().size() - 1;

        Uint32 elapsedTime = (SDL_GetTicks() - GetValueToSet()); //Converts from ms to seconds

        if (elapsedTime >= kFrameIntereval) {

            mValueToSet = SDL_GetTicks();

            if (GetCounter() == vector_list_size) {
                SetCounter(0);
            }
            else {
                SetCounter(++mCounter);
            }
        }

        
        mGame.GetImageManger()->DrawImage(agent.GetAgentAnimations()[GetCounter()], screen_x, screen_y, tw, th);

        

    };


    void AnimationIdleBase::Handle(PlayerAgent& test) {
        CharacterAnimation(test);
    }

    void AnimationIdleBase::Handle(Enemy& enemy) {
        CharacterAnimation(enemy);
    }

    void AnimationIdleBase::Handle(EnemyAgent& enemy) {
        CharacterAnimation(enemy);
    }

}
