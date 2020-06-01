#pragma once

#include "ScreenElement.hpp"

class Button : public ScreenElement
{
public:
	Button();
	Button(int xOffset, int yOffset, int width, int height, std::string name, ofColor color, ofColor bgColor, SimpleCallback callback);
	~Button();

	void update() override;
	void draw() override;
	void draw(int xOffset, int yOffset, int width, int height) override;

	void setOffset(int xOffset, int yOffset) override;
	void setSize(int width, int height) override;
	void setFillMode(bool fill) override;

	bool onClick(int x, int y, int button) override;

	const inline ElementType getType() const override { return ElementType::Button; };
	const inline std::string getName() const override { return name; };


private:
	int xOffset;
	int yOffset;
	int width;
	int height;
	std::string name;
	ofColor color;
	ofColor bgColor;

	SimpleCallback callback;
};