#include "gray_filter.h"

using namespace cv;


Mat GrayScaleFilter::filter(const Mat &input)
{
	Mat output;
	cvtColor(input, output, CV_BGR2GRAY);
	return output;
}
