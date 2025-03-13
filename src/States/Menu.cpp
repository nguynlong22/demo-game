#include "Menu.h"
#include "Engine.h"
#include "Play.h"

Menu::Menu()
{
    playButton = {400, 200, 160, 80};
    exitButton = { 400, 400, 160, 80 };
    continueButton = {400, 300, 160, 80};
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
    TextureManager::GetInstance()->Load("bg", "assets/background.png");
    TextureManager::GetInstance()->Draw("bg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Vẽ nút Play
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Xanh lá
    SDL_RenderFillRect(renderer, &playButton);
    TextureManager::GetInstance()->DrawText("Play", playButton.x + 40, playButton.y + 20, 255, 255, 255);

    // Vẽ nút Exit
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Đỏ
    SDL_RenderFillRect(renderer, &exitButton);
    TextureManager::GetInstance()->DrawText("Exit", exitButton.x + 40, exitButton.y + 20, 255, 255, 255);

    if (PlayState::HasPlayed()) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Đỏ
        SDL_RenderFillRect(renderer, &continueButton);
        TextureManager::GetInstance()->DrawText("Continue", continueButton.x + 20, continueButton.y + 20, 255, 255, 255);
    }

    SDL_RenderPresent(renderer);
}

void Menu::Enter() {
    TextureManager::GetInstance()->LoadFont("assets/arial.ttf", 32); // Load font nếu cần
}

void Menu::Exit()
{

}
