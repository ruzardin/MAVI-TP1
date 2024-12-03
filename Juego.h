#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemigo.h"
#include "Inocente.h"
#include "Crosshair.h"

using namespace sf;
using namespace std;

class Juego {
private:
    RenderWindow App;
    Texture enemyTexture;
    Texture innocentTexture;
    Texture crosshairTexture;
    Texture backgroundTexture;
    Sprite backgroundSprite;
    Texture gameOverTexture;  
    Sprite gameOverSprite;   

    Crosshair* crosshair;
    vector<Enemigo> enemies;
    vector<Inocente> innocents;

    const int maxEnemies;
    Font fuente;
    
    Text vidasTexto;
    Text _puntaje, _puntajeTotal ;
    int inocenteEliminados = 0;
    int puntaje = 0;
    int puntajeTotal = 0;
    int vidas;



public:
    Juego();
    ~Juego();
    void run();

private:

    void processEvents();
    void update();
    void render();
    void handleMouseClick(Vector2i mousePos);
    void actualizarPuntajeTotal();
}; 
