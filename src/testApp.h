#pragma once

#include "ofMain.h"

#include "OSCCommunication.h"
#include "gestureRecognition.h"
#include "Trick.h"
#include "trackedObject.h"
#include "Kinect.h"

#define USE_KINECT
#define USE_UI

#ifdef USE_UI
    #include "Sequencer.h"
#endif


class testApp : public ofBaseApp{

	int mode;

    bool fullscreen;

    string dataTrainingFilename;

    string infoText; //This string will be used to draw some info messages to the main app window

    string infoWiimote;

    bool tracked;
    float x;
    float y;

    int width;
    int height;

    gestureRecognition gr;
    OSCCommunication osc;

    Trick trick;

    verticalAcc vertAcc;
    legSatellite legSat;
    horizontalAcc horAcc;
    Elevator elevator;
    armSatellite armSat;


    Kinect kinect;

#ifdef USE_UI
    Sequencer seq;
#endif

    /*ofPoint leftHandPosition;
    ofPoint rightHandPosition;
    ofPoint diaboloPosition;*/

    ofShader shader;

    trackedObject leftHand;
    trackedObject rightHand;
    trackedObject leftKnee;
    trackedObject rightKnee;
    trackedObject diabolo;

	public:

        void setTrainingDataFilename(char* filename);

		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
};
