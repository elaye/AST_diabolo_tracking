#pragma once

#include "ofMain.h"

#include "ofxOpenNI.h"
#include "colorTracking.h"


class Kinect {

    ofxOpenNI oni;
    colorTracking color_tracking;

    ofPoint pDiabolo;
    bool diaboloTracked;

	public:

		void setup();
		bool update();
		void draw();

        void selectDiaboloColor(int x, int y);
        bool getLeftHandPosition(ofPoint * leftHandPosition);
        bool getRightHandPosition(ofPoint * rightHandPosition);
        bool getLeftKneePosition(ofPoint * rightHandPosition);
        bool getRightKneePosition(ofPoint * rightHandPosition);
        bool getDiaboloPosition(ofPoint * diaboloPosition);

};