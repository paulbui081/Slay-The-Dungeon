/**
 * @file GameView.cpp
 * @author Group 17
 */

#include "GameView.hpp"
#include <iostream>
#include "SDL2/SDL_video.h"

namespace cse498 {

GameView::GameView(const std::string& title, int width, int height) : mTitle(title), mWidth(width), mHeight(height) {}

GameView::~GameView() { Shutdown(); }

bool GameView::Initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        return false;
    }

    mWindow = SDL_CreateWindow(mTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth, mHeight,
                               SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (mWindow == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (mRenderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
        SDL_Quit();
        return false;
    }

    return true;
}

void GameView::Clear() {
    if (mRenderer == nullptr)
        return;
    SDL_SetRenderDrawColor(mRenderer, mBackgroundColor.r, mBackgroundColor.g, mBackgroundColor.b, mBackgroundColor.a);
    SDL_RenderClear(mRenderer);
}

void GameView::Present() {
    if (mRenderer == nullptr)
        return;
    SDL_RenderPresent(mRenderer);
}

void GameView::Shutdown() {
    if (mRenderer != nullptr) {
        SDL_DestroyRenderer(mRenderer);
        mRenderer = nullptr;
    }
    if (mWindow != nullptr) {
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
    }
    SDL_Quit();
}

void GameView::SetWindowSize(const int& width, const int& height) {
    SDL_SetWindowSize(mWindow, width, height);
}
void GameView::SetWindowHeight(int& height) {

}

void GameView::SetWindowWidth(int& width) {

}




bool GameView::IsReady() const { return mWindow != nullptr && mRenderer != nullptr; }

} // namespace cse498
