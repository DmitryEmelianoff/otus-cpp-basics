#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
public:
    Ball(const Point& ce, const Velocity& v, const Color& co, double r, bool iscol);
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    bool ballIsCollidable() const;
private:
    Point center;
    Velocity velocity;
    const Color color;
    const double radius;
    const bool isCollidable;
};
