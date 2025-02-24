#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <vector>
#include"Layer.h"

#include<iostream>
class GameMap
{
    public:
        void Render(){
            for (unsigned int i = 0; i < m_MapLayers.size(); i++) {
                m_MapLayers[i]->Render();
            }
        }

        void Update(){
            for (unsigned int i = 0; i < m_MapLayers.size(); i++) {
                m_MapLayers[i]->Update();
            }
        }

        vector<Layer*> GetMapPlayers(){return m_MapLayers;}

    private:
        vector<Layer*> m_MapLayers;
};

#endif // GAMEMAP_H
