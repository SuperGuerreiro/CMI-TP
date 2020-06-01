#include "Video.hpp"

Video::Video(std::string pathname, int xOffset, int yOffset, int width, int height)
	: xOffset(xOffset), yOffset(yOffset), width(width), height(height)
{
	boost::filesystem::path path(pathname);
	name = path.filename().string();
	self = ofVideoPlayer();
	self.load(pathname);

	self.setLoopState(OF_LOOP_NORMAL);
	//self.firstFrame();
	//self.play();
	generateThumbnailFrames();

	isFullScreen = false;
	//drawThumbnail();
	//saveFrame(self.getCurrentFrame())
	fillMode = false;
	currTime = 0;
	currThumb = 0;
	updateDrawValues();
}

void Video::update()
{
	//self.update();

	currTime++;

	//If in fullScreen, plays video
	if (isFullScreen) {
		//self.play();
		//self.setPaused(false);
		self.update();
	}
	else {
		//Gallery Mode: Shows Thumbnails
		
		//Shows currThumbnail for a given time frame
		if (currTime > INTERVAL_TIME) {

			drawThumbnail(thumbnailFrames[currThumb++]);
			if (currThumb == thumbnailFrames.size()) {
				currThumb = 0;
			}
			currTime = 0;
		}
	}

}

void Video::draw()
{
	ofSetColor(ofColor::white);
	if (fillMode)
	{
		self.draw(xOffset, yOffset, width, height);
	}
	else
	{
		self.draw(nXOffset, nYOffset, nWidth, nHeight);
	}
	if (!isFullScreen)
	{
		ofSetColor(ofColor::black);
		ofDrawTriangle(v1, v2, v3);
	}
}

void Video::draw(int xOffset, int yOffset, int width, int height)
{

	ofSetColor(ofColor::white);
	if (fillMode)
	{
		self.draw(xOffset, yOffset, width, height);

	}
	else
	{
		size_t x = self.getPixels().getWidth();
		size_t y = self.getPixels().getHeight();
		float sourceAR = (float)x / y;
		float displayAR = (float)width / height;
		int nWidth = width;
		int nHeight = height;
		if (y < nHeight)
		{
			nHeight = y;
			nWidth = x;
			if (width < nWidth)
			{
				float ratio = (float)width / nWidth;
				nWidth = width;
				nHeight = ratio * nHeight;
			}
		}
		else if (x < nWidth)
		{
			nHeight = y;
			nWidth = x;
			if (height < nHeight)
			{
				float ratio = (float)height / nHeight;
				nHeight = height;
				nWidth = ratio * nWidth;
			}
		}
		else
		{
			if (sourceAR < displayAR)
			{
				nWidth = height * sourceAR;
			}
			else
			{
				nHeight = width / sourceAR;
			}
		}
		self.draw(xOffset + ((width - nWidth) * 0.5), yOffset + ((height - nHeight) * 0.5), nWidth, nHeight);
	}
}

void Video::setOffset(int xOffset, int yOffset)
{
	this->xOffset = xOffset;
	this->yOffset = yOffset;
	updateDrawValues();
}

void Video::setSize(int width, int height)
{
	this->width = width;
	this->height = height;
	updateDrawValues();
}

void Video::setFillMode(bool fill)
{
	fillMode = fill;
}

bool Video::onClick(int x, int y, int button)
{
	return x >= xOffset && x <= xOffset + width && y >= yOffset && y <= yOffset + height;
}

void Video::updateDrawValues()
{
	size_t x = self.getPixels().getWidth();
	size_t y = self.getPixels().getHeight();
	float sourceAR = (float)x / y;
	float displayAR = (float)width / height;
	int nWidth = width;
	int nHeight = height;
	if (y < nHeight)
	{
		nHeight = y;
		nWidth = x;
		if (width < nWidth)
		{
			float ratio = (float)width / nWidth;
			nWidth = width;
			nHeight = ratio * nHeight;
		}
	}
	else if (x < nWidth)
	{
		nHeight = y;
		nWidth = x;
		if (height < nHeight)
		{
			float ratio = (float)height / nHeight;
			nHeight = height;
			nWidth = ratio * nWidth;
		}
	}
	else
	{
		if (sourceAR < displayAR)
		{
			nWidth = height * sourceAR;
		}
		else
		{
			nHeight = width / sourceAR;
		}
	}
	this->nWidth = nWidth;
	this->nHeight = nHeight;
	this->nXOffset = xOffset + ((width - nWidth) * 0.5);
	this->nYOffset = yOffset + ((height - nHeight) * 0.5);
	
	int tWidth = width / 4;
	int tHeight = height / 5;
	int hPadding = (width - tWidth) / 2;
	int vPadding = (height - tHeight) / 2;
	v1 = glm::vec2(xOffset + hPadding, yOffset + vPadding);
	v2 = glm::vec2(xOffset + hPadding + tWidth, yOffset + vPadding + tHeight / 2);
	v3 = glm::vec2(xOffset + hPadding, yOffset + vPadding + tHeight);
}

void Video::drawThumbnail(int frame) {

	self.setPaused(false);
	self.setFrame(frame);
	self.setPaused(true);
	self.update();
	/*while (!self.isFrameNew() && frame < self.getTotalNumFrames() - 1) {
		self.update();
	}
	*/
	/*
	for (int i = 0; i < 10; i++) {
		self.setFrame(frame);

		ofImage curr;
		curr.setFromPixels(self.getPixels());
		curr.save(i+"screenshot.jpg");
		thumbnail.push_back(curr);

		frame += totalFrames / 10;
	}


	/*
	while (frame < totalFrames) {
		printf("Frame: %d", frame);
		self.setPaused(false);
		self.setFrame(frame);
		
		self.setPaused(true);
		self.update();
		
		frame += totalFrames / 10;

		if (frame >= (totalFrames / 10) * 8)
			frame = 0;
	}
	*/
}

void Video::generateThumbnailFrames() {
	int totalFrames = self.getTotalNumFrames();
	int frame = 1;

	for (int i = 0; i < 10; i++) {
		thumbnailFrames.push_back(frame);
		frame += totalFrames / 10;
	}
}

void Video::setFullScreen(bool bFullScreen) {
	isFullScreen = bFullScreen;
	self.firstFrame();
	if (bFullScreen)
	{
		self.play();
		self.setPaused(false);
	}
}

float Video::getRuntime() {
	return self.getDuration();
}