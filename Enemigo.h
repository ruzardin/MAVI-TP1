#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Enemigo {
public:
    Sprite sprite;
    float lifetime; // Tiempo de vida en segundos

    Enemigo(const Texture& texture, Vector2f position, float scale, float lifetime);

    bool isClicked(Vector2i mousePos) const;
    bool isExpired() const;

};
