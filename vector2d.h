#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
    public:
        Vector2D(float inX, float inY);
        ~Vector2D();

        void sub(Vector2D inVector2D);
        void add(Vector2D inVector2D);
        void multiply(float inFactor);
        void copy(Vector2D inVector2D);

        float x;
        float y;
};

#endif
