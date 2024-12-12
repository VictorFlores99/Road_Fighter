#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

double velocidad = 0.1; // Velocidad del jugador

class Personaje
{
public:
    Personaje(const std::string &textureFile, sf::Vector2f position)
    {
        if (!texture.loadFromFile(textureFile))
        {
            std::cerr << "Error al cargar la textura del personaje." << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setPosition(position);
    }

    void move(float offsetX, float offsetY)
    {
        sprite.move(offsetX, offsetY);
    }

    void setPosition(float x, float y)
    {
        sprite.setPosition(x, y);
    }

    void draw(sf::RenderWindow &window)
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