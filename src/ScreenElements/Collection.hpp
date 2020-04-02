#pragma once

#include "ScreenElement.hpp"

class Collection : public ScreenElement
{
public:
	Collection();
	Collection(int xOffset, int yOffset, int width, int height, int elementWidth, int elementHeight, int padding);
	~Collection();

	void update() override;
	void draw() override;

	void setOffset(int xOffset, int yOffset) override;
	void setSize(int width, int height) override;
	void setFillMode(bool fill) override;
	ElementType getType() override { return ElementType::Collection; };

	void add(ScreenElement* e);
	void setElementsSize(int width, int height);
	void scroll(float value);

private:
	int xOffset;
	int yOffset;
	int width;
	int height;
	int elementWidth;
	int elementHeight;
	int padding;
	int selected;

	int perRow;
	float scrollVal;
	float scrollMult;
	int scrollOffset;
	int spacing;

	std::vector<ScreenElement*> elements;

	void resetAttributes();
};
