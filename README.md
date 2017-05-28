# kinectgestures

Kinect gesture engine demo using XML to define gestures

Kinect gestures are defined in a XML file.  The file is read at runtime and the application determines what actions to take when gestures are completed.  Created in Visual Studio Express 2012 using Openframeworks 0.8.4 with the ofxKinect2 addon.


The src directory contains all the source files needed for the project.  The data directory, which should be in the Openframeworks bin directory, contains the XML file that defines a few simple gestures.


# How This Demo Works

When the program is run you should see on the screen the body stream of the person in front of the Kinect.  There will be infomation about the body on screen drawn in red. 

Keeping their right elbow straight, the person should lift their arm to the right so it is parallel to the floor.  If they bend their right elbow so that their wrist crosses their chest a "swipe left" gestrue is recognized and the text turns green.  

Extend the right elbow so that the right wrist is back to where it was, this is a "swipe right" gesture and the text turns blue.

Start with the left arm straight down so that the hand is below the left shoulder then raise the left arm so that the hand is above the left shoulder.  This is a "raise left hand" gesture and the text turns purple.

This code was written to work with multiple bodies but has only been tested with one, it is not considered production code but a demonstration of how to define Kinect gestures using XML.

# Defining Gestures

A gesture consists of segments that must be performed one after the other within a specific period of time.  When each segment is observed the gesture is considered complete.  

A segment is made up of any number of conditions.  Most conditions specify the relationship between two body joints.

For example, in the "raise left arm" gesture there are two segments, each with only one condition.  The condition of the first segment is that the left hand is below the left shoulder, the second condition is that the left hand is above the left shoulder.

It is defined in gestures.xml as follows.

```
  <gesture id="Raise Left Hand">
    <repeat>1</repeat>
    <segments>
      <segment>
        <condition>
          <rel>BELOW</rel>
          <joints>
            <joint>LEFT_HAND</joint>
            <joint>LEFT_SHOULDER</joint>
          </joints>
        </condition>
      </segment>
      <segment>
        <condition>
          <rel>ABOVE</rel>
          <joints>
            <joint>LEFT_HAND</joint>
            <joint>LEFT_SHOULDER</joint>
          </joints>
        </condition>
      </segment>
    </segments>
  </gesture>
</gestures>
```
The id of the getsture should be used to tie the gesture to an action (see kRegisterGesture() in GestureController.cpp).  

A repeat count is optional.  It could be used in this case to specify that the person being tracked would have to raise and lower their hand three times without having to define six segments.

The rel tag specifies the relationship between joints, legal values are RIGHT_OF, LEFT_OF, BELOW and ABOVE.  In the example above one condition is as follows
```
        <condition>
          <rel>BELOW</rel>
          <joints>
            <joint>LEFT_HAND</joint>
            <joint>LEFT_SHOULDER</joint>
          </joints>
        </condition>
```

This says that the left hand should be below the left shoulder.  When the XML is processed (in XGesture.cpp) a pointer to a method of the GestureUtility class is stored along with the aruments for the method.  In the above example the method is compareBelow() and the argument vector will contain the Kinect constants for left hand and left shoulder, in that order.

Gestures are registered to bodies individually.  This gives the program flexability on which gestures it responds to from which bodies. It could, in theory, define six gestures and register "player 1" to three of them and "player 2" to the other three for a multi-player game.

![slipeleft](https://cloud.githubusercontent.com/assets/318132/26525759/94135b4c-432f-11e7-917a-f4ea7d7c3a80.jpeg)
![swiperight](https://cloud.githubusercontent.com/assets/318132/26525764/a4ba2804-432f-11e7-9657-2a0a300d853c.jpeg)
![raiselefthand](https://cloud.githubusercontent.com/assets/318132/26525767/b11249c4-432f-11e7-8814-25db62a7825d.jpeg)


