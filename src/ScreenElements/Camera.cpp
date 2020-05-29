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
	finder.setup("haarcascade_frontalface_default.xml");

	currTime = 0;
	intervalTime = 60;

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
	vidGrabber.draw(0, 0);

	if (currTime > intervalTime) {
		screenCap.grabScreen(0, 0, camWidth, camHeight);
		screenCap.save("screenshot.jpg");
		screenCap.load("screenshot.jpg");
		finder.findHaarObjects(screenCap);

		currTime = 0;
	}

	ofNoFill(); //To draw sqared unfilled
	for (unsigned int i = 0; i < finder.blobs.size(); i++) {
		ofRectangle cur = finder.blobs[i].boundingRect;
		//ofSetColor(ofColor::black);
		ofDrawRectangle(cur.x, cur.y, cur.width, cur.height);
	}
	
	ofFill();
}

void Camera::draw(int xOffset, int yOffset, int width, int height)
{
}

void Camera::detectFaces()
{
}

void Camera::setOffset(int xOffset, int yOffset)
{
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
