#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

const float MIN_X = 240.0f; // Límite inferior de la posición X
const float MAX_X = 440.0f; // Límite superior de la posición X
const float VELOCIDAD_OBSTACULO_Y = 0.2f; // Velocidad de los obstáculos

class Obstaculo
{
public:
    Obstaculo(const std::string &textureFile, sf::Vector2f position)
    {
        if (!texture.loadFromFile(textureFile))
        {
            std::cerr << "Error al cargar la textura del obstáculo." << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setPosition(position);
    }

    void mover(float velocidadY)
    {
        sprite.move(0, velocidadY); // Solo se mueve hacia abajo
    }

    void draw(sf::RenderWindow &window) const
    {
        window.draw(sprite);
    }

    const sf::Sprite &getSprite() const
    {
        return sprite;
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;
};