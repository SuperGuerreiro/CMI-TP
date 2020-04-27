#pragma once

#include "ScreenElement.hpp"

class Triangle : public ScreenElement
{
public:
	Triangle() = default;
	Triangle(int xOffset, int yOffset, int size, float rotation, ofColor color);

	void update() override;
	void draw() override;

	void setOffset(int xOffset, int yOffset) override;
	void setSize(int width, int height) override;
	void setFillMode(bool fill) override;

	bool onClick(int x, int y, int button) override;

	const inline ElementType getType() const override { return ElementType::Triangle; };
	const inline std::string getName() const override { return ""; };

	void setRotation(float rotation);

private:
	int xOffset;
	int yOffset;
	int size;
	float rotation;
	ofColor color;
};