# kinectgestures

Kinect gesture engine demo using XML to define gestures

Kinect gestures are defined in a XML file.  The file is read at runtime and the application determines what actions to take when gestures are completed.  Created in Visual Studio Express 2012 using Openframeworks 0.8.4 with the ofxKinect2 addon.


The src directory contains all the source files needed for the project.  The data directory, which should be in the Openframeworks bin directory, contains the XML file that defines a few simple gestures.


# How This Demo Works

When the program is run you should see on the screen the body stream of the person in front of the Kinect.  There will be infomation about the body on screen drawn in red. 

Keeping their right elbow straight, the person should lift their arm to the right so it is parallel to the floor.  If they bend their right elbow so that their wrist crosses their chest a "swipe left" gestrue is recognized and the text turns green.  

Extend the right elbow so that the right wrist is back to where it was, this is a "swipe right" gesture and the text turns blue.

Start with the left arm straight down so that the wrist is below the left shoulder then raise the left arm so that the wrist is above the left shoulder.  This is a "raise left hand" gesture and the text turns purple.

This code was written to work with multiple bodies but has only been tested with one, it is not considered production code but a demonstration of how to define Kinect gestures using XML.

