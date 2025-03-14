#ifndef HEART_H
#define HEART_H
#include "SDL.h"

class Heart {
private:
    int m_Hearts; // Số mạng còn lại
    int m_MaxHearts; // Số mạng tối đa

public:
    Heart(int maxHearts = 5);
    void LoseHeart(); // Giảm 1 mạng
    void Draw1(); // Vẽ biểu tượng trái tim
    void Draw2();
    bool IsGameOver() const { return m_Hearts <= 0; }
    int GetHearts() const { return m_Hearts; }
};

#endif
