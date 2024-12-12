#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <Personaje.hpp>
#include <Obstaculo.hpp>
#include <PersonajeAuto.hpp>
#include <Control.hpp>
#include <Texto.hpp>
#include <Musica.hpp>
#include <Contador.hpp>
#include <Vidas.hpp>

void reiniciarJuego(Personaje &jugador, std::vector<Obstaculo> &obstaculos, Vidas &vidas, Contador &contador, Texto &textoVidas)
{
    jugador.setPosition(350, 400);
    obstaculos.clear();
    vidas = Vidas(3); // Reiniciar vidas
    textoVidas.actualizarContenido("Vidas: 3");
    contador.reiniciar(); // Reiniciar contador
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 780), "Road_Fighter");

    // Música
    Musica musica("./assets/music/doom.ogg");
    musica.play();

    // Fondo
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("./assets/images/escenario2.jpg"))
    {
        std::cerr << "Error al cargar la textura del fondo." << std::endl;
        return -1;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    // Personajes
    Personaje jugador("./assets/images/personaje.png", sf::Vector2f(350, 400));
    Personaje personajeAuto("./assets/images/personaje.png", sf::Vector2f(350, 780));

    // Obstáculos
    std::vector<Obstaculo> obstaculos;

    // Control
    Control control(velocidad);

    // Contador de tiempo
    Contador contador(60.0f);

    // Vidas
    Vidas vidas(3);

    // Textos
    Texto textoTiempo("./assets/text/Minecraft-Bold.otf", "Tiempo: 60 s", 24, sf::Color::Red, sf::Vector2f(620, 110));
    Texto textoBienvenida("./assets/text/Minecraft-Bold.otf", "¡Bienvenido a \n Road Fighter!", 24, sf::Color::Red, sf::Vector2f(600, 50));
    Texto textoVidas("./assets/text/Minecraft-Bold.otf", "Vidas: 3", 24, sf::Color::Red, sf::Vector2f(620, 140));

    sf::Clock relojObstaculo;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Terminar el juego si el tiempo se agota
        if (contador.tiempoAgotado())
        {
            std::cout << "Fin del juego: tiempo completado." << std::endl;
            reiniciarJuego(jugador, obstaculos, vidas, contador, textoVidas);
        }

        // Movimiento automático del personaje
        float nuevaYAuto = 780 - (780 * (60.0f - contador.tiempoRestante()) / 60.0f);
        personajeAuto.setPosition(-10, nuevaYAuto);

        // Controlar el movimiento del jugador
        control.manejarEntrada(jugador);

        // Generar obstáculos
        if (relojObstaculo.getElapsedTime().asSeconds() > 3.0f)
        {
            float xPos = static_cast<float>(rand() % (static_cast<int>(MAX_X) - static_cast<int>(MIN_X) + 1) + static_cast<int>(MIN_X));
            obstaculos.emplace_back("./assets/images/obstaculo.png", sf::Vector2f(xPos, -50));
            relojObstaculo.restart();
        }

        for (auto &obstaculo : obstaculos)
        {
            obstaculo.mover(VELOCIDAD_OBSTACULO_Y);
        }

        obstaculos.erase(
            std::remove_if(obstaculos.begin(), obstaculos.end(),
                           [](const Obstaculo &obstaculo)
                           {
                               return obstaculo.getSprite().getPosition().y > 780;
                           }),
            obstaculos.end());

        // Verificar colisiones
        for (const auto &obstaculo : obstaculos)
        {
            if (jugador.getSprite().getGlobalBounds().intersects(obstaculo.getSprite().getGlobalBounds()))
            {
                if (vidas.restarVida())
                {
                    reiniciarJuego(jugador, obstaculos, vidas, contador, textoVidas);
                }
                else
                {
                    textoVidas.actualizarContenido("Vidas: " + std::to_string(vidas.obtenerVidas()));
                }
                break;
            }
        }

        // Actualizar textos
        textoTiempo.actualizarContenido("Tiempo: " + std::to_string(static_cast<int>(contador.tiempoRestante())) + " s");

        // Dibujar escena
        window.clear();
        window.draw(backgroundSprite);
        jugador.draw(window);
        personajeAuto.draw(window);
        for (const auto &obstaculo : obstaculos)
        {
            obstaculo.draw(window);
        }
        textoTiempo.draw(window);
        textoBienvenida.draw(window);
        window.display();
    }

    return 0;
}
