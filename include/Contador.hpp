#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

// Clase para manejar el contador de tiempo
class Contador
{
public:
    Contador(float tiempoLimite) : tiempoLimite(tiempoLimite), reloj() {}

    float tiempoRestante() const
    {
        return tiempoLimite - reloj.getElapsedTime().asSeconds();
    }

    bool tiempoAgotado() const
    {
        return tiempoRestante() <= 0;
    }

    void reiniciar()
    {
        reloj.restart();
    }

private:
    float tiempoLimite;
    sf::Clock reloj;
};