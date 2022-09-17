////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#define WidthSize 800
#define HeightSize 600
#define SeparationScale 30

class Plane
{
	sf::RenderWindow* window;
	int height = HeightSize;
	int width = WidthSize;
	float scale = 1;
	sf::RectangleShape* xSeparation;
	sf::RectangleShape* ySeparation;
	sf::RectangleShape* xGrid;
	sf::RectangleShape* yGrid;
	sf::Text* xNumbers;
	sf::Text* yNumbers;
	int xShift = 0;
	int yShift = 0;

public:
	Plane();
	~Plane();
	void setPlane();
	void reScale();
};

int main()
{
	Plane* plane = new Plane();

	return 0;
}

Plane::Plane()
{
	// create the window
	window = new sf::RenderWindow(sf::VideoMode(WidthSize, HeightSize), "Laba 1");

	// run the program as long as the window is open
	while (window->isOpen())
	{
		int height = window->getSize().y;
		int width = window->getSize().x;

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window->pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window->close();


			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Left)
				{
					this->xShift += 10;
				}

				if (event.key.code == sf::Keyboard::Right)
				{
					this->xShift -= 10;
				}

				if (event.key.code == sf::Keyboard::Up)
				{
					this->yShift += 10;
				}

				if (event.key.code == sf::Keyboard::Down)
				{
					this->yShift -= 10;
				}
			}
		}

		// clear the window with black color
		window->clear(sf::Color::Black);

		// draw everything here...
		// window.draw(...);
		setPlane();

		// end the current frame
		window->display();
	}
}

void Plane::setPlane()
{
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(width, height));
	rectangle.setFillColor(sf::Color::White);

	sf::RectangleShape xLine;
	xLine.setSize(sf::Vector2f(width, 1));
	if (abs(yShift) < height / 2)
		xLine.setPosition(sf::Vector2f(0, height / 2 + yShift));
	else
		if (yShift > 0)
			xLine.setPosition(sf::Vector2f(0, height));
		else
			xLine.setPosition(sf::Vector2f(0, 0));
	xLine.setFillColor(sf::Color::Black);

	sf::RectangleShape yLine;
	yLine.setSize(sf::Vector2f(1, height));
	if (abs(xShift) < width / 2)
		yLine.setPosition(sf::Vector2f(width / 2 + xShift, 0));
	else
		if (xShift < 0)
			yLine.setPosition(sf::Vector2f(0, width));
		else
			yLine.setPosition(sf::Vector2f(width, 0));
	yLine.setFillColor(sf::Color::Black);

	sf::CircleShape xArrow(10.f, 3);
	xArrow.rotate(90);
	if (abs(yShift) < height / 2)
		xArrow.setPosition(sf::Vector2f(width, height / 2 - 10.f + yShift));
	else
		if (yShift > 0)
			xArrow.setPosition(sf::Vector2f(width, height - 10.f));
		else
			xArrow.setPosition(sf::Vector2f(width, 0 - 10.f));
	xArrow.setFillColor(sf::Color::Black);

	sf::CircleShape yArrow(10.f, 3);
	if (abs(xShift) < width / 2)
		yArrow.setPosition(sf::Vector2f(width / 2 - 10.f + xShift, 0));
	else
		if (xShift < 0)
			yArrow.setPosition(sf::Vector2f(0 - 10.f, 0));
		else
			yArrow.setPosition(sf::Vector2f(width - 10.f, 0));
	yArrow.setFillColor(sf::Color::Black);

	window->draw(rectangle);


	sf::RectangleShape Separation;
	sf::RectangleShape Grid;
	sf::Text number;
	Separation.setSize(sf::Vector2f(1, 6));
	Grid.setSize(sf::Vector2f(1, height));
	Grid.setFillColor(sf::Color::Cyan);
	Separation.setFillColor(sf::Color::Black);
	
	int xSepStart = abs((width / 2 + xShift) % SeparationScale);
	int ySepStart = abs((height / 2 + yShift) % SeparationScale);
	
	int sepSize = width / SeparationScale + 2;

	for (int i = 0; i < sepSize; ++i)
	{
		Separation.setPosition(sf::Vector2f(xSepStart + SeparationScale * i, xLine.getPosition().y - 3));
		Grid.setPosition(sf::Vector2f(xSepStart + SeparationScale * i, 0));
		number.setString(std::to_string(i));
		number.setPosition(sf::Vector2f(xSepStart + SeparationScale * i, xLine.getPosition().y - 3));
		window->draw(Grid);
		window->draw(Separation);
		window->draw(number);
	}

	sepSize = height / SeparationScale + 2;

	Separation.rotate(90);
	Grid.setSize(sf::Vector2f(width, 1));
	
	for (int i = 0; i < sepSize; ++i)
	{
		Separation.setPosition(sf::Vector2f(yLine.getPosition().x + 3, ySepStart + SeparationScale * i));
		Grid.setPosition(sf::Vector2f(0, ySepStart + SeparationScale * i));
		window->draw(Grid);
		window->draw(Separation);
	}

	window->draw(xLine);
	window->draw(yLine);
	window->draw(xArrow);
	window->draw(yArrow);
}

void Plane::reScale()
{
}

Plane::~Plane()
{
	delete[] this->xSeparation;
	delete[] this->ySeparation;
	delete[] this->xGrid;
	delete[] this->yGrid;
	delete[] this->xNumbers;
	delete[] this->yNumbers;

	delete this->window;
}