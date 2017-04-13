//
// Created by kamil7 on 2017-03-30.
//

#include "GameScene.h"

GameScene::GameScene()
: _playerLifes(3), _playerScore(0), _isPaused(true), _isEnded(false)
{
    //increasing the line size
    glLineWidth(3.0f);

    this->createTriangleDrawingObjects();
    this->createTriangleModelObjects();

    this->createLineTextDrawingObjects();
    this->createLineTextModelObjects();

    this->createNumberDrawingObjects();
    this->createNumberModelObjects();

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
    if(this->_isEnded == false)
    {
        if (this->_isPaused == false)
        {
            this->updateModels();
        }
        else
        {
            if (SharedData::getTouchingStatus())
            {
                if (this->_ball->setDirectionAngle())
                {
                    this->_isPaused = false;
                    this->_lineTextModelObjects.at(0)->setVisibility(false); //shouldn't be in this way
                }
            }
        }
    }
    else
    {
        if (SharedData::getTouchingStatus())
        {
            this->restart();
        }
        else
        {
            this->_isEnded = false;
        }
    }
    SharedData::checkGLError(LOG_GAME_SCENE_TAG, "updateModels");
    this->drawModels();
    SharedData::checkGLError(LOG_GAME_SCENE_TAG, "drawModels");
}

void GameScene::restart()
{
    this->_isPaused = true;
//    this->_isEnded = false;
    this->_playerScore = 0;
    this->_playerLifes = 3;
    this->_lineTextModelObjects.at(0)->setVisibility(true); //shouldn't be in this way

    for(uint i = 0; i < this->_lifesModelObjects.size(); i++)
    {
        this->_lifesModelObjects.at(i)->setColourVector(1.0f, 0.0f, 0.0f, 1.0f);
    }

    for(uint i = 0; i < this->_triangleModelObjects.size(); i++)
    {
        this->_triangleModelObjects.at(i)->setVisibility(true);
    }

    this->_ball->resetBall();
    this->_board->resetBoard();
}

void GameScene::newBall()
{
    this->_isPaused = true;
    this->_lineTextModelObjects.at(0)->setVisibility(true); //shouldn't be in this way
    this->_playerLifes--;
    this->_lifesModelObjects.at(this->_playerLifes)->setColourVector(0.0f, 0.0f, 0.0f, 1.0f);
    if(this->_playerLifes)
    {
        this->_ball->resetBall();
        this->_board->resetBoard();
    }
    else
    {
        this->_isEnded = true;
    }
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

    int rowsNumber = 6; // should be 6
    int columnsNumber = 6; //should be 6

    for(uint i = 0; i < rowsNumber; i++)
    {
        for(uint j = 0; j < columnsNumber; j++)
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

    bool anyBrickLeft = false;
    for(std::shared_ptr<ModelInterface> triangleModelObject: this->_triangleModelObjects)
    {
        if(triangleModelObject->getVisibility())
        {
            anyBrickLeft = true;
            std::string triangleDrawingName = triangleModelObject->getDrawingName();
            this->_triangleDrawingObjects.at(triangleDrawingName)->draw(triangleModelObject);
        }
    }
    if(anyBrickLeft == false)
    {
        this->_isEnded = true;
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

    std::string scoreString = a2s<int>(this->_playerScore);

    for(uint i = 0; i < this->_numberModelObjects.size(); i++)
    {
        std::string numberName;
        std::shared_ptr<Number> numberModelObject = this->_numberModelObjects.at(i);
        if(i < scoreString.size())
        {
            numberName = scoreString.substr(scoreString.size() - 1 - i,1);
        }
        else
        {
            numberName = numberModelObject->getDrawingName();
        }
        this->_numberDrawingObjects.at(numberName)->draw(numberModelObject);
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

void GameScene::createNumberDrawingObjects()
{
    this->_numberDrawingObjects.clear();

    std::string allNumbers("0123456789");

    for(uint i = 0; i < allNumbers.size(); i++ )
    {
        std::string numberName = allNumbers.substr(i,1);
        NumberDescription numberDescription(numberName);
        std::shared_ptr<LineDrawing> numberDrawing(new LineDrawing(numberDescription));
        this->_numberDrawingObjects.insert({numberName,std::move(numberDrawing)});
    }

}

void GameScene::createNumberModelObjects()
{
    this->_numberModelObjects.clear();

    for(uint i = 0; i < 3; i++)
    {
        std::shared_ptr<Number> numberModel(new Number("0"));
        numberModel->setNewPosition(-0.05f - 0.11f*i, 1.35f);
        numberModel->setColourVector(1.0f, 0.0f, 0.0f, 1.0f);
        this->_numberModelObjects.push_back(std::move(numberModel));
    }
}


void GameScene::updateModels()
{
    this->_board->update();

    bool isCollision = false;

    glm::vec2 stepTranslation = this->_ball->getMovementVector();
    float directionAngle = this->_ball->getDirectionAngle();
    glm::mat4 modelMatrix = this->_ball->getModelMatrix();

//    SharedData::logInfo(LOG_GAME_SCENE_TAG, "");
//
//    std::string message = "\nmovementVector = x: " + a2s<>(stepTranslation[0]);
//    message = message  +  ", y: " + a2s<>(stepTranslation[1]);
//    SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
//
//    message = "position = x: " + a2s<>(modelMatrix[3][0]);
//    message = message  +  ", y: " + a2s<>(modelMatrix[3][1]);
//    SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

    if( (directionAngle > M_PI) && (directionAngle < 2*M_PI) && (modelMatrix[3][1] < BOTTOM_SCREEN_POSITION + BOARD_HEIGHT + 2*BALL_MAX_SPEED) )
    {
        isCollision = this->checkCollisionBallBoard(stepTranslation);
//        if(isCollision)
//        {
//            this->_playerScore++;
//        }
    }

    // check collision between bricks and ball
    if(modelMatrix[3][1] > 0.0f)
    {
        std::vector<uint> bricksNumbers; //possible collision
        float minimalDistance = BRICK_WIDTH/2 + BALL_MAX_SPEED + 2*BALL_RADIUS;

        for(uint i = 0; i < this->_triangleModelObjects.size(); i++ ) {
            if (this->_triangleModelObjects.at(i)->getVisibility()) {
                glm::mat4 brickMatrix = this->_triangleModelObjects.at(i)->getModelMatrix();
                float distance = (modelMatrix[3][0] - brickMatrix[3][0]) *
                                 (modelMatrix[3][0] - brickMatrix[3][0]) +
                                 (modelMatrix[3][1] - brickMatrix[3][1]) *
                                 (modelMatrix[3][1] - brickMatrix[3][1]);
                distance = sqrt(distance);
                if (distance < minimalDistance) {
                    bool areIntersecting =
                            (abs(modelMatrix[3][0] + stepTranslation[0] - brickMatrix[3][0]) * 2 <
                             (2 * BALL_RADIUS + BRICK_WIDTH)) &&
                            (abs(modelMatrix[3][1] + stepTranslation[1] - brickMatrix[3][1]) * 2 <
                             (2 * BALL_RADIUS + BRICK_HEIGHT));
                    if (areIntersecting) {
                        bricksNumbers.push_back(i);
                    }
                }
            }
        }
//            if(bricksNumbers.size() == 1)
//            {
////                std::string message = "brickNumber = " + a2s<>(bricksNumbers.at(0));
////                SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
//                std::shared_ptr<ModelInterface> brickModel = this->_triangleModelObjects.at(bricksNumbers.at(0));
//                isCollision = this->checkCollisionBallBrick(brickModel);
//                if(isCollision)
//                {
//                    this->_playerScore =  this->_playerScore + 10;
//                }
//            }
//            else
//            {
//                if(bricksNumbers.size() > 1)
//                {
//                    std::string message = "More bricks to consider = " + a2s<>(bricksNumbers.size());
//                    SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
//                    this->_lineTextModelObjects.at(0)->setVisibility(true);
//                    //creating vector with pointers to bricks (possibility of collision)
//                    std::vector<std::shared_ptr<ModelInterface> > bricks;
//                    for(uint i = 0; i < bricksNumbers.size(); i++)
//                    {
//                        std::shared_ptr<ModelInterface> brickModel = this->_triangleModelObjects.at(i);
//                        bricks.push_back(brickModel);
//                    }
//                    this->checkCollisionBallBricks(bricks);
//                }
//            }

        std::string message = "possible collided bricks amount = " + a2s<>(bricksNumbers.size());
        SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

        if(bricksNumbers.size())
        {
            std::vector<std::shared_ptr<ModelInterface> > possiblyCollidedBricks;
            for(uint i = 0; i < bricksNumbers.size(); i++)
            {
                std::string message = "possible collided brick = " + a2s<>(bricksNumbers.at(i));
                SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

                std::shared_ptr<ModelInterface> brickModel = this->_triangleModelObjects.at(bricksNumbers.at(i));
                possiblyCollidedBricks.push_back(brickModel);
            }
            isCollision = this->checkCollisionBallBricks(possiblyCollidedBricks);
        }

    }

    if( (modelMatrix[3][1] > TOP_SCREEN_POSITION - 2*BALL_MAX_SPEED) || (modelMatrix[3][0] < LEFT_SCREEN_POSITION + 2*BALL_MAX_SPEED) || (modelMatrix[3][0] > RIGHT_SCREEN_POSITION - 2*BALL_MAX_SPEED) )
    {
        isCollision = this->checkCollisionBallBoundaries(stepTranslation);
    }

//    this->_ball->update();

    if(isCollision == false)
    {
        this->_ball->update();
//        SharedData::logInfo(LOG_GAME_SCENE_TAG, "updatingBallPosition");
    }

    //reset game, player is lossing one life
    if( modelMatrix[3][1] < BOTTOM_SCREEN_POSITION )
    {
        if(this->_playerLifes)
        {
            this->newBall();
        }
        else
        {
            this->_isEnded = true;
            //game over
        }
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

    float yDifference = yHightBoard - yLowBall; //compute distance between bottom part of Ball, and top part of Board

    if(std::abs(yDifference) > std::abs(stepTranslation[1])) // if difference is smaller than stepMovement in y axes, there is possibility for collision
    {
        float xDifference = stepTranslation[0]*(yDifference)/stepTranslation[1]; // compute xDifference from proportion
        float xNewPosition = xBall + xDifference;
        float yNewPosition = yBall + yDifference; //

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
    float leftBall = xBall - BALL_RADIUS;
    float xRightBall = xBall + BALL_RADIUS;
    float yBall = this->_ball->getModelMatrix()[3][1];
    float topBall = yBall + BALL_RADIUS;

    //first case top boundary
    if(stepTranslation[1] > 0.0f)
    {
        float yDifference = TOP_SCREEN_POSITION - topBall;

        if (std::abs(yDifference) <= std::abs(stepTranslation[1])) // if difference is smaller than stepMovement in y axes, there is possibility for collision
        {
            float xDifference = stepTranslation[0] * (yDifference) /
                                stepTranslation[1]; // compute xDifference from proportion
            float xNewPosition = xBall + xDifference;
            float yNewPosition = yBall + yDifference; //

            this->_ball->increaseVelocity();
            this->_ball->reverseY();
            this->_ball->setNewPosition(xNewPosition, yNewPosition);

            return true;
        }
    }

    //second case left boundary
    if(stepTranslation[0] < 0.0f)
    {
        float xDifference = LEFT_SCREEN_POSITION - leftBall; //compute distance between bottom part of Ball, and top part of Board

//        if(xDifference > stepTranslation[0]+0.01) // if difference is smaller than stepMovement in y axes, there is possibility for collision
        if(std::abs(xDifference) <= std::abs(stepTranslation[0])) // if difference is smaller than stepMovement in y axes, there is possibility for collision
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
    if(stepTranslation[0] > 0.0f)
    {
        float xDifference = RIGHT_SCREEN_POSITION - xRightBall; //compute distance between bottom part of Ball, and top part of Board

        if(std::abs(xDifference) <= std::abs(stepTranslation[0])) // if difference is smaller than stepMovement in y axes, there is possibility for collision
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


    return false;
}

//deprecated
bool GameScene::checkCollisionBallBrick(std::shared_ptr<ModelInterface> brickObject)
{
    SharedData::logInfo(LOG_GAME_SCENE_TAG, "checkCollisionBallBrick");
    glm::vec2 stepVector = this->_ball->getMovementVector();
    glm::mat4 ballModelMatrix = this->_ball->getModelMatrix();
    float leftBall = ballModelMatrix[3][0] - BALL_RADIUS;
    float rightBall = ballModelMatrix[3][0] + BALL_RADIUS;
    float topBall = ballModelMatrix[3][1] + BALL_RADIUS;
    float bottomBall = ballModelMatrix[3][1] - BALL_RADIUS;

    glm::mat4 brickMatrix = brickObject->getModelMatrix();
    float leftBrick = brickMatrix[3][0] - BRICK_WIDTH/2;
    float rightBrick = brickMatrix[3][0] + BRICK_WIDTH/2;
    float topBrick = brickMatrix[3][1] + BRICK_HEIGHT/2;
    float bottomBrick = brickMatrix[3][1] - BRICK_HEIGHT/2;

    if(stepVector[0] < 0.0f)
    {
        float rightDistance = leftBall - rightBrick; //xStep negative
        if(stepVector[1] < 0.0f)
        {
            //ball can hit right and top of the brick
            float topDistance = bottomBall - topBrick; //yStep negative

            float percentageRightDistance = 999.0f;
            if(stepVector[0] != 0.0f)
            {
                percentageRightDistance = std::abs(rightDistance/stepVector[0]);
            }
            float percentageTopDistance = 999.0f;
            if(stepVector[1] != 0.0f)
            {
                percentageTopDistance = std::abs(topDistance/stepVector[1]);
            }

            if(percentageRightDistance < percentageTopDistance)
            {
                if(std::abs(rightDistance) < std::abs(stepVector[0])) // if difference is smaller than stepMovement in y axes, there is possibility for collision
                {
                    float yDistance = stepVector[1] * (rightDistance) /
                                      stepVector[0]; // compute xDifference from proportion
                    float xNewPosition = ballModelMatrix[3][0] + rightDistance;
                    float yNewPosition = ballModelMatrix[3][1] + yDistance; //

                    this->_ball->increaseVelocity();
                    this->_ball->reverseX();
                    this->_ball->setNewPosition(xNewPosition, yNewPosition);

                    brickObject->setVisibility(false);

                    return true;
                }
            }
            else
            {
                if(std::abs(topDistance) < std::abs(stepVector[1]))
                {
                    float xDistance = stepVector[0] * (topDistance) /
                                      stepVector[1];
                    float xNewPosition = ballModelMatrix[3][0] + xDistance;
                    float yNewPosition = ballModelMatrix[3][1] + topDistance; //

                    this->_ball->increaseVelocity();
                    this->_ball->reverseY();
                    this->_ball->setNewPosition(xNewPosition, yNewPosition);

                    brickObject->setVisibility(false);

                    return true;
                }
            }
        }
        else
        {
            //ball can hit right and bottom of brick
            float bottomDistance = bottomBrick - topBall; //yStep positive

            float percentageRightDistance = 999.0f;
            if(stepVector[0] != 0.0f)
            {
                percentageRightDistance = std::abs(rightDistance/stepVector[0]);
            }

            float percentageBottomDistance = 999.0f;
            if(stepVector[1] != 0.0f)
            {
                percentageBottomDistance =  abs(bottomDistance/stepVector[1]);
            }

            if(percentageRightDistance < percentageBottomDistance)
            {
                if(std::abs(rightDistance) < std::abs(stepVector[0])) // if difference is smaller than stepMovement in y axes, there is possibility for collision
                {
                    float yDistance = stepVector[1] * (rightDistance) /
                                      stepVector[0]; // compute xDifference from proportion
                    float xNewPosition = ballModelMatrix[3][0] + rightDistance;
                    float yNewPosition = ballModelMatrix[3][1] + yDistance; //

                    this->_ball->increaseVelocity();
                    this->_ball->reverseX();
                    this->_ball->setNewPosition(xNewPosition, yNewPosition);

                    brickObject->setVisibility(false);

                    return true;
                }
            }
            else
            {
                if(std::abs(bottomDistance) < std::abs(stepVector[1]))
                {
                    float xDistance = stepVector[0] * (bottomDistance) /
                                      stepVector[1];
                    float xNewPosition = ballModelMatrix[3][0] + xDistance;
                    float yNewPosition = ballModelMatrix[3][1] + bottomDistance; //

                    std::string message = "xdistance = " + a2s<>(xDistance) + ", yDistance = " + a2s<>(bottomDistance);
                    SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

                    message = "xNewPosition = " + a2s<>(xNewPosition) + ", yNewPosition = " + a2s<>(yNewPosition);
                    SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

                    this->_ball->increaseVelocity();
                    this->_ball->reverseY();
                    this->_ball->setNewPosition(xNewPosition, yNewPosition);

                    brickObject->setVisibility(false);

                    return true;
                }
            }


        }
    }
    else
    {
        float leftDistance = leftBrick - rightBall; //xStep positive
        if(stepVector[1] < 0.0f)
        {
            //ball can hit left and top of the brick
            float topDistance = topBrick - bottomBall; //yStep negative

            float percentageLeftDistance = 999.0f;
            if(stepVector[0] != 0.0f)
            {
                percentageLeftDistance = std::abs(leftDistance/stepVector[0]);
            }
            float percentageTopDistance = 999.0f;
            if(stepVector[1] != 0.0f)
            {
                percentageTopDistance = std::abs(topDistance/stepVector[1]);
            }

            if(percentageLeftDistance < percentageTopDistance)
            {
                if(std::abs(leftDistance) < std::abs(stepVector[0])) // if difference is smaller than stepMovement in y axes, there is possibility for collision
                {
                    float yDistance = stepVector[1] * (leftDistance) /
                                      stepVector[0]; // compute xDifference from proportion
                    float xNewPosition = ballModelMatrix[3][0] + leftDistance;
                    float yNewPosition = ballModelMatrix[3][1] + yDistance; //

                    this->_ball->increaseVelocity();
                    this->_ball->reverseX();
                    this->_ball->setNewPosition(xNewPosition, yNewPosition);

                    brickObject->setVisibility(false);

                    return true;
                }
            }
            else
            {
                if(std::abs(topDistance) < std::abs(stepVector[1]))
                {
                    float xDistance = stepVector[0] * (topDistance) /
                                      stepVector[1];
                    float xNewPosition = ballModelMatrix[3][0] + xDistance;
                    float yNewPosition = ballModelMatrix[3][1] + topDistance; //

                    this->_ball->increaseVelocity();
                    this->_ball->reverseY();
                    this->_ball->setNewPosition(xNewPosition, yNewPosition);

                    brickObject->setVisibility(false);

                    return true;
                }
            }

        }
        else
        {
            //ball can hit left and bottom of brick
            float bottomDistance = bottomBrick - topBall; //yStep positive

            float percentageLeftDistance = 999.0f;
            if(stepVector[0] != 0.0f)
            {
                percentageLeftDistance = std::abs(leftDistance/stepVector[0]);
            }

            float percentageBottomDistance = 999.0f;
            if(stepVector[1] != 0.0f)
            {
                percentageBottomDistance =  abs(bottomDistance/stepVector[1]);
            }

            if(percentageLeftDistance < percentageBottomDistance)
            {
                if(std::abs(leftDistance) < std::abs(stepVector[0])) // if difference is smaller than stepMovement in y axes, there is possibility for collision
                {
                    float yDistance = stepVector[1] * (leftDistance) /
                                      stepVector[0]; // compute xDifference from proportion
                    float xNewPosition = ballModelMatrix[3][0] + leftDistance;
                    float yNewPosition = ballModelMatrix[3][1] + yDistance; //

                    this->_ball->increaseVelocity();
                    this->_ball->reverseX();
                    this->_ball->setNewPosition(xNewPosition, yNewPosition);

                    brickObject->setVisibility(false);

                    return true;
                }
            }
            else
            {
                if(std::abs(bottomDistance) < std::abs(stepVector[1]))
                {
                    float xDistance = stepVector[0] * (bottomDistance) /
                                      stepVector[1];
                    float xNewPosition = ballModelMatrix[3][0] + xDistance;
                    float yNewPosition = ballModelMatrix[3][1] + bottomDistance; //

                    this->_ball->increaseVelocity();
                    this->_ball->reverseY();
                    this->_ball->setNewPosition(xNewPosition, yNewPosition);

                    brickObject->setVisibility(false);

                    return true;
                }
            }
        }
    }

    return false;
}

bool GameScene::checkCollisionBallBricks(std::vector<std::shared_ptr<ModelInterface> > brickObjects)
{
//    SharedData::logInfo(LOG_GAME_SCENE_TAG, "checkCollisionBallBricks new");
    // variables data
    glm::mat4 ballModelMatrix = this->_ball->getModelMatrix();
    glm::vec2 stepMovementVector = this->_ball->getMovementVector();

    // possible Collision Sides
    collision possibleCollisionSides = this->findPossibleCollisionSides(stepMovementVector);

    //for each of bricks the distance of movementVector, which is traveled by ball before collision, needs to be find
    std::vector<float> distance;
    //for each of bricks the side of collision needs to be find
    std::vector<collision> collisionSide;
    //for each of bricks the status of collission needs to be find
    std::vector<bool> collisionStatus;

//    SharedData::logInfo(LOG_GAME_SCENE_TAG, "gethering information about bricks");
    for(uint i = 0; i < brickObjects.size(); i++)
    {
        std::pair<collision, float> result = findCollisionSideAndMovementDistance(possibleCollisionSides, stepMovementVector, ballModelMatrix, brickObjects.at(i));
        collisionSide.push_back(result.first);
        distance.push_back(result.second);
    }
//    SharedData::logInfo(LOG_GAME_SCENE_TAG, "after gethering information about bricks");

    //check bricks with which ball is colliding
    int brickHitAmount = 0;
    for(uint i = 0; i < brickObjects.size(); i++)
    {
        if(collisionSide.at(i) == COLLISION_RIGHT || collisionSide.at(i) == COLLISION_LEFT)
        {
            if(std::abs(distance.at(i)) < std::abs(stepMovementVector[0]))
            {
                collisionStatus.push_back(true);
                brickHitAmount++;
            }
            else
            {
                collisionStatus.push_back(false);
            }
        }
        else
        {
            if(std::abs(distance.at(i)) < std::abs(stepMovementVector[1]))
            {
                collisionStatus.push_back(true);
                brickHitAmount++;
            }
            else
            {
                collisionStatus.push_back(false);
            }
        }
    }

//    SharedData::logInfo(LOG_GAME_SCENE_TAG, "after gethering hit amount");

    std::string message = "HitBricks number = " + a2s<>(brickHitAmount);
    SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

    if(brickHitAmount == 1)
    {
        collision brickCollisionSide;
        float ballMovmentDistance;
        std::shared_ptr<ModelInterface> collidedBrick;
        for(uint i = 0; i < brickObjects.size(); i++)
        {
            if(collisionStatus.at(i))
            {
                brickCollisionSide = collisionSide.at(i);
                ballMovmentDistance = distance.at(i);
                collidedBrick = brickObjects.at(i);
                break;
            }
        }

        glm::mat4 brickModelMatrix = collidedBrick->getModelMatrix();
        message = "brickCenterPosition x = " +a2s<>(brickModelMatrix[3][0]) + ", y = " + a2s<>(brickModelMatrix[3][0]);
        SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

        bool result;
        result = this->manageBallAfterCollisionWithBrick(brickCollisionSide, ballMovmentDistance, collidedBrick, stepMovementVector, ballModelMatrix);
        return result;
    }

    if(brickHitAmount == 2)
    {
        std::vector<std::shared_ptr<ModelInterface> > collidedBricks; //don't need it
        std::vector<float> ballMovmentDistances;
        std::vector<collision> brickCollisionSides;

        for(uint i = 0; i < brickObjects.size(); i++)
        {
            if(collisionStatus.at(i))
            {
                brickCollisionSides.push_back(collisionSide.at(i));
                ballMovmentDistances.push_back(distance.at(i));
                std::shared_ptr<ModelInterface> brick = brickObjects.at(i);
                collidedBricks.push_back(brick);
            }
        }

        this->manageBallAfterCollisionWithBricks(brickCollisionSides, ballMovmentDistances, collidedBricks, stepMovementVector, ballModelMatrix);
        return true;
    }

    if(brickHitAmount > 2)
    {
        std::string message = "ball collide with " + a2s<int>(brickHitAmount) + "objects";
        SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
    }

    return false;
}


bool GameScene::manageBallAfterCollisionWithBricks(std::vector<collision> collisionSides, std::vector<float> distances, std::vector<std::shared_ptr<ModelInterface> > brickObjects, glm::vec2 stepMovementVector, glm::mat4 ballModelMatrix)
{
    enum reverseType{ReverseX, ReverseY, ReverseXY};

    SharedData::logInfo(LOG_GAME_SCENE_TAG, "manageBallAfterCollisionWith Bricks many");
    //Values are computed for one brick, the ball would have similar position anyway
    std::vector<float> xNewPositions;
    std::vector<float> yNewPositions;
    std::vector<reverseType> reverseTypeData;
    std::vector<bool> collisionStatuses;

    bool result = false;

    std::string message = "amount of recived blocks = " + a2s<uint>(brickObjects.size());
    SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

    for(uint i = 0; i < brickObjects.size(); i++)
    {
        glm::mat4 brickModelMatrix = brickObjects.at(i)->getModelMatrix();
        float topBrick = brickModelMatrix[3][1] + BRICK_HEIGHT/2;
        float rightBrick = brickModelMatrix[3][0] + BRICK_WIDTH/2;
        float bottomBrick = brickModelMatrix[3][1] - BRICK_HEIGHT/2;
        float leftBrick = brickModelMatrix[3][0] - BRICK_WIDTH/2;

        if(collisionSides.at(i) == COLLISION_LEFT || collisionSides.at(i) == COLLISION_RIGHT)
        {
            float otherDistance = distances.at(i) * stepMovementVector[1] / stepMovementVector[0];
            float xNewPosition = ballModelMatrix[3][0] + distances.at(i);
            xNewPositions.push_back(xNewPosition);
            float yNewPosition = ballModelMatrix[3][1] + otherDistance;
            yNewPositions.push_back(yNewPosition);
            reverseTypeData.push_back(ReverseX);
            if( yNewPosition >= bottomBrick && yNewPosition <= topBrick )
            {
                collisionStatuses.push_back(true);
                result = true;
            }
            else
            {
                collisionStatuses.push_back(false);
            }
        }
        else
        {
            float otherDistance = distances.at(i) * stepMovementVector[0] / stepMovementVector[1];
            float xNewPosition = ballModelMatrix[3][0] + otherDistance;
            xNewPositions.push_back(xNewPosition);
            float yNewPosition = ballModelMatrix[3][1] + distances.at(i);
            yNewPositions.push_back(yNewPosition);
            reverseTypeData.push_back(ReverseY);
            if( xNewPosition >= leftBrick && xNewPosition <= rightBrick )
            {
                collisionStatuses.push_back(true);
                result = true;
            }
            else
            {
                collisionStatuses.push_back(false);
            }
        }
    }

    int amountOfDestroyedBricks = 0;

    uint blockDestroyedIndex = 999;

    for(uint i = 0; i < collisionStatuses.size(); i++)
    {
        if(collisionStatuses.at(i))
        {
            amountOfDestroyedBricks++;
            brickObjects.at(i)->setVisibility(false);
            blockDestroyedIndex = i;
        }
    }

    {
        std::string message = "size of collisionStatutes = " + a2s<>(collisionStatuses.size());
        SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

        message = "amount of destroyed blocks = " + a2s<int>(amountOfDestroyedBricks);
        SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

        message = "result = " + a2s<>(result);
        SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());
    }

    if(result)
    {
        // first case two bricks destroyed
        if(amountOfDestroyedBricks > 1)
        {
            if(reverseTypeData.at(0) != reverseTypeData.at(1))
            {
                this->_ball->reverseXY();
            }
            else
            {
                if(reverseTypeData.at(0) == ReverseX)
                {
                    this->_ball->reverseX();
                }
                else
                {
                    this->_ball->reverseY();
                }
            }
            this->_playerScore = this->_playerScore + 40;
            this->_ball->increaseVelocity();
            this->_ball->setNewPosition(xNewPositions.at(0), yNewPositions.at(0));
        }
        else // second case one brick destroyed
        {
            if(reverseTypeData.at(blockDestroyedIndex) == ReverseX)
            {
                this->_ball->reverseX();
            }
            else
            {
                this->_ball->reverseY();
            }
            this->_playerScore = this->_playerScore + 10;
            this->_ball->increaseVelocity();
            this->_ball->setNewPosition(xNewPositions.at(blockDestroyedIndex), yNewPositions.at(blockDestroyedIndex));
        }
    }

    return result;
}

bool GameScene::manageBallAfterCollisionWithBrick(collision collisionSide, float distance, std::shared_ptr<ModelInterface> brickObject, glm::vec2 stepMovementVector, glm::mat4 ballModelMatrix)
{
    SharedData::logInfo(LOG_GAME_SCENE_TAG, "manageBallAfterCollisionWith Brick");

    std::string message = "distance = " +a2s<>(distance);
    SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

    message = "stepMovement x = " +a2s<>(stepMovementVector[0]) + ", y = " + a2s<>(stepMovementVector[1]);
    SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

    message = "bellCenterPosition x = " +a2s<>(ballModelMatrix[3][0]) + ", y = " + a2s<>(ballModelMatrix[3][0]);
    SharedData::logInfo(LOG_GAME_SCENE_TAG, message.c_str());

    glm::mat4 brickModelMatrix = brickObject->getModelMatrix();
    float topBrick = brickModelMatrix[3][1] + BRICK_HEIGHT/2;
    float rightBrick = brickModelMatrix[3][0] + BRICK_WIDTH/2;
    float bottomBrick = brickModelMatrix[3][1] - BRICK_HEIGHT/2;
    float leftBrick = brickModelMatrix[3][0] - BRICK_WIDTH/2;

    float otherDistance;
    float xNewPosition;
    float yNewPosition;

    bool result = false;

    if(collisionSide == COLLISION_LEFT || collisionSide == COLLISION_RIGHT)
    {
        otherDistance = distance * stepMovementVector[1] / stepMovementVector[0];
        xNewPosition = ballModelMatrix[3][0] + distance;
        yNewPosition = ballModelMatrix[3][1] + otherDistance;
        if( yNewPosition >= bottomBrick && yNewPosition <= topBrick )
        {
            this->_ball->reverseX();
            result = true;
        }
    }
    else
    {
        otherDistance = distance * stepMovementVector[0] / stepMovementVector[1];
        xNewPosition = ballModelMatrix[3][0] + otherDistance;
        yNewPosition = ballModelMatrix[3][1] + distance;
        if( xNewPosition >= leftBrick && xNewPosition <= rightBrick )
        {
            this->_ball->reverseY();
            result = true;
        }
    }

    if(result)
    {
        this->_ball->increaseVelocity();
        this->_ball->setNewPosition(xNewPosition, yNewPosition);
        this->_playerScore = this->_playerScore + 10;
        brickObject->setVisibility(false);
    }

    return result;
}

collision GameScene::findPossibleCollisionSides(glm::vec2 stepMovementVector)
{
    if(stepMovementVector[0] < 0.0f)
    {
        if(stepMovementVector[1] < 0.0f)
        {
            return COLLISION_TOP_RIGHT;
        }
        else
        {
            return COLLISION_BOTTOM_RIGHT;
        }
    }
    else
    {
        if(stepMovementVector[1] < 0.0f)
        {
            return COLLISION_TOP_LEFT;
        }
        else
        {
            return COLLISION_BOTTOM_LEFT;
        }
    }
}


std::pair<float, float> GameScene::computePercentageDistance(float fromPosition, float toPosition, float stepValue)
{
    std::pair<float, float> result;
    float percentageDistance = 999.0f;
    if(stepValue != 0.0f)
    {
        float distance = fromPosition - toPosition; //xStep negative
        percentageDistance = std::abs(distance/stepValue);
        result = std::pair<float, float>(distance, percentageDistance);
    }
    return result;
}

std::pair<collision, float>  GameScene::findCollisionSideAndMovementDistance(collision posibleCollisionSides, glm::vec2 stepMovementVector, glm::mat4 ballModelMatrixData, std::shared_ptr<ModelInterface> brickObject)
{
    float leftBall = ballModelMatrixData[3][0] - BALL_RADIUS;
    float rightBall = ballModelMatrixData[3][0] + BALL_RADIUS;
    float topBall = ballModelMatrixData[3][1] + BALL_RADIUS;
    float bottomBall = ballModelMatrixData[3][1] - BALL_RADIUS;

    glm::mat4 brickMatrix = brickObject->getModelMatrix();
    float leftBrick = brickMatrix[3][0] - BRICK_WIDTH/2;
    float rightBrick = brickMatrix[3][0] + BRICK_WIDTH/2;
    float topBrick = brickMatrix[3][1] + BRICK_HEIGHT/2;
    float bottomBrick = brickMatrix[3][1] - BRICK_HEIGHT/2;

    std::pair<float, float> percentageRightDistance = this->computePercentageDistance(leftBall, rightBrick, stepMovementVector[0]);
    std::pair<float, float> percentageBottomDistance = this->computePercentageDistance(bottomBrick, topBall, stepMovementVector[1]);
    std::pair<float, float> percentageLeftDistance = this->computePercentageDistance(leftBrick, rightBall, stepMovementVector[0]);
    std::pair<float, float> percentageTopDistance = this->computePercentageDistance(topBrick, bottomBall, stepMovementVector[1]);

    std::pair<collision, float> result;

    //first case COLLISION_BOTTOM_RIGHT
    if(posibleCollisionSides == COLLISION_BOTTOM_RIGHT)
    {
        if(percentageBottomDistance.second < percentageRightDistance.second)
        {
            result = std::pair<collision, float>(COLLISION_BOTTOM, percentageBottomDistance.first);
        }
        else
        {
            result = std::pair<collision, float>(COLLISION_RIGHT, percentageRightDistance.first);
        }
    }

    //second case COLLISION_BOTTOM_LEFT
    if(posibleCollisionSides == COLLISION_BOTTOM_LEFT)
    {
        if(percentageBottomDistance.second < percentageLeftDistance.second)
        {
            result = std::pair<collision, float>(COLLISION_BOTTOM, percentageBottomDistance.first);
        }
        else
        {
            result = std::pair<collision, float>(COLLISION_LEFT, percentageLeftDistance.first);
        }
    }

    //third case COLLISION_TOP_LEFT
    if(posibleCollisionSides == COLLISION_TOP_LEFT)
    {
        if(percentageTopDistance.second < percentageLeftDistance.second)
        {
            result = std::pair<collision, float>(COLLISION_TOP, percentageTopDistance.first);
        }
        else
        {
            result = std::pair<collision, float>(COLLISION_LEFT, percentageLeftDistance.first);
        }
    }

    //fourth case COLLISION_TOP_RIGHT
    if(posibleCollisionSides == COLLISION_TOP_RIGHT)
    {
        if(percentageTopDistance.second < percentageRightDistance.second)
        {
            result = std::pair<collision, float>(COLLISION_TOP, percentageTopDistance.first);
        }
        else
        {
            result = std::pair<collision, float>(COLLISION_RIGHT, percentageRightDistance.first);
        }
    }

    return result;
}

