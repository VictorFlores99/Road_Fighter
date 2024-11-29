#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib> // Para rand()

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

    const sf::Sprite& getSprite() const {
        return sprite;
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;
};

class Obstaculo {
public:
    Obstaculo(const std::string& textureFile, sf::Vector2f position) {
        if (!texture.loadFromFile(textureFile)) {
            std::cerr << "Error al cargar la textura del obstáculo." << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setPosition(position);
    }

    void mover(float velocidadX, float velocidadY) {
        sprite.move(-velocidadX, velocidadY); // Mueve hacia la izquierda y hacia abajo
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(sprite);
    }

    const sf::Sprite& getSprite() const {
        return sprite;
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;
};

double velocidad = 0.1;
const float VELOCIDAD_OBSTACULO_X = 0.2f; // Velocidad horizontal (de derecha a izquierda)
const float VELOCIDAD_OBSTACULO_Y = 0.1f; // Velocidad vertical (de arriba a abajo)

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 779), "DinoChrome");

    // Cargar el fondo
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("./assets/escenario.png")) {
        std::cerr << "Error al cargar la textura del fondo." << std::endl;
        return -1;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    // Crear el personaje
    Personaje character("./assets/personaje.png", sf::Vector2f(400, 300));

    // Lista para los obstáculos
    std::vector<Obstaculo> obstaculos;

    // Reloj para controlar el tiempo de aparición de obstáculos
    sf::Clock relojObstaculo;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Movimiento del personaje
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

        // Aparecer un nuevo obstáculo cada 5 segundos
        if (relojObstaculo.getElapsedTime().asSeconds() > 5.0f) {
            obstaculos.emplace_back("./assets/personaje.png", sf::Vector2f(800, rand() % 779));
            relojObstaculo.restart();
        }

        // Mover obstáculos
        for (auto& obstaculo : obstaculos) {
            obstaculo.mover(VELOCIDAD_OBSTACULO_X, VELOCIDAD_OBSTACULO_Y);
        }

        // Eliminar obstáculos que salen de la pantalla
        obstaculos.erase(
            std::remove_if(obstaculos.begin(), obstaculos.end(),
                           [](const Obstaculo& obstaculo) {
                               return obstaculo.getSprite().getPosition().x < -50; // Fuera de la pantalla
                           }),
            obstaculos.end());

        // Verificar colisiones
        for (const auto& obstaculo : obstaculos) {
            if (character.getSprite().getGlobalBounds().intersects(obstaculo.getSprite().getGlobalBounds())) {
                std::cout << "Colisión. Fin del juego." << std::endl;
                window.close();
                break;
            }
        }

        // Dibujar escena
        window.clear();
        window.draw(backgroundSprite);
        character.draw(window);
        for (const auto& obstaculo : obstaculos) {
            obstaculo.draw(window);
        }
        window.display();
    }

    return 0;
}



