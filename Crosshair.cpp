#include "Crosshair.h"

Crosshair::Crosshair(const Texture& texture) {
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setScale(0.1f, 0.1f);  // Ajusta el tamaño de la mira
}

void Crosshair::updatePosition(Vector2i mousePos) {
    sprite.setPosition(static_cast <Vector2f>(mousePos));
}