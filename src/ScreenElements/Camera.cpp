#include "Camera.hpp"

Camera::Camera()
{

}

void Camera::setup(int camWidth, int camHeight)
{

	this->camWidth = camWidth;
	this->camHeight = camHeight;

	vidGrabber.setVerbose(true);
	vidGrabber.setup(camWidth, camHeight);

	ofEnableAlphaBlending();

	//Needs this file to detect
	finder.setup("haarcascade_frontalface_alt.xml");

	currTime = 0;

	ofBackground(ofColor::white);
}

Camera::Camera(int camWidth, int camHeight)
	: camWidth(camWidth), camHeight(camHeight)
{

}

void Camera::update() {
	vidGrabber.update();
	currTime++;
}

void Camera::draw() 
{
	vidGrabber.draw(xOffset, yOffset);
	detectFaces(vidGrabber.getPixels());

}

void Camera::draw(int xOffset, int yOffset, int width, int height)
{
}

void Camera::detectFaces(ofPixels videoPixels)
{
	//Finds faces in a given interval of frames
	if (currTime > INTERVAL_TIME) {
		finder.findHaarObjects(videoPixels);
		currTime = 0;
	}

	ofNoFill(); //To draw square unfilled
	for (unsigned int i = 0; i < finder.blobs.size(); i++) {
		ofRectangle cur = finder.blobs[i].boundingRect;
		ofDrawRectangle(cur.x + xOffset, cur.y + yOffset, cur.width, cur.height);
	}

	ofFill();
}

void Camera::setOffset(int xOffset, int yOffset)
{
	this->xOffset = xOffset;
	this->yOffset = yOffset;
}

void Camera::setSize(int width, int height)
{
	
}

void Camera::setFillMode(bool fill)
{
}

bool Camera::onClick(int x, int y, int button)
{
	return false;
}
