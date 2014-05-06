#include "tom.h"

void tom::growRectangle (ofRectangle &r, float growFactor){	
	r.x -= growFactor;
	r.width += growFactor * 2;
	r.y -= growFactor;
	r.height += growFactor * 2;
}

// returns a sub image of as a ofxvc grayscale image
// assumes the image is 640 x 480
void tom::getGrayscaleSubImage(unsigned char * pixels, ofRectangle region, ofxCvGrayscaleImage &res) {
	return getGrayscaleSubImage(pixels, 640, 480, region, res);
}  

// returns a sub image of as a ofxvc grayscale image
// assumes the image is 640 x 480
// maintained for compatibility with older code
// todo: delete it
void tom::getGrayscaleSubImage(unsigned char * pixels, int wPixels, int hPixels, ofRectangle region, ofxCvGrayscaleImage &res) {
	ofImage temp;
	temp.setFromPixels(pixels, wPixels, hPixels, OF_IMAGE_COLOR, true);

	temp.crop(region.x, region.y, region.width, region.height);

	ofxCvColorImage tempCv;
	tempCv.setFromPixels(temp.getPixels(), temp.width, temp.height);		

	res = tempCv;		          
}  

// returns a subregion of pixels
ofImage tom::getSubImage(unsigned char * pixels, int wPixels, int hPixels, ofRectangle region) {
	ofImage temp;
	temp.setFromPixels(pixels, wPixels, hPixels, OF_IMAGE_COLOR, pixels);
	temp.crop(region.x, region.y, region.width, region.height);
	return temp;
}

// returns a subregion of pixels
ofImage tom::getSubImage(ofImage im, ofRectangle region) {
	ofImage temp;
	temp = im;
	temp.crop(region.x, region.y, region.width, region.height);
	return temp;
}


// returns the numbner of milliseconds since jan 1, 1970
long long tom::getMillisSince1970() {
	Poco::Timestamp epoch(0);  
	Poco::Timestamp now;  
	Poco::Timestamp::TimeDiff diffTime = (now - epoch);  
	long long millisSince1970 = (long long) (diffTime/1000);  	
	return millisSince1970;
}


// returns true if |c - v| < f
bool tom::isNear (float c, float v, float f, bool isAngle) {
	bool n = ((v >= (c-f)) && (v <= (c+f)));
	bool n1 = ((v-180 >= (c-f)) && (v-180 <= (c+f)));
	bool n2 = ((v+180 >= (c-f)) && (v+180 <= (c+f)));

	if (!isAngle) return n;
	else return (n || n1 || n2);
}
