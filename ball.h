#ifndef BALL_H
#define BALL_H

#include "vector2d.h"

class Ball
{
    public:
        Ball(float inX, float inY, float inRadius);
        ~Ball();
        
        Vector2D& getPos() const;
        Vector2D& getVel() const;
        Vector2D& getAcc() const;
        float getRadius() const;

        void hReflect();
        void vReflect();
        
        void update(float inTime);

        void render();
        
    private:
        Vector2D* pos;
        Vector2D* vel;
        Vector2D* acc;
        float radius;
};

#endif
