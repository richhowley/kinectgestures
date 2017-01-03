#include "KGesture.h"


KGesture::KGesture()
{
	init();
}

KGesture::~KGesture()
{

}

// init
//
// Initialize gesture, call from constructor
//
void KGesture::init() 
{  
	// initialize counters
	frameCount = 0;
	totalFrames = 0;
	currentSegment = 0;
	currentCycle = 0;

	// default # of frames to complete a segment
	windowSize = 50;

	// default repeats - override in XML if desired
	cycleCount = 1;

}

// attach
//
// Attach gesture to passed body
//
void KGesture::attach(int id) 
{  
	myID = id;
}


// update
//
// Call to update status of a gesture for a body.
//
// Returns true if gesture has been completed
//
bool KGesture::update(ofxKinect2::Body bod) { 

	bool retVal = false;

	bool segOK = checkSegment(bod,currentSegment);			

	// increment frame count and total frame count
	frameCount++;
	totalFrames++;

	// if this sement checked out
	if( segOK )
	{
		// reset frame count
		frameCount = 0;

		// if this was the first segment, total frame count starts now
		if( !currentSegment && !currentCycle ) totalFrames = 0;

		// if last segment, reset and bump cycle count
		if( ++currentSegment == segmentCount ) {

			// if last cycle
			if( ++currentCycle == cycleCount )
			{
				// succcess
				currentCycle = 0;	
				totalFrames = 0;

				retVal = true;

			} // if

			// reset for next segment
			currentSegment = 0;

		} // if

	} else {

		// no match on current segment

		// check how long we've been checking this segment
		if( frameCount > windowSize )
		{
			// time to give up, reset
			frameCount = 0;
			totalFrames = 0;
			currentSegment = 0;
			currentCycle = 0;

			reset();  //tell gesture to reset

		} // if
	}

	return(retVal);
}

