#pragma once
#include <math.h>
class Players
{
public:
    float x;
    float y;
    float z;

    Players(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    Players()
    {
    }

    float length()
    {
        return (float)sqrt(x * x + y * y + z * z);
    }

    float dotproduct(Players dot)
    {
        return (x * dot.x + y * dot.y + z * dot.z);
    }

};

struct Colors
{
public:
    short R;
    short G;
    short B;

    Colors()
    {

    }
    Colors(short r, short g, short b)
    {
        R = r;
        G = g;
        B = b;
    }

};

class PlayerDataVec
{
public:
    float xMouse;
    float yMouse;
    int isValid;
    float xPos;
    float yPos;
    float zPos;
    int isAlive;
    int clientNum;
    Colors color;
    char name[16];
    int pose;
    int team;
    bool visible;
    int isInGame;
    int health;

    Players VecCoords()
    {
        Players vec(xPos, zPos, yPos);
        return vec;
    }
};
