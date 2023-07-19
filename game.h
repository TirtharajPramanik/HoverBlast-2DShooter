#pragma once
#include <raylib.h>

const char windowTitle[] = "Dungeon Fighter";
const int windowWidth = 740, windowHeight = 820;
const int railWidth = windowHeight - windowWidth;
const int gameWidth = windowWidth, gameHeight = (windowHeight - railWidth) / 2;

typedef struct Ship
{
    float xPos, yPos, width, height, accel, maxSpeed, xSpeed, ySpeed;
    bool isEnemy;
    Texture2D texture;
} Ship;

void initShip(Ship *ship, float xPos, float yPos, bool isEnemy, Texture2D *texture)
{
    ship->isEnemy = isEnemy;
    ship->texture = *texture;
    ship->width = texture->width;
    ship->height = texture->height;
    ship->xPos = xPos;
    ship->yPos = isEnemy ? yPos : yPos - ship->height;
    ship->accel = 30;
    ship->maxSpeed = 300;
    ship->xSpeed = 0;
    ship->ySpeed = 0;
}

void drawShip(Ship *ship)
{
    DrawTexturePro(ship->texture, (Rectangle){0, 0, ship->texture.width, ship->texture.height},
                   (Rectangle){ship->xPos, ship->yPos, ship->width, ship->height},
                   ship->isEnemy ? (Vector2){ship->width, ship->height} : (Vector2){0, 0},
                   ship->isEnemy ? 180 : 0, WHITE);
}

static void accelerate(int a, int b, float *speed, Ship *ship)
{
    if (IsKeyDown(a))
    {
        if (*speed > -ship->maxSpeed)
        {
            *speed -= ship->accel;
            if (*speed < -ship->maxSpeed)
                *speed = -ship->maxSpeed;
        }
    }
    else if (IsKeyDown(b))
    {
        if (*speed < ship->maxSpeed)
        {
            *speed += ship->accel;
            if (*speed > ship->maxSpeed)
                *speed = ship->maxSpeed;
        }
    }
    else if (*speed < 0)
    {
        *speed += ship->accel;
        if (*speed > 0)
            *speed = 0;
    }
    else if (*speed > 0)
    {
        *speed -= ship->accel;
        if (*speed < 0)
            *speed = 0;
    }
}

void moveShip(Ship *ship)
{
    int *moves = (ship->isEnemy) ? (int[]){KEY_RIGHT, KEY_LEFT, KEY_DOWN, KEY_UP} : (int[]){KEY_A, KEY_D, KEY_W, KEY_S};

    accelerate(moves[0], moves[1], &(ship->xSpeed), ship);
    accelerate(moves[2], moves[3], &ship->ySpeed, ship);

    float frameDelta = GetFrameTime();
    ship->xPos += ship->xSpeed * frameDelta;
    ship->yPos += ship->ySpeed * frameDelta;

    if (ship->xPos < 0)
        ship->xPos = 0;
    else if (ship->xPos > gameWidth - ship->width)
        ship->xPos = gameWidth - ship->width;

    if (ship->isEnemy)
    {
        if (ship->yPos < 0)
            ship->yPos = 0;
        else if (ship->yPos > gameHeight - ship->height)
            ship->yPos = gameHeight - ship->height;
    }
    else
    {
        if (ship->yPos < gameHeight + railWidth)
            ship->yPos = gameHeight + railWidth;
        else if (ship->yPos > windowHeight - ship->height)
            ship->yPos = windowHeight - ship->height;
    }
}

typedef struct Train
{
    Texture2D engineTexture, healCabinTexture, bombCabinTexture, ammoCabinTexture, healthCabinTexture;
    float xPos, yPos, cabinWidth, height;
} Train;

void initTrain(Train *train, float xPos, float yPos, Texture2D *engineTexture, Texture2D *bombCabinTexture, Texture2D *ammoCabinTexture, Texture2D *healthCabinTexture)
{
    train->engineTexture = *engineTexture;
    train->ammoCabinTexture = *ammoCabinTexture;
    train->bombCabinTexture = *bombCabinTexture;
    train->healthCabinTexture = *healthCabinTexture;
    train->height = railWidth;
    train->cabinWidth = engineTexture->width / engineTexture->height * railWidth;
    train->xPos = xPos - train->cabinWidth;
    train->yPos = yPos;
}

void drawTrain(Train *train)
{
    DrawTexturePro(train->engineTexture, (Rectangle){0, 0, train->engineTexture.width, train->engineTexture.height},
                   (Rectangle){train->xPos, train->yPos, train->cabinWidth, train->height}, (Vector2){0, 0}, 0, WHITE);
    DrawTexturePro(train->bombCabinTexture, (Rectangle){0, 0, train->bombCabinTexture.width, train->bombCabinTexture.height},
                   (Rectangle){train->xPos + train->cabinWidth, train->yPos, train->cabinWidth, train->height}, (Vector2){0, 0}, 0, WHITE);
    DrawTexturePro(train->ammoCabinTexture, (Rectangle){0, 0, train->ammoCabinTexture.width, train->ammoCabinTexture.height},
                   (Rectangle){train->xPos + train->cabinWidth * 2, train->yPos, train->cabinWidth, train->height}, (Vector2){0, 0}, 0, WHITE);
    DrawTexturePro(train->healthCabinTexture, (Rectangle){0, 0, train->healthCabinTexture.width, train->healthCabinTexture.height},
                   (Rectangle){train->xPos + train->cabinWidth * 3, train->yPos, train->cabinWidth, train->height}, (Vector2){0, 0}, 0, WHITE);
}