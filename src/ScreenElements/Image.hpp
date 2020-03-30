#pragma once

#include "ScreenElement.hpp"

class Image : public ScreenElement
{
public:
	Image() = default;
	Image(const char* path, std::string name, int xOffset, int yOffset, int width, int height);

	void update() override;
	void draw() override;

	void setOffset(int xOffset, int yOffset) override;
	void setSize(int width, int height) override;
	void setFillMode(bool fill) override;
	ElementType getType() override { return ElementType::Image; };

private:
	int xOffset;
	int yOffset;
	int width;
	int height;
	bool fillMode;

	std::string name;
	ofImage self;
};