#pragma once

#include "ScreenElement.hpp"

class Dropdown : public ScreenElement
{
public:
	Dropdown();
	Dropdown(int xOffset, int yOffset, int width, int height, std::string name, ofColor color);
	~Dropdown();

	void update() override;
	void draw() override;
	void draw(int xOffset, int yOffset, int width, int height) override;

	void setOffset(int xOffset, int yOffset) override;
	void setSize(int width, int height) override;
	void setFillMode(bool fill) override;

	bool onClick(int x, int y, int button) override;

	const inline ElementType getType() const override { return ElementType::Dropdown; };
	const inline std::string getName() const override { return name; };

	void addElement(ScreenElement* element, int length);
	inline ScreenElement* operator[](int i) const { return elements[i]; };


private:
	int xOffset;
	int yOffset;
	int width;
	int height;
	std::string name;
	ofColor color;

	int maxElementWidth = 0;
	int totalHeight = 0;

	bool drawElements;
	std::vector<ScreenElement*> elements;

	void resetAttributes();
};