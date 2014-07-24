#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofSetVerticalSync(false);
    ofSetFrameRate(60);

    ofSetBackgroundColor(0,0,0);

    tracked = false;
    x = 0;
    y = 0;

    width = 640;
    height = 480;

    infoText = "";

    //Gesture recognition setup
    gr.setup();
    //OSC communication setup
    osc.setup(12001);

    leftHand.setPos(ofPoint(ofGetWidth() / 3, ofGetHeight() / 2));
    rightHand.setPos(ofPoint(2*ofGetWidth() / 3, ofGetHeight() / 2));
    leftKnee.setPos(ofPoint(ofGetWidth() / 3, ofGetHeight() / 2 / 2));
    rightKnee.setPos(ofPoint(2*ofGetWidth() / 3, ofGetHeight() / 2 / 2));
    diabolo.setPos(ofPoint(ofGetWidth() / 2, 2*ofGetHeight() / 3));

    trick.setup(&leftHand, &rightHand, &leftKnee, &rightKnee, &diabolo, &gr);

    // Bind events
    //trick.event.connect(bind(&OSCCommunication::sendEvent, &osc, _1));

    //ofAddListener(filter.event, osc, &OSCCommunication::sendEvent);
#ifdef USE_KINECT
    kinect.setup();
#endif

#ifdef USE_UI
    seq.setup(Trick::tricksList, &osc, &diabolo);
#endif

    elevator.event.connect(bind(&Sequencer::trickEvent, &seq, _1, _2));
    horAcc.event.connect(bind(&Sequencer::trickEvent, &seq, _1, _2));
    legSat.event.connect(bind(&Sequencer::trickEvent, &seq, _1, _2));
    vertAcc.event.connect(bind(&Sequencer::trickEvent, &seq, _1, _2));
    armSat.event.connect(bind(&Sequencer::trickEvent, &seq, _1, _2));
}

//--------------------------------------------------------------
void testApp::update(){

    ofPoint lh; //temporary left hand
    ofPoint rh; //temporary right hand
    ofPoint lk; //temporary left knee
    ofPoint rk; //temporary right knee
    ofPoint d;  //temporary diabolo

#ifdef USE_KINECT

    kinect.update();
    if(kinect.getLeftHandPosition(&lh)){
        leftHand.update(lh);
        //ofLog() << leftHand.getPos()[0].y ;
        //cout << leftHand.getPos.x << endl;
        osc.sendJointPosition("lefthand",lh);
    }
    if(kinect.getRightHandPosition(&rh)){
        rightHand.update(rh);
        osc.sendJointPosition("righthand",rh);
    }
    if(kinect.getLeftKneePosition(&lk)){
        leftKnee.update(lk);
    }
    if(kinect.getRightKneePosition(&rk)){
        rightKnee.update(rk);
    }
    if(kinect.getDiaboloPosition(&d)){
        diabolo.update(d);
        //cout << "diabolotracked" << endl;
        //osc.sendPosition(d);
        osc.sendPosition(d);
    }

#endif

    gr.update(d);
    
    elevator.detect();
    horAcc.detect();
    legSat.detect();
    vertAcc.detect();
    armSat.detect();

    seq.update();
}

//--------------------------------------------------------------
void testApp::draw(){
     ofSetColor(ofColor::black);
     ofRect(0,0,ofGetWidth(),ofGetHeight());
#ifdef USE_KINECT
    kinect.draw();
#endif
    gr.draw(0,0,height,width);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

    switch( key ){

        case 'j':
            //color_tracking.toggleJitter();
            break;
        case 'r':
            gr.recordGesture();
            break;
        // [
        case 53:
            gr.decreaseClassLabel();
            break;
        // ]
        case 45:
            gr.increaseClassLabel();
            break;
        case 't':
            gr.trainPipeline();
            break;
        case 's':
            gr.saveTrainingData();
            break;
        case 'c':
            gr.clearTrainingData();
            break;
        case 'l':
            gr.loadTrainingData();
            break;
        case 'f':
            ofToggleFullscreen();
            fullscreen = !fullscreen;
            break;
        case 'k':
            seq.trickEvent(2, true);
            break;
        // Backspace
        case 8:
            //filter.event("foo");
            //ir_tracking.clearTrackingPointsType();
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    switch(button){
        case 0:
            break;
        case 1:
            kinect.selectDiaboloColor(x, y);
            break;
        case 2:
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}

void testApp::setTrainingDataFilename(char* filename){
    gr.setTrainingDataFilename(filename);
}

void testApp::exit(){
    //color_tracking.stopVideo();
}