#include <SFML/Graphics.hpp>
#include <iostream>
#include <Obstaculo.hpp>

std::vector<Obstaculo> obstaculos = {
    Obstaculo("./assets/images/personaje.png", sf::Vector2f(100, -50), 2.0f),
    Obstaculo("./assets/images/personaje.png", sf::Vector2f(300, -200), 3.0f),
    Obstaculo("./assets/images/personaje.png", sf::Vector2f(500, -150), 4.0f)
};

class Personaje {
public:
    Personaje(const std::string& textureFile, sf::Vector2f position) {
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

    // Método para obtener el sprite (necesario para colisiones)
    const sf::Sprite& getSprite() const {
        return sprite;
    }
private:
    sf::Texture texture;
    sf::Sprite sprite;
};

double velocidad = 0.1;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 779), "DinoChrome");

    // Cargar el fondo
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("./assets/images/escenario.png")) {
        std::cerr << "Error al cargar la textura del fondo." << std::endl;
        return -1;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    // Crear el personaje
    Personaje character("./assets/images/personaje.png", sf::Vector2f(50,68));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            character.move(velocidad * -1, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            character.move(velocidad, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            character.move(0, velocidad * -1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            character.move(0, velocidad);
        }

        for (const auto& obstaculo : obstaculos) {
    if (obstaculo.colisionaCon(character.getSprite())) {
        std::cout << "¡Colisión! Fin del juego." << std::endl;
        window.close(); // Termina el juego
        break;
    }
}

for (auto& obstaculo : obstaculos) {
    obstaculo.mover();
}

        window.clear();
        window.draw(backgroundSprite); // Dibujar el fondo
        character.draw(window);       // Dibujar el personaje
        window.display();
    }

    return 0;
}
