#include "Juego.h"
#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()


Juego::Juego() : App(VideoMode(1200, 600), "Gun Storm"), maxEnemies(5), vidas(3), puntaje(0), puntajeTotal(0), inocenteEliminados(0) {

    enemyTexture.loadFromFile("assets\\enemigo.png");
    innocentTexture.loadFromFile("assets\\inocente.png");
    crosshairTexture.loadFromFile("assets\\crosshair.png");
    backgroundTexture.loadFromFile("assets\\fondo.png");
    backgroundSprite.setTexture(backgroundTexture);
    gameOverTexture.loadFromFile("assets/game_over.png");
    gameOverSprite.setTexture(gameOverTexture);
    gameOverSprite.setOrigin(gameOverSprite.getLocalBounds().width / 2, gameOverSprite.getLocalBounds().height / 2);
    gameOverSprite.setPosition(App.getSize().x / 2, App.getSize().y / 2);  
    fuente.loadFromFile("assets\\Smokum-Regular.ttf");

    backgroundSprite.setScale(
        static_cast<float>(App.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(App.getSize().y) / backgroundTexture.getSize().y
    );

    crosshair = new Crosshair(crosshairTexture);
    
    vidasTexto.setFont(fuente);
    vidasTexto.setPosition(700.0f, 10.0f);
    vidasTexto.setCharacterSize(50.0f);
    vidasTexto.setFillColor(Color::White);
    vidasTexto.setString("Vidas: ");

    _puntaje.setFont(fuente);
    _puntaje.setPosition(250.0f, 10.0f);
    _puntaje.setCharacterSize(50.0f);
    _puntaje.setFillColor(Color::White); 
    _puntaje.setString("Puntaje: ");

    _puntajeTotal.setFont(fuente);
    _puntajeTotal.setPosition(470.0f, 500.0f);
    _puntajeTotal.setCharacterSize(50.0f);
    _puntajeTotal.setFillColor(Color::Black);


    App.setFramerateLimit(60);
    srand(static_cast<unsigned>(time(0)));  // Inicializa el generador aleatorio

    Cursor cursor;
    if (cursor.loadFromSystem(sf::Cursor::Arrow)) {
        App.setMouseCursor(cursor);
    }
}


void Juego::run() {
    App.setMouseCursorVisible(false);
    while (App.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Juego::processEvents() {
    Event event;
    while (App.pollEvent(event)) {
        if (event.type == Event::Closed)
            App.close();
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            handleMouseClick(Mouse::getPosition(App));
        }
    }
}

void Juego::update() {

    crosshair->updatePosition(Mouse::getPosition(App));

    // Generar enemigo aleatoriamente
    if (enemies.size() < maxEnemies && rand() % 100 < 20) {
        Vector2f pos(static_cast<float>(rand() % App.getSize().x), static_cast<float>(rand() % App.getSize().y + 100.0f));
        enemies.push_back(Enemigo(enemyTexture, pos, 0.22f, 1.0f));  // Escala enemigo y tiempo de vida
    }

    if (innocents.size() < 3 && rand() % 100 < 8) {  // 5% de probabilidad
        Vector2f pos(static_cast<float>(rand() % App.getSize().x ), static_cast<float>(rand() % App.getSize().y + 100.0f));
        innocents.push_back(Inocente(innocentTexture, pos, 0.5f, 2.0f));
    }

    for (auto i = enemies.begin(); i != enemies.end();) {
        i->lifetime -= 1.0f / 60.0f;  // Asume 60 FPS, reduce en ~0.016s por cuadro
        if (i->isExpired()) {
            i = enemies.erase(i);  
        }
        else {
            ++i;
        }
    }

    for (auto i = innocents.begin(); i != innocents.end();) {
        i->lifetime -= 1.0f / 60.0f;  // Asume 60 FPS, reduce en ~0.016s por cuadro
        if (i->isExpired()) {
            i = innocents.erase(i); 
        }
        else {
            ++i;
        }
    }
}

void Juego::render() {
    App.clear();
    App.draw(backgroundSprite);

    //enemigos
    for (const auto& enemy : enemies)
        App.draw(enemy.sprite);

    //inocentes
    for (const auto& innocent : innocents) {
        App.draw(innocent.sprite);
    }

    if (vidas <= 0) {
        App.clear(Color::White);
        App.draw(gameOverSprite); 
        App.draw(_puntajeTotal);
    }

    App.setMouseCursorVisible(false);
    App.draw(_puntaje);
    App.draw(vidasTexto);
    App.draw(crosshair->sprite);
    App.display();
}

void Juego::handleMouseClick(::Vector2i mousePos) {

    for (auto i = enemies.begin(); i != enemies.end();) {
        if (i->isClicked(mousePos)) {
            puntaje++;
            _puntaje.setString("Puntaje: " + to_string(puntaje));
            i = enemies.erase(i);  // Elimina el enemigo y actualiza el iterador
            actualizarPuntajeTotal();
        }
        else {
            ++i;
        }
    }

    for (auto i = innocents.begin(); i != innocents.end();) {
        if (i->isClicked(mousePos)) {
            i = innocents.erase(i);

            vidas--;
            inocenteEliminados++;
            vidasTexto.setString("Vidas: " + to_string(vidas));
            actualizarPuntajeTotal();
            if (vidas <= 0) {
                App.draw(gameOverSprite);
                return;
            }
        }
        else {
            ++i;  
        }
    }
}

void Juego::actualizarPuntajeTotal() {
    puntajeTotal = puntaje - (inocenteEliminados * 2);  // Cálculo centralizado
    _puntajeTotal.setString("Puntaje Total: " + std::to_string(puntajeTotal));
}

Juego::~Juego() {
    delete crosshair;
}

