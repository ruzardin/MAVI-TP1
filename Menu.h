#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Menu {
private:
    RenderWindow& app;  // Referencia al RenderWindow del juego
    Texture menuTexture; // Textura para el fondo del men�
    Sprite menuSprite;  // Sprite para el fondo del men�

    // Bot�n de inicio o eventos de la pantalla
    Text startText;
    Font font;

public:
    Menu(RenderWindow& app);
    bool run();
};