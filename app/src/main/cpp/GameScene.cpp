//
// Created by kamil7 on 2017-03-30.
//

#include "GameScene.h"

GameScene::GameScene()
: _board(nullptr), _boardDrawable(nullptr)
{
    this->createTriangleDrawingObjects();

    this->_board = std::shared_ptr<Board> (new Board);
    float screenHeight = SharedData::getScreenHeight();
    std::string message = "screen height = " + a2s<float>(screenHeight);
    SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

//    if(this->_boardDrawable == NULL)
//    {
//        SharedData::logInfo(LOG_GAME_SCENE_TAG, "creating boardDrawable");
//        this->_boardDrawable = std::shared_ptr<TriangleDrawing> (new TriangleDrawing(this->_board));
//        this->_boardDrawable->setColour(1.0f, 0.0f, 0.5f, 1.0f);
//    }

    message = "GL_INVALID_OPERATION = " + a2s<GLfloat>(GL_INVALID_OPERATION);
    SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

    message = "GL_INVALID_VALUE = " + a2s<GLfloat>(GL_INVALID_VALUE);
    SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

    message = "ProgramID = " + a2s<GLuint>(SharedData::getTriangleShader()->getProgramID(0));
    SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
}

void GameScene::render()
{
    _board->setXPosition(36);
    this->clearBackground();
    glm::mat4 per(1.0f);
    glm::mat4 vis(1.0f);
//    SharedData::logInfo(LOG_GAME_SCENE_TAG, glm::to_string(per).c_str());
//    _boardDrawable->draw();
    _triangleDrawingObjects.at("Board")->draw();
}

void GameScene::clearBackground()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    SharedData::checkGLError(LOG_GAME_SCENE_TAG, "glClearColor");
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    SharedData::checkGLError(LOG_GAME_SCENE_TAG, "glClear");
}

void GameScene::createTriangleDrawingObjects()
{
    BoardDescription boardDescription;
    std::shared_ptr<TriangleDrawing> boarDescription(new TriangleDrawing(boardDescription));
    this->_triangleDrawingObjects.insert({"Board",std::move(boarDescription)});
    //delete this stuff
    _triangleDrawingObjects.at("Board")->setColour(1.0f, 0.0f, 0.5f, 1.0f);
}