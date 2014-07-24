#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "OSCCommunication.h"
#include "gestureRecognition.h"
#include "Trick.h"
#include "trackedObject.h"

class Sequencer {

	ofxUISuperCanvas * gui;

	ofxUIWidget * curSeqWidget;
	ofxUITextArea * trickInfoWidget;

	vector<trickInfo> tricksList;

	int seqLength;
	int seqIndex;
	vector<int> sequences;

	bool trickOn;

	OSCCommunication * osc;
	OSCCommunication oscSC;

	trackedObject * diabolo;

	ofPoint lastClicPos;



	void guiEvent(ofxUIEventArgs &e);

	public:
		void setup(vector<trickInfo> list, OSCCommunication * oscServer, trackedObject * d);
		void update();
		void trickEvent(int i, bool state);
		void startTrickEvent();
};