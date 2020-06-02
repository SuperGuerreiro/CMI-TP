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
	Button* tb = new Button(0, 0, 0, 0, "Browse", ofColor::black, ofColor::lightGray, [this] { currentView = PresentMode::Gallery; });
	td->addElement(tb, tb->getName().length() * CHAR_WIDTH);
	tb = new Button(0, 0, 0, 0, "Display", ofColor::black, ofColor::lightGray, [this] { currentView = PresentMode::ViewItem; });
	td->addElement(tb, tb->getName().length() * CHAR_WIDTH);
	tb = new Button(0, 0, 0, 0, "Properties", ofColor::black, ofColor::lightGray, [this] { currentView = PresentMode::ItemProperties; });
	td->addElement(tb, tb->getName().length() * CHAR_WIDTH);
	topbar.addElement(td, td->getName().length() * CHAR_WIDTH);
	tb = new Button(0, 0, 0, 0, "Presentation Mode", ofColor::white, ofColor::cornflowerBlue, [this] {  });
	topbar.addElement(tb, tb->getName().length() * CHAR_WIDTH);
	tb = new Button(0, 0, 0, 0, "CamMode", ofColor::white, ofColor::cornflowerBlue, [this] { currentView = PresentMode::Camera; });
	topbar.addElement(tb, tb->getName().length() * CHAR_WIDTH);

	dir.listDir(DIRECTORY);
	dir.allowExt("jpg");
	dir.allowExt("png");
	//dir.allowExt("gif");
	dir.allowExt("mov");
	dir.allowExt("mp4");

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
			else if (ext == ".mov" || ext == ".mp4")
			{
				Video* t = new Video(pathname, 0, 0, ELEMENT_WIDTH, ELEMENT_HEIGHT);
				elements.add(t);
				explorer.add(t);
				index++;
			}
		}
	}

	propertiesScreen.add(new Text("THIS IS A TEXT\nA REALLY BIG TEXT\nNOW TELL ME WHAT YOU WANT\nWHAT YOU REALLY REALLY WANT", ofColor::black, 0 + 10, TOPBAR_HEIGHT + 10));
	propertiesScreen.add(new Text("Add/Remove Tags:", ofColor::black, 0, 0));
	propertiesScreen.add(new Button(0, 0, 12 + (7 * CHAR_WIDTH), 12 + CHAR_HEIGHT, "Add Tag", ofColor::white, ofColor::cornflowerBlue, [this]
	{
		if (elements.getSelectedIndex() != -1)
		{
			std::string tag = ofSystemTextBoxDialog("New Tag", "");
			if (tag != "")
			{
				explorer[elements.getSelectedIndex()]->addTag(tag);
				//explorer.addTag(elements.getSelectedIndex(), tag);
				updateFileProperties();
			}
		}
	}));
	propertiesScreen.add(new Group());
	//explorer[0]->addTag("xisde");
	//explorer.addTag(0, "EXXDEEEE");
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
		if (elements.getSelectedIndex() != -1)
		{
			elements[elements.getSelectedIndex()]->draw(width - ELEMENT_WIDTH - 10, TOPBAR_HEIGHT + 10, ELEMENT_WIDTH, ELEMENT_HEIGHT);
		}
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
			
			//If user is in gallery, video shows thumbnail
			if (elements[elements.getSelectedIndex()]->getType() == ElementType::Video) {
				Video* tmp = (Video*)elements[elements.getSelectedIndex()];
				tmp->setFullScreen(false);
			}
		}
		else
		{
			currentView = PresentMode::ViewItem;

			//EdgeHistogram e = EdgeHistogram((Image*)elements[elements.getSelectedIndex()]);

			//If user chooses fullscreen mode, video starts playing
			if (elements[elements.getSelectedIndex()]->getType() == ElementType::Video) {
				Video* tmp = (Video*)elements[elements.getSelectedIndex()];
				tmp->setFullScreen(true);
			}
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
	resizeFileProperties();
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
	Group* g = (Group*)propertiesScreen[3];
	g->clear();
	Text* t = (Text*)propertiesScreen[0];
	int index = elements.getSelectedIndex();
	if (index != -1)
	{
		Item* cur = explorer[index];
		t->setText(cur->getPropertyString());
		std::vector<std::string> tags = cur->getTags();
		for each (std::string tag in tags)
		{
			g->add(new Button(0, 0, 12 + (tag.length() * CHAR_WIDTH), 12 + CHAR_HEIGHT, tag, ofColor::white, ofColor::red, [this, cur, tag]
			{
				cur->removeTag(tag);
				updateFileProperties();
			}));
		}
		resizeFileProperties();
	}
	else
	{
		t->setText("No file selected.");
	}
}

void ofApp::resizeFileProperties()
{
	propertiesScreen[1]->setOffset(10, height / 2);
	propertiesScreen[2]->setOffset(10, height - 22 - CHAR_HEIGHT);
	Group* g = (Group*)propertiesScreen[3];
	int nTags = g->getNumElements();
	int x = 10;
	int y = height / 2 + 20;
	for (int i = 0; i < nTags; i++)
	{
		(*g)[i]->setOffset(x, y);
		x += (*g)[i]->getName().length() * CHAR_WIDTH + 22;
		if (x > width / 2)
		{
			x = 10;
			y += 32;
		}
	}
}
