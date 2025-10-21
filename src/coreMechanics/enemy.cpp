//
// Created by vanget on 10/20/2025.
//

#include <iostream>

#include "enemy.h"

#include "player.h"
#include "playerCamera.h"
using namespace std;

Enemy::Enemy(float x, float y, float w, float h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

void Enemy::setX(float x_pos) {
    x = x_pos;
}

void Enemy::setY(float y_pos) {
    y = y_pos;
}

float Enemy::getX() const {
    return x;
}

float Enemy::getY() const {
    return y;
}

void Enemy::setWidth(float width) {
    w = width;
}

void Enemy::setHeight(float height) {
    h = height;
}

float Enemy::getWidth() {
    return w;
}

float Enemy::getHeight() {
    return h;
}

void Enemy::update(float delta_time, float playerX, float playerY, PlayerCamera& pc) {
    updateMovement(delta_time, playerX, playerY, pc);
}

void Enemy::updateMovement(float delta_time, float playerX, float playerY, PlayerCamera& pc) {
    vx = 0;
    vy = 0;

    rect = {x - pc.camRect.x - w/2, y - pc.camRect.y - h/2, w, h};

    float angle = atan2(playerY - (y), playerX - (x));
    vx = cos(angle);
    vy = sin(angle);

    float distance = sqrt(pow(playerX - x, 2) + pow(playerY - y, 2));
    cout<<distance<<endl;
    if (distance >= 40) {
        x += vx * speed * delta_time;
        y += vy * speed * delta_time;
    }
}

void Enemy::drawEnemy(PlayerCamera& pc) const {
    DrawRectangle(x - pc.camRect.x - w/2, y - pc.camRect.y - h/2, w, h, MAROON);
    DrawBoundingBox({{x - pc.camRect.x - w/2, y - pc.camRect.y - h/2,0}, {x - pc.camRect.x + w/2, y - pc.camRect.y + h/2, 0}}, BLUE);
}

Rectangle Enemy::getRect() const {
    return rect;
}













