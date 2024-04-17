//
// Created by Oliver on 17.04.2024.
//

#include "Scene.h"
#include "GameObject.h"
#include "GameObjects/Player.h"
#include "config.h"

void Scene::update() {
    for (auto &gameObject : objects) {
        gameObject->Update();
    }

}

void Scene::draw() {
    //draw background

    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            int tile = tileMap[y * mapWidth + x];
            DrawRectangle(x * 16, y * 16, 16, 16, tile == 0 ? WHITE : tile == 1 ? GRAY : tile == 2 ? DARKGRAY : BLACK);
        }
    }

    for (auto &gameObject : objects) {
        gameObject->Draw();
    }

    //draw foreground
}

Scene::Scene(const char *filename) {
    if (filename == nullptr) {
        addGameObject(new Player(this));
        mapWidth = Game::ScreenWidth / 16;
        mapHeight = Game::ScreenHeight / 16;
        for (int i = 0; i < mapWidth * mapHeight; i++) {
            tileMap.push_back(GetRandomValue(0,3));
        }
    }
}

void Scene::addGameObject(GameObject *object) {
    objects.push_back(object);
}

int Scene::getTileAt(float x, float y) {
    //catch out of bounds
    if (x < 0 || y < 0 || x >= mapWidth * 16 || y >= mapHeight * 16) {
        return 0;
    }
    int tileX = x / 16;
    int tileY = y / 16;
    return tileMap[tileY * mapWidth + tileX];
}
