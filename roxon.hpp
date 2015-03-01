// roxon.hpp ///////////////////////////////////////////////////////////////////
// wrapping up Box2D, Ooobject oriented style //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//#include <std_files>
//#include "Headers.h"
//#include "Source.c"

//#include "Headers.hpp"
//#include "Source.cpp"
#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>

#define Pi 3.141592654

class roxonGround
{
};

class roxonBox
{	public:
	roxonBox();
	roxonBox(sf::Vector2f initialPosition, b2World &world, float width, float height, float density, float friction, sf::Color boxColor);
	
	b2BodyDef bodyDef;
	b2Body * body;
	b2PolygonShape dynamicBox;
	b2FixtureDef fixtureDef;
	
	sf::RectangleShape boxImage;
	
	void setImage(const sf::Vector2u windowSize);
	roxonBox * getRoxonBoxPointer();
	
	~roxonBox();
};

void createRoxonBox(sf::Vector2f initialPosition, b2World &world, float width, float height, float density, float friction, sf::Color boxColor, std::vector<roxonBox*> &boxList);
void createRoxonBox(roxonBox * new_this, std::vector<roxonBox*> &boxList);

float radiansAsDegrees(float radians);

