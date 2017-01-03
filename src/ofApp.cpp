#include "ofApp.h"

// Kinect gesture demo 
//
// When a tracked body is found we attach a gesture controller to it
// and register for events we want to watch for.  The gesture controller
// is responsible for determining whether a body completes a registered gesture.
//
// An event is fired when a gesture is completed.

// change text color on gestures, for testing
ofColor red(255,0,0);
ofColor green(0,255,0);
ofColor blue(0,0,255);
ofColor purple(255,0,255);
ofColor currentColor = red;

//--------------------------------------------------------------
void ofApp::setup(){

	// set up Kinect
	device_ = new ofxKinect2::Device();
	device_->setup();

	myFont.loadFont("franklinGothic.otf", 32);

	// open depth, color and ir streams
	if(depth_.setup(*device_))
	{
		depth_.open();
	}

	if (color_.setup(*device_))
	{
		color_.open();
	}

	if (ir_.setup(*device_))
	{
		ir_.open();
	}

	if(body_stream_.setup(*device_))
	{
		body_stream_.open();
	}

}



//--------------------------------------------------------------
void ofApp::update(){

	// update Kinect data
	device_->update();

}

//--------------------------------------------------------------
void ofApp::draw(){

	static int trackedBodyCount;
	int trackedBodyIdx=0;
	ofSetWindowTitle(ofToString(ofGetFrameRate()));

	int w = ofGetWidth();
	int h = ofGetHeight();

//	color_.draw();
//	depth_.draw(w - 512, h - 424);
//	ir_.draw(w - 512, h - 848);
//	body_stream_.draw(w - 512, h - 424, 512, 424);


	ofBackground(0);
	body_stream_.draw(0, 0, w, h);
	//depth_.draw(0,0, w, h);

	// if any bodies 
	if( body_stream_.getNumBodies() ) {

		// init count of tracked bodies
		trackedBodyCount = 0;

		// timestamp for all controllers 
		uint64_t tStamp = ofGetElapsedTimeMillis();

		// get list of bodies
		vector<ofxKinect2::Body> bodies =  body_stream_.getBodies();

		// look at each body
		for( ofxKinect2::Body bod :  bodies )
		{

			// if this body is tracked
			if( bod.isTracked() )
			{
				// increment count
				trackedBodyCount++;

				// show its ID */
				myFont.drawString("ID: " + ofToString(bod.getId(),2),50,400 +(50*trackedBodyIdx++));

				// try to find a gesture controller for this body
				if( gControllers.find(bod.getId()) == gControllers.end() ) 
				{
					myFont.drawString("no controller " + ofToString(bod.getId(),2),50,450);

					// no controller found, create one
					gController = new GestureController();

					// attach it to this body
					gController->attachToBody(bod);

					// listen for gesture events
					ofAddListener(gController->kevent, this, &ofApp::gotKGesture);

					// register for left swipe
					gController->kRegisterGesture(GREEN_TEXT);

					// register for right swipe
					gController->kRegisterGesture(BLUE_TEXT);

					// register for raise left hand
					gController->kRegisterGesture(PURPLE_TEXT);

					// add to map
					gControllers[bod.getId()] = gController;

				} else {

					// get gesture controller from map entry
					gController = gControllers.begin()->second;	

					myFont.drawString("found controller " + ofToString(bod.getId(),2),50,450);

				} //else

				// timestamp controller
				gController->setTimeStamp(tStamp);

				// update the controller
				gController->update(bod);

				/**** show some stats on screen ****/

				Joint theJoint;
				string s;
				int leftX = 60;
				int rightX = w - 280; //1640;


				ofSetColor(currentColor);
				ofFill();

				theJoint = bod.getJoint(JointType_ElbowLeft);


				// show left elbow position
				if( theJoint.TrackingState == TrackingState_Tracked )
				{

					myFont.drawString("Left Elbow",leftX,50);
					s = "x:  " + ofToString(theJoint.Position.X, 2);
					myFont.drawString(s, leftX,100);
					s = "y:  " + ofToString(theJoint.Position.Y,2);
					myFont.drawString(s, leftX,150);

				} //if

				theJoint = bod.getJoint(JointType_WristLeft);
			
				// show left wrist position
				if( theJoint.TrackingState == TrackingState_Tracked )
				{

					myFont.drawString("Left Wrist",leftX,200);
					s = "x:  " + ofToString(theJoint.Position.X, 2);
					myFont.drawString(s, leftX,250);
					s = "y:  " + ofToString(theJoint.Position.Y,2);
					myFont.drawString(s, leftX,300);

				} // if


				theJoint = bod.getJoint(JointType_ElbowRight);


				// show right elbow position
				if( theJoint.TrackingState == TrackingState_Tracked )
				{

					myFont.drawString("Right Elbow",rightX,50);
					s = "x:  " + ofToString(theJoint.Position.X, 2);
					myFont.drawString(s, rightX,100);
					s = "y:  " + ofToString(theJoint.Position.Y,2);
					myFont.drawString(s, rightX,150);

				} // if

				theJoint = bod.getJoint(JointType_WristRight);

				// show right wrist position
				if( theJoint.TrackingState == TrackingState_Tracked )
				{

					myFont.drawString("Right Wrist",rightX,200);
					s = "x:  " + ofToString(theJoint.Position.X, 2);
					myFont.drawString(s, rightX,250);
					s = "y:  " + ofToString(theJoint.Position.Y,2);
					myFont.drawString(s, rightX,300);

				} // if


			}  // if

		} // for

		// if no bodies are being tracked
		if( !trackedBodyCount )
		{

			// we know that all the controllers can be deleted,
			// so let's clean up
			//

			// remove all event listeners
			for (std::map <int, GestureController *>::iterator it=gControllers.begin(); it!=gControllers.end(); ++it)
			{
				
		//		ofRemoveListener((it->second)->gevent, this, &ofApp::gotGesture);
				ofRemoveListener(gController->kevent, this, &ofApp::gotKGesture);

			} // for

			// controllers could also be deleted while bodies
			// are being tracked based on their timestamp
			gControllers.clear();

			currentColor = red; // reset color

		} // if


	} // if


}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::exit()
{
	color_.close();
	depth_.close();
	ir_.close();
	body_stream_.close();
	device_->exit();
	delete device_;
	device_ = NULL;


}


// gotKGesture
//
// A gesture has completed
//
void ofApp::gotKGesture(GesEventArgs &gArgs)
{


	switch(gArgs.type)
	{
	case GREEN_TEXT:				// green text
		currentColor = green;
		break;

	case BLUE_TEXT:					// blue text
		currentColor = blue;
		break;

	case PURPLE_TEXT:				// purple text
		currentColor = purple;
		break;

	default:
		break;


	} // switch

}
