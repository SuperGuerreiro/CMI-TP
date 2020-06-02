#pragma once

#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "../ScreenElements/Image.hpp"
#include "../ScreenElements/Video.hpp"
#include <math.h>




class EdgeHistogram {

public:
	EdgeHistogram(Image* image);
	EdgeHistogram(Video* video);

	

private:
	int width, height;
	int nRows, mCols;

	std::vector<cv::Mat> imgChunks;

	const int NUM_BLOCKS = 16;
	const int SUBDIVISIONS = 4;

	std::vector<cv::Mat> tmpFilterResult;
};