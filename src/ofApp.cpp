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
	cam.setOffset(10, 10 + TOPBAR_HEIGHT);

	display = DynamicDisplay(0, TOPBAR_HEIGHT, 100, 100, &elements, &cam, &explorer);

	fillToggle = Button(0, 0, 12 + 15 * CHAR_WIDTH, 12 + CHAR_HEIGHT, "Toggle Stretch", ofColor::white, ofColor::cornflowerBlue, [this] { fill = !fill; elements.setFillMode(fill); });

	Dropdown* td = new Dropdown(0, 0, 0, 0, "File", ofColor::white, ofColor::cornflowerBlue);
	Button* tb = new Button(0, 0, 0, 0, "Browse", ofColor::black, ofColor::lightGray, [this] { currentView = PresentMode::Gallery; });
	td->addElement(tb, tb->getName().length() * CHAR_WIDTH);
	tb = new Button(0, 0, 0, 0, "Display", ofColor::black, ofColor::lightGray, [this] { currentView = PresentMode::ViewItem; });
	td->addElement(tb, tb->getName().length() * CHAR_WIDTH);
	tb = new Button(0, 0, 0, 0, "Properties", ofColor::black, ofColor::lightGray, [this] { currentView = PresentMode::ItemProperties; });
	td->addElement(tb, tb->getName().length() * CHAR_WIDTH);
	topbar.addElement(td, td->getName().length() * CHAR_WIDTH);
	tb = new Button(0, 0, 0, 0, "Presentation Mode", ofColor::white, ofColor::cornflowerBlue, [this] 
	{
		if (currentView != PresentMode::Showcase)
		{
			currentView = PresentMode::Showcase;
			explorer.generatePlaylists();
			elements.select(0);
		}
	});
	topbar.addElement(tb, tb->getName().length() * CHAR_WIDTH);
	tb = new Button(0, 0, 0, 0, "CamMode", ofColor::white, ofColor::cornflowerBlue, [this] { currentView = PresentMode::Camera; });
	topbar.addElement(tb, tb->getName().length() * CHAR_WIDTH);

	dir.listDir(DIRECTORY);
	dir.allowExt("jpg");
	dir.allowExt("png");
	//dir.allowExt("gif");
	dir.allowExt("mov");
	dir.allowExt("mp4");
	dir.allowExt("webm");

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
			else if (ext == ".mov" || ext == ".mp4" || ext == ".webm")
			{
				Video* t = new Video(pathname, 0, 0, ELEMENT_WIDTH, ELEMENT_HEIGHT);
				elements.add(t);
				explorer.add(t);
				index++;
			}
		}
	}

	propertiesScreen.add(new Text("No file selected.", ofColor::black, 0 + 10, TOPBAR_HEIGHT + 10));
	propertiesScreen.add(new Text("Add/Remove Tags:", ofColor::black, 0, 0));
	propertiesScreen.add(new Button(0, 0, 12 + (7 * CHAR_WIDTH), 12 + CHAR_HEIGHT, "Add Tag", ofColor::white, ofColor::cornflowerBlue, [this]
	{
		if (elements.getSelectedIndex() != -1)
		{
			std::string tag = ofSystemTextBoxDialog("New Tag", "");
			if (tag != "")
			{
				explorer[elements.getSelectedIndex()]->addTag(tag);
			}
		}
	}));
	propertiesScreen.add(new Group());
}

//--------------------------------------------------------------
void ofApp::update() {
	topbar.update();
	int i = elements.getSelectedIndex();
	switch (currentView)
	{
	case PresentMode::Gallery:
		elements.update();
		break;
	case PresentMode::ViewItem:
		if (play && i != -1)
		{
			elements[i]->update();
		}
		fillToggle.update();
		break;
	case PresentMode::ItemProperties:
		propertiesScreen.update();
		if (i != -1)
		{
			elements[i]->update();
		}
		break;
	case PresentMode::Camera:
		cam.update();
		break;
	case PresentMode::Showcase:
		if (play)
		{
			display.update();
		}
		fillToggle.update();
		break;
	default:
		break;
	}
	handleTransition();
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
		fillToggle.draw();
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
	case PresentMode::Showcase:
		display.draw();
		fillToggle.draw();
		break;
	default:
		break;
	}
	topbar.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (currentView != PresentMode::Showcase && currentView != PresentMode::Camera)
	{
		elements.onKeyPressed(key);
	}
	switch (key) 
	{
	case OF_KEY_RETURN: //return = enter
		currentView = PresentMode::ViewItem;
		break;
	case OF_KEY_BACKSPACE:
		currentView = PresentMode::Gallery;
		break;
	case 32: //space
		if (elements.getSelectedIndex() != -1 && elements[elements.getSelectedIndex()]->getType() == ElementType::Video)
		{
			((Video*)elements[elements.getSelectedIndex()])->getOFHandle().setPaused(play);
		}
		play = !play;
		break;
	case 100: // d
		currentView = PresentMode::Camera;
		break;
	case 111: // o
		currentView = PresentMode::ItemProperties;
		break;
	case 112: // p
		if (currentView != PresentMode::Showcase)
		{
			currentView = PresentMode::Showcase;
			explorer.generatePlaylists();
			elements.select(0);
		}
		break;
	case 102: // f
		if (currentView == PresentMode::Showcase || currentView == PresentMode::ViewItem)
		{
			fill = !fill;
			elements.setFillMode(fill);
		}
		break;
	default:
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
			break;
		case PresentMode::ItemProperties:
			propertiesScreen.onClick(x, y, button); 
		case PresentMode::ViewItem:
		case PresentMode::Showcase:
			fillToggle.onClick(x, y, button);
			break;
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
	display.setSize(w, h - TOPBAR_HEIGHT);
	fillToggle.setOffset(width - (22 + 15 * CHAR_WIDTH), height - (22 + CHAR_HEIGHT));
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



void ofApp::handleTransition()
{
	if (elements.getSelectedIndex() != -1)
	{
		if (currentView != lastView)
		{
			if (currentView == PresentMode::ViewItem || currentView == PresentMode::Showcase)
			{
				if (elements[elements.getSelectedIndex()]->getType() == ElementType::Video)
				{
					((Video*)elements[elements.getSelectedIndex()])->setFullScreen(true);
				}
				elements.setFillMode(fill);
			}
			else if (lastView == PresentMode::ViewItem || lastView == PresentMode::Showcase)
			{
				if (elements[elements.getSelectedIndex()]->getType() == ElementType::Video)
				{
					((Video*)elements[elements.getSelectedIndex()])->setFullScreen(false);
				}
				elements.setFillMode(false);
			}
			play = true;
			lastView = currentView;
		}
		if (lastElement != elements.getSelectedIndex())
		{
			updateFileProperties();
			if (currentView == PresentMode::ViewItem || currentView == PresentMode::Showcase)
			{
				if (lastElement != -1 && elements[lastElement]->getType() == ElementType::Video)
				{
					((Video*)elements[lastElement])->setFullScreen(false);
				}
				if (elements[elements.getSelectedIndex()]->getType() == ElementType::Video)
				{
					((Video*)elements[elements.getSelectedIndex()])->setFullScreen(true);
				}
			}
			play = true;
			lastElement = elements.getSelectedIndex();
		}
	}
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
