//
// Created by Oliver on 17.04.2024.
//

#include "Player.h"
#include "../Scene.h"
#include "raymath.h"

void Player::Update() {
    // Update player position
    if (IsKeyDown(KEY_RIGHT)) position.x += 2.0f;
    if (IsKeyDown(KEY_LEFT)) position.x -= 2.0f;
    if (IsKeyDown(KEY_UP)) position.y -= 2.0f;
    if (IsKeyDown(KEY_DOWN)) position.y += 2.0f;

    for (int i = 0;scene->touchesWall(position, size)&&i<4;i++) {
        Rectangle touchedWall = scene->getTouchedWall(position, size);
        Vector2 touchPoint = Vector2Clamp(position, {touchedWall.x, touchedWall.y}, {touchedWall.x + touchedWall.width, touchedWall.y + touchedWall.height});
        Vector2 pushForce = Vector2Subtract(position, touchPoint);
        float overlapDistance = size - Vector2Length(pushForce);
        if (overlapDistance <= 0) {
            break;
        }
        pushForce = Vector2Normalize(pushForce);
        pushForce = Vector2Scale(pushForce, overlapDistance);
        position = Vector2Add(position, pushForce);
    }
}

void Player::Draw() {
    // Draw player
    Color RenderColor = GREEN;
    //if player is on TileID 3 or higher, turn green
    if (scene->touchesWall(position, size)) {
        RenderColor = GREEN;
    }

    DrawCircle(position.x, position.y, size, RenderColor);
    DrawTexture(sprite, position.x, position.y, WHITE);
}

Player::Player(Scene *scene) : GameObject(scene) {
    this->scene = scene;
    position = {100, 100};
    size = 6;
    sprite = LoadTexture("resources/player.png");
    name = "Player";
}
