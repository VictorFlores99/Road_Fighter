#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Fondo
{
private:
    sf::Texture backgroundTexture;  // La textura es ahora un miembro de la clase
    sf::Sprite backgroundSprite;

public:
    Fondo()
    {
        // Cargar el fondo
        if (!backgroundTexture.loadFromFile("C:/Users/Departamento/Pictures/escenario.png"))
        {
            std::cerr << "Error al cargar la textura del fondo." << std::endl;
            throw "Error al cargar imagen";
        }
        backgroundSprite.setTexture(backgroundTexture); // Asociar la textura al sprite
    }

    ~Fondo() {}

    void draw(sf::RenderWindow& window) {
        window.draw(backgroundSprite); // Dibujar el fondo
    }
};

