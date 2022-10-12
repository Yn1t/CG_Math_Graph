#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#define WidthSize 800
#define HeightSize 600
#define SeparationScale 80
#define ConstA 5
#define pointSize 500
#define speed 20

class Plane
{
	sf::RenderWindow* window;
	int height = HeightSize;
	int width = WidthSize;
	float scale = 1;
	int xShift = 0;
	int yShift = 0;
	float a = ConstA;

public:
	Plane();
	~Plane();
	void setPlane();
	void madePlot();
};

int main()
{
	try
	{
		Plane* plane = new Plane();
	}
	catch (const std::exception& ex)
	{
	
	}
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
					this->xShift += speed;
				}

				if (event.key.code == sf::Keyboard::Right)
				{
					this->xShift -= speed;
				}

				if (event.key.code == sf::Keyboard::Up)
				{
					this->yShift += speed;
				}

				if (event.key.code == sf::Keyboard::Down)
				{
					this->yShift -= speed;
				}
			}
			else if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.delta == 1)
				{
					scale /= 2;
				}
				else
				{
					scale *= 2;
				}
			}
		}

		// clear the window with black color
		window->clear(sf::Color::Black);

		// draw everything here...
		// window.draw(...);
		setPlane();
		madePlot();

		// end the current frame
		window->display();
	}
}

void Plane::setPlane()
{
	// create and draw white field
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(width, height));
	rectangle.setFillColor(sf::Color::White);
	window->draw(rectangle);

	// create and set horizontal axis
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


	// create and set vertical axis
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


	// create arrow for vertical axis
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


	// create arrow for horizontal axis
	sf::CircleShape yArrow(10.f, 3);
	if (abs(xShift) < width / 2)
		yArrow.setPosition(sf::Vector2f(width / 2 - 10.f + xShift, 0));
	else
		if (xShift < 0)
			yArrow.setPosition(sf::Vector2f(0 - 10.f, 0));
		else
			yArrow.setPosition(sf::Vector2f(width - 10.f, 0));
	yArrow.setFillColor(sf::Color::Black);

	// create and set separators, numbers, grid for axises
	sf::RectangleShape Separation;
	sf::RectangleShape Grid;
	sf::Font font;
	sf::Text number;
	

	if (!font.loadFromFile("arial.ttf"))
	{
		throw std::exception();
	}


	Separation.setSize(sf::Vector2f(1, 6));
	Separation.setFillColor(sf::Color::Black);
	Grid.setSize(sf::Vector2f(1, height));
	Grid.setFillColor(sf::Color::Cyan);
	number.setCharacterSize(12);
	number.setFont(font);
	//number.setStyle(sf::Text::Bold);
	number.setFillColor(sf::Color::Black);
	window->draw(number);
	
	int xSepStart = abs((width / 2 + xShift) % SeparationScale);
	int ySepStart = abs((height / 2 + yShift) % SeparationScale);
	
	int sepSize = width / SeparationScale + 1;
	int numShift = (width / 2 + xShift) / SeparationScale;

	int numAxisShift;

	if (-xShift > width / 2)
	{
		xSepStart = SeparationScale - xSepStart;
		numShift--;
	}
	
	if (sepSize % 2 != 0)
	{
		sepSize++;
	}

	if (xLine.getPosition().y == 0)
		numAxisShift = 6;
	else
		numAxisShift = -18;
	
	// set vertical elements on plane
	for (int i = 0; i < sepSize; ++i)
	{
		// set separations positions
		Separation.setPosition(sf::Vector2f(xSepStart + SeparationScale * i, xLine.getPosition().y - 3));

		// set grid separations positions
		Grid.setPosition(sf::Vector2f(xSepStart + SeparationScale * i, 0));

		// draw
		window->draw(Grid);
		window->draw(Separation);

		// set numbers positions and enumerate them
		if (Separation.getPosition().x != yLine.getPosition().x)
		{
			number.setString(std::to_string((i - numShift) * scale));
			number.setPosition(sf::Vector2f(xSepStart + SeparationScale * i - 6, xLine.getPosition().y + numAxisShift));
			window->draw(number);
		}
	}

	// made separations 
	sepSize = height / SeparationScale + 2;

	Separation.rotate(90);
	Grid.setSize(sf::Vector2f(width, 1));


	numShift = (height / 2 + yShift) / SeparationScale;
	if (-yShift > height / 2)
	{
		ySepStart = SeparationScale - ySepStart;
		numShift--;
	}

	if (yLine.getPosition().x == width)
		numAxisShift = -100;
	else
		numAxisShift = 9;
	
	// set horizontal elements on plane
	for (int i = 0; i < sepSize; ++i)
	{
		// set separations positions
		Separation.setPosition(sf::Vector2f(yLine.getPosition().x + 3, ySepStart + SeparationScale * i));
		
		// set grid positions
		Grid.setPosition(sf::Vector2f(0, ySepStart + SeparationScale * i));

		// draw
		window->draw(Grid);
		window->draw(Separation);


		//set and draw numbers
		if (Separation.getPosition().y != xLine.getPosition().y)
		{
			number.setString(std::to_string(-(i - numShift) * scale));
			number.setPosition(sf::Vector2f(yLine.getPosition().x + numAxisShift + number.getCharacterSize(), ySepStart + SeparationScale * i - 8));
			window->draw(number);
		}
		
	}


	// draw lines and arrows
	window->draw(xLine);
	window->draw(yLine);
	window->draw(xArrow);
	window->draw(yArrow);
}

void Plane::madePlot()
{
	sf::VertexArray line(sf::LinesStrip, 360);

	for (int param = 0; param < 360; ++param)
	{
		float phi = (float)param * 3.14159 / 180;
		float x = width / 2 + xShift + SeparationScale * (a * cos(phi * 3) * cos(phi)) / scale;
		float y = height / 2 + yShift + SeparationScale * (a * cos(phi * 3) * sin(phi)) / scale;
		line[param].position = (sf::Vector2f(x, y));
		line[param].color = (sf::Color::Black);
	}

	window->draw(line);
}

Plane::~Plane()
{
	delete this->window;
}