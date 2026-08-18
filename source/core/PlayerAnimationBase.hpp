



#pragma once

#include "AnimationIdleBase.hpp"


namespace cse498 {


    class PlayerAnimationBase : private AnimationIdleBase {

        public:

            PlayerAnimationBase(Game& mGame);
            ~PlayerAnimationBase();

        private:
            int testing;



    };
}
