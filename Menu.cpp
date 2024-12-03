#include "Menu.h"

Menu::Menu(RenderWindow& app) : app(app) {

    menuTexture.loadFromFile("assets/menu_background.png");
    menuSprite.setTexture(menuTexture);
    menuSprite.setScale(
        static_cast<float>(app.getSize().x) / menuTexture.getSize().x,
        static_cast<float>(app.getSize().y) / menuTexture.getSize().y
    );

}

bool Menu::run() {
    while (app.isOpen()) {
        Event event;
        while (app.pollEvent(event)) {
            if (event.type == Event::Closed)
                app.close();
            if (event.type == Event::MouseButtonPressed || event.type == Event::KeyPressed) {
                if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                    app.close();
                    return false;  
                }
                return true; 
            }
        }

        app.clear();
        app.draw(menuSprite);
        app.draw(startText);
        app.display();
    }
    return false;  
}

