/*
	GestureUtility

	Group of methods used to evaluate relationships between
	joints or get information about specifc joints, such as angle
	of an elbow.  Pointers to these methods are stored in a list
	used to check whether the conditions of a gesture segment
	have been met.

	Comparison methods are passed a body and list of joints and returns
	the relationship between the first and second joints on the list.  
	For example, gutil_compareRightOf(body, <joint1, joint2>) returns
	true if joint1 is to the right of joint2.


*/

#pragma once

#include "ofxKinect2.h"


class GestureUtility
{

public:	
	GestureUtility(void);
	~GestureUtility(void);

	// evaluation methods called by a gesture second parameter is a list of joints
	bool gutil_compareRightOf(ofxKinect2::Body bod, vector<int>); 
	bool gutil_compareLeftOf(ofxKinect2::Body bod, vector<int>); 
	bool gutil_compareAboveOf(ofxKinect2::Body bod, vector<int>);
	bool gutil_compareBelow(ofxKinect2::Body bod, vector<int>); 

	float rightElbowBendAngle(ofxKinect2::Body bod);
	float leftElbowBendAngle(ofxKinect2::Body bod);
	bool gutil_elbowAcute(ofxKinect2::Body bod, vector<int>); 
	bool gutil_elbowObtuse(ofxKinect2::Body bod, vector<int>); 

private:

	float elbowBendAngle(ofxKinect2::Body bod, int wristIdx, int shoulderIdx, int elbowIdx);
	bool gutil_leftElbowAcute(ofxKinect2::Body bod, int bp[]);
	bool gutil_rightElbowAcute(ofxKinect2::Body bod, int bp[]);
	bool gutil_leftElbowObtuse(ofxKinect2::Body bod, int bp[]);
	bool gutil_rightElbowObtuse(ofxKinect2::Body bod, int bp[]);

};