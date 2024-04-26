
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <complex>
#include <cmath>
#include "ComplexPlane.h"

using namespace sf;
using namespace std;

int main()
{
	int pixelWidth = VideoMode::getDesktopMode().width / 2;
	int pixelHeight = VideoMode::getDesktopMode().height / 2;
	VideoMode vm(pixelWidth, pixelHeight);
	RenderWindow window(vm, "Mandelbrot", Style::Default);
	Clock clock;

	ComplexPlane complexPlane(pixelWidth, pixelHeight);

	//Text
	Font font;
	if (!font.loadFromFile("Gundam.otf"))
	{
		cout << "Can't load the font file." << endl;
	}
	Text text1("TEST", font);
	text1.setCharacterSize(20);
	text1.setStyle(Text::Regular);
	text1.setFillColor(Color::White);

	while (window.isOpen())
	{
		//User input
		clock.restart();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
			else if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Right)
				{
					cout << "the right button was pressed" << endl;
					cout << "mouse x: " << event.mouseButton.x << endl;
					cout << "mouse y: " << event.mouseButton.y << endl;
					complexPlane.zoomOut();
					complexPlane.setCenter(Mouse::getPosition(window));
				}
				else if (event.mouseButton.button == sf::Mouse::Left)
				{
					cout << "the left button was pressed" << endl;
					cout << "mouse x: " << event.mouseButton.x << endl;
					cout << "mouse y: " << event.mouseButton.y << endl;
					complexPlane.zoomIn();
					complexPlane.setCenter(Mouse::getPosition(window));
				}
			}
			if (event.type == sf::Event::MouseMoved)
			{
				complexPlane.setMouseLocation(Mouse::getPosition(window));
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		//complexPlane.updateRender();
		complexPlane.multiThread();		//use this for multithreading, "complexPlane.updateRender();" function must be disabled
		complexPlane.loadText(text1);

		//Draw
		window.clear();
		window.draw(complexPlane);
		window.draw(text1);
		window.display();
	}
}
