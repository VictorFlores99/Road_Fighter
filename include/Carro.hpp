#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Control.hpp>

class Carro {
public:
    Carro(sf::Vector2f position, Control control) {
        this->control = control;
        
        const std::string& textureFile = "C:/Users/Departamento/Pictures/personaje.png";
        
        if (!texture.loadFromFile(textureFile)) {
            std::cerr << "Error al cargar la textura del personaje." << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setPosition(position);
    }

    void move(float offsetX, float offsetY) {
        sprite.move(offsetX, offsetY);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    void actualizar(){
        if (sf::Keyboard::isKeyPressed(control.BotonIzquierda())) {
            this->move(velocidad * -1, 0);
        }
        if (sf::Keyboard::isKeyPressed(control.BotonDerecha())) {
            this->move(velocidad, 0);
        }
        if (sf::Keyboard::isKeyPressed(control.BotonArriba())) {
            this->move(0, velocidad * -1);
        }
        if (sf::Keyboard::isKeyPressed(control.BotonAbajo())) {
            this->move(0, velocidad);
        }
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;
    double velocidad = 0.1;
    Control control;
};
