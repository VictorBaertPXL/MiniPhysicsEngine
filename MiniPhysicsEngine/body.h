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

    // Setter voor positie (voor drag & drop)
    void setPosition(float newX, float newY) { x = newX; y = newY; }

    //Setters voor snelheid
    void setVelocity(float newVX, float newVY) { vx = newVX; vy = newVY; }



    virtual void applyForces(float dt); // polymorfisme


    void integrate(float dt);

    virtual ~Body() = default; // altijd virtuele destructor voor polymorfisme
};

#endif
