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

    // Setters voor drag & drop
    void setX(float newX) { x = newX; }
    void setY(float newY) { y = newY; }
    void setVX(float newVX) { vx = newVX; }
    void setVY(float newVY) { vy = newVY; }

    // Forces
    virtual void applyForces(float dt); // polymorfisme

    // Integratie
    void integrate(float dt, float windowWidth, float windowHeight);

    virtual ~Body() = default; // altijd virtuele destructor voor polymorfisme
};

#endif
