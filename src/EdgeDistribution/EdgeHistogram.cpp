#include "EdgeHistogram.hpp"

using namespace cv;
using namespace ofxCv;

EdgeHistogram::EdgeHistogram(Image* image) {

	ofImage img = image->getOFHandle();
	Mat imgMat = toCv(img);

	Point anchor = Point(-1, -1);
	double delta = 0;
	int ddepth = -1;

	gaborKernels = getGaborKernels();

	//Split Image into chunks

	width = image->getOFHandle().getWidth();
	height = image->getOFHandle().getHeight();

	/*Since we're splitting the image into a 4x4 (16 chunks), we can have images that are not divisible by this number
	in order to account for that, we simply ignore some outmost pixels so that the division is possible */

	//This will give us a value without the decimal part
	int widthBlock = width / SUBDIVISIONS;
	int heightBlock = height / SUBDIVISIONS;

	//This will give us both the width and height without the decimal part
	int widthInt = widthBlock * SUBDIVISIONS;
	int heightInt = heightBlock * SUBDIVISIONS;

	Mat maskImg = imgMat.clone(); //For visualization
	try {
		
		for (int y = 0; y < heightInt; y += heightBlock) {
			for (int x = 0; x < widthInt; x += widthBlock) {
				
				imgChunks.push_back(imgMat(Rect(x, y, widthBlock, heightBlock)).clone());

				//Visualization
				/*rectangle(maskImg, Point(x, y), Point(x + widthBlock - 1, y + heightBlock - 1), CV_RGB(255, 0, 0), 1); 
				ofImage test;
				toOf(maskImg, test);
				test.save("test.jpg");
				*/
			}
		}
	}
	catch (cv::Exception & e) 
	{
		cerr << e.msg << endl; // output exception message
	}

	//Define Kernels
	float k1data[] = { 1, -1, 1, -1 };
	float k2data[] = { 1, 1, -1, -1 };
	float k3data[] = { sqrt(2), 0, 0, -sqrt(2) };
	float k4data[] = { 0, sqrt(2), -sqrt(2), 0 };
	float k5data[] = { 2, -2, -2, 2 };

	Mat verticalKernel(2, 2, CV_32F, k1data);
	Mat horizontalKernel(2, 2, CV_32F, k2data);
	Mat FrtyFveDgrKernel(2, 2, CV_32F, k3data);
	Mat oneHndrdThrtyFvDgrKernel(2, 2, CV_32F, k4data);
	Mat nonDirectionalKernel(2, 2, CV_32F, k5data);

	Mat res;
	Mat res01;
	Mat res02;
	Mat res03;
	Mat res04;

	//Apply Filters
	try {
		for (int i = 0; i < imgChunks.size(); i++) {

			//Edge Histogram
			filter2D(imgChunks[i], res, ddepth, verticalKernel, anchor, delta, BORDER_DEFAULT);
			tmpFilterResult.push_back(res);

			filter2D(imgChunks[i], res01, ddepth, horizontalKernel, anchor, delta, BORDER_DEFAULT);
			tmpFilterResult.push_back(res01);

			filter2D(imgChunks[i], res02, ddepth, FrtyFveDgrKernel, anchor, delta, BORDER_DEFAULT);
			tmpFilterResult.push_back(res02);

			filter2D(imgChunks[i], res03, ddepth, oneHndrdThrtyFvDgrKernel, anchor, delta, BORDER_DEFAULT);
			tmpFilterResult.push_back(res03);

			filter2D(imgChunks[i], res04, ddepth, nonDirectionalKernel, anchor, delta, BORDER_DEFAULT);
			tmpFilterResult.push_back(res04);

			//Max in each pixel for the edge histogram
			Mat currMax;

			cv::max(tmpFilterResult[0], cv::max(tmpFilterResult[1],
				cv::max(tmpFilterResult[2], cv::max(tmpFilterResult[3], tmpFilterResult[4]))), currMax);


			//TEXTURE HISTOGRAM
			//Apply all the Gabor Kernels in each image block
			std::vector<cv::Mat> gaborRes;
			for (int l = 0; l < gaborKernels.size(); l++){
				Mat gabRes;
				filter2D(imgChunks[i], gabRes, ddepth, gaborKernels[l], anchor, delta, BORDER_DEFAULT);
				gaborRes.push_back(gabRes);
			}


			//This is dumb, but it's late
			Mat currGaborMax;
			cv::max(gaborRes[0], cv::max(gaborRes[1],
				cv::max(gaborRes[2], cv::max(gaborRes[3],
					cv::max(gaborRes[4], cv::max(gaborRes[5], cv::max(gaborRes[6],
						cv::max(gaborRes[7], cv::max(gaborRes[8], cv::max(gaborRes[9], cv::max(gaborRes[10],
							cv::max(gaborRes[11], cv::max(gaborRes[12], cv::max(gaborRes[13], cv::max(gaborRes[14],
								cv::max(gaborRes[15], cv::max(gaborRes[16], cv::max(gaborRes[17], cv::max(gaborRes[18],
									cv::max(gaborRes[19], cv::max(gaborRes[20], cv::max(gaborRes[21], cv::max(gaborRes[22],
										cv::max(gaborRes[23], gaborRes[24]))))))))))))))))))))))), currGaborMax);

			ofImage currGaborImg;
			toOf(currGaborMax, currGaborImg);

			//Percentage 
			//Counts white pixels in image with a threshold
			cvtColor(currMax, currMax, COLOR_BGR2GRAY);

			ofImage currImg;
			toOf(currMax, currImg);

			width = currImg.getWidth();
			height = currImg.getHeight();

			float totalWhitePixels = 0;
			float totalWhiteGaborPixels = 0;

			for (int j = 0; j < width; j++)
			{
				for (int k = 0; k < height; k++)
				{
					//Edge histogram
					ofColor currPixel = currImg.getColor(j, k);
					if (currPixel.getBrightness() >= 60) {
						totalWhitePixels++;
					}

					//Texture histogram
					ofColor currTexPixel = currGaborImg.getColor(j, k);
					if (currTexPixel.getBrightness() >= 60) {
						totalWhiteGaborPixels++;
					}
				}
			}

			float percentage = totalWhitePixels / (width*height);
			edgeHistogramVals.push_back(percentage);

			float percentageTextureHist = totalWhiteGaborPixels / (width*height);
			textureHistogramVals.push_back(percentageTextureHist);
		}
	}
	catch (cv::Exception & e)
	{
		cerr << e.msg << endl; // output exception message
	}
}

EdgeHistogram::EdgeHistogram(ofPixels frame)
{
	Mat imgMat = toCv(frame);

	Point anchor = Point(-1, -1);
	double delta = 0;
	int ddepth = -1;

	//Split Image into chunks

	width = frame.getWidth();
	height = frame.getHeight();

	/*Since we're splitting the image into a 4x4 (16 chunks), we can have images that are not divisible by this number
	in order to account for that, we simply ignore some outmost pixels so that the division is possible */

	//This will give us a value without the decimal part
	int widthBlock = width / SUBDIVISIONS;
	int heightBlock = height / SUBDIVISIONS;

	//This will give us both the width and height without the decimal part
	int widthInt = widthBlock * SUBDIVISIONS;
	int heightInt = heightBlock * SUBDIVISIONS;

	Mat maskImg = imgMat.clone(); //For visualization
	try
	{

		for (int y = 0; y < heightInt; y += heightBlock)
		{
			for (int x = 0; x < widthInt; x += widthBlock)
			{

				imgChunks.push_back(imgMat(Rect(x, y, widthBlock, heightBlock)).clone());

				//Visualization
				rectangle(maskImg, Point(x, y), Point(x + widthBlock - 1, y + heightBlock - 1), CV_RGB(255, 0, 0), 1);
				ofImage test;
				toOf(maskImg, test);
				//test.save("test.jpg");
			}
		}
	}
	catch (cv::Exception & e)
	{
		cerr << e.msg << endl; // output exception message
	}

	//Define Kernels
	float k1data[] = { 1, -1, 1, -1 };
	float k2data[] = { 1, 1, -1, -1 };
	float k3data[] = { sqrt(2), 0, 0, -sqrt(2) };
	float k4data[] = { 0, sqrt(2), -sqrt(2), 0 };
	float k5data[] = { 2, -2, -2, 2 };

	Mat verticalKernel(2, 2, CV_32F, k1data);
	Mat horizontalKernel(2, 2, CV_32F, k2data);
	Mat FrtyFveDgrKernel(2, 2, CV_32F, k3data);
	Mat oneHndrdThrtyFvDgrKernel(2, 2, CV_32F, k4data);
	Mat nonDirectionalKernel(2, 2, CV_32F, k5data);

	Mat res;
	Mat res01;
	Mat res02;
	Mat res03;
	Mat res04;

	//Apply Filters
	try
	{
		for (int i = 0; i < imgChunks.size(); i++)
		{

			filter2D(imgChunks[i], res, ddepth, verticalKernel, anchor, delta, BORDER_DEFAULT);
			tmpFilterResult.push_back(res);

			filter2D(imgChunks[i], res01, ddepth, horizontalKernel, anchor, delta, BORDER_DEFAULT);
			tmpFilterResult.push_back(res01);

			filter2D(imgChunks[i], res02, ddepth, FrtyFveDgrKernel, anchor, delta, BORDER_DEFAULT);
			tmpFilterResult.push_back(res02);

			filter2D(imgChunks[i], res03, ddepth, oneHndrdThrtyFvDgrKernel, anchor, delta, BORDER_DEFAULT);
			tmpFilterResult.push_back(res03);

			filter2D(imgChunks[i], res04, ddepth, nonDirectionalKernel, anchor, delta, BORDER_DEFAULT);
			tmpFilterResult.push_back(res04);

			//Max in each pixel
			Mat currMax;

			cv::max(tmpFilterResult[0], cv::max(tmpFilterResult[1],
				cv::max(tmpFilterResult[2], cv::max(tmpFilterResult[3], tmpFilterResult[4]))), currMax);

			/*
			ofImage tmpFilterResult01;
			toOf(tmpFilterResult[0], tmpFilterResult01);
			tmpFilterResult01.save("tmpFilterRes01.jpg");
			ofImage tmpFilterResult02;
			toOf(tmpFilterResult[1], tmpFilterResult02);
			tmpFilterResult02.save("tmpFilterRes02.jpg");
			ofImage tmpFilterResult03;
			toOf(tmpFilterResult[2], tmpFilterResult03);
			tmpFilterResult03.save("tmpFilterRes03.jpg");
			ofImage tmpFilterResult04;
			toOf(tmpFilterResult[3], tmpFilterResult04);
			tmpFilterResult04.save("tmpFilterRes04.jpg");
			ofImage tmpFilterResult05;
			toOf(tmpFilterResult[4], tmpFilterResult05);
			tmpFilterResult05.save("tmpFilterResult05.jpg");
			*/

			ofImage test02;
			toOf(currMax, test02);
			/*
			char temp[20];
			sprintf(temp, "test02-%d.jpg", i);
			test02.save(temp);
			*/

			//Percentage 
			//Counts white pixels in image with a threshold
			cvtColor(currMax, currMax, COLOR_BGR2GRAY);

			ofImage currImg;
			toOf(currMax, currImg);

			width = currImg.getWidth();
			height = currImg.getHeight();

			float totalWhitePixels = 0;

			for (int j = 0; j < width; j++)
			{
				for (int k = 0; k < height; k++)
				{
					ofColor currPixel = currImg.getColor(j, k);
					if (currPixel.getBrightness() >= 60)
					{
						totalWhitePixels++;
					}

				}
			}

			float percentage = totalWhitePixels / (width*height);
			edgeHistogramVals.push_back(percentage);
			/*
			printf("Whites: %f - ", totalWhitePixels);
			printf("Res: %d -> ", width*height);
			printf("%9.6f\n", percentage);
			*/
		}
	}
	catch (cv::Exception & e)
	{
		cerr << e.msg << endl; // output exception message
	}
}

std::vector<float> EdgeHistogram::getHistogramVals() {
	return edgeHistogramVals;
}

std::vector<float> EdgeHistogram::getTextureHistogramVals() {
	return textureHistogramVals;
}

std::vector<cv::Mat> EdgeHistogram::getGaborKernels() {
	/*Several orientations could be used and frequencies/wavelengths resulting 
	in a bank with multiple filters (for example 6 orientations and 4 frequencies).
	*/
	std::vector<cv::Mat> kernels;

	double sigma = 0.5; //The bandwidth or sigma controls the overall size of the Gabor envelope

	/*Since we'll be using 6 orientations, and a theta = 0 corresponds to horizontal features only
	we'll divide the interval between 0 and 180 in 6 equal parts.
	*/
	std::vector<double> theta{0, 30, 60, 90, 120, 150, 180 }; //orientation
	std::vector<double> lambd{ 1.0, 2.0, 3.0, 4.0 }; //wavelength
	double gamma = 0.1;

	for (int i = 0; i < theta.size(); i++) {
		for (int j = 0; j < lambd.size(); j++) {
			kernels.push_back(getGaborKernel(cv::Size(64, 64), sigma, (theta[i]*3.14)/180, lambd[j], gamma));
		}
	}
	
	return kernels;
	
}
