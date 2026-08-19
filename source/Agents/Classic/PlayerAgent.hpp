/**
 * @file PlayerAgent.hpp
 * @brief Human-controlled player (text input / interface agent).
 */

#pragma once


#include "../../core/AgentBase.hpp"
#include "PlayerFeatures/Inventory.hpp"
#include <array>

namespace cse498 {

    const std::string PLAYER_IDLE_ANIM_0_R = "player_idle_0_r";
    const std::string PLAYER_IDLE_ANIM_1_R = "player_idle_1_r";
    const std::string PLAYER_IDLE_ANIM_2_R = "player_idle_2_r";
    const std::string PLAYER_IDLE_ANIM_3_R = "player_idle_3_r";

    const std::string PLAYER_IDLE_ANIM_0_L = "player_idle_0_l";
    const std::string PLAYER_IDLE_ANIM_1_L = "player_idle_1_l";
    const std::string PLAYER_IDLE_ANIM_2_L = "player_idle_2_l";
    const std::string PLAYER_IDLE_ANIM_3_L = "player_idle_3_l";
    
    enum PlayerStates {
        IDLE,
        ATTACK
    };


    class PlayerAgent : public AgentBase {
    private:
        Inventory mInventory;
        /// the amount of gold the player has
        std::size_t mGold = 0;



    public:
        /**
         * Constructor
         * @param id - should be 0 for the player agent in general
         * @param name - name of the agent
         * @param world - world it belongs to
         */
        PlayerAgent(size_t id, const std::string& name, const WorldBase& world);

        /**
         * Don't call this function. Needs to be overriden but doesn't serve a good use
         * @param grid
         * @return
         */
        [[nodiscard]] size_t SelectAction(const WorldGrid& grid) override;

        /**
         * Accepts char input and returns action
         *
         * This is the entrance for the UI to tell the player what the user has clicked
         * This would need to be changed when designing 8-directional movement
         * @param input - character pressed
         */
        size_t SelectPlayerAction(char input);

        [[nodiscard]] Inventory& GetInventory() override { return mInventory; }
        [[nodiscard]] const Inventory& GetInventory() const override { return mInventory; }

        [[nodiscard]] std::size_t GetGold() const { return mGold; }

        /**
         * Add currency directly to the player.
         */
        void AddGold(std::size_t amount) { mGold += amount; }

        /**
         * Try to spend currency.
         * @return true if enough gold was available and removed.
         */
        bool SpendGold(std::size_t amount);

        /**
         * Sets gold to a known value. Mainly useful for demos/tests.
         */
        void SetGold(std::size_t amount) { mGold = amount; }

        bool IsPlayerAgent() const override { return true; }

        /**
         * Stores base combat stats and recomputes effective combat values from the
         * currently selected hand item.
         * @param stats Incoming baseline stats from world/factory setup.
         */
        void SetStats(const AgentStats& stats) override;

        /**
         * Wires inventory-change notifications so hand-weapon effects stay in sync.
         * @return true when initialization succeeds.
         */
        bool Initialize() override;

        std::vector<std::vector<std::string>>& GetAgentAnimations() override;

        /**
         * Recomputes effective attack and range from base stats plus the weapon in the selected hotbar hand slot.
         */
        void RefreshCombatFromHand();
        /**
         * Sets last damage dealt - could be replaced to log it, just for information to pull into UI
         * @param dmg - damage dealt
         */
        void SetLastDamageDealt(double dmg) { mLastDamageDealt = dmg; }

        double GetLastDamageDealt() const { return mLastDamageDealt; }

       
        /// @brief Dispatches to Animation class to set up Idle Agent Animation 
        /// @param anim Idle Agent Animation Class
        void AnimationIdleDispatch(AnimationIdleBase& anim) override {anim.IdleHandle(*this);}

        /// @brief Dispatches to Animation Class to determine animation render and sets internal Player Direction
        /// @param anim Idle Agent Animation Class
        /// @param action_id action id player is taking (what direction they're moving)
        void AnimationDirectionDispatch(AnimationIdleBase& anim, size_t action_id);

    private:
        /// Unmodified stats from the world (before hand weapon bonuses).
        AgentStats mBaseCombatStats{};
        double mLastDamageDealt{};
    };

} // namespace cse498
