#pragma once

#include "Personaje.hpp"

class PersonajeAuto : public Personaje {
public:
    using Personaje::Personaje; // Hereda constructor
    void update(float elapsedTime, float startY, float duration);
};