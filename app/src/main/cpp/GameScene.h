//
// Created by kamil7 on 2017-03-30.
//

#ifndef GAME_GAMESCENE_H
#define GAME_GAMESCENE_H

#include "glm/glm.hpp" //ec3, vec4, ivec4, mat4
#include "glm/gtc/matrix_transform.hpp" // translate, rotate, scale, perspective
#include "glm/gtc/type_ptr.hpp" // value_ptr
#include "glm/ext.hpp" //to_string

#include "TriangleDrawing.h"
#include "Board.h"
#include "SharedData.h"

#define  LOG_GAME_SCENE_TAG    "GameScene"

class GameScene
{
public:
    GameScene();
//    ~GameScene();
    void render();
private:
    void clearBackground();
    std::shared_ptr<Board> _board;
    std::shared_ptr<TriangleDrawing> _boardDrawable;
};


#endif //GAME_GAMESCENE_H