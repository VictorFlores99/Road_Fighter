#pragma once
#include <SFML/Graphics.hpp>

class Control
{
private:
    sf::Keyboard::Key mover_arriba;
    sf::Keyboard::Key mover_abajo;
    sf::Keyboard::Key mover_izquierda;
    sf::Keyboard::Key mover_derecha;

public:
    Control(){}
    Control(
        sf::Keyboard::Key arriba,
        sf::Keyboard::Key abajo, 
        sf::Keyboard::Key izquierda, 
        sf::Keyboard::Key derecha)
    {
        this->mover_arriba = arriba;
        this->mover_abajo = abajo;
        this->mover_izquierda = izquierda;
        this->mover_derecha = derecha;
    } 
    ~Control() {}

    sf::Keyboard::Key BotonArriba()
    {
        return this->mover_arriba;
    }
    sf::Keyboard::Key BotonAbajo()
    {
        return this->mover_abajo;
    }
    sf::Keyboard::Key BotonIzquierda()
    {
        return this->mover_izquierda;
    }
    sf::Keyboard::Key BotonDerecha()
    {
        return this->mover_derecha;
    }
};