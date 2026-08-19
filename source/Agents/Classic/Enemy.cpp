/**
 * @file Enemy.cpp
 * @author lrima
 */

#include "Enemy.hpp"
#include "../../core/WorldBase.hpp"

namespace cse498 {

Enemy::Enemy(size_t id, const std::string& name, const WorldBase& world) : AgentBase(id, name, world) {
        ///Populating Player with the animations to Cycle through

        //RIGHT SIDE
        mAgentAnimations.push_back(std::vector<std::string>{
            GOBLIN_IDLE_ANIM_0_R,
            GOBLIN_IDLE_ANIM_1_R,
            GOBLIN_IDLE_ANIM_2_R,
            GOBLIN_IDLE_ANIM_3_R
        });

        //LEFT SIDE
        mAgentAnimations.push_back(std::vector<std::string>{
            GOBLIN_IDLE_ANIM_0_L,
            GOBLIN_IDLE_ANIM_1_L,
            GOBLIN_IDLE_ANIM_2_L,
            GOBLIN_IDLE_ANIM_3_L
        });

}

size_t Enemy::SelectAction([[maybe_unused]] const WorldGrid& grid) {

    if (!mBehaviorRoot)
        return 0;

    mBlackboard.Remove("selected_action");

    BehaviorTrees::ExecutionContext ctx(mBlackboard);
    mBehaviorRoot->Tick(ctx);

    // ***for an enemy this will only be wasd, stay***
    // REASON: passing attack codes in here doesn't define who the enemy is attacking so that is handled within
    // the behavior tree. (Enemies can attack enemies, helpers attack enemies)

    // Note: The demo tree does not do this because we don't have world functions for finding certain agents
    // in our surrounding that the world group "should" have done because we requested it.
    return mBlackboard.Get<size_t>("selected_action", 0);
}

std::size_t Enemy::ClaimGoldDrop() {
    if (mGoldClaimed) {
        return 0;
    }

    mGoldClaimed = true;
    return mGoldDrop;
}

void Enemy::TakeDamage(double amount) {
    AgentBase::TakeDamage(amount);
    if (auto analytics = world.GetAnalyticsManager()) {
        analytics->LogRunDamage(amount);
    }
}

void Enemy::OnDeath() {
    if (auto analytics = world.GetAnalyticsManager()) {
        analytics->LogRunEnemiesKilled(1);
    }
}

void Enemy::AnimationDirectionDispatch(AnimationIdleBase& anim, size_t action_id) {
    if (action_id != 0) {
        anim.DirectionHandle(*this, action_id);
        SetDirection(mDirectionalArray[action_id]);
    }
}



} // namespace cse498
