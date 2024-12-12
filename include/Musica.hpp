#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Musica
{
public:
    Musica(const std::string &filePath)
    {
        if (!music.openFromFile(filePath))
        {
            std::cerr << "Error al cargar el archivo de música." << std::endl;
        }
    }

    void play()
    {
        music.setLoop(true); // Repetir la música
        music.play();
    }

private:
    sf::Music music;
};