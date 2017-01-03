#include "GestureUtility.h"


GestureUtility::GestureUtility(void)
	{

	}

GestureUtility::~GestureUtility(void)
{

}


// elbowBendAngle
//
// Return bend angle of elbow
float GestureUtility::elbowBendAngle(ofxKinect2::Body bod, int wristIdx, int shoulderIdx, int elbowIdx)
{

	float retVal = 0.0f;

	if(bod.getJoint(elbowIdx).TrackingState != TrackingState_NotTracked
		&& bod.getJoint(wristIdx).TrackingState != TrackingState_NotTracked
		&& bod.getJoint(shoulderIdx).TrackingState != TrackingState_NotTracked)
	{
		float tx = bod.getJoint(elbowIdx).Position.X - bod.getJoint(shoulderIdx).Position.X;
		float ty = bod.getJoint(elbowIdx).Position.Y - bod.getJoint(shoulderIdx).Position.Y;
		float tz = bod.getJoint(elbowIdx).Position.Z - bod.getJoint(shoulderIdx).Position.Z;

		// elbow to shoulder
		float tdist1 = sqrt(tx*tx + ty*ty + tz*tz);

		tx = bod.getJoint(wristIdx).Position.X - bod.getJoint(elbowIdx).Position.X;
		ty = bod.getJoint(wristIdx).Position.Y - bod.getJoint(elbowIdx).Position.Y;
		tz = bod.getJoint(wristIdx).Position.Z - bod.getJoint(elbowIdx).Position.Z;

		// wrist to elbow
		float tdist2 = sqrt(tx*tx + ty*ty + tz*tz);

		tx = bod.getJoint(shoulderIdx).Position.X - bod.getJoint(wristIdx).Position.X;
		ty = bod.getJoint(shoulderIdx).Position.Y - bod.getJoint(wristIdx).Position.Y;
		tz = bod.getJoint(shoulderIdx).Position.Z - bod.getJoint(wristIdx).Position.Z;

		// shoulder to wrist
		float tdist3 = sqrt(tx*tx + ty*ty + tz*tz);

		// calculate angle of elbow bend
		float tangle = acos((tdist2 * tdist2 + tdist1 * tdist1 - tdist3 * tdist3) / (2 * tdist2 * tdist1)) * RAD_TO_DEG;

		retVal = tangle;

	}// if

	return(retVal);

}

// rightElbowBendAngle
//
// Return angle of right elbow
float GestureUtility::rightElbowBendAngle(ofxKinect2::Body bod)
{
	return(elbowBendAngle(bod,JointType_WristRight,JointType_ShoulderRight,JointType_ElbowRight));
}

// leftElbowBendAngle
//
// Left angle of left elbox
float GestureUtility::leftElbowBendAngle(ofxKinect2::Body bod)
{
	return(elbowBendAngle(bod,JointType_WristLeft,JointType_ShoulderLeft,JointType_ElbowLeft));
}

// Comparison functions used when updating gesture

// first body part to right of second body part
bool GestureUtility::gutil_compareRightOf(ofxKinect2::Body bod, vector<int> bp)
{
	bool retVal = false;

	// if tracking both body parts
	if(bod.getJoint(bp[0]).TrackingState == TrackingState_Tracked && bod.getJoint(bp[1]).TrackingState == TrackingState_Tracked )
	{
		// compare Y axis position
		retVal = bod.getJoint(bp[0]).Position.X > bod.getJoint(bp[1]).Position.X;

	} // if

	return(retVal);
}

// first body part to left of second body part
bool GestureUtility::gutil_compareLeftOf(ofxKinect2::Body bod, vector<int> bp)
{
	bool retVal = false;

	// if tracking both body parts
	if(bod.getJoint(bp[0]).TrackingState == TrackingState_Tracked && bod.getJoint(bp[1]).TrackingState == TrackingState_Tracked )
	{
		// compare Y axis position
		retVal = bod.getJoint(bp[0]).Position.X < bod.getJoint(bp[1]).Position.X;

	} // if

	return(retVal);
}

// first body part above of second body part
bool GestureUtility::gutil_compareAboveOf(ofxKinect2::Body bod, vector<int> bp)
{
	bool retVal = false;

	// if tracking both body parts
	if(bod.getJoint(bp[0]).TrackingState == TrackingState_Tracked && bod.getJoint(bp[1]).TrackingState == TrackingState_Tracked )
	{
		// compare X axis position
		retVal = bod.getJoint(bp[0]).Position.Y > bod.getJoint(bp[1]).Position.Y;

	} // if

	return(retVal);
}

// first body part below second body part
bool GestureUtility::gutil_compareBelow(ofxKinect2::Body bod, vector<int> bp)
{
	bool retVal = false;

	// if tracking both body parts
	if(bod.getJoint(bp[0]).TrackingState == TrackingState_Tracked && bod.getJoint(bp[1]).TrackingState == TrackingState_Tracked )
	{
		// compare X axis position
		retVal = bod.getJoint(bp[0]).Position.Y < bod.getJoint(bp[1]).Position.Y;

	} // if

	return(retVal);
}

// elbow angle is acute, arg should be left or right elbow
bool GestureUtility::gutil_elbowAcute(ofxKinect2::Body bod, vector<int> bp)
{
	int eAngle;

	eAngle = bp[0] == JointType_ElbowLeft ? leftElbowBendAngle(bod) : rightElbowBendAngle(bod);

	return(eAngle < 90.0);

}

// elbow angle is obtuse, arg should be left or right elbow
bool GestureUtility::gutil_elbowObtuse(ofxKinect2::Body bod, vector<int> bp)
{
	int eAngle;

	eAngle = bp[0] == JointType_ElbowLeft ? leftElbowBendAngle(bod) : rightElbowBendAngle(bod);

	return(eAngle > 90.0);

}