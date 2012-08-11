#ifndef BAR_H
#define BAR_H

#include "vector2d.h"

class Bar
{
    public:
        Bar(float inX, float inY, float inWidth, float inHeight);
        ~Bar();

        Vector2D& getPos() const;
        Vector2D& getVel() const;
        Vector2D& getAcc() const;
        float getWidth() const;
        float getHeight() const;

        void moveUp();
        void moveDown();
        void stop();

        void render();

    private:
        Vector2D *pos;
        Vector2D *vel;
        Vector2D *acc;
        float width;
        float height;
};

#endif
