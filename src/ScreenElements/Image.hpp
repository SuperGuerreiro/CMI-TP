#pragma once

#include "ScreenElement.hpp"

class Image : public ScreenElement
{
public:
	Image() = default;
	Image(std::string pathname, int xOffset, int yOffset, int width, int height);

	void update() override;
	void draw() override;
	void draw(int xOffset, int yOffset, int width, int height) override;

	void setOffset(int xOffset, int yOffset) override;
	void setSize(int width, int height) override;
	void setFillMode(bool fill) override;

	bool onClick(int x, int y, int button) override;

	const inline ElementType getType() const override { return ElementType::Image; };
	const inline std::string getName() const override { return name; };


private:
	int xOffset;
	int yOffset;
	int width;
	int height;
	bool fillMode;

	std::string name;
	ofImage self;
};