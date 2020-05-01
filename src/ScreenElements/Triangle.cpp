#include "Triangle.hpp"

Triangle::Triangle(int xOffset, int yOffset, int size, float rotation, ofColor color)
	: xOffset(xOffset), yOffset(yOffset), size(size), color(color)
{
	this->rotation = PI * 2 * rotation;
}

void Triangle::update()
{

}

void Triangle::draw()
{
	ofSetColor(color);
	ofDrawTriangle(glm::vec2(xOffset + cos(rotation) * size, yOffset + sin(rotation) * size), 
		glm::vec2(xOffset + cos((PI / 3) * 2 + rotation) * size, yOffset + sin((PI / 3) * 2 + rotation) * size), 
		glm::vec2(xOffset + cos((PI / 3) * 4 + rotation) * size, yOffset + sin((PI / 3) * 4 + rotation) * size));
}

void Triangle::draw(int xOffset, int yOffset, int width, int height)
{
	//TODO: width/height based on parameters
}

void Triangle::setRotation(float rotation)
{
	this->rotation = PI * 2 * rotation;
}

void Triangle::setOffset(int xOffset, int yOffset)
{
	this->xOffset = xOffset;
	this->yOffset = yOffset;
}

void Triangle::setSize(int width, int height)
{
	this->size = std::min(width, height) * 2;
}

void Triangle::setFillMode(bool fill)
{
}

bool Triangle::onClick(int x, int y, int button)
{
	return false;
}