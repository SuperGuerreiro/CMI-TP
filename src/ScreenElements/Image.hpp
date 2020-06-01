#pragma once

#include "ScreenElement.hpp"

class Image : public ScreenElement
{
public:
	Image() = default;
	Image(std::string pathname, int xOffset, int yOffset, int width, int height);

	void update() override;
	void draw() override;
	void draw(int xOffset, int yOffset, int width, int height) override;

	void setOffset(int xOffset, int yOffset) override;
	void setSize(int width, int height) override;
	void setFillMode(bool fill) override;

	bool onClick(int x, int y, int button) override;

	const inline ElementType getType() const override { return ElementType::Image; };
	const inline std::string getName() const override { return name; };

	inline ofImage& getOFHandle() { return self; };
	const inline int getId() const { return id; };
	inline void setId(int newId) { id = newId; };


private:
	int xOffset;
	int yOffset;
	int width;
	int height;
	bool fillMode;

	std::string name;
	ofImage self;
	int id = -1;


	int nXOffset, nYOffset, nWidth, nHeight;
	void updateDrawValues();
};