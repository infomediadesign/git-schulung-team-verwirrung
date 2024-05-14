//
// Created by Oliver on 14.05.2024.
//


#ifndef RAYLIBSTARTER_PARTICLE_H
#define RAYLIBSTARTER_PARTICLE_H


#include "raylib.h"

class Particle {
public:
    void update();
    void draw();
    Particle(Vector2 position, Vector2 velocity, float size, float lifeTime, Color color);
    bool lifeTimeOver();
protected:
    Vector2 position;
    Vector2 velocity;
    float size;
    float lifeTimeLeft;
    Color color;
};


#endif //RAYLIBSTARTER_PARTICLE_H
