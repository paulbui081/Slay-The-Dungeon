



#pragma once

#include "AnimationManagerBase.hpp"


namespace cse498 {


    class PlayerAnimationBase : private AnimationManagerBase {

        public:

            PlayerAnimationBase(Game& mGame);
            ~PlayerAnimationBase();

        private:
            int testing;



    };
}
