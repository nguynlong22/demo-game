#include "Timer.h"
#include "SDL.h"

Timer* Timer::s_Instance = nullptr;

void Timer::Tick()
{
    m_DeltaTime = (SDL_GetTicks() - m_LastTime)*(TARGET_FPS/1000.0f);

    // Đảm bảo DeltaTime không quá lớn để tránh giật lag
    if (m_DeltaTime > TARGET_DELTATIME) {
        m_DeltaTime = TARGET_DELTATIME;
    }

    m_LastTime = SDL_GetTicks();
}
