#include "Inocente.h"

Inocente::Inocente(const Texture& texture, Vector2f position, float scale, float lifetime)
    : lifetime(lifetime) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(scale, scale);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

bool Inocente::isClicked(Vector2i mousePos) const {
    return sprite.getGlobalBounds().contains(static_cast<Vector2f>(mousePos));
}

void Inocente::draw(RenderWindow& window) const {
    window.draw(sprite);
}

bool Inocente::isExpired() const {
    return lifetime <= 0;
}
