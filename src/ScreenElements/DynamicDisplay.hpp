#pragma once

#include "ScreenElement.hpp"
#include "Image.hpp"
#include "Video.hpp"
#include "Collection.hpp"
#include "Camera.hpp"
#include "../Explorer/Explorer.hpp"

class DynamicDisplay : public ScreenElement
{
public:
	DynamicDisplay() = default;
	DynamicDisplay(int xOffset, int yOffset, int width, int height, Collection* collection, Camera* cam, Explorer* explorer);
	~DynamicDisplay() = default;

	void update() override;
	void draw() override;
	void draw(int xOffset, int yOffset, int width, int height) override;

	void setOffset(int xOffset, int yOffset) override;
	void setSize(int width, int height) override;
	void setFillMode(bool fill) override;

	bool onClick(int x, int y, int button) override;

	const inline ElementType getType() const override { return ElementType::DynamicDisplay; };
	const inline std::string getName() const override { return ""; };

private:
	int xOffset;
	int yOffset;
	int width;
	int height;

	Collection* elements;
	Camera* cam;
	Explorer* explorer;

	std::vector<int> playlist;
	int viewers = 0;
};