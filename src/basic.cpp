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

	RenderWindow window(VideoMode(800, 600), "SFML works!");
	window.setFramerateLimit(60);

	Vector3f tileSizes[4] = {
		Vector3f(50, 50, 50),
		Vector3f(100, 50, 50),
		Vector3f(50, 100, 50),
		Vector3f(50, 50, 100)
	};

	IsoShape shapes[4];

	for (size_t i = 0; i < 4; i++) {
		shapes[i].init(tileSizes[i]);
		shapes[i].setPosition(IsoVector(0, 0, 0, 0, 0));
		shapes[i].setColor(0, Color::Red);
		shapes[i].setColor(1, Color::Green);
		shapes[i].setColor(2, Color::Green);

		float ix = (i % 2) * 200;
		float iy = (i / 2) * 200;

		shapes[i].setPosition(IsoVector(ix + 100, iy + 100, 0, 300, 100));
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

		for (size_t i = 0; i < 4; i++) {
			shapes[i].draw(&window);
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
