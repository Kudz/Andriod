//
// Created by kamil7 on 2017-03-30.
//

#ifndef GAME_GAMESCENE_H
#define GAME_GAMESCENE_H

#include <unordered_map>

#include "glm/glm.hpp" //ec3, vec4, ivec4, mat4
#include "glm/gtc/matrix_transform.hpp" // translate, rotate, scale, perspective
#include "glm/gtc/type_ptr.hpp" // value_ptr
#include "glm/ext.hpp" //to_string

#include "TriangleDrawing.h"
#include "Board.h"
#include "BoardDescription.h"
#include "SharedData.h"

#define  LOG_GAME_SCENE_TAG    "GameScene"

typedef std::unordered_map<std::string, std::shared_ptr<TriangleDrawing> > TriangleDrawingObjects;
typedef std::vector<std::shared_ptr<TriangleModelInterface> > TriangleModelObjects;

class GameScene
{
public:
    GameScene();
    void render();
private:
    void clearBackground();
    void createTriangleDrawingObjects();
    void createTriangleModelObjects();
    void updateModels();
    void drawModels();

    //TriangleDescriptionObjects
    TriangleDrawingObjects _triangleDrawingObjects;

    TriangleModelObjects _triangleModelObjects;
};


#endif //GAME_GAMESCENE_H
