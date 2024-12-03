#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

class Inocente {
public:
    Sprite sprite;
    float lifetime;

    Inocente(const Texture& texture, Vector2f position, float scale, float lifetime);
    
    bool isClicked(Vector2i mousePos) const;
    void draw(RenderWindow& window) const;
    bool isExpired() const;

};
