//
// Created by Oliver on 17.04.2024.
//

#include "Player.h"
#include "../Scene.h"

void Player::Update() {
    // Update player position
    if (IsKeyDown(KEY_RIGHT)) position.x += 2.0f;
    if (IsKeyDown(KEY_LEFT)) position.x -= 2.0f;
    if (IsKeyDown(KEY_UP)) position.y -= 2.0f;
    if (IsKeyDown(KEY_DOWN)) position.y += 2.0f;
}

void Player::Draw() {
    // Draw player
    Color RenderColor = RED;
    //if player is on TileID 3 or higher, turn green
    int onTile = scene->getTileAt(position.x, position.y);
    if (onTile >= 3) {
        RenderColor = GREEN;
    }

    DrawCircle(position.x, position.y, size, RenderColor);
    DrawTexture(sprite, position.x, position.y, WHITE);
}

Player::Player(Scene *scene) {
    this->scene = scene;
    position = {100, 100};
    size = 8;
    sprite = LoadTexture("resources/player.png");
    name = "Player";
}
