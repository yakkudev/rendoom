#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <cmath>

#include "config.h"
#include "color.h"

using rendoom::Color;

void handleEvents(sf::RenderWindow& window, sf::VideoMode vm) {
	sf::Event Event;
	while (window.pollEvent(Event)) {
		switch (Event.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::Resized:
			// cancel resize
			window.setSize(sf::Vector2u(vm.width, vm.height));
			break;
		case sf::Event::KeyPressed:
			if (Event.key.code == sf::Keyboard::Escape)
				window.close();
			break;
		default:
			break;
		}
	}
}

void setPixel(sf::Uint8* pixels, int width, int x, int y, int r, int g, int b) {
	int index = (x + y * width) * 4;
	pixels[index] = r;
	pixels[index + 1] = g;
	pixels[index + 2] = b;
	pixels[index + 3] = 255;
}

void setPixel(sf::Uint8* pixels, int width, int x, int y, const Color color) {
	setPixel(pixels, width, x, y, color.r, color.g, color.b);
}

int main(int argc, char* argv[]) {
	// Output project version
	std::cout << "Version: " << PROJECT_VERSION_MAJOR << "."
		<< PROJECT_VERSION_MINOR << std::endl;

	// Create and configure window
	sf::VideoMode vm(800, 600);

	sf::RenderWindow window(vm, "RENDOOM",
		sf::Style::Titlebar | sf::Style::Close);
	sf::View view(sf::FloatRect(0, 0, vm.width, vm.height));
	window.setView(view);

	window.setFramerateLimit(60);

	// Screen scale
	const unsigned int screenScale = 8;
	const unsigned int screenX = vm.width / screenScale;
	const unsigned int screenY = vm.height / screenScale;

	// Create and sfml specific rendering stuff
	sf::Texture drawTexture;
	drawTexture.create(screenX, screenY);

	sf::Sprite drawSprite;
	drawSprite.setTexture(drawTexture);

	// Create pixel array (this is where we draw to)
	sf::Uint8* pixels = new sf::Uint8[screenX * screenY * screenScale];

	// Random seed
	srand(time(NULL));

	int frame = 0;

	// Handle closing the window
	while (window.isOpen()) {
		frame++;

		handleEvents(window, vm);

		// Update pixels
		for (int y = 0; y < screenY; y++) {
			for (int x = 0; x < screenX; x++) {
				// temporary test
				double offset = frame * 0.9333; // magic number
				setPixel(pixels, screenX, x, y, Color::palette[(int)(y + offset) % 8]);
			}
		}

		// Render pixel array
		drawTexture.update(pixels);
		drawSprite.setPosition(0, 0);
		drawSprite.setScale(screenScale, screenScale);
		window.draw(drawSprite);
		window.display();
	}

	// Cleanup
	delete[] pixels;
	return 0;
}
