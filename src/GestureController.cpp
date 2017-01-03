#include "GestureController.h"


GestureController::GestureController(void)
{
	init();
}


GestureController::~GestureController(void)
{


	// for all registered gestures
	for( gestureinfo *g :  kGestures )
	{
		// delete gesture
		delete g->ges;

		// delet info
		delete g;

	} // for
}

// init
//
// Initialize gesture controller
//
void GestureController::init()
{

	// read gestures
	processXML();

}

// getter and setter for timestamp
uint64_t GestureController::getTimeStamp()
{
	return(timeStamp);
}

 void GestureController::setTimeStamp(uint64_t t)
{
	timeStamp = t;
}


 // processXML
 //
 // Read gestures from XML file into an 
 // object that can be traversed
 //
void GestureController::processXML()
{

	// read XML file to buffer
	ofFile file;
	file.open("gestures.xml");
	ofBuffer buffer = file.readToBuffer();

	// load XML object from buffer
	gestures.loadFromBuffer(buffer.getText());

}

// attachToBody
//
// Use this controller for passed body 
//
void GestureController::attachToBody(ofxKinect2::Body bod )
{

	// record the body this is attached to
	myBody = bod;

}

// kRegisterGesture
//
// Add passed gesture to list of registered gestures
//
//
// The gesture type value passed to kRegisterGesture indicates
// the action that will be taken when the gesture is completed.
// This method binds the action to a generic gesture defined in
// the gesture XML file.
//
void GestureController::kRegisterGesture(int gestureType)
{
	gestureinfo *info;
	char gFinder[50];
	char *gName;

	// tie a gesture defined in XML to a specific program action
	switch(gestureType)
	{

	case GREEN_TEXT:					// turn text green on a left swipe
		
		sprintf(gFinder,"gesture[@id=%s]","Swipe Left");

		break;

		
	case BLUE_TEXT:					// turn text blue on a right swipe

		sprintf(gFinder,"gesture[@id=%s]","Swipe Right");

		break;
		
	case PURPLE_TEXT:				// turn text purple when left hand is raised 

		sprintf(gFinder,"gesture[@id=%s]","Raise Left Hand");

		break;

	default:
		break;

	} // switch

	// create structure for this gesture
	info = new gestureinfo();

	// set type
	info->gType = gestureType;

	// build gesture
	info->ges = new XGesture(gFinder, gestures);

	// add to list of gestures being listened for
	kGestures.push_back(info);

}

// update
//
// Update any registered gestures and fire event if complete
//
void GestureController::update(ofxKinect2::Body bod)
{
	// for all registered gestures
	for( gestureinfo *g :  kGestures )
	{
		// if gesture is complete
		if( g->ges->update(bod) )
		{
			// set args for event
			GesEventArgs gArgs;
			gArgs.type = g->gType;
			gArgs.bod = myBody;

			//  let listners know
			ofNotifyEvent(kevent,gArgs);

		} // if

	} // for

}



