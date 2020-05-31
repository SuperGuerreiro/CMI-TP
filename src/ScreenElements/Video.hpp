#pragma once

#include "ScreenElement.hpp"

class Video : public ScreenElement
{
public:
	Video() = default;
	Video(std::string pathname, int xOffset, int yOffset, int width, int height);

	void update() override;
	void draw() override;
	void draw(int xOffset, int yOffset, int width, int height) override;

	void setOffset(int xOffset, int yOffset) override;
	void setSize(int width, int height) override;
	void setFillMode(bool fill) override;

	void drawThumbnail(int frame);
	void generateThumbnailFrames();
	void setFullScreen(bool bFullScreen);


	bool onClick(int x, int y, int button) override;

	const inline ElementType getType() const override { return ElementType::Video; };
	const inline std::string getName() const override { return name; };

	inline ofVideoPlayer& getOFHandle() { return self; };
	const inline int getId() const { return id; };
	inline void setId(int newId) { id = newId; };

private:
	int xOffset;
	int yOffset;
	int width;
	int height;
	int currThumb;
	
	int currTime;
	const unsigned int INTERVAL_TIME = 10;


	bool fillMode;
	bool isFullScreen;

	std::string name;
	std::vector<ofImage> thumbnail;
	std::vector<int> thumbnailFrames;
	ofVideoPlayer self;
	int id = -1;
};