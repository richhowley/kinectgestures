/*

	Gesture Engine for Microsoft Kinect

	This application builds on the idea explained well here:  http://pterneas.com/2014/01/27/implementing-kinect-gestures/
	that a Kinect gesture can be broken down into a series of segments, each defined by a number of
	conditions.  If all segments are completed within a given timeframe whatever action that is associated 
	with the gesture takes place.

	For example, a "swipe right" gesture might require two segments, each with two conditions.  
	In the first segment the right wrist must be above the waist and to the left of the right hip, 
	in the second the right wrist must be above the waist and to the right of the right hip. 
	
	If segment one is observed and then, within the given timeframe, segment two is observed
	the gesture is considered to be complete and some action is taken.

	Gestures are defined in XML.  A vocabulary has been created so the conditions of each
	segment, such as "to the right of" and "above" can be defined in text and read by the
	applicaiton at runtime.  The XML file defines genereic gestures shuch as "swipe left" and "raise hand".
	It is up to the applicaiton to determine which gestures are used on bodies being tracked
	and what action to take when a gesture is complete.

*/

#pragma once

#include "ofMain.h"
#include "ofxKinect2.h"
#include "ofArduino.h"
#include "GestureController.h"


class ofApp : public ofBaseApp{


public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void controllerUpdate();
	void exit();

	ofxKinect2::Device* device_;

	ofxKinect2::IrStream ir_;
	ofxKinect2::ColorStream color_;
	ofxKinect2::DepthStream depth_;
	ofxKinect2::BodyStream body_stream_;

	ofTrueTypeFont myFont;

private:

	void ofApp::gotKGesture(GesEventArgs &gArgs);	// event handler for completed gestures

	// gesture controller map:  body id, gesture controllers
	map <int, GestureController *> gControllers;

	// a gesture controller checks a body for all gestures we care about
	GestureController *gController;

};