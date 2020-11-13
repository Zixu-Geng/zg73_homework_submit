//
//  Mover.cpp
//  zg73_week03class05_interstellar
//
//  Created by Bob G on 2020/11/13.
//

#include "Mover.hpp"

Mover::Mover()
{
    pos = glm::vec2(0,0);
    vel = glm::vec2(0,0);
    acc = glm::vec2(0,0);
}

Mover::Mover(glm::vec2 _pos, glm::vec2 _vel, float _mass)
{
    pos = _pos;
    vel = _vel;
    mass = _mass;
}

void Mover::addForce(glm::vec2 force)
{
    acc += force / mass;
}

void Mover::addDampingForce(float strength)
{
    float length = glm::length(vel);
    if (length != 0){                       // prevent illegally dividing by zero if vel is 0
        acc -= vel / length * strength;     // drag
    }
}

void Mover::update()
{
    vel += acc;
    pos += vel;
    acc *= 0;
}

void Mover::draw()
{
    ofPushStyle();
    float hue = ofMap(mass, 0, 10, 0, 255);
    ofSetColor(ofColor::fromHsb(hue,255,255));
    ofDrawCircle(pos, mass * 2.);
    ofPopStyle();
}

