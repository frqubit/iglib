#include <SFML/Graphics.hpp>
#include <iostream>
#include <iglib/iglib.hpp>
#include <memory>
#include <stdlib.h>
#include "time.h"

using namespace iglib;
using namespace sf;

int main() {
	srand(time(NULL));

	setGridSize(50);

	RenderWindow window(VideoMode(800, 600), "SFML works!");
	window.setFramerateLimit(60);

	Vector3f tileSizes[4] = {
		Vector3f(50, 50, 50),
		Vector3f(100, 50, 50),
		Vector3f(50, 100, 50),
		Vector3f(50, 50, 100)
	};

	IsoShape shapes[4];
	IsoShape floor(Vector3f(1000, 100, 1000));

	Texture texture;
	texture.loadFromFile("assets/bluewall.png");
	texture.setRepeated(true);

	floor.setTexture(0, &texture);
	floor.setColor(1, Color::Green);
	floor.setColor(2, Color::Green);
	floor.setPosition(IsoVector(0, 0, 0, 300, 70));

	float tileHovers[4] = { 0, 10, 30, -10 };
	bool directions[4] = { true, true, true, true };

	for (size_t i = 0; i < 4; i++) {
		shapes[i].init(tileSizes[i]);
		shapes[i].setColor(0, Color::Red);
		shapes[i].setColor(1, Color::Green);
		shapes[i].setColor(2, Color::Green);

		float ix = (i % 2) * 200;
		float iy = (i / 2) * 200;

		shapes[i].setPosition(IsoVector(ix + 100, iy + 100, 0, 300, 100 + tileHovers[i]));
	}

	Clock clock;
	Clock totalClock;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		floor.draw(&window);

		for (size_t i = 0; i < 4; i++) {
			shapes[i].draw(&window);

			if (directions[i]) {
				tileHovers[i] += 1;
			} else {
				tileHovers[i] -= 1;
			}

			if (tileHovers[i] >= 30) {
				directions[i] = false;
			} else if (tileHovers[i] <= -30) {
				directions[i] = true;
			}

			float ix = (i % 2) * 200;
			float iy = (i / 2) * 200;

			shapes[i].setPosition(IsoVector(ix + 100, iy + 100, 0, 300, 100 + tileHovers[i]));
		}

		window.display();

		// Show FPS in title

		if (totalClock.getElapsedTime().asSeconds() >= 0.5) {
			window.setTitle("FPS: " + std::to_string(1 / clock.getElapsedTime().asSeconds()));
			totalClock.restart();
		}
		clock.restart();

	}
}
