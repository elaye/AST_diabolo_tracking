#include "ofMain.h"
#include "Kinect.h"

void Kinect::setup(){
    oni.setup();
    oni.addImageGenerator();
    oni.addDepthGenerator();
    oni.setRegister(true);
    oni.setMirror(true);
    oni.addUserGenerator();
    oni.setMaxNumUsers(2);
    oni.start();
    
    //oni.setUseTexture(true);

    // set properties for all user masks and point clouds
    //oni.setUseMaskPixelsAllUsers(true); // if you just want pixels, use this set to true
    oni.setUseMaskTextureAllUsers(true); // this turns on mask pixels internally AND creates mask textures efficiently
    oni.setUsePointCloudsAllUsers(true);
    oni.setPointCloudDrawSizeAllUsers(2); // size of each 'point' in the point cloud
    oni.setPointCloudResolutionAllUsers(2); // resolution of the mesh created for the point cloud eg., this will use every second depth pixel

    // Setup color tracking
    cout << "W : " << oni.getWidth() << " H : " << oni.getHeight() << endl;
    color_tracking.setup(640, 480);
    

}

bool Kinect::update(){
    oni.update();
    diaboloTracked = color_tracking.update(oni.getImagePixels(), &pDiabolo);
}

void Kinect::draw(){
    ofSetColor(255, 255, 255);
    
    ofPushMatrix();
    // draw debug (ie., image, depth, skeleton)
    // oni.drawDebug();
    oni.drawImage(0, 0);
    //oni.drawDepth(oni.getWidth(), 0);
    ofPopMatrix();
    
    ofPushMatrix();
    // use a blend mode so we can see 'through' the mask(s)
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    // get number of current users
    int numUsers = oni.getNumTrackedUsers();
    
    // iterate through users
    for (int i = 0; i < numUsers; i++){
        
        // get a reference to this user
        ofxOpenNIUser & user = oni.getTrackedUser(i);
        
        // draw the mask texture for this user
        //user.drawMask();
        oni.drawSkeletons();
        // you can also access the pixel and texture references individually:
        
        // TEXTURE REFERENCE
        //ofTexture & tex = user.getMaskTextureReference();
        // do something with texture...
        
        // PIXEL REFERENCE
        //ofPixels & pix = user.getMaskPixels();
        // do something with the pixels...
        
        // and point clouds:
        
        ofPushMatrix();
        // move it a bit more central
        ofTranslate(320, 240, 10);
        user.drawPointCloud();
        
        // you can also access the mesh:
        
        // MESH REFERENCE
        //ofMesh & mesh = user.getPointCloud();
        // do something with the point cloud mesh
        
        ofPopMatrix();
        
    }
    
    ofDisableBlendMode();
    ofPopMatrix();
    
    // draw some info regarding frame counts etc
    ofSetColor(0, 255, 0);
    string msg = " MILLIS: " + ofToString(ofGetElapsedTimeMillis()) + " FPS: " + ofToString(ofGetFrameRate()) + " Device FPS: " + ofToString(oni.getFrameRate());

    color_tracking.draw();

}

void Kinect::selectDiaboloColor(int x, int y){
    // ofPixels pixels;
    // ofColor color;
    // pixels = oni.getImagePixels();
    // color = pixels.getColor(x-640, y);
    // cout << "R : " << color.getHue()  << " G : " << color.getSaturation() << " B : " << color.getBrightness() << endl;
    // color_tracking.selectColor(color, x+640, y);
    ofTexture tex;
    tex = oni.getimageTextureReference();
    ofPixels pixels;
    ofColor color;
    tex.readToPixels(pixels);
    color = pixels.getColor(x, y);
    color_tracking.selectColor(color, x, y);
}

bool Kinect::getLeftHandPosition(ofPoint * leftHandPosition){
    if(oni.getNumTrackedUsers() == 1){
        ofxOpenNIUser & user = oni.getTrackedUser(0);
        ofxOpenNIJoint leftHandJoint = user.getJoint(JOINT_LEFT_HAND);
        
        ofPoint lhp = leftHandJoint.getProjectivePosition();
        lhp.x /= 640;
        lhp.y /= 480;
        *leftHandPosition = lhp;
        return true;
    }
    return false;
}

bool Kinect::getRightHandPosition(ofPoint * rightHandPosition){
    if(oni.getNumTrackedUsers() == 1){
        ofxOpenNIUser & user = oni.getTrackedUser(0);
        ofxOpenNIJoint rightHandJoint = user.getJoint(JOINT_RIGHT_HAND);
        
        ofPoint rhp = rightHandJoint.getProjectivePosition();
        rhp.x /= 640;
        rhp.y /= 480;
        *rightHandPosition = rhp;
        return true;
    }
    return false;
}

bool Kinect::getLeftKneePosition(ofPoint * leftKneePosition){
    if(oni.getNumTrackedUsers() == 1){
        ofxOpenNIUser & user = oni.getTrackedUser(0);
        ofxOpenNIJoint leftKneeJoint = user.getJoint(JOINT_LEFT_KNEE);
        
        ofPoint lkp = leftKneeJoint.getProjectivePosition();
        lkp.x /= 640;
        lkp.y /= 480;
        *leftKneePosition = lkp;
        return true;
    }
    return false;
}

bool Kinect::getRightKneePosition(ofPoint * rightKneePosition){
    if(oni.getNumTrackedUsers() == 1){
        ofxOpenNIUser & user = oni.getTrackedUser(0);
        ofxOpenNIJoint rightKneeJoint = user.getJoint(JOINT_RIGHT_KNEE);
        
        ofPoint rkp = rightKneeJoint.getProjectivePosition();
        rkp.x /= 640;
        rkp.y /= 480;
        *rightKneePosition = rkp;
        return true;
    }
    return false;
}

bool Kinect::getDiaboloPosition(ofPoint * diaboloPosition){
    *diaboloPosition = pDiabolo;
    return diaboloTracked;
}