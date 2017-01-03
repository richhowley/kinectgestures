/*
	XGesture

	Dirived from the base class for a Kinect gesture, this
	gesture is defined in XML.

	On construction a list of segments is built.  Each segment
	has an arbitrary number of condiitons, all of which must
	pass for the segment to be completed.

	Each condiiton is represented by a pointer to an evaluation
	method and an argument list for the method.  The checkSegment
	method is passed a segment number.  Each condition in the 
	segment is checked by calling its evaluation method until a 
	conditinon is not met or all conditions are met.

*/


#include "KGesture.h"


class XGesture: public KGesture {

	typedef bool (GestureUtility::*evalptr)(ofxKinect2::Body, vector<int>); // ptr to evaluation method

public:

	XGesture(char *gID, ofXml gestures);
	~XGesture(void);

protected:
	void XGesture::buildSegments(char *gID, ofXml gestures);
	virtual bool checkSegment(ofxKinect2::Body bod, int seg);
	virtual void reset();
	void XGesture::getEvalPtr(string str, evalptr *ptr);
	int XGesture::getJoint(string str);
	GestureUtility gUtility;	// contains evaluation methods 

	// segments for this gesture - each segment is a list
	// of conditions, each condition is a pointer to an 
	// evaluation method and its argument list
	vector< vector<pair<evalptr,vector<int>>> > gSegments;

};
