#pragma once

#include <iostream>

class Vidas
{
public:
    Vidas(int vidasIniciales) : vidas(vidasIniciales) {}

    bool restarVida()
    {
        if (vidas > 0)
        {
            vidas--;
            if (vidas == 0)
            {
                std::cout << "Juego reiniciado. Se acabaron las vidas." << std::endl;
                return true; // Indica que todas las vidas se han perdido
            }
        }
        return false;
    }

    int obtenerVidas() const
    {
        return vidas;
    }

private:
    int vidas;
};