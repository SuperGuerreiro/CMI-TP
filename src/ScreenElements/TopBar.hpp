#pragma once

#include "ScreenElement.hpp"

class TopBar : public ScreenElement
{
public:
	TopBar();
	TopBar(int xOffset, int yOffset, int width, int height, int padding, int hPadding);
	~TopBar();

	void update() override;
	void draw() override;
	void draw(int xOffset, int yOffset, int width, int height) override;

	void setOffset(int xOffset, int yOffset) override;
	void setSize(int width, int height) override;
	void setFillMode(bool fill) override;

	bool onClick(int x, int y, int button) override;

	const inline ElementType getType() const override { return ElementType::TopBar; };
	const inline std::string getName() const override { return ""; };

	void addElement(ScreenElement* element, int width);
	inline ScreenElement* operator[](int i) const { return tabs[i]; };


private:
	int xOffset;
	int yOffset;
	int width;
	int height;
	int padding;
	int hPadding;

	std::vector<ScreenElement*> tabs;
	std::vector<int> tabLengths;

	void resetAttributes();
};