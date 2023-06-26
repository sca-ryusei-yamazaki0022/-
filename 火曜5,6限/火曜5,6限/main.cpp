#include "main.h"

Player::Player(int x, int y)
    : x_(x), y_(y)
{
}

void Player::Update()
{
    if (CheckHitKey(KEY_INPUT_LEFT) && x_ > 0)
    {
        x_ -= CHARACTER_SPEED;
    }
    if (CheckHitKey(KEY_INPUT_RIGHT) && x_ < SCREEN_WIDTH - CHARACTER_SIZE)
    {
        x_ += CHARACTER_SPEED;
    }
}

void Player::Draw()
{
    DrawBox(x_, y_, x_ + CHARACTER_SIZE, y_ + CHARACTER_SIZE, GetColor(255, 255, 255), TRUE);
}

int Player::GetX() const
{
    return x_;
}

int Player::GetY() const
{
    return y_;
}

int Player::GetWidth() const
{
    return CHARACTER_SIZE;
}

int Player::GetHeight() const
{
    return CHARACTER_SIZE;
}

bool Player::CheckPlayerCollision(int x,int y,int w,int h,int ex,int ey,int ew,int eh)
{
    if (x<ex + ew && x_ + w > ex && y < ey + eh && y + h > ey)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Enemy::Enemy(int x, int y)
    : x_(x), y_(y)
{
}

void Enemy::Update()
{
    y_ += ENEMY_SPEED;
    if (y_ > SCREEN_HEIGHT)
    {
        y_ = -GetRand(200);
        x_ = GetRand(SCREEN_WIDTH - GetWidth());
    }
}

void Enemy::Draw()
{
    DrawBox(x_, y_, x_ + ENEMY_SIZE, y_ + ENEMY_SIZE, GetColor(255, 0, 0), TRUE);
}

int Enemy::GetX() const
{
    return x_;
}

int Enemy::GetY() const
{
    return y_;
}

int Enemy::GetWidth() const
{
    return ENEMY_SIZE;
}

int Enemy::GetHeight() const
{
    return ENEMY_SIZE;
}

bool Enemy::CheckEnemyCollision(const Enemy& enemy) const
{
    return (x_ < enemy.GetX() + enemy.GetWidth() &&
        x_ + GetWidth() > enemy.GetX() &&
        y_ < enemy.GetY() + enemy.GetHeight() &&
        y_ + GetHeight() > enemy.GetY());
}


int GameMain()
{
    int playerX = SCREEN_WIDTH / 2;
    int playerY = SCREEN_HEIGHT - CHARACTER_SIZE;
    int enemyX = GetRand(SCREEN_WIDTH - ENEMY_SIZE);
    int enemyY = -ENEMY_SIZE;

    Player player(playerX, playerY);
    Enemy enemy(enemyX, enemyY);

    if (DxLib_Init() == -1)
    {
        return -1;
    }

    while (true)
    {
        if (ProcessMessage() != 0 || CheckHitKey(KEY_INPUT_ESCAPE) != 0)
        {
            break;
        }

        player.Update();
        enemy.Update();

        if (player.CheckPlayerCollision(player.x_,player.y_,player.GetWidth(),player.GetHeight(),enemy.x_,enemy.y_,enemy.GetWidth(),enemy.GetHeight()))
        {
            break;
        }

        ClearDrawScreen();

        player.Draw();
        enemy.Draw();

        ScreenFlip();
    }

    DxLib_End();

    return 0;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    SetMainWindowText("Avoid the Enemy Game");
    ChangeWindowMode(TRUE);

    if (DxLib_Init() == -1)
    {
        return -1;
    }

    SetDrawScreen(DX_SCREEN_BACK);

    GameMain();

    DxLib_End();

    return 0;
}
