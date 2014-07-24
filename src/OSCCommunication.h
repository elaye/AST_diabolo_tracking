#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class OSCCommunication {
    // Osc
    //ofxOscReceiver receiver;
    ofxOscSender sender;
    ofxOscMessage message;

	public:
		void setup(int port);
		void sendPosition(ofPoint p);
		void sendJointPosition(string jointName, ofPoint p);
		void sendEvent(string event);
		/*void nextMessage(ofxOscMessage* message);
		bool hasMessage(); */
};