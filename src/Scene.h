//
// Created by Oliver on 17.04.2024.
//

#ifndef RAYLIBSTARTER_SCENE_H
#define RAYLIBSTARTER_SCENE_H

#include <vector>
#include "raylib.h"

class GameObject; //forward declaration of GameObject
class Particle;

class Scene {
public:
    void update(); //first update all objects, then delete those marked for deletion
    void draw();
    Scene(const char * filename);
    //Collision detection functions
    bool touchesWall(Vector2 pos, float size);
    bool touchesWall(Vector2 pos);
    Vector2 touchWallPosition(Vector2 pos, Vector2 size);
    Rectangle getWallAt(Vector2 pos);
    std::vector<GameObject*> getGameObjectsAt(Vector2 pos, Vector2 size);
    //game object handling functions
    void addGameObject(GameObject* object);
    GameObject* getGameObject(int64_t id);
    //particle handling functions
    void addParticle(Particle* particle);


    int getTileAt(float x, float y);

    Rectangle getTouchedWall(Vector2 position, float radius);

protected:
    std::vector<GameObject*> objects;
    std::vector<int> tileMap;
    std::vector<Particle*> particles;
    int mapWidth{};
    int mapHeight{};
};


#endif //RAYLIBSTARTER_SCENE_H
