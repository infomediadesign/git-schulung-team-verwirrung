//
// Created by Oliver on 17.04.2024.
//

#ifndef RAYLIBSTARTER_PLAYER_H
#define RAYLIBSTARTER_PLAYER_H


#include "../GameObject.h"

class Player : public GameObject{
public:
    void Update() override;
    void Draw() override;
    Player(Scene *scene);
protected:

};


#endif //RAYLIBSTARTER_PLAYER_H
