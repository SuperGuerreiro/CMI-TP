#pragma once

#include "ScreenElement.hpp"

class Image : public ScreenElement
{
public:
	Image() = default;
	Image(const char* path, int xOffset, int yOffset, int width, int height);

	void update() override;
	void draw() override;

	void setOffset(int xOffset, int yOffset) override;
	void setSize(int width, int height) override;
	void setFillMode(bool fill) override;

private:
	int xOffset;
	int yOffset;
	unsigned int width;
	unsigned int height;
	bool fillMode;

	ofImage self;
};