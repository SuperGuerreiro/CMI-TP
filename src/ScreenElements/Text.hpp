#pragma once

#include "ScreenElement.hpp"

class Text : public ScreenElement
{
public:
	Text();
	Text(std::string text, ofColor color, int xOffset, int yOffset);
	~Text();

	void update() override;
	void draw() override;
	void draw(int xOffset, int yOffset, int width, int height) override;

	void setOffset(int xOffset, int yOffset) override;
	void setSize(int width, int height) override;
	void setFillMode(bool fill) override;

	bool onClick(int x, int y, int button) override;

	const inline ElementType getType() const override { return ElementType::Text; };
	const inline std::string getName() const override { return ""; };

	inline void setText(std::string text) { this->text = text; };
	inline void setColor(ofColor color) { this->color = color; };


private:
	int xOffset, yOffset;
	std::string text;
	ofColor color;
};