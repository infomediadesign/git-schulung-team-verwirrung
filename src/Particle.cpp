//
// Created by Oliver on 14.05.2024.
//

#include "Particle.h"

void Particle::update() {
    position.x += velocity.x;
    position.y += velocity.y;
    lifeTimeLeft -= GetFrameTime();
    return;
}

void Particle::draw() {
    DrawCircleV(position, size, ColorAlpha(color, lifeTimeLeft));
}

bool Particle::lifeTimeOver() {
    return lifeTimeLeft <= 0;
}

Particle::Particle(Vector2 position, Vector2 velocity, float size, float lifeTime, Color color) : position(position), velocity(velocity), size(size), lifeTimeLeft(lifeTime), color(color) {

}
