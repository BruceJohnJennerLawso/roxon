// rox2d.cpp ///////////////////////////////////////////////////////////////////
// Testing bed for understanding box2d with SFML for graphics //////////////////
////////////////////////////////////////////////////////////////////////////////
//#include <std_files>
//#include "Headers.h"
//#include "Headers.hpp"
//#include "Source.cpp"
#include <iostream>
#include "roxon.hpp"


int main()
{
	// lets get this party started in here
	b2Vec2 gravity (0.0f, -9.81f);
	// welcome to Earth
	b2World world(gravity);
	
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, 0.0f);
	// create the ground and make its position 10m below whatever our origin is
	
	b2Body * groundBody = world.CreateBody(&groundBodyDef);
	// passed to the world, but world doesnt store a reference???
	// okaaay
	b2PolygonShape groundBox;
	groundBox.SetAsBox(20.0f, 10.0f);
	// a box centered around the groundBody position thats 100m wide, 20 tall
	groundBody->CreateFixture(&groundBox, 0.0f);
	// create a fixture, binding a shape to a body, ie the shape of ground box
	// bound to the static groundBodyDef
	
	// zero mass here by definition, although shouldnt it really be infinite???
	// probably wrong way of looking at it

	std::vector<roxonBox*> roxonBoxes;
	
	roxonBox body1(sf::Vector2f(0.0f, 4.0f), world, 2.0f, 2.0f, 1.0f, 0.3f, sf::Color(0, 100, 100)); 
	createRoxonBox(body1.getRoxonBoxPointer(), roxonBoxes);
	roxonBox body2(sf::Vector2f(0.0f, 6.0f), world, 2.0f, 2.0f, 1.0f, 0.3f, sf::Color(0, 0, 255)); 
	createRoxonBox(body2.getRoxonBoxPointer(), roxonBoxes);
	
	roxonBox rockOn(sf::Vector2f(5.0f, 2.0f), world, 1, 1, 2, 0.5, sf::Color(0, 255, 0));
	createRoxonBox(rockOn.getRoxonBoxPointer(), roxonBoxes);
	
	createRoxonBox(sf::Vector2f(-0.5f, 59.0f), world, 2.0f, 2.0f, 1.0f, 0.3f, sf::Color(100, 0, 100), roxonBoxes);
	
	
	
	
	
	std::string title = "Rox2D";
	sf::RenderWindow window(sf::VideoMode(600, 599), title);	
	const sf::Vector2u WSize(600,599);
	
	sf::Clock clock;
	clock.restart();
	float deltat = 0;
	// just making sure here
	sf::Vector2f initPosition(0.0f, 50.0f);
	while (window.isOpen())
	{	window.setSize(WSize);
		// force our window size to the constant size so that weird things dont
		// happen
		deltat = clock.restart().asSeconds();
		
		sf::Event event;
		while (window.pollEvent(event))
		{	if (event.type == sf::Event::Closed)
			{	window.close();
			}
			if(event.type == sf::Event::MouseButtonPressed)
			{	if(event.mouseButton.button == sf::Mouse::Button::Left)
				{	sf::Vector2i input_click = sf::Mouse::getPosition(window);
					initPosition.x = input_click.x/10 - ((float)WSize.x/20);
					initPosition.y = ((float)WSize.y/10) - input_click.y/10;	

					createRoxonBox(initPosition, world, 4.0f, 4.0f, 0.5f, 0.5f, sf::Color(std::rand()*200, std::rand()*200, std::rand()*200), roxonBoxes);
				}
				if(event.mouseButton.button == sf::Mouse::Button::Right)
				{	sf::Vector2i input_click = sf::Mouse::getPosition(window);
					initPosition.x = input_click.x/10 - ((float)WSize.x/20);
					initPosition.y = ((float)WSize.y/10) - input_click.y/10;	

					createRoxonBox(initPosition, world, 1.0f, 1.0f, 2.0f, 0.5f, sf::Color(std::rand()*200, std::rand()*200, std::rand()*200), roxonBoxes);
				}
			}
        }
		
		int32 velocityIterations = 8;
		int32 positionIterations = 3;
		world.Step(deltat, velocityIterations, positionIterations);
		
		for(std::vector<roxonBox*>::iterator it = roxonBoxes.begin(); it != roxonBoxes.end(); ++it)
		{	(*it)->setImage(WSize);
		}
	
		window.clear();
		for(std::vector<roxonBox*>::iterator it = roxonBoxes.begin(); it != roxonBoxes.end(); ++it)
		{	window.draw((*it)->boxImage);
		}
		window.display();
	}	
	return 0;
}


