#ifndef MENU_H
#define MENU_H
#include "GameState.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "TextureManager.h"
#include "Input.h"

class Menu : public GameState {
public:
    Menu();
    void Update(float dt) override;
    void Render() override;
    void Enter() override;

private:
    SDL_Rect playButton;
    SDL_Rect exitButton;
    SDL_Rect continueButton;
    Mix_Music* backgroundMusic = nullptr;
};

#endif // MENU_H
