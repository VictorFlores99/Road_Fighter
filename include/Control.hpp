#pragma once

#include <SFML/Graphics.hpp>
#include "Personaje.hpp" 

class Control
{
public:
    Control(float velocidad) : velocidad(velocidad) {}

    void manejarEntrada(Personaje &jugador)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            jugador.move(-velocidad, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            jugador.move(velocidad, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            jugador.move(0, -velocidad);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            jugador.move(0, velocidad);
        }
    }

private:
    float velocidad;
};