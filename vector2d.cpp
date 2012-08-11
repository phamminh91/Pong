#include "vector2d.h"

Vector2D::Vector2D(float inX, float inY)
{
    x = inX;
    y = inY;
}

Vector2D::~Vector2D()
{
}

void Vector2D::sub(Vector2D inVector2D)
{
    x -= inVector2D.x;
    y -= inVector2D.y;
}

void Vector2D::add(Vector2D inVector2D)
{
    x += inVector2D.x;
    y += inVector2D.y;
}

void Vector2D::multiply(float inFactor)
{
    x *= inFactor;
    y *= inFactor;
}

void Vector2D::copy(Vector2D inVector2D)
{
    x = inVector2D.x;
    y = inVector2D.y;
}
