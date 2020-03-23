#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	isFullScreen = false;

	dir.listDir("images/of_logos/");
	dir.allowExt("jpg");
	dir.allowExt("mov");

	dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order

	//allocate the vector to have as many ofImages as files
	if( dir.size() ){
		images.assign(dir.size(), ofImage());
	}

	// you can now iterate through the files and load them into the ofImage vector
	for(int i = 0; i < (int)dir.size(); i++){
		images[i].load(dir.getPath(i));

// Uncomment this to show movies with alpha channels
 //fingerMovie.setPixelFormat(OF_PIXELS_RGBA);

		fingerMovie.load("images/of_logos/fingers.mov");
		fingerMovie.setLoopState(OF_LOOP_NORMAL);
		fingerMovie.play();
		isPaused = true;
		fingerMovie.setPaused(isPaused);
	}
	currentImage = 0;

	ofBackground(ofColor::white);


}

//--------------------------------------------------------------
void ofApp::update() {
	fingerMovie.update();
}

//--------------------------------------------------------------
void ofApp::draw() {

	if (dir.size() > 0) {
		ofSetColor(ofColor::white);
		if (currentImage < (int)dir.size() - 1); {
			images[currentImage].draw(300, 50);
			if ((currentImage + 5) < (int)dir.size()) {
				images[currentImage + 1].draw(610, 50);
				images[currentImage + 2].draw(920, 50);
				images[currentImage + 3].draw(300, 310);
				images[currentImage + 4].draw(610, 310);
				images[currentImage + 5].draw(920, 310);
			}
		}

		if (currentImage == (int)dir.size() - 1) {
			//VIDEO STUFF HERE

			ofSetHexColor(0xFFFFFF);
			ofPixels & pixels = fingerMovie.getPixels();

			int vidWidth = pixels.getWidth();
			int vidHeight = pixels.getHeight();
			int nChannels = pixels.getNumChannels();

			if (!isFullScreen)
				fingerMovie.draw(300, 50, 100, 100);
			else
				fingerMovie.draw(300, 50, vidWidth, vidHeight);
			
			ofSetHexColor(0x000000);


			if (fingerMovie.getIsMovieDone()) {
				ofSetHexColor(0xFF0000);
				ofDrawBitmapString("end of movie", 20, 440);
			}
		}

		//ofSetColor(ofColor::gray);
		//string pathInfo = dir.getName(currentImage) + " " + dir.getPath(currentImage) + "\n\n" +
		//	"press any key to advance current image\n\n" +
		//	"many thanks to hikaru furuhashi for the OFs";
		//ofDrawBitmapString(pathInfo, 300, images[currentImage].getHeight() + 80);
	}

	ofSetColor(ofColor::gray);
	for (int i = 0; i < (int)dir.size(); i++) {
		if (i == currentImage) {
			ofSetColor(ofColor::red);
		}
		else {
			ofSetColor(ofColor::black);
		}

		string fileInfo = "file " + ofToString(i + 1) + " = " + dir.getName(i);
		ofDrawBitmapString(fileInfo, 50, i * 20 + 50);
		
		
	}

	/*
	currImg = images[currentImage];

	if (!isFullScreen) {
		currImg.draw(300, 50, currImg.getWidth(), currImg.getHeight());
	}

	if (isFullScreen) {
		currImg.draw(300, 50);
	}
	
	*/
	
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

	switch (key) {
	case OF_KEY_SHIFT:
		isPaused = !isPaused;
		fingerMovie.setPaused(isPaused);
		cout << "A" << endl;
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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
