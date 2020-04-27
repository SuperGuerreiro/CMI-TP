#include "ofApp.h"

#include "ScreenElements/Image.hpp"
#include "ScreenElements/Video.hpp"
#include "ScreenElements/Triangle.hpp"

#define DIRECTORY "gallery/"
#define ELEMENT_WIDTH 300
#define ELEMENT_HEIGHT 300

//--------------------------------------------------------------
void ofApp::setup(){

	isFullScreen = false;
	elements.setElementsSize(ELEMENT_WIDTH, ELEMENT_HEIGHT);

	dir.listDir(DIRECTORY);
	dir.allowExt("jpg");
	dir.allowExt("png");
	dir.allowExt("gif");
	dir.allowExt("mov");

	dir.sort();
	/*
	int x = 50;
	int y = 50;
	*/
	for(int i = 0; i < dir.size(); i++){
		string e = dir.getPath(i);
		boost::filesystem::path p(e);
		if (p.has_extension())
		{
			string ext = p.extension().string();
			if (ext == ".jpg" || ext == ".png" || ext == ".gif")
			{
				elements.add(new Image(e.c_str(), p.filename().string(), 0, 0, ELEMENT_WIDTH, ELEMENT_HEIGHT));
			}
			else if (ext == ".mov")
			{
				elements.add(new Video(e.c_str(), p.filename().string(), 0, 0, ELEMENT_WIDTH, ELEMENT_HEIGHT));
			}
			/*
			x += 50 + ELEMENT_WIDTH;
			if (x > 1300)
			{
				x = 50;
				y += 50 + ELEMENT_HEIGHT;
			}
			*/
		}
	}
	currentImage = 0;

	ofBackground(ofColor::white);


}

//--------------------------------------------------------------
void ofApp::update() {
	/*
	for each (ScreenElement* e in elements)
	{
		e->update();
	}
	*/
	elements.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	/*
	for each (ScreenElement* e in elements)
	{
		e->draw();
	}
	*/
	elements.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == OF_KEY_DOWN && dir.size() > 0) {
		currentImage++;
		//currentImage %= dir.size();

		if (currentImage >= (int)dir.size())
			currentImage = 0;
	}

	if (key == OF_KEY_UP && dir.size() > 0){
		currentImage--;
		//currentImage %= dir.size();

		if (currentImage < 0)
			currentImage = (int)dir.size() - 1;

	}
	elements.onKeyPressed(key);
	switch (key) {
	case OF_KEY_SHIFT:
		isPaused = !isPaused;
		fingerMovie.setPaused(isPaused);
		cout << "A" << endl;
		cout << elements.getSelected() << endl;
		break;

	case OF_KEY_LEFT:
		isFullScreen = !isFullScreen;
		cout << isFullScreen << endl;
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
	elements.onClick(x, y, button);
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
	elements.setSize(w, h);
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
