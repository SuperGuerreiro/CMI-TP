#include "ofApp.h"

#include "ScreenElements/Image.hpp"
#include "ScreenElements/Video.hpp"
#include "ScreenElements/Triangle.hpp"
#include "ScreenElements/Dropdown.hpp"
#include "ScreenElements/Button.hpp"
#include "ScreenElements/Text.hpp"

#define DIRECTORY "gallery/"
#define ELEMENT_WIDTH 300
#define ELEMENT_HEIGHT 300
#define TOPBAR_HEIGHT 32

//--------------------------------------------------------------
void ofApp::setup(){
	currentView = PresentMode::Gallery;
	elements.setElementsSize(ELEMENT_WIDTH, ELEMENT_HEIGHT);
	elements.setOffset(0, TOPBAR_HEIGHT);

	cam.setup(320, 240);

	Dropdown* td = new Dropdown(0, 0, 0, 0, "File", ofColor::white, ofColor::cornflowerBlue);
	Button* tb = new Button(0, 0, 0, 0, "Browse", ofColor::black, [this] { currentView = PresentMode::Gallery; });
	td->addElement(tb, tb->getName().length() * CHAR_WIDTH);
	tb = new Button(0, 0, 0, 0, "Display", ofColor::black, [this] { currentView = PresentMode::ViewItem; });
	td->addElement(tb, tb->getName().length() * CHAR_WIDTH);
	tb = new Button(0, 0, 0, 0, "Properties", ofColor::black, [this] { currentView = PresentMode::ItemProperties; });
	td->addElement(tb, tb->getName().length() * CHAR_WIDTH);
	topbar.addElement(td, td->getName().length() * CHAR_WIDTH);
	tb = new Button(0, 0, 0, 0, "Presentation Mode", ofColor::white, [this] {  });
	topbar.addElement(tb, tb->getName().length() * CHAR_WIDTH);
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

	propertiesScreen.add(new Text("THIS IS A TEXT\nA REALLY BIG TEXT\nNOW TELL ME WHAT YOU WANT\nWHAT YOU REALLY REALLY WANT", ofColor::black, 0 + 10, TOPBAR_HEIGHT + 10));
	propertiesScreen.add(new Text("Tags:\n - Viewers:\n - tag_1:\n - tag_2:\n - tag_3:\n - tag_4:\n - tag_5:\n - tag_6:\n - tag_7:", ofColor::black, 0, 0));
	Dropdown* dd = new Dropdown(0, 0, 0, 0, "0", ofColor::white, ofColor::cornflowerBlue);
	Button* b = new Button(0, 0, 0, 0, "Any", ofColor::black, [] {});
	dd->addElement(b, b->getName().length() * CHAR_WIDTH);
	Button* b = new Button(0, 0, 0, 0, "0", ofColor::black, [] {});
	dd->addElement(b, b->getName().length() * CHAR_WIDTH);
	Button* b = new Button(0, 0, 0, 0, "1", ofColor::black, [] {});
	dd->addElement(b, b->getName().length() * CHAR_WIDTH);
	Button* b = new Button(0, 0, 0, 0, "2", ofColor::black, [] {});
	dd->addElement(b, b->getName().length() * CHAR_WIDTH);
	Button* b = new Button(0, 0, 0, 0, "3", ofColor::black, [] {});
	dd->addElement(b, b->getName().length() * CHAR_WIDTH);
	propertiesScreen.add(dd);
	//ofSystemTextBoxDialog();
}

//--------------------------------------------------------------
void ofApp::update() {
	topbar.update();
	elements.update();
	cam.update();
	propertiesScreen.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	switch (currentView)
	{
	case PresentMode::Gallery:
		elements.draw();
		break;
	case PresentMode::ViewItem:
		if (elements.getSelectedIndex() != -1)
		{
			elements[elements.getSelectedIndex()]->draw(0, TOPBAR_HEIGHT, width, height - TOPBAR_HEIGHT);
		}
		break;
	case PresentMode::Camera:
		cam.draw();
		break;
	case PresentMode::ItemProperties:
		propertiesScreen.draw();
		break;
	default:
		break;
	}
	topbar.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	elements.onKeyPressed(key);
	updateFileProperties();
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
		switch (currentView)
		{
		case PresentMode::Gallery:
			elements.onClick(x, y, button);
			updateFileProperties();
			break;
		case PresentMode::ItemProperties:
			propertiesScreen.onClick(x, y, button);
		default:
			break;
		}
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
	propertiesScreen[1]->setOffset(10, height / 2);
	propertiesScreen[2]->setOffset(10 + CHAR_WIDTH * 12, height / 2 + (15 * 1));
	propertiesScreen[2]->setSize(CHAR_WIDTH * 4, CHAR_HEIGHT);
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



void ofApp::updateFileProperties()
{
	if (elements.getSelectedIndex() != -1)
	{
		Text* t = (Text*)propertiesScreen[0];
		t->setText(explorer[elements.getSelectedIndex()].getPropertyString());
	}
}
