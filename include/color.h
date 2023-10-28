#pragma once
#include <SFML/Graphics.hpp>

namespace rendoom {
    struct Color {
    public:
        sf::Uint8 r, g, b;
        Color();
        Color(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b);
        static const Color palette[8];
    };
}

