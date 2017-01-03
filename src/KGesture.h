/*

	kGesture

	This is the base class for a Kinect gesture.

	The update method is repsonsible for keeping track of whether the
	gesture is in the process of being completed, has timed out or has
	been completed.  It returns true only if the gesture is complete.
	
	Details of determining whether segments of getures have been
	completed are determined in a dirived class.
*/

#pragma once

#include "ofMain.h"
#include "ofxKinect2.h"
#include "GestureUtility.h"

class KGesture
{


public: 

	bool update(ofxKinect2::Body bod);
	KGesture(void);
	~KGesture(void);
	void KGesture::attach(int id);

protected:

	void init();
	virtual bool checkSegment(ofxKinect2::Body bod, int seg) = 0;  // dirived class must implement this 
	virtual void reset() = 0;   // called when window expires

	int myID;					// ID of body gesture is attached to
	int windowSize;				// # of frames for each segment until timeout
	int frameCount;				// running count when evaluating a segment
	int totalFrames;			// total # of frames from beginning to end of gesture
	int segmentCount;			// # of segments in this geesture
	int currentSegment;			// segment being evaluated 
	int cycleCount;				// how many times we cycle through all segments for complete gesture
	int currentCycle;			// keeps track of which cycle is being evaluated

};
