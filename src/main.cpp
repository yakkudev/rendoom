#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <cmath>

#include "config.h"
#include "color.h"

#define PI 3.1415

using rendoom::Color;

static double pRot = 0;
static double pX = 3.456;
static double pY = 2.345;
static double fov = PI / 4;
static double moveSpeed = 0.05;
static double rotSpeed = 0.075;

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
			if (Event.key.code == sf::Keyboard::Left)
				pRot -= rotSpeed;
			if (Event.key.code == sf::Keyboard::Right)
				pRot += rotSpeed;
			if (Event.key.code == sf::Keyboard::W) {
				pX += moveSpeed * cos(pRot);
				pY += moveSpeed * sin(pRot);
			}
			if (Event.key.code == sf::Keyboard::S) {
				pX -= moveSpeed * cos(pRot);
				pY -= moveSpeed * sin(pRot);
			}
			if (Event.key.code == sf::Keyboard::A) {
				pX += moveSpeed * sin(pRot);
				pY -= moveSpeed * cos(pRot);
			}
			if (Event.key.code == sf::Keyboard::D) {
				pX -= moveSpeed * sin(pRot);
				pY += moveSpeed * cos(pRot);
			}
			break;
		default:
			break;
		}
	}
}

void setPixel(sf::Uint8* pixels, int width, int x, int y, int r, int g, int b) {
	long int index = (x + y * width) * 4;
	pixels[index] = r;
	pixels[index + 1] = g;
	pixels[index + 2] = b;
	pixels[index + 3] = 255;
}

void setPixel(sf::Uint8* pixels, int width, int x, int y, const Color color) {
	setPixel(pixels, width, x, y, color.r, color.g, color.b);
}

void drawRect(sf::Uint8* pixels, int screenWidth, int x, int y, int width, int height, int r, int g, int b) {
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			setPixel(pixels, screenWidth, x + i, y + j, r, g, b);
}

void drawRect(sf::Uint8* pixels, int screenWidth, int x, int y, int width, int height, const Color color) {
	drawRect(pixels, screenWidth, x, y, width, height, color.r, color.g, color.b);
}



int main(int argc, char* argv[]) {

	const int mapX = 16; // map width
	const int mapY = 16; // map height
	const char map[] = \
		"0000222222220000"\
		"1              0"\
		"1      11111   0"\
		"1     0        0"\
		"0     0  1110000"\
		"0     3        0"\
		"0   10000      0"\
		"0   0   11100  0"\
		"0   0   0      0"\
		"0   0   1  00000"\
		"0       1      0"\
		"2       1      0"\
		"0       0      0"\
		"0 0000000      0"\
		"0              0"\
		"0002222222200000"; // game map

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
	const unsigned int screenScale = 2;
	const unsigned int screenX = vm.width / screenScale;
	const unsigned int screenY = vm.height / screenScale;

	// Create and SFML specific rendering objects
	sf::Texture drawTexture;
	drawTexture.create(screenX, screenY);

	sf::Sprite drawSprite;
	drawSprite.setTexture(drawTexture);

	// Create pixel array (this is where we draw to)
	sf::Uint8* pixels = new sf::Uint8[vm.width * vm.height * 4];

	// Random seed
	srand(time(NULL));

	// Main loop
	int frame = 0;
	while (window.isOpen()) {
		frame++;
		handleEvents(window, vm);

		// Clear buffer so we don't draw over the previous frame
		drawRect(pixels, screenX, 0, 0, screenX, screenY, Color(0, 0, 0));

		// Raycasting
		for (int ray = 0; ray < screenX; ray++) {
			double angle = (pRot - fov / 2) + (double)ray / (double)screenX * fov;

			double c = 0.01;
			for (; c < 20; c += .01) {
				int cx = pX + c * cos(angle);
				int cy = pY + c * sin(angle);

				char block = map[int(cx) + int(cy) * mapX];
				if (block != ' ') { // our ray touches a wall, so draw the vertical column to create an illusion of 3D
					int column_height = mapY / c * 3;
					// Calculate color
					const float fogIntensity = 10;
					const float fog = fabs(1 - c / fogIntensity);
					int r, g, b = 0;
					r = Color::palette[block % 8].r * fog;
					g = Color::palette[block % 8].g * fog;
					b = Color::palette[block % 8].b * fog;
					drawRect(pixels, screenX, screenX + ray, screenY / 2 - column_height / 2, 1, column_height, r, g, b);
					break;
				}
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
