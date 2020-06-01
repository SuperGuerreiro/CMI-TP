#include "Image.hpp"

Image::Image(std::string pathname, int xOffset, int yOffset, int width, int height)
	: xOffset(xOffset), yOffset(yOffset), width(width), height(height)
{
	boost::filesystem::path path(pathname);
	name = path.filename().string();
	self = ofImage();
	self.load(pathname);
	fillMode = false;
	updateDrawValues();
}

void Image::update()
{
	self.update();
}

void Image::draw()
{
	ofSetColor(ofColor::white);
	if (fillMode)
	{
		self.draw(xOffset, yOffset, width, height);
	}
	else
	{
		self.draw(nXOffset, nYOffset, nWidth, nHeight);
	}
}

void Image::draw(int xOffset, int yOffset, int width, int height)
{
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
		int nWidth = width;
		int nHeight = height;
		if (y < nHeight)
		{
			nHeight = y;
			nWidth = x;
			if (width < nWidth)
			{
				float ratio = (float)width / nWidth;
				nWidth = width;
				nHeight = ratio * nHeight;
			}
		}
		else if (x < nWidth)
		{
			nHeight = y;
			nWidth = x;
			if (height < nHeight)
			{
				float ratio = (float)height / nHeight;
				nHeight = height;
				nWidth = ratio * nWidth;
			}
		}
		else
		{
			if (sourceAR < displayAR)
			{
				nWidth = height * sourceAR;
			}
			else
			{
				nHeight = width / sourceAR;
			}
		}
		self.draw(xOffset + ((width - nWidth) * 0.5), yOffset + ((height - nHeight) * 0.5), nWidth, nHeight);
	}
}

void Image::setOffset(int xOffset, int yOffset)
{
	this->xOffset = xOffset;
	this->yOffset = yOffset;
	updateDrawValues();
}

void Image::setSize(int width, int height)
{
	this->width = width;
	this->height = height;
	updateDrawValues();
}

void Image::setFillMode(bool fill)
{
	fillMode = fill;
}

bool Image::onClick(int x, int y, int button)
{
	return x >= xOffset && x <= xOffset + width && y >= yOffset && y <= yOffset + height;
}

void Image::updateDrawValues()
{
	size_t x = self.getPixels().getWidth();
	size_t y = self.getPixels().getHeight();
	float sourceAR = (float)x / y;
	float displayAR = (float)width / height;
	int nWidth = width;
	int nHeight = height;
	if (y < nHeight)
	{
		nHeight = y;
		nWidth = x;
		if (width < nWidth)
		{
			float ratio = (float)width / nWidth;
			nWidth = width;
			nHeight = ratio * nHeight;
		}
	}
	else if (x < nWidth)
	{
		nHeight = y;
		nWidth = x;
		if (height < nHeight)
		{
			float ratio = (float)height / nHeight;
			nHeight = height;
			nWidth = ratio * nWidth;
		}
	}
	else
	{
		if (sourceAR < displayAR)
		{
			nWidth = height * sourceAR;
		}
		else
		{
			nHeight = width / sourceAR;
		}
	}
	this->nWidth = nWidth;
	this->nHeight = nHeight;
	this->nXOffset = xOffset + ((width - nWidth) * 0.5);
	this->nYOffset = yOffset + ((height - nHeight) * 0.5);
}
