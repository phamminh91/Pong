#include <allegro5/allegro_primitives.h>
#include "bar.h"

Bar::Bar(float inX, float inY, float inWidth, float inHeight)
{
    pos = new Vector2D(inX, inY);
    vel = new Vector2D(0, 2);
    acc = new Vector2D(0, 1);
    width = inWidth;
    height = inHeight;
}
Bar::~Bar()
{
    delete pos;
    delete vel;
    delete acc;
}

Vector2D& Bar::getPos() const
{
    return *pos;
}

Vector2D& Bar::getVel() const
{
    return *vel;
}

Vector2D& Bar::getAcc() const
{
    return *acc;
}

float Bar::getWidth() const
{
    return width;
}

float Bar::getHeight() const
{
    return height;
}

void Bar::moveUp()
{
    pos->add(*vel);
}

void Bar::moveDown()
{
    pos->sub(*vel);
}

void Bar::stop()
{
    vel->x = 0;
    vel->y = 0;
}

void Bar::render()
{
    al_draw_filled_rectangle(pos->x, pos->y, pos->x + width, pos->y + height, al_map_rgb(255, 255, 255));
}
