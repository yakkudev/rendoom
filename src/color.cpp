#include "color.h"

using rendoom::Color;

Color::Color(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

Color::Color() {
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

// Colors:
// #49e7ec
// #3368dc
// #2b0f54
// #ab1f65
// #ff4f69
// #ff8142
// #ffda45
// #fff7f8

const Color Color::palette[] = {
    Color(73, 231, 236),
    Color(51, 104, 220),
    Color(43, 15, 84),
    Color(171, 31, 101),
    Color(255, 79, 105),
    Color(255, 129, 66),
    Color(255, 218, 69),
    Color(255, 247, 248)
};