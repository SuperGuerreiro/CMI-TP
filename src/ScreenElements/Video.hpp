#pragma once

#include "ScreenElement.hpp"

class Video : public ScreenElement
{
public:
	Video() = default;
	Video(const char* path, std::string name, int xOffset, int yOffset, int width, int height);

	void update() override;
	void draw() override;

	void setOffset(int xOffset, int yOffset) override;
	void setSize(int width, int height) override;
	void setFillMode(bool fill) override;
	ElementType getType() override { return ElementType::Video; };

private:
	int xOffset;
	int yOffset;
	int width;
	int height;
	bool fillMode;

	std::string name;
	ofVideoPlayer self;
};