#include "WarZone.h"

WarZone::WarZone(sf::Texture* text, sf::Vector2f pos, float scl)
    :Entity(text, pos, 0){
    // Create Image from texture pack
    sf::IntRect uvRect;
    body.setOrigin(text->getSize().x/ 2, text->getSize().y / 2);

    // Scale Image
    body.scale(scl, scl);
}
