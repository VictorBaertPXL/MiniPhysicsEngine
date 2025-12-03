#ifndef BODY_H
#define BODY_H

// vraag 3: correct class
// vraag 4: correct abstraction
// vraag 5: correct encapsulation
// vraag 8: correct base class
// vraag 11: correct virtual function
class Body {
protected:
    float mass;
    float x, y;    // positie (Box: linkeronderhoek; Circle: centrum)
    float vx, vy;  // snelheid
    float ax, ay;  // versnelling

    // fysische eigenschappen
    float restitution; // bounciness (0..1)
    float friction;    // simpele coulomb/approx

public:
    Body(float x, float y, float mass);

    // Getters
    float getX() const;
    float getY() const;
    float getVX() const;
    float getVY() const;
    float getMass() const;

    // Setters (voor drag & drop en collision response)
    void setX(float newX);
    void setY(float newY);
    void setVX(float newVX);
    void setVY(float newVY);

    float getRestitution() const;
    float getFriction() const;
    void setRestitution(float r);
    void setFriction(float f);

    // Forces
    virtual void applyForces(float dt); // polymorfisme

    // Integratie
    void integrate(float dt, float windowWidth, float windowHeight);

    virtual ~Body() = default; // altijd virtuele destructor voor polymorfisme
};

#endif
