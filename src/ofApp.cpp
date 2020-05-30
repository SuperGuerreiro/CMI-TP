#include "ofApp.h"

#include "ScreenElements/Image.hpp"
#include "ScreenElements/Video.hpp"
#include "ScreenElements/Triangle.hpp"
#include "ScreenElements/Dropdown.hpp"
#include "ScreenElements/Button.hpp"

#define DIRECTORY "gallery/"
#define ELEMENT_WIDTH 300
#define ELEMENT_HEIGHT 300
#define TOPBAR_HEIGHT 32

//--------------------------------------------------------------
void ofApp::setup(){
	currentView = PresentMode::Gallery;
	elements.setElementsSize(ELEMENT_WIDTH, ELEMENT_HEIGHT);
	elements.setOffset(0, TOPBAR_HEIGHT);

	cam.setup(640, 480);

	Dropdown* td = new Dropdown(0, 0, 0, 0, "File", ofColor::white);
	Button* tb = new Button(0, 0, 0, 0, "Display", ofColor::black, [this] { currentView = PresentMode::ViewItem; });
	td->addElement(tb, tb->getName().length() * CHAR_WIDTH);
	tb = new Button(0, 0, 0, 0, "Details", ofColor::black, [] {});
	td->addElement(tb, tb->getName().length() * CHAR_WIDTH);
	tb = new Button(0, 0, 0, 0, "Test", ofColor::black, [] {});
	td->addElement(tb, tb->getName().length() * CHAR_WIDTH);
	topbar.addElement(td, td->getName().length() * CHAR_WIDTH);
	tb = new Button(0, 0, 0, 0, "CamMode", ofColor::white, [this] { currentView = PresentMode::Camera; });
	topbar.addElement(tb, tb->getName().length() * CHAR_WIDTH);

	dir.listDir(DIRECTORY);
	dir.allowExt("jpg");
	dir.allowExt("png");
	//dir.allowExt("gif");
	dir.allowExt("mov");

	dir.sort();
	int index = -1;
	for(int i = 0; i < dir.size(); i++){
		string pathname = dir.getPath(i);
		boost::filesystem::path p(pathname);
		if (p.has_extension())
		{
			string ext = p.extension().string();
			if (ext == ".jpg" || ext == ".png" || ext == ".gif")
			{
				Image* t = new Image(pathname, 0, 0, ELEMENT_WIDTH, ELEMENT_HEIGHT);
				elements.add(t);
				explorer.add(t);
				index++;
			}
			else if (ext == ".mov")
			{
				Video* t = new Video(pathname, 0, 0, ELEMENT_WIDTH, ELEMENT_HEIGHT);
				elements.add(t);
				explorer.add(t);
				index++;
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	topbar.update();
	elements.update();
	cam.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	switch (currentView)
	{
	case PresentMode::Gallery:
		elements.draw();
		topbar.draw();
		break;
	case PresentMode::ViewItem:
		if (elements.getSelectedIndex() != -1)
		{
			elements[elements.getSelectedIndex()]->draw(0, 0, width, height);
		}
		break;
	case PresentMode::Camera:
		cam.draw();
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	elements.onKeyPressed(key);
	switch (key) {
	case OF_KEY_RETURN: //return = enter
		if (currentView == PresentMode::ViewItem)
		{
			currentView = PresentMode::Gallery;
		}
		else
		{
			currentView = PresentMode::ViewItem;
		}
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (!topbar.onClick(x, y, button))
	{
		elements.onClick(x, y, button);
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	width = w;
	height = h;
	topbar.setSize(w, TOPBAR_HEIGHT);
	elements.setSize(w, h - TOPBAR_HEIGHT);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){
	elements.scroll(scrollY);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
