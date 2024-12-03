#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Juego.h"
#include "Menu.h"  

using namespace sf;
using namespace std;

int main() {

	RenderWindow app(VideoMode(1230, 580), "Gun Storm");

    Menu menu(app);
    if (menu.run()) {  // Solo ejecuta el juego si el menú devuelve true
        Juego juego;
        juego.run();
    }

	return 0;
}