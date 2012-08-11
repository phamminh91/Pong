#include <allegro5/allegro_primitives.h>
#include "ball.h"

Ball::Ball(float inX, float inY, float inRadius)
{
    pos = new Vector2D(inX, inY);
    vel = new Vector2D(-1, 1);
    acc = new Vector2D(0, 0);
    radius = inRadius;
}

Ball::~Ball()
{
    delete pos;
    delete vel;
    delete acc;
}

Vector2D& Ball::getPos() const
{
    return *pos;
}

Vector2D& Ball::getVel() const
{
    return *vel;
}

Vector2D& Ball::getAcc() const
{
    return *acc;
}

float Ball::getRadius() const
{
    return radius;
}

void Ball::hReflect()
{
    vel->x *= -1;
}

void Ball::vReflect()
{
    vel->y *= -1;
}

void Ball::update(float inTime)
{
    pos->x += inTime * vel->x; 
    pos->y += inTime * vel->y; 
}

void Ball::render()
{
    al_draw_filled_circle(pos->x, pos->y, radius, al_map_rgb(255, 255, 255));
}
