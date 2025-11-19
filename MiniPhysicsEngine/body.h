#ifndef BODY_H
#define BODY_H

class Body {
protected:
    float mass;
    float x, y;    // positie
    float vx, vy;  // snelheid
    float ax, ay;  // versnelling

public:
    Body(float x, float y, float mass);

    // Getters
    float getX() const;
    float getY() const;
    float getVX() const;
    float getVY() const;
    float getMass() const;

    // Forces
    virtual void applyForces(float dt); // polymorfisme

    // Integratie
    void integrate(float dt);

    virtual ~Body() = default; // altijd virtuele destructor voor polymorfisme
};

#endif
