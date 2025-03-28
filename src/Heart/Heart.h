#ifndef HEART_H
#define HEART_H
#include "SDL.h"

class Heart {
private:
    int m_Hearts;
    int m_MaxHearts;

public:
    Heart(int maxHearts = 5);
    void LoseHeart();
    void Draw1();
    void Draw2();
    bool IsGameOver() const { return m_Hearts <= 0; }
    int GetHearts() const { return m_Hearts; }
};

#endif
