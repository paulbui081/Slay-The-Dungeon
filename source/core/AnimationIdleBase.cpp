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

    /// Important
    ///set Game.hpp/cpp with a getter for the enemy agents up so that we can then go into each enemy agent and 
    /// grab the direction they're facing in order to properly render them  

    /// ^ We already have that with the agent that's pass in, we need to make a getter for agent that grabs it's internal direction
    
    constexpr int ANIMATION_SET_ONE = 0;
    constexpr int ANIMATION_SET_TWO = 1;

    AnimationIdleBase::AnimationIdleBase(Game& mGame) : mGame(mGame) {};
    
    /// @brief 
    /// @param agent 
    /// @param tile_width static_cast<int>(mOverworldGrid->GetTileWidth());
    /// @param tile_height static_cast<int>(mOverworldGrid->GetTileHeight());
    /// @param camX mCamX
    /// @param camY mCamY
    void AnimationIdleBase::CharacterAnimation(AgentBase& agent, const AgentDirection& direction) {
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

        ///IMPORTANT
        ///We we grab the agent from teh agent list (from game) and then grab their AnimationDirection enum state
        /// which will then be used to equate the direction we're facing
        if (agent.GetAgentDirection() == AgentDirection::RIGHT) {
            mGame.GetImageManger()->DrawImage(agent.GetAgentAnimations()[ANIMATION_SET_ONE][GetCounter()], screen_x, screen_y, tw, th);
        }

        else if (agent.GetAgentDirection() == AgentDirection::LEFT) {
            mGame.GetImageManger()->DrawImage(agent.GetAgentAnimations()[ANIMATION_SET_TWO][GetCounter()], screen_x, screen_y, tw, th);

        }

        else {
            if (agent.GetAgentDirection() == AgentDirection::RIGHT) mGame.GetImageManger()->DrawImage(agent.GetAgentAnimations()[ANIMATION_SET_ONE][GetCounter()], screen_x, screen_y, tw, th);

            else if (agent.GetAgentDirection() == AgentDirection::LEFT) mGame.GetImageManger()->DrawImage(agent.GetAgentAnimations()[ANIMATION_SET_TWO][GetCounter()], screen_x, screen_y, tw, th);
        }

    };


    void AnimationIdleBase::IdleHandle(PlayerAgent& test) {
        CharacterAnimation(test, test.GetAgentDirection());
    }

    void AnimationIdleBase::IdleHandle(Enemy& enemy) {
        CharacterAnimation(enemy, enemy.GetAgentDirection());
    }

    void AnimationIdleBase::IdleHandle(EnemyAgent& enemy) {
        CharacterAnimation(enemy, enemy.GetAgentDirection());
    }

    /// TO - DO REPLACE WITH TERNARY BRANCH NOT IF ELSE

    void AnimationIdleBase::DirectionHandle(PlayerAgent& test, size_t action_id) {
        if (test.GetAgentDirection() == AgentDirection::LEFT ) {
            mAgentDirection = AnimationDirection::LEFT;
        }
        else if (test.GetAgentDirection() == AgentDirection::RIGHT ) {
            mAgentDirection = AnimationDirection::RIGHT;
        }


        CharacterAnimation(test, test.GetAgentDirection());
    }

    void AnimationIdleBase::DirectionHandle(Enemy& enemy, size_t action_id) {
        if (enemy.GetAgentDirection() == AgentDirection::LEFT ) {
            mAgentDirection = AnimationDirection::LEFT;
        }
        else if (enemy.GetAgentDirection() == AgentDirection::RIGHT ) {
            mAgentDirection = AnimationDirection::RIGHT;
        }
        CharacterAnimation(enemy, enemy.GetAgentDirection());

    }

    void AnimationIdleBase::DirectionHandle(EnemyAgent& enemy, size_t action_id) {

        if (enemy.GetAgentDirection() == AgentDirection::LEFT ) {
            mAgentDirection = AnimationDirection::LEFT;
        }
        else if (enemy.GetAgentDirection() == AgentDirection::RIGHT ) {
            mAgentDirection = AnimationDirection::RIGHT;
        }

        CharacterAnimation(enemy, enemy.GetAgentDirection());
    }

}
