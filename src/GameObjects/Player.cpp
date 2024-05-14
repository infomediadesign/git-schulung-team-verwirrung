//
// Created by Oliver on 17.04.2024.
//

#include "Player.h"
#include "../Scene.h"
#include "raymath.h"
#include "../Particle.h"

void Player::Update() {

    Vector2 input = {0, 0};
    if (IsKeyDown(KEY_W)) {
        input.y -= 1;
    }
    if (IsKeyDown(KEY_S)) {
        input.y += 1;
    }
    if (IsKeyDown(KEY_A)) {
        input.x -= 1;
    }
    if (IsKeyDown(KEY_D)) {
        input.x += 1;
    }
    if (input.x == 0 && input.y == 0) {
        input = {GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X), GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y)};
    }
    input = Vector2Normalize(input);
    if (input.x != 0 || input.y != 0) {
        float lookAngle = atan2(lookDirection.y, lookDirection.x);
        float moveAngle = atan2(input.y, input.x);
        // generate new lookDirection which moves towards the input direction by up to 2 degrees per frame
        float angleDifference = moveAngle - lookAngle;
        if (angleDifference > PI) {
            angleDifference -= 2 * PI;
        }
        if (angleDifference < -PI) {
            angleDifference += 2 * PI;
        }
        float maxAngleChange = 2 * DEG2RAD;
        if (angleDifference > maxAngleChange) {
            lookAngle += maxAngleChange;
        } else if (angleDifference < -maxAngleChange) {
            lookAngle -= maxAngleChange;
        } else {
            lookAngle = moveAngle;
        }
        lookDirection = {cosf(lookAngle), sinf(lookAngle)};
        //move character towards lookDirection
        float dot = Vector2DotProduct(input, lookDirection);
        if (dot > -2) {
            position = Vector2Add(position, Vector2Scale(Vector2Normalize(lookDirection), dot));
            scene->addParticle(new Particle(position, Vector2Scale(lookDirection,0), 2, 3, ColorFromHSV(GetTime() * 360, 1, 1)));
        }

    }

    for (int i = 0; scene->touchesWall(position, size) && i<4;i++) {
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
    //draw a small red circle at the player's position clamped to map boundaries
    Vector2 clampedPos = Vector2Clamp(position, {0, 0}, {scene->getSize().x, scene->getSize().y});
    DrawCircle(clampedPos.x, clampedPos.y, 3, RED);
    // Draw player
    Color RenderColor = GREEN;
    //if player is on TileID 3 or higher, turn green
    if (scene->touchesWall(position, size)) {
        RenderColor = YELLOW;
    }



    DrawCircle(position.x, position.y, size, RenderColor);
    DrawTexture(sprite, position.x, position.y, WHITE);
    DrawLine(position.x, position.y, position.x + lookDirection.x * 10, position.y + lookDirection.y * 10, RED);
}

Player::Player(Scene *scene) : GameObject(scene) {
    this->scene = scene;
    position = {100, 100};
    size = 6;
    sprite = LoadTexture("resources/player.png");
    name = "Player";
}
