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
	void draw(int xOffset, int yOffset, int width, int height) override;

	void setOffset(int xOffset, int yOffset) override;
	void setSize(int width, int height) override;
	void setFillMode(bool fill) override;

	bool onClick(int x, int y, int button) override;

	const inline ElementType getType() const override { return ElementType::Collection; };
	const inline std::string getName() const override { return ""; };

	void add(ScreenElement* e);
	void onKeyPressed(int key);
	void setElementsSize(int width, int height);
	void scroll(float value);

	inline int getSelectedIndex() const { return selected; };
	inline ScreenElement* operator[](int i) const { return elements[i]; };
	inline void select(int i) { selected = i; };

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
