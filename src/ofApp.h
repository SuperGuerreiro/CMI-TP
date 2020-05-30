#pragma once

#include "ofMain.h"
#include "ScreenElements/Collection.hpp"
#include "ScreenElements/TopBar.hpp"
#include "ScreenElements/Camera.hpp"
#include "Explorer/Explorer.hpp"
#include "ofxXmlSettings.h"



enum class PresentMode
{
	None = 0,
	Gallery,
	ViewItem,
	Camera
};

class ofApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		
		void mouseScrolled(int x, int y, float scrollX, float scrollY);
		
		// we will have a dynamic number of images, based on the content of a directory:
		ofDirectory dir;
		vector<ofImage> images;
		
		ofxXmlSettings XML;
		ofColor a;

		ofImage currImg;
		int currentImage;

		ofVideoPlayer 		fingerMovie;
		bool                isPaused;
		bool				isFullScreen;

		PresentMode currentView = PresentMode::None;
		/*
		//WebCam
		ofVideoGrabber vidGrabber;
		int camWidth;
		int camHeight;
		bool camDebug;

		ofImage screenCap;
		ofxCvHaarFinder finder;
		unsigned int currTime, intervalTime;
		*/

		Camera cam;

		//vector<ScreenElement*> elements;
		TopBar topbar;
		Collection elements;
		Explorer explorer;
		int width, height;
};
