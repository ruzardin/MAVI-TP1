#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Crosshair {
public:
    Sprite sprite;

    Crosshair(const Texture& texture);
    void updatePosition(Vector2i mousePos);
};