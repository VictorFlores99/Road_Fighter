#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Obstaculo {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    float velocidad; // Velocidad de movimiento del obstáculo

public:
    Obstaculo(const std::string& rutaImagen, sf::Vector2f posicionInicial, float velocidadInicial)
        : velocidad(velocidadInicial)
    {
        if (!texture.loadFromFile(rutaImagen)) {
            std::cerr << "Error al cargar la textura del obstáculo." << std::endl;
            throw "Error al cargar imagen";
        }
        sprite.setTexture(texture);
        sprite.setPosition(posicionInicial);
    }

    ~Obstaculo() {}

    void mover() {
        // Mueve el obstáculo hacia abajo
        sprite.move(0, velocidad);

        // Si sale de la ventana, vuelve a aparecer arriba en una posición aleatoria
        if (sprite.getPosition().y > 800) { // 800 es la altura de la ventana
            float nuevaX = rand() % 800; // Posición X aleatoria
            sprite.setPosition(nuevaX, -sprite.getGlobalBounds().height);
        }
    }

    bool colisionaCon(const sf::Sprite& personaje) const {
        // Detecta colisión con otro sprite
        return sprite.getGlobalBounds().intersects(personaje.getGlobalBounds());
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }
};
