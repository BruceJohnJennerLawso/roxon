// roxon.cpp ///////////////////////////////////////////////////////////////////
// wrapping up Box2D, Ooobject oriented style //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//#include <std_files>
//#include "Headers.h"
//#include "Source.c"

//#include "Headers.hpp"
//#include "Source.cpp"
#include "roxon.hpp"

// roxonBox ////////////////////////////////////////////////////////////////////
// wrapper for a box in box 2d /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

roxonBox::roxonBox()
{
}

roxonBox::roxonBox(sf::Vector2f initialPosition, b2World &world, float width, float height, float density, float friction, sf::Color boxColor)
{	bodyDef.type = b2_dynamicBody;
	// set  our bodydef type as dynamicBody, so its dynamic
	bodyDef.position.Set(initialPosition.x, initialPosition.y);
	// set our position to what, 14 m above the ground I think?
	body = world.CreateBody(&bodyDef);
	// create a b2Body pointer using the output from the world creating it using
	// the defs that we supplied
	
	dynamicBox.SetAsBox(width/2, height/2);
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = density;
	fixtureDef.friction = friction;
	body->CreateFixture(&fixtureDef);
	// and somehow append the fixtureDef to our lovel
	
	// umm... I have no Idea what that was supposed to mean, but lets keep
	// going...

	
	boxImage.setSize(sf::Vector2f(width*10, height*10));
	boxImage.setFillColor(boxColor);
	boxImage.setOrigin(sf::Vector2f(width*5, height*5));	
	// okay, that works much better
	
}

void roxonBox::setImage(const sf::Vector2u windowSize)
{	b2Vec2 position = body->GetPosition();
	float32 angle = body->GetAngle();
		
	boxImage.setPosition(((position.x*10) + ((float)windowSize.x/2)),((float)windowSize.y - (position.y*10)));
	boxImage.setRotation(radiansAsDegrees(-angle));
	// weird that the sign was off here... I would think we could all at least
	// stick to clockwise positive as a convention...
}

roxonBox * roxonBox::getRoxonBoxPointer()
{	return this;
}

roxonBox::~roxonBox()
{	//delete body;
	// this... umm, we will have to see what effect this has on the simulation
	// as a whole. I doubt it can be good...

	// fine, we'll just leak memory then
	// see if I care
}

void createRoxonBox(sf::Vector2f initialPosition, b2World &world, float width, float height, float density, float friction, sf::Color boxColor, std::vector<roxonBox*> &boxList)
{	roxonBox * newRoxonBoxon = new roxonBox(initialPosition, world, width, height, density, friction, boxColor);
	boxList.insert(boxList.end(), newRoxonBoxon);
}

void createRoxonBox(roxonBox * new_this, std::vector<roxonBox*> &boxList)
{	boxList.insert(boxList.end(), new_this);
}


float radiansAsDegrees(float radians)
{	radians /= (2*Pi);
	radians *= 360;
	return radians;
}
