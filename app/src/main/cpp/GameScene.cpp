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

//    std::shared_ptr<TriangleShader> traingleShader = SharedData::getTriangleShader();
//    message = "ProgramID = " + a2s<GLuint>(traingleShader->getProgramID());
//    SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
}

void GameScene::render()
{
//    std::string vertexShader = SharedData::getContentOfAssetFile("Shaders/triangle_shader_v");
//    SharedData::logInfo(LOG_GAME_SCENE_TAG, vertexShader.c_str());
//
//    std::string fragmentShader = SharedData::getContentOfAssetFile("Shaders/triangle_shader_f");
//    SharedData::logInfo(LOG_GAME_SCENE_TAG, fragmentShader.c_str());

//    GLint linkStatus = GL_FALSE;
//    glGetProgramiv(SharedData::getTriangleShader()->getProgramID(), GL_LINK_STATUS, &linkStatus);
//    if(!linkStatus)
//    {
//        SharedData::getTriangleShader()->checkCompilationStatus();
//    }

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
    this->_triangleDrawingObjects.clear();

    BoardDescription boardDescription;
    std::shared_ptr<TriangleDrawing> boardDrawing(new TriangleDrawing(boardDescription));
    this->_triangleDrawingObjects.insert({"Board",std::move(boardDrawing)});

    BallDescription ballDescription;
    std::shared_ptr<TriangleDrawing> ballDrawing(new TriangleDrawing(ballDescription));
    this->_triangleDrawingObjects.insert({"Ball",std::move(ballDrawing)});

    BrickDescription brickDescription;
    std::shared_ptr<TriangleDrawing> brickDrawing(new TriangleDrawing(brickDescription));
    this->_triangleDrawingObjects.insert({"Brick",std::move(brickDrawing)});
}

void GameScene::createTriangleModelObjects()
{
    this->_triangleModelObjects.clear();

    std::shared_ptr<Board> boardModel(new Board);
    boardModel->setColourVector(0.0f, 0.0f, 1.0f, 1.0f);
    this->_triangleModelObjects.push_back(std::move(boardModel));

    std::shared_ptr<Ball> ballModel(new Ball);
    ballModel->setColourVector(1.0f, 0.0f, 0.0f, 1.0f);
    this->_triangleModelObjects.push_back(std::move(ballModel));

    for(uint i = 0; i < 6; i++)
    {
        std::shared_ptr<Brick> brickModel(new Brick(-0.77f + i*0.31f, 0.9f));
        this->_triangleModelObjects.push_back(std::move(brickModel));
    }
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
