#ifndef GAMESTATE_H
#define GAMESTATE_H


class GameState
{
    public:
        virtual ~GameState() {}
        virtual void Update(float dt) = 0;
        virtual void Render() = 0;
        virtual void Enter() = 0;
};

#endif // GAMESTATE_H
