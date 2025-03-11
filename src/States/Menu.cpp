#include "Menu.h"
#include "Engine.h"
#include "Play.h"

Menu::Menu()
{
    playButton = {400, 200, 160, 80};
    exitButton = { 400, 300, 160, 80 };
}

void Menu::Update(float dt) {
    if (Input::GetInstance()->GetMouseButtonDown(1)) { // Nhấn chuột trái
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        if (mouseX >= playButton.x && mouseX <= playButton.x + playButton.w &&
            mouseY >= playButton.y && mouseY <= playButton.y + playButton.h) {
            Engine::GetInstance()->PushState(new PlayState()); // Chuyển sang PlayState
        }
        if (mouseX >= exitButton.x && mouseX <= exitButton.x + exitButton.w &&
            mouseY >= exitButton.y && mouseY <= exitButton.y + exitButton.h) {
            Engine::GetInstance()->Quit();
        }
    }
}

void Menu::Render() {
    SDL_Renderer* renderer = Engine::GetInstance()->GetRenderer();
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); // Màu xám cho nền
    SDL_RenderClear(renderer);

    // Vẽ nút Play
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Xanh lá
    SDL_RenderFillRect(renderer, &playButton);
    TextureManager::GetInstance()->DrawText("Play", playButton.x + 40, playButton.y + 20, 255, 255, 255);

    // Vẽ nút Exit
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Đỏ
    SDL_RenderFillRect(renderer, &exitButton);
    TextureManager::GetInstance()->DrawText("Exit", exitButton.x + 40, exitButton.y + 20, 255, 255, 255);

    SDL_RenderPresent(renderer);
}

void Menu::Enter() {
    TextureManager::GetInstance()->LoadFont("assets/arial.ttf", 32); // Load font nếu cần
}

void Menu::Exit()
{

}
