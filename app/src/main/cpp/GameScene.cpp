//
// Created by kamil7 on 2017-03-30.
//

#include "GameScene.h"

GameScene::GameScene()
{
    this->createTriangleDrawingObjects();
    this->createTriangleModelObjects();

    float screenHeight = SharedData::getScreenHeight();
    std::string message = "screen height = " + a2s<float>(screenHeight);
    SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

    message = "GL_INVALID_OPERATION = " + a2s<GLfloat>(GL_INVALID_OPERATION);
    SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

    message = "GL_INVALID_VALUE = " + a2s<GLfloat>(GL_INVALID_VALUE);
    SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

    std::shared_ptr<TriangleShader> traingleShader = SharedData::getTriangleShader();
    message = "ProgramID = " + a2s<GLuint>(traingleShader->getProgramID());
    SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
}

void GameScene::render()
{
    this->clearBackground();
    this->updateModels();
    SharedData::checkGLError(LOG_GAME_SCENE_TAG, "updateModels");
    this->drawModels();
    SharedData::checkGLError(LOG_GAME_SCENE_TAG, "drawModels");
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

void GameScene::createTriangleModelObjects()
{
    std::shared_ptr<Board> boardModel(new Board);
    boardModel->setColour(0.0f, 0.0f, 1.0f, 1.0f);
    this->_triangleModelObjects.push_back(std::move(boardModel));
}

void GameScene::updateModels()
{
//    SharedData::logInfo(LOG_GAME_SCENE_TAG, "updateModels");
    for(std::shared_ptr<TriangleModelInterface> triangleModelObject: this->_triangleModelObjects)
    {
        triangleModelObject->update();
    }
}

void GameScene::drawModels()
{
//    SharedData::logInfo(LOG_GAME_SCENE_TAG, "drawModels");
    for(std::shared_ptr<TriangleModelInterface> triangleModelObject: this->_triangleModelObjects)
    {
        std::string triangleDrawingName = triangleModelObject->getTriangleDrawingName();
        this->_triangleDrawingObjects.at(triangleDrawingName)->draw(triangleModelObject);
    }
}
