#ifndef BODY_H
#define BODY_H

#include <string>

class Body {
protected:
    float x, y;
    float vx, vy;
    float ax, ay;
    float mass;

    bool isStatic;
    bool isCollidable;

    std::string name;

public:
    Body(float x, float y, float mass);
    Body(const Body& other);
    virtual ~Body();

    float getX() const;
    float getY() const;
    float getVX() const;
    float getVY() const;
    float getMass() const;

    bool getIsStatic() const;
    bool getIsCollidable() const;

    void setIsStatic(bool v);
    void setIsCollidable(bool v);

    void setX(float v);
    void setY(float v);
    void setVX(float v);
    void setVY(float v);

    void setName(const std::string& n);
    const std::string& getName() const;

    virtual void applyForces(float dt = 1.0f) = 0;

    void integrate(float dt, float windowWidth, float windowHeight);
};

#endif // BODY_H
