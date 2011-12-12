#include "GridNode.h"
#include "GameWindow.h"
#include "cmath"

GridNode::GridNode(Point location, Colour colour, double size)
	: 
	currentLocation(location),
	defaultLocation(location),
	currentColour(colour), 
	defaultColour(colour),
	size(size), 
	maximumSpeed(0.50),
	maximumSpeedChange(0.03), 
	maximumDistanceFromDefault(0.50),
	maximumDistanceOfInfluence(1.70)

{
	textureID = ResourceCache::getTextureID("resources/gridParticle.png");
	edge = false;
}

void GridNode::draw() const
{
	if(isOnScreen())
	{
		glPushMatrix();
		glTranslatef(currentLocation.x, currentLocation.y, 0);
		//glRotatef(angle + textureAngleOffset, 0, 0, 1);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glBegin(GL_QUADS);
		{
		    glNormal3f(0, 0, 1);
		    glTexCoord2f(0, 0); glVertex3f(-size, size, 0.01);
		    glTexCoord2f(0, 1); glVertex3f(-size, -size, 0.01);
		    glTexCoord2f(1, 1); glVertex3f(size, -size, 0.01);
		    glTexCoord2f(1, 0); glVertex3f(size, size, 0.01);
		}
		glEnd();
		glPopMatrix();
	}
}

bool GridNode::isOnScreen() const
{
	Point viewLocation = parent->getViewLocation();
	double leftEdge = viewLocation.x - Globals::viewWidth/2;
	double rightEdge = viewLocation.x + Globals::viewWidth/2;
	double upperEdge = viewLocation.y + Globals::viewHeight/2;
	double bottomEdge = viewLocation.y - Globals::viewHeight/2;

	if(currentLocation.x < leftEdge || currentLocation.x > rightEdge 
		|| currentLocation.y < bottomEdge || currentLocation.y > upperEdge)
		return false;
	else
		return true;
}

void GridNode::update()
{
	if(!edge)
	{
		performRepulsions();
		moveToDefault();
		clampToPlayArea();
	}
}

void GridNode::performRepulsions()
{
	std::vector<Projectile*> projectiles = parent->getProjectiles();
	Vector totalInfluence = Vector(0,0,0);
	
	for(unsigned i = 0; i < projectiles.size(); i++)
	{
		if(fabs((projectiles.at(i))->getLocation().x - currentLocation.x) > maximumDistanceOfInfluence)
			continue;
		if(fabs((projectiles.at(i))->getLocation().y - currentLocation.y) > maximumDistanceOfInfluence)
			continue;
				
		double distance = (projectiles.at(i))->getLocation().distance(currentLocation);
		if(distance < maximumDistanceOfInfluence)
		{
			Vector influence = Vector((projectiles.at(i))->getLocation(), currentLocation).setNorm(.4/(distance+1));
			totalInfluence = totalInfluence + influence;
		}
	}
	
	// capuje totalInfluence normu na maximumRepulsionSpeed
	if(totalInfluence.norm() > 0.2)
		totalInfluence = totalInfluence.setNorm(0.2);
	
	// ne dozvoljava cvoru da se odmakne od default lokacije za vise od maximumDistanceFromDefault
	if(currentLocation.translate(totalInfluence).distance(defaultLocation) < maximumDistanceFromDefault)
	{
		currentLocation = currentLocation.translate(totalInfluence.getX(), totalInfluence.getY());
		currentMotion = Vector(0, 0, 0);
	}
}

void GridNode::moveToDefault()
{
	// if current locaton of grid node is diferent from default location, 
	//we need to move current location in the direction of the default
	if(currentLocation != defaultLocation)
	{
		// racunamo vektor od trenutne ka default lokaciji
		Vector direction = Vector(currentLocation, defaultLocation).setNorm(maximumSpeedChange);
		
		// ako je vektor kretanja (0, 0), to znaci da je ovo prvi update u kom se vracamo
		// ka default poziciji. Trenutno kretanje treba postaviti na max u tom slucaju.
		//if(currentMotion == Vector(0, 0, 0))
			//currentMotion = direction.setNorm(maximumSpeed-0.2);
		// postavljamo ga na maximumSpeedChange duzine i dodajemo na trenutni vektor kretanja
		//else
			currentMotion = currentMotion + direction;
			
		// ako smo prekoracili maks brzinu, opet capujemo
		if(currentMotion.norm() > maximumSpeed)
			currentMotion =	currentMotion.setNorm(maximumSpeed);
			
		// ukoliko se odmicemo od default lokacije, usporimo za dodatni faktor
		double oldDistance = defaultLocation.distance(currentLocation);
		double newDistance = defaultLocation.distance(
			currentLocation.translate(currentMotion.getX(), currentMotion.getY()));
		if(oldDistance < newDistance)
			currentMotion = currentMotion.setNorm(0.9 * currentMotion.norm());
		
		// transliramo trenutnu poziciju za vektor kretanja. ako smo se kretali ka 
		// default tacci, ovo nas ubrzava, inace, usporava/okrece u suprotnom smeru
		currentLocation = currentLocation.translate(currentMotion.getX(), currentMotion.getY());
		
		// ukoliko su trenutna i default lokacija blizu, i brzina kretanja (norma vektora
		// kretanja) mala, postaviti trenutnu lokaciju na default, vektor kretanja na (0, 0)
		if(currentLocation.distance(defaultLocation) < 0.05 && currentMotion.norm() < 0.1)
		{
			currentMotion = Vector(0, 0, 0);
			currentLocation = defaultLocation;
		}
	}
}

void GridNode::clampToPlayArea()
{
	if(currentLocation.x < -Globals::worldWidth/2)
		currentLocation.x = -Globals::worldWidth/2;
	
	if(currentLocation.x > Globals::worldWidth/2)
		currentLocation.x = Globals::worldWidth/2;
	
	if(currentLocation.y < -Globals::worldHeight/2)
		currentLocation.y = -Globals::worldHeight/2;
	
	if(currentLocation.y > Globals::worldHeight/2)
		currentLocation.y = Globals::worldHeight/2;
}

void GridNode::setLocation(const Point& location)
{
	defaultLocation = currentLocation = location;
}

void GridNode::setLocationX(double x)
{
	defaultLocation.x = currentLocation.x = x;
}

void GridNode::setLocationY(double y)
{
	defaultLocation.y = currentLocation.y = y;
}

void GridNode::setColour(const Colour& colour)
{
	defaultColour = currentColour = colour;
}

void GridNode::setSize(double size)
{
	this->size = size;
}

void GridNode::setParent(GameWindow* parent)
{
	this->parent = parent;
}

const Point& GridNode::getLocation() const
{
	return currentLocation;
}

void GridNode::setEdge(bool edge)
{
	this->edge = edge;
}









