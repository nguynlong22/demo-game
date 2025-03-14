#include "Menu.h"
#include "Engine.h"
#include "Play.h"
#include "SDL_mixer.h"

Menu::Menu()
{
    playButton = {430, 470, 160, 80};
    exitButton = { 430, 570, 160, 80 };
    continueButton = {430, 520, 160, 80};
}

void Menu::Update(float dt) {
    if (Input::GetInstance()->GetMouseButtonDown(1)) { // Nhấn chuột trái
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        if (mouseX >= playButton.x && mouseX <= playButton.x + playButton.w &&
            mouseY >= playButton.y && mouseY <= playButton.y + playButton.h) {
            Engine::GetInstance()->PushState(new PlayState());
        }
        if (mouseX >= exitButton.x && mouseX <= exitButton.x + exitButton.w &&
            mouseY >= exitButton.y && mouseY <= exitButton.y + exitButton.h) {
            Engine::GetInstance()->Quit();
        }
        if (mouseX >= continueButton.x && mouseX <= continueButton.x + continueButton.w &&
            mouseY >= continueButton.y && mouseY <= continueButton.y + continueButton.h) {
            Engine::GetInstance()->PopState();
        }
    }
}

void Menu::Render() {
    SDL_Renderer* renderer = Engine::GetInstance()->GetRenderer();
    SDL_RenderClear(renderer);
    TextureManager::GetInstance()->Load("menu", "assets/menu.png");
    TextureManager::GetInstance()->Draw("menu", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Vẽ nút Play
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
    SDL_RenderFillRect(renderer, &playButton);
    TextureManager::GetInstance()->DrawText("New Game", playButton.x + 10 , playButton.y + 20, 255, 255, 255);

    // Vẽ nút Exit
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
    SDL_RenderFillRect(renderer, &exitButton);
    TextureManager::GetInstance()->DrawText("Exit", exitButton.x + 50, exitButton.y + 20, 255, 255, 255);

    if (PlayState::HasPlayed()) {
        SDL_SetRenderDrawColor(renderer, 128, 217, 134, 0.8); // Đỏ
        SDL_RenderFillRect(renderer, &continueButton);
        TextureManager::GetInstance()->DrawText("Continue", continueButton.x + 20, continueButton.y + 20, 255, 255, 255);
    }

    SDL_RenderPresent(renderer);
}

void Menu::Enter() {
    TextureManager::GetInstance()->LoadFont("assets/BubblegumSans.ttf", 32); // Load font nếu cần
    backgroundMusic = Mix_LoadMUS("assets/Happy Bee - Surf.mp3");
    if (!backgroundMusic) {
        SDL_Log("Failed to load background music! SDL_mixer Error: %s", Mix_GetError());
    } else {
        Mix_PlayMusic(backgroundMusic, -1); // Phát lặp lại vô hạn
    }
}

void Menu::Exit()
{

}
