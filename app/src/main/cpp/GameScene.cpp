//
// Created by kamil7 on 2017-03-30.
//

#include "GameScene.h"

GameScene::GameScene()
{
    //increasing the line size
    glLineWidth(3.0f);

    this->createTriangleDrawingObjects();
    this->createTriangleModelObjects();

    //boundary
    BoundaryDescription boundaryDescription;
    std::shared_ptr<LineDrawing> boundaryDrawing(new LineDrawing(boundaryDescription));
    this->_boundaryDrawingObject = std::move(boundaryDrawing);

    this->_boundaryModelObject = std::shared_ptr<Boundary>(new Boundary);
    this->_boundaryModelObject->setColourVector(0.0f, 0.0f, 1.0f, 1.0f);

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
    this->_boundaryDrawingObject->draw(this->_boundaryModelObject);
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
    std::shared_ptr<TriangleDrawing> boardDrawing(new TriangleDrawing(boardDescription));
    this->_triangleDrawingObjects.insert({"Board",std::move(boardDrawing)});
    //delete this stuff
    _triangleDrawingObjects.at("Board")->setColour(1.0f, 0.0f, 0.5f, 1.0f);
}

void GameScene::createTriangleModelObjects()
{
    std::shared_ptr<Board> boardModel(new Board);
    boardModel->setColourVector(0.0f, 0.0f, 1.0f, 1.0f);
    this->_triangleModelObjects.push_back(std::move(boardModel));
}

void GameScene::updateModels()
{
//    SharedData::logInfo(LOG_GAME_SCENE_TAG, "updateModels");
    for(std::shared_ptr<ModelInterface> triangleModelObject: this->_triangleModelObjects)
    {
        triangleModelObject->update();
    }
}

void GameScene::drawModels()
{
//    SharedData::logInfo(LOG_GAME_SCENE_TAG, "drawModels");
    for(std::shared_ptr<ModelInterface> triangleModelObject: this->_triangleModelObjects)
    {
        std::string triangleDrawingName = triangleModelObject->getDrawingName();
        this->_triangleDrawingObjects.at(triangleDrawingName)->draw(triangleModelObject);
    }
}
