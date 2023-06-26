#pragma once

#include "DxLib.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int CHARACTER_SPEED = 5;  // �v���C���[�̈ړ����x
const int CHARACTER_SIZE = 32;  // �v���C���[�̃T�C�Y
const int ENEMY_SPEED = 3;      // �G�̗������x
const int ENEMY_SIZE = 32;      // �G�̃T�C�Y

class Player
{
public:
    Player(int x, int y);
    void Update();
    void Draw();
    int GetX() const;
    int GetY() const;
    int GetWidth() const;
    int GetHeight() const;
    bool CheckPlayerCollision(int x, int y, int w,int h,int ex,int ey,int ew,int eh);

//private:
    int x_;
    int y_;
};

class Enemy
{
public:
    Enemy(int x, int y);
    void Update();
    void Draw();
    int GetX() const;
    int GetY() const;
    int GetWidth() const;
    int GetHeight() const;
    bool CheckEnemyCollision(const Enemy& enemy) const;

//private:
    int x_;
    int y_;
};

int GameMain();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);

