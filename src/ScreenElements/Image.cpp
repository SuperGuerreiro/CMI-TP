#include "Image.hpp"

Image::Image(const char* path, int xOffset, int yOffset, int width, int height)
	: xOffset(xOffset), yOffset(yOffset), width(width), height(height)
{
	self = ofImage();
	self.load(path);
	fillMode = false;
}

void Image::update()
{
	self.update();
}

void Image::draw()
{
	ofSetColor(ofColor::black);							//These 2 lines draw a black rectangle behind the element for placement purposes only
	ofDrawRectangle(xOffset, yOffset, width, height);	//TODO: remove in the final build

	ofSetColor(ofColor::white);
	if (fillMode)
	{
		self.draw(xOffset, yOffset, width, height);
	}
	else
	{
		size_t x = self.getPixels().getWidth();
		size_t y = self.getPixels().getHeight();
		float sourceAR = (float)x / y;
		float displayAR = (float)width / height;
		if (sourceAR < displayAR)
		{
			int nWidth = width * sourceAR;
			self.draw(xOffset + ((width - nWidth) * 0.5), yOffset, nWidth, height);
		}
		else
		{
			int nHeight = height / sourceAR;
			self.draw(xOffset, yOffset + ((height - nHeight) * 0.5), width, nHeight);
		}
	}
}

void Image::setOffset(int xOffset, int yOffset)
{
	this->xOffset = xOffset;
	this->yOffset = yOffset;
}

void Image::setSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void Image::setFillMode(bool fill)
{
	fillMode = fill;
}
