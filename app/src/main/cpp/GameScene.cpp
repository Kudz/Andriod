//
// Created by kamil7 on 2017-03-30.
//

#include "GameScene.h"

GameScene::GameScene()
: _playerLifes(3), _playerScore(0), _isPaused(true)
{
    //increasing the line size
    glLineWidth(3.0f);

    this->createTriangleDrawingObjects();
    this->createTriangleModelObjects();

    this->createLineTextDrawingObjects();
    this->createLineTextModelObjects();

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
    if(this->_isPaused == false)
    {
        this->updateModels();
    }
    else
    {
        if(SharedData::getTouchingStatus())
        {
            if(this->_ball->setDirectionAngle())
            {
                this->_isPaused = false;
                this->_lineTextModelObjects.at(0)->setVisibility(false); //shouldn't be in this way
            }
        }
    }
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
    this->_lifesModelObjects.clear();

    std::shared_ptr<Board> boardModel(new Board);
    boardModel->setColourVector(0.0f, 0.0f, 1.0f, 1.0f);
    this->_board = std::move(boardModel);

    std::shared_ptr<Ball> ballModel(new Ball);
    ballModel->setColourVector(1.0f, 0.0f, 0.0f, 1.0f);
    this->_ball = std::move(ballModel);

    for(uint i = 0; i < 6; i++)
    {
        for(uint j = 0; j < 6; j++)
        {
            std::shared_ptr<Brick> brickModel(new Brick(-0.77f + i * 0.31f, 1.0f - 0.1 * j));
            this->_triangleModelObjects.push_back(std::move(brickModel));
        }
    }

    for(uint i = 0; i < 3; i++)
    {
//        std::shared_ptr<Ball> ballModel(new Ball(0.92f - i*0.1f, 1.35f));
        std::shared_ptr<Ball> ballModel(new Ball(0.72f + i*0.1f, 1.35f));
        ballModel->setColourVector(1.0f, 0.0f, 0.0f, 1.0f);
        this->_lifesModelObjects.push_back(std::move(ballModel));
    }
}

void GameScene::updateModels()
{
    this->_board->update();

    bool isCollision = false;

    glm::vec2 stepTranslation = this->_ball->getMovementVector();
    float directionAngle = this->_ball->getDirectionAngle();
    glm::mat4 modelMatrix = this->_ball->getModelMatrix();

//    std::string message = "directionAgnle = " + a2s<float>(directionAngle);
//    SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

    if( (directionAngle > M_PI) && (directionAngle < 2*M_PI) && (modelMatrix[3][1] < BOTTOM_SCREEN_POSITION + BOARD_HEIGHT + 2*BALL_MAX_SPEED) )
    {
//        std::string message = "stepTranslation[1] = " + a2s<float>(stepTranslation[1]);
//        SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
//        std::string message = "modelMatrix[3][1] = " + a2s<float>(modelMatrix[3][1]);
//        SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
//        message = "offset = " + a2s<float>(BOTTOM_SCREEN_POSITION + BOARD_HEIGHT + 2*BALL_MAX_SPEED);
//        SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
//        message = "Board_top = " + a2s<float>(BOTTOM_SCREEN_POSITION + BOARD_HEIGHT);
//        SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

        isCollision = this->checkCollisionBallBoard(stepTranslation);
    }

    if( (modelMatrix[3][1] > TOP_SCREEN_POSITION - 2*BALL_MAX_SPEED) || (modelMatrix[3][0] < LEFT_SCREEN_POSITION + 2*BALL_MAX_SPEED) || (modelMatrix[3][0] > RIGHT_SCREEN_POSITION - 2*BALL_MAX_SPEED) )
    {
        isCollision = this->checkCollisionBallBoundaries(stepTranslation);
    }

//    this->_ball->update();

    if(isCollision == false)
    {
        this->_ball->update();
    }

    //reset game, player is lossing one life
    if( modelMatrix[3][1] < BOTTOM_SCREEN_POSITION )
    {
        if(this->_playerLifes)
        {
            this->_isPaused = true;
            this->_lineTextModelObjects.at(0)->setVisibility(true); //shouldn't be in this way
            this->_playerLifes--;
            this->_lifesModelObjects.at(this->_playerLifes)->setColourVector(0.0f, 0.0f, 0.0f, 1.0f);
            this->_ball->resetBall();
            this->_board->resetBoard();
        }
        else
        {
            this->_isPaused = true;
            //game over
        }
    }

}

void GameScene::drawModels()
{
    {
        std::string triangleDrawingName = this->_board->getDrawingName();
        this->_triangleDrawingObjects.at(triangleDrawingName)->draw(this->_board);
    }

    {
        std::string triangleDrawingName = this->_ball->getDrawingName();
        this->_triangleDrawingObjects.at(triangleDrawingName)->draw(this->_ball);
    }

//    SharedData::logInfo(LOG_GAME_SCENE_TAG, "drawModels");
    for(std::shared_ptr<ModelInterface> triangleModelObject: this->_triangleModelObjects)
    {
        std::string triangleDrawingName = triangleModelObject->getDrawingName();
        this->_triangleDrawingObjects.at(triangleDrawingName)->draw(triangleModelObject);
    }

    for(std::shared_ptr<ModelInterface> lineTextModelObject: this->_lineTextModelObjects)
    {
        std::string lineDrawingName = lineTextModelObject->getDrawingName();
        this->_lineTextDrawingObjects.at(lineDrawingName)->draw(lineTextModelObject);
    }

    for(std::shared_ptr<ModelInterface> lifetModelObject: this->_lifesModelObjects)
    {
        std::string lifeDrawingName = lifetModelObject->getDrawingName();
        this->_triangleDrawingObjects.at(lifeDrawingName)->draw(lifetModelObject);
    }
}

void GameScene::createLineTextDrawingObjects()
{
    this->_lineTextDrawingObjects.clear();

    {
        LineTextDescription lineTextDescription("T");
        std::shared_ptr<LineDrawing> lineTextDrawing(new LineDrawing(lineTextDescription));
        this->_lineTextDrawingObjects.insert({"T",std::move(lineTextDrawing)});
    }

    {
        LineTextDescription lineTextDescription("SCORE");
        std::shared_ptr<LineDrawing> lineTextDrawing(new LineDrawing(lineTextDescription));
        this->_lineTextDrawingObjects.insert({"SCORE",std::move(lineTextDrawing)});
    }

    {
        LineTextDescription lineTextDescription("LIFES");
        std::shared_ptr<LineDrawing> lineTextDrawing(new LineDrawing(lineTextDescription));
        this->_lineTextDrawingObjects.insert({"LIFES",std::move(lineTextDrawing)});
    }
}

void GameScene::createLineTextModelObjects()
{
    this->_lineTextModelObjects.clear();

    {
        std::shared_ptr<LineText> lineTextModel(new LineText("T", 0.0f, 0.0f));
        this->_lineTextModelObjects.push_back(std::move(lineTextModel));
    }

    {
        std::shared_ptr<LineText> lineTextModel(new LineText("SCORE", -0.9f, 1.35f));
        this->_lineTextModelObjects.push_back(std::move(lineTextModel));
    }

    {
        std::shared_ptr<LineText> lineTextModel(new LineText("LIFES", 0.15f, 1.35f));
        this->_lineTextModelObjects.push_back(std::move(lineTextModel));
    }
}

bool GameScene::checkCollisionBallBoard(glm::vec2 stepTranslation)
{
    SharedData::logInfo(LOG_GAME_SCENE_TAG, "checkCollisionBallBoard");
    float xBoard = this->_board->getModelMatrix()[3][0];
    float yBoard = this->_board->getModelMatrix()[3][1];
    float xLowBoard = xBoard - BOARD_WIDTH/2;
    float xHightBoard = xBoard + BOARD_WIDTH/2;
    float yLowBoard = yBoard - BOARD_HEIGHT/2;
    float yHightBoard = yBoard + BOARD_HEIGHT/2;

    float xBall = this->_ball->getModelMatrix()[3][0];
    float yBall = this->_ball->getModelMatrix()[3][1];
    float yLowBall = yBall - BALL_RADIUS;

//    std::string message = "yBall = " + a2s<float>(yBall);
//    SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
//    message = "yLowBall = " + a2s<float>(yLowBall);
//    SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
//    message = "yHightBoard = " + a2s<float>(yHightBoard);
//    SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

    float yDifference = yHightBoard - yLowBall; //compute distance between bottom part of Ball, and top part of Board

//    message = "yDifference = " + a2s<float>(yDifference);
//    SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
//
//    message = "stepTranslation[1] = " + a2s<float>(stepTranslation[1]);
//    SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

    if(yDifference > stepTranslation[1]+0.01) // if difference is smaller than stepMovement in y axes, there is possibility for collision
    {
//        yDifference = yDifference + BALL_RADIUS; //moving from low part of ball to middle part of ball
        float xDifference = stepTranslation[0]*(yDifference)/stepTranslation[1]; // compute xDifference from proportion
        float xNewPosition = xBall + xDifference;
        float yNewPosition = yBall + yDifference; //

//        message = "xBall = " + a2s<float>(xBall);
//        SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
//        message = "xNewPosition = " + a2s<float>(xNewPosition);
//        SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
//        message = "xLowBoard = " + a2s<float>(xLowBoard);
//        SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
//        message = "xHightBoard = " + a2s<float>(xHightBoard);
//        SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

        if( (xNewPosition >= xLowBoard) && (xNewPosition <= xHightBoard) )
        {
            this->_ball->increaseVelocity();
            this->_ball->reverseY();

            //experimental
            float angleChange = M_PI/3*(xNewPosition - xLowBoard)/(xLowBoard - xHightBoard) + M_PI/6;
            this->_ball->increaseDirectionAngle(angleChange);

            this->_ball->setNewPosition(xNewPosition,yNewPosition);

            return true;
        }
    }
    return false;
}

bool GameScene::checkCollisionBallBoundaries(glm::vec2 stepTranslation)
{
    SharedData::logInfo(LOG_GAME_SCENE_TAG, "checkCollisionBallBoundaries");

    float xBall = this->_ball->getModelMatrix()[3][0];
    float xLeftBall = xBall - BALL_RADIUS;
    float xRightBall = xBall + BALL_RADIUS;
    float yBall = this->_ball->getModelMatrix()[3][1];
    float yHighBall = yBall + BALL_RADIUS;

    //first case top boundary
    {
        float yDifference = TOP_SCREEN_POSITION - yHighBall;

//        std:string message = "TOP_SCREEN_POSITION = " + a2s<float>(TOP_SCREEN_POSITION);
//        SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
//
//        message = "yHighBall = " + a2s<float>(yHighBall);
//        SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
//
//        message = "stepTranslation[1] = " + a2s<float>(stepTranslation[1]);
//        SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
//
//        message = "yDifference = " + a2s<float>(yDifference);
//        SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

        if (yDifference < stepTranslation[1] +
                          0.01) // if difference is smaller than stepMovement in y axes, there is possibility for collision
        {
            float xDifference = stepTranslation[0] * (yDifference) /
                                stepTranslation[1]; // compute xDifference from proportion
            float xNewPosition = xBall + xDifference;
            float yNewPosition = yBall + yDifference; //

//            message = "xBall = " + a2s<float>(xBall);
//            SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
//
//            message = "yBall = " + a2s<float>(yBall);
//            SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
//
//            message = "xNewPosition = " + a2s<float>(xNewPosition);
//            SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
//
//            message = "yNewPosition = " + a2s<float>(yNewPosition);
//            SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

            this->_ball->increaseVelocity();
            this->_ball->reverseY();
            this->_ball->setNewPosition(xNewPosition, yNewPosition);

            return true;
        }
    }

    //second case left boundary
    {
        float xDifference = LEFT_SCREEN_POSITION - xLeftBall; //compute distance between bottom part of Ball, and top part of Board

        if(xDifference > stepTranslation[0]+0.01) // if difference is smaller than stepMovement in y axes, there is possibility for collision
        {
            float yDifference = stepTranslation[1]*(xDifference)/stepTranslation[0]; // compute xDifference from proportion
            float xNewPosition = xBall + xDifference;
            float yNewPosition = yBall + yDifference; //

            this->_ball->increaseVelocity();
            this->_ball->reverseX();
            this->_ball->setNewPosition(xNewPosition,yNewPosition);

            return true;
        }
    }

    //third case right boundary
    {
        float xDifference = RIGHT_SCREEN_POSITION - xRightBall; //compute distance between bottom part of Ball, and top part of Board

//        std:string message = "RIGHT_SCREEN_POSITION = " + a2s<float>(RIGHT_SCREEN_POSITION);
//        SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
//
//        message = "xRightBall = " + a2s<float>(xRightBall);
//        SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
//
//        message = "xBall = " + a2s<float>(xBall);
//        SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
//
//        message = "stepTranslation[0] = " + a2s<float>(stepTranslation[0]);
//        SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
//
//        message = "xDifference = " + a2s<float>(xDifference);
//        SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

        if(xDifference < stepTranslation[0]+0.01) // if difference is smaller than stepMovement in y axes, there is possibility for collision
        {
            float yDifference = stepTranslation[1]*(xDifference)/stepTranslation[0]; // compute xDifference from proportion
            float xNewPosition = xBall + xDifference;
            float yNewPosition = yBall + yDifference; //

//            message = "xBall = " + a2s<float>(xBall);
//            SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
//
//            message = "yBall = " + a2s<float>(yBall);
//            SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
//
//            message = "xNewPosition = " + a2s<float>(xNewPosition);
//            SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
//
//            message = "yNewPosition = " + a2s<float>(yNewPosition);
//            SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

            this->_ball->increaseVelocity();
            this->_ball->reverseX();
            this->_ball->setNewPosition(xNewPosition,yNewPosition);

            return true;
        }
    }


    return false;
}