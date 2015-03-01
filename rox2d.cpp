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
	groundBodyDef.position.Set(0.0f, -10.0f);
	// create the ground and make its position 10m below whatever our origin is
	
	b2Body * groundBody = world.CreateBody(&groundBodyDef);
	// passed to the world, but world doesnt store a reference???
	// okaaay
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	// a box centered around the groundBody position thats 100m wide, 20 tall
	groundBody->CreateFixture(&groundBox, 0.0f);
	// create a fixture, binding a shape to a body, ie the shape of ground box
	// bound to the static groundBodyDef
	
	// zero mass here by definition, although shouldnt it really be infinite???
	// probably wrong way of looking at it
	
	
	
	
	
	
	
	b2BodyDef bodyDef1;
	// create our soon to be dynamic object
	bodyDef1.type = b2_dynamicBody;
	// set its type as dynamicBody, so its dynamic
	bodyDef1.position.Set(0.0f, 4.0f);
	// set our position to what, 14 m above the ground I think?
	b2Body * body1 = world.CreateBody(&bodyDef1);
	// create a b2Body pointer using the output from the world creating it using
	// the defs that we supplied
	
	b2PolygonShape dynamicBox1;
	dynamicBox1.SetAsBox(1.0f, 1.0f);
	// uh, so a box 2m square
	b2FixtureDef fixtureDef1;
	fixtureDef1.shape = &dynamicBox1;
	fixtureDef1.density = 1.0f;
	fixtureDef1.friction = 0.3f;
	body1->CreateFixture(&fixtureDef1);
	// and somehow append the fixtureDef to our lovel

	roxonBox body1(sf::Vector2f(0.0f, 6.0f), world, 2.0f, 2.0f, 1.0f, 0.3f, sf::Color(0, 0, 255)); 
	
	roxonBox body2(sf::Vector2f(0.0f, 6.0f), world, 2.0f, 2.0f, 1.0f, 0.3f, sf::Color(0, 0, 255)); 
	
	
	roxonBox rockOn(sf::Vector2f(5.0f, 2.0f), world, 1, 1, 2, 0.5, sf::Color(0, 255, 0));
	
	
	
	
	
	
	
	
	float32 timeStep = 1.0f/60.0f;
	// so we run at 60fps, not unexpected
	// ie the literal length of the frame
	
	int32 velocityIterations = 8;
	int32 positionIterations = 3;
	
	std::string title = "Rox2D";
	sf::RenderWindow window(sf::VideoMode(600, 599), title);
	
	sf::RectangleShape rect_image1(sf::Vector2f(20,20));
	// we'll do this scaled up by 10x so its easier to see
	rect_image1.setFillColor(sf::Color(0,0,255));
	// lancelots favourite colour
	rect_image1.setOrigin(sf::Vector2f(10, 10));
	// center the rectangle so that we are drawing to center of mass?
	// I think Box2D works this way
	
	sf::RectangleShape rect_image2(sf::Vector2f(20,20));
	// we'll do this scaled up by 10x so its easier to see
	rect_image2.setFillColor(sf::Color(0,0,255));
	// lancelots favourite colour
	rect_image2.setOrigin(sf::Vector2f(10, 10));
	// center the rectangle so that we are drawing to center of mass?
	// I think Box2D works this way
	
	
	
	const sf::Vector2u WSize(600,599);
	
	sf::Clock clock;
	clock.restart();
	float deltat = 0;
	// just making sure here
	while (window.isOpen())
	{	window.setSize(WSize);
		// force our window size to the constant size so that weird things dont
		// happen
		deltat = clock.restart().asSeconds();
		
		world.Step(deltat, velocityIterations, positionIterations);
		
		
		b2Vec2 position1 = body1->GetPosition();
		float32 angle1 = body1->GetAngle();
		
		rect_image1.setPosition(((position1.x*10) + 300),(599 - (position1.y*10)));
		rect_image1.setRotation(radiansAsDegrees(-angle1));
		
		b2Vec2 position2 = body2->GetPosition();
		float32 angle2 = body2->GetAngle();
		
		rect_image2.setPosition(((position2.x*10) + 300),(599 - (position2.y*10)));
		rect_image2.setRotation(radiansAsDegrees(-angle2));		
		
		rockOn.setImage(WSize);
		
		
		sf::Event event;
		while (window.pollEvent(event))
		{	if (event.type == sf::Event::Closed)
			{	window.close();
			}
        }
        

		window.clear();
		window.draw(rect_image1);
		window.draw(rect_image2);		
		window.draw(rockOn.boxImage);
		window.display();
	}	
	return 0;
}


