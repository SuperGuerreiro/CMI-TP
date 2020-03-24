#pragma once

#include "ScreenElement.hpp"

class Video : public ScreenElement
{
public:
	Video() = default;
	Video(const char* path, int xOffset, int yOffset, int width, int height);

	void update() override;
	void draw() override;

	void setOffset(int xOffset, int yOffset) override;
	void setSize(int width, int height) override;
	void setFillMode(bool fill) override;

private:
	int xOffset;
	int yOffset;
	int width;
	int height;
	bool fillMode;

	ofVideoPlayer self;
};