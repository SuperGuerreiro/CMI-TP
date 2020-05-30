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
		
		ofDirectory dir;

		PresentMode currentView = PresentMode::None;

		Camera cam;
		TopBar topbar;
		Collection elements;
		Explorer explorer;
		int width, height;
};
