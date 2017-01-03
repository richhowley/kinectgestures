
/*
	GestureController

	A GestureController is attached to each body being
	tracked by the Kinect.  Use the GestureController to
	register specific gestures to a body.  Continually call
	the update method to determiune if a gesture has been
	completed and fire an event.

*/

#pragma once

#include "ofMain.h"
#include "ofxKinect2.h"
#include "KGestureTypes.h"
#include "XGesture.h"

// Custom event arguments for gesture completed event
//
class GesEventArgs: public ofEventArgs {
	public:
		GesEventArgs() {};
		int type;
		ofxKinect2::Body bod;
};

class GestureController
{
	// storage for each gesture being listened for
	typedef struct {
		int gType;			// type of gesture (swipe left, swipe right ...)
		KGesture *ges;		// object that defines specfic gesture
	} gestureinfo;

public:

	GestureController(void);
	~GestureController(void);

	void GestureController::update(ofxKinect2::Body bod);
	void GestureController::attachToBody(ofxKinect2::Body bod );
	void GestureController::kRegisterGesture(int gestureType);
	void GestureController::setTimeStamp(uint64_t t);
	uint64_t GestureController::getTimeStamp();

	ofEvent<GesEventArgs> kevent; // fired when gesture is complete

private:

	void init();
	void GestureController::processXML();

	ofxKinect2::Body myBody;			// body this gesture is attached to
	uint64_t timeStamp;					// updated when we use the controller
	vector <gestureinfo *> kGestures;	// list of gestures being listened for
	ofXml gestures;						// XML descripotion of gesture 
};

