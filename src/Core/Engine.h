#ifndef ENGINE_H
#define ENGINE_H

#include"SDL.h"
#include"SDL_image.h"
#include"SDL_mixer.h"
#include"GameState.h"
#include"Menu.h"
#include"GameOver.h"
#include<vector>

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 800

class Engine
{
    public:
        static Engine* GetInstance() {
            return s_Instance = (s_Instance != nullptr)? s_Instance : new Engine();
        }

        bool Init();
        bool Clean();
        void Quit();

        void Update();
        void Render();
        void Events();

        void PushState(GameState* state); // Thêm trạng thái mới
        void PopState();                  // Xóa trạng thái hiện tại
        void ChangeState(GameState* state); // Thay đổi trạng thái

        inline bool IsRunning(){return m_IsRunning;}
        inline SDL_Window* GetMainWindow(){return m_Window;}
        inline SDL_Renderer* GetRenderer(){return m_Renderer;}

    private:
        Engine(){}
        bool m_IsRunning;

        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        static Engine* s_Instance;
        std::vector<GameState*> m_States;
};

#endif // ENGINE_H
