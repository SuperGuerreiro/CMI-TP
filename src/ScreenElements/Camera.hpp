#pragma once

#include "ScreenElement.hpp"
#include "ofxCvHaarFinder.h"

class Camera : public ScreenElement
{
public:
	Camera();
	Camera(int camWidth, int camHeight);

	void setup(int camWidth, int camHeight);

	void update() override;
	void draw() override;
	void draw(int xOffset, int yOffset, int width, int height) override;
	void detectFaces(ofPixels videoPixels);

	void setOffset(int xOffset, int yOffset) override;
	void setSize(int width, int height) override;
	void setFillMode(bool fill) override;

	bool onClick(int x, int y, int button) override;

	const inline ElementType getType() const override { return ElementType::Camera; };
	const inline std::string getName() const override { return ""; };

	inline int getNumFaces() { return finder.blobs.size(); };

	void getProps(float* brightness, float* hue);

private:

	int xOffset;
	int yOffset;
	int camWidth;
	int camHeight;

	std::string name;
	ofColor color;

	ofVideoGrabber vidGrabber;
	//bool camDebug;

	const unsigned int INTERVAL_TIME = 10;

	ofImage screenCap;
	ofxCvHaarFinder finder;
	unsigned int currTime, intervalTime;


};