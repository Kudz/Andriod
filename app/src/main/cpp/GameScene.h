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

#include "SharedData.h"
#include "LineDrawing.h"
#include "TriangleDrawing.h"
#include "Board.h"
#include "BoardDescription.h"
#include "Boundary.h"
#include "BoundaryDescription.h"
#include "Ball.h"
#include "BallDescription.h"
#include "Brick.h"
#include "BrickDescription.h"
#include "lineText.h"
#include "Number.h"

#define  LOG_GAME_SCENE_TAG    "GameScene"

enum collision{COLLISION_BOTTOM, COLLISION_RIGHT, COLLISION_LEFT, COLLISION_TOP, COLLISION_BOTTOM_RIGHT, COLLISION_BOTTOM_LEFT, COLLISION_TOP_RIGHT, COLLISION_TOP_LEFT};

typedef std::unordered_map<std::string, std::shared_ptr<TriangleDrawing> > TriangleDrawingObjects;
typedef std::vector<std::shared_ptr<ModelInterface> > TriangleModelObjects;

typedef std::unordered_map<std::string, std::shared_ptr<LineDrawing> > LineTextDrawingObjects;
typedef std::vector<std::shared_ptr<LineText> > LineTextModelObjects;

typedef std::unordered_map<std::string, std::shared_ptr<LineDrawing> > NumberDrawingObjects;
typedef std::vector<std::shared_ptr<Number> > NumberModelObjects;

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

    void createLineTextDrawingObjects();
    void createLineTextModelObjects();

    void createNumberDrawingObjects();
    void createNumberModelObjects();

    //TriangleDescriptionObjects
    TriangleDrawingObjects _triangleDrawingObjects;
    TriangleModelObjects _triangleModelObjects;

    std::shared_ptr<LineDrawing> _boundaryDrawingObject;
    std::shared_ptr<ModelInterface> _boundaryModelObject;

    LineTextDrawingObjects _lineTextDrawingObjects;
    LineTextModelObjects _lineTextModelObjects;

    NumberDrawingObjects _numberDrawingObjects;
    NumberModelObjects _numberModelObjects;

    //Game Status
    bool _isPaused;
    bool _isEnded;
    std::shared_ptr<Ball> _ball;
    std::shared_ptr<Board> _board;
    void newBall();
    void restart();

    bool checkCollisionBallBoard(glm::vec2 stepTranslation);
    bool checkCollisionBallBoundaries(glm::vec2 stepTranslation);

    bool checkCollisionBallBrick(std::shared_ptr<ModelInterface> brickObject);
    bool checkCollisionBallBricks(std::vector<std::shared_ptr<ModelInterface> > brickObjects);
    collision findPossibleCollisionSides(glm::vec2 stepMovementVector);
    std::pair<float, float> computePercentageDistance(float fromPosition, float toPosition, float stepValue);
    std::pair<collision, float>  findCollisionSideAndMovementDistance(collision posibleCollisionSides, glm::vec2 stepMovementVector, glm::mat4 ballModelMatrixData, std::shared_ptr<ModelInterface> brickObject);
    bool manageBallAfterCollisionWithBrick(collision collisionSide, float distance, std::shared_ptr<ModelInterface> brickObject, glm::vec2 stepMovementVector, glm::mat4 ballModelMatrix);
    bool manageBallAfterCollisionWithBricks(std::vector<collision> collisionSides, std::vector<float> distances, std::vector<std::shared_ptr<ModelInterface> > brickObject, glm::vec2 stepMovementVector, glm::mat4 ballModelMatrix);
//    bool checkBrickCollisionStatus(collision collisionSide, glm::vec2 stepMovementVector, std::shared_ptr<ModelInterface> brickObjects, glm::mat4 ballModelMatrix);

    //Player Stats
    TriangleModelObjects _lifesModelObjects;
    int _playerLifes;
    int _playerScore;
};


#endif //GAME_GAMESCENE_H
