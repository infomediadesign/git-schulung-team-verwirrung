//
// Created by Oliver on 17.04.2024.
//

#ifndef RAYLIBSTARTER_GAMEOBJECT_H
#define RAYLIBSTARTER_GAMEOBJECT_H


#include <string>
#include "raylib.h"
class Scene;

class GameObject {
public:
    virtual void Update() = 0;
    virtual void Draw() = 0;


    Vector2 getPosition() const;
    Scene* scene;
    GameObject(Scene* scene);
protected:
    //static uint32_t objectsCreated;

    int64_t id;
    Vector2 position;
    float size;
    Texture2D sprite;
    std::string name;
};


#endif //RAYLIBSTARTER_GAMEOBJECT_H
