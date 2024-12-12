#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

// Clase para manejar textos
class Texto
{
public:
    Texto(const std::string &fontFile, const std::string &contenido, unsigned int tamanio, sf::Color color, sf::Vector2f posicion)
    {
        if (!font.loadFromFile(fontFile))
        {
            std::cerr << "Error al cargar la fuente." << std::endl;
        }
        text.setFont(font);
        text.setString(contenido);
        text.setCharacterSize(tamanio);
        text.setFillColor(color);
        text.setPosition(posicion);
    }

    void actualizarContenido(const std::string &contenido)
    {
        text.setString(contenido);
    }

    void draw(sf::RenderWindow &window) const
    {
        window.draw(text);
    }

private:
    sf::Font font;
    sf::Text text;
};