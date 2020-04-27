#include "Video.hpp"

Video::Video(const char* path, std::string name, int xOffset, int yOffset, int width, int height)
	: name(name), xOffset(xOffset), yOffset(yOffset), width(width), height(height)
{
	self = ofVideoPlayer();
	self.load(path);

	self.setLoopState(OF_LOOP_NORMAL);
	//self.firstFrame();
	self.play();
	fillMode = false;
}

void Video::update()
{
	self.update();
}

void Video::draw()
{
	//ofSetColor(ofColor::black);							//These 2 lines draw a black rectangle behind the element for placement purposes only
	//ofDrawRectangle(xOffset, yOffset, width, height);	//TODO: remove in the final build

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

void Video::setOffset(int xOffset, int yOffset)
{
	this->xOffset = xOffset;
	this->yOffset = yOffset;
}

void Video::setSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void Video::setFillMode(bool fill)
{
	fillMode = fill;
}

bool Video::onClick(int x, int y, int button)
{
	return x >= xOffset && x <= xOffset + width && y >= yOffset && y <= yOffset + height;
}
