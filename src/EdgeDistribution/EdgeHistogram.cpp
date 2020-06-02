#include "EdgeHistogram.hpp"

using namespace cv;
using namespace ofxCv;

EdgeHistogram::EdgeHistogram(Image* image) {

	ofImage img = image->getOFHandle();
	Mat imgMat = toCv(img);

	Point anchor = Point(-1, -1);
	double delta = 0;
	int ddepth = -1;

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
				rectangle(maskImg, Point(x, y), Point(x + widthBlock - 1, y + heightBlock - 1), CV_RGB(255, 0, 0), 1); 
				ofImage test;
				toOf(maskImg, test);
				test.save("test.jpg");
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

			char temp[20];
			sprintf(temp, "test02-%d.jpg", i);
			test02.save(temp);


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
					if (currPixel.getBrightness() >= 60) {
						totalWhitePixels++;
					}

				}
			}

			float percentage = totalWhitePixels / (width*height);
			edgeHistogramVals.push_back(percentage);

			printf("Whites: %f\n", totalWhitePixels);
			printf("Res: %f\n", width*height);
			printf("%9.6f\n", percentage);
			
		}
	}
	catch (cv::Exception & e)
	{
		cerr << e.msg << endl; // output exception message
	}
}

EdgeHistogram::EdgeHistogram(Video * video)
{
}

std::vector<float> EdgeHistogram::getHistogramVals() {
	return edgeHistogramVals;
}