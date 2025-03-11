#ifndef PLAY_H
#define PLAY_H

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "GameState.h"
#include "Warrior.h"
#include "Menu.h"
#include "Timer.h"
#include "Input.h"
#include "TextureManager.h"
#include "Collision.h"

class Play : public GameState {
public:
    Play();

    void Events();
    virtual bool Init();
    virtual bool Exit();
    virtual void Update();
    virtual void Render();

    //inline GameMap* GetMap() { return m_LevelMap; }

private:
    static void OpenMenu();
    static void PauseGame();

private:
    bool m_EditMode;
    std::vector<GameObject*> m_GameObjects;
};

#endif // PLAY_H
