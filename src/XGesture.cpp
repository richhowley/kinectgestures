#include "XGesture.h"

// Gesture created from XML

XGesture::XGesture(char *gID, ofXml gestures)
{

	// build segmenbts for this gesture
	buildSegments(gID, gestures);



}

XGesture::~XGesture()
{

}

// Conversion from XML strings to method pointers and body indicies

// getEvalPtr
//
// set evaluation method based on passed string
//
void XGesture::getEvalPtr(string str, evalptr *ptr)
{
	if( !str.compare("RIGHT_OF") )
	{
		*ptr = &GestureUtility::gutil_compareRightOf;
	} else if( !str.compare("LEFT_OF" )) {
		*ptr = &GestureUtility::gutil_compareLeftOf;
	} else if( !str.compare("BELOW") ) {
		*ptr = &GestureUtility::gutil_compareBelow;
	} else if( !str.compare("ABOVE") ) {
		*ptr = &GestureUtility::gutil_compareAboveOf;
	}

}

// getJoint
//
// return joint index based on passed string
//
int XGesture::getJoint(string str)
{
	int retVal;

	if( !str.compare("RIGHT_WRIST") )
	{
		retVal = JointType_WristRight;
	} else 	if( !str.compare("RIGHT_HAND") ) {
		retVal = JointType_HandRight;
	} else 	if( !str.compare("RIGHT_SHOULDER") ) {
		retVal = JointType_ShoulderRight;
	} else 	if( !str.compare("RIGHT_HIP") ) {
		retVal = JointType_HipRight;
	} else 	if( !str.compare("LEFT_WRIST") ) {
		retVal = JointType_WristLeft;
	} else 	if( !str.compare("LEFT_HAND") ) {
		retVal = JointType_HandLeft;
	} else 	if( !str.compare("LEFT_SHOULDER") ) {
		retVal = JointType_ShoulderLeft;
	} else 	if( !str.compare("LEFT_HIP") ) {
		retVal = JointType_HipLeft;
	} else if( !str.compare("RIGHT_KNEE") ) {
		retVal = JointType_KneeRight;
	} else 	if( !str.compare("RIGHT_ANKLE") ) {
		retVal = JointType_AnkleRight;
	} else 	if( !str.compare("RIGHT_FOOT") ) {
		retVal = JointType_FootRight;
	} else 	if( !str.compare("LEFTKNEE") ) {
		retVal = JointType_KneeLeft;
	} else 	if( !str.compare("LEFT_ANKLE") ) {
		retVal = JointType_AnkleLeft;
	} else 	if( !str.compare("LEFT_FOOT") ) {
		retVal = JointType_FootLeft;
	} else if( !str.compare("HEAD") ) {
		retVal = JointType_Head;
	} else 	if( !str.compare("SPINE_MID") ) {
		retVal = JointType_SpineMid;
	} else 	if( !str.compare("SPINE_BASE") ) {
		retVal = JointType_SpineBase;
	} else 	if( !str.compare("SPINE_Shoulder") ) {
		retVal = JointType_SpineShoulder;
	} else 	if( !str.compare("NECK") ) {
		retVal = JointType_Neck;
	} 

	return(retVal);
}


// buildSegments
//
// Use passed XML to build segemnt descriptions for gesture
//
void XGesture::buildSegments(char *gID, ofXml gestures) 
{
	evalptr evalFunction;
	vector <int> args;
	vector<pair<evalptr,vector<int>>> segConditions;

	// point to this gesture in XML
	gestures.setTo(gID);

	// try to read cycle count value
	string cycleString = gestures.getValue("repeat");

	// set cycle count if specified
	if( cycleString.size() )
	{

		cycleCount = ofToInt(gestures.getValue("repeat"));

	} // if

	ofLog(OF_LOG_NOTICE, "*** Repeat ****");
	ofLog(OF_LOG_NOTICE, ofToString(cycleCount));

	// point to segments for this gesture
	gestures.setTo("segments");

	// set # of segments
	segmentCount = gestures.getNumChildren();

	ofLog(OF_LOG_NOTICE, "*** Segments ****");
	ofLog(OF_LOG_NOTICE, ofToString(segmentCount));

	// for each segment
	for(int i=0; i < segmentCount; i++)
	{

		ofLog(OF_LOG_NOTICE, "*** Start Segment ****");

		// point to segment
		gestures.setToChild(i);

		// set # of conditions for segment
		int numConditions =  gestures.getNumChildren();

		// for each condition
		for(int c=0; c < numConditions; c++)
		{
			// point to condition
			gestures.setToChild(c);

			ofLog(OF_LOG_NOTICE, gestures.getValue("rel"));

			// set evaluation method
			getEvalPtr( gestures.getValue("rel"), &evalFunction);

			// point to joints
			gestures.setTo("joints");

			// set # of joints for this condition
			int numJoints =  gestures.getNumChildren();

			// point at first joint
			gestures.setToChild(0);

			// for each joint
			for(int j=0; j < numJoints; j++)
			{
				// add to evaluation method arguments
				args.push_back(getJoint(gestures.getValue()));

				ofLog(OF_LOG_NOTICE, gestures.getValue());

				// move to next joint
				gestures.setToSibling();

			} // for

			// add condition to segment
			segConditions.push_back(std::make_pair(evalFunction,args));

			// clear arguments
			args.clear();

			gestures.setToParent();		// joints
			gestures.setToParent();		// condition
			gestures.setToParent();		// segment

		} // for

		gestures.setToParent();			// segments

		// add segment to gesture
		gSegments.push_back(segConditions);

		// clear conditions
		segConditions.clear();

	} // for

}


void XGesture::reset() {}

// checkSegment
//
// Return true if conditions of current segment are met
//
bool XGesture::checkSegment(ofxKinect2::Body bod, int seg)
{
	bool retVal = false;

	evalptr evalFunction;											// evaluation method
	vector <int> args;												// arguments for evaluation
	vector<pair<evalptr,vector<int>>> thisSegmentConditions;		// all conditions for this segment

	// get conditions for segment with passed index
	thisSegmentConditions = gSegments[seg];

	// while more conditions
	for(int i=0; i < thisSegmentConditions.size(); i++)
	{
		// get method pointer and arguments
		evalFunction = thisSegmentConditions[i].first;
		args = thisSegmentConditions[i].second;

		// call evaluation method
		retVal = (gUtility.*evalFunction)(bod, args);

		// if condition not met, stop checking
		if( !retVal ) break;

	} // if

	return retVal;
}


