#include "Trick.h"

vector<trickInfo> Trick::tricksList;
trackedObject* Trick::leftHand;
trackedObject* Trick::rightHand;
trackedObject* Trick::leftKnee;
trackedObject* Trick::rightKnee;
trackedObject* Trick::diabolo;
gestureRecognition* Trick::gr;

void Trick::setup(trackedObject * lh, trackedObject * rh, trackedObject * lk, trackedObject * rk, trackedObject * d, gestureRecognition * gestureRecog){
	// leftHand = lh;
	// rightHand = rh;
	// diabolo = d;
	// gr = gestureRecog;
	leftHand = lh;
	rightHand = rh;
	leftKnee = lk;
	rightKnee = rk;
	diabolo = d;
	gr = gestureRecog;
}

int Trick::addTrick(trickInfo info){
	Trick::tricksList.push_back(info);
	return Trick::tricksList.size()-1;
}

bool Trick::startTrick(){
	if(state == false){
		t = ofGetElapsedTimef();
		state = true;
		//cout << trickIndex << endl;
		return true;
	}
	// Reinit time counter when the trick is redone
	t = ofGetElapsedTimef();
	return false;
} 
void Trick::update(){
	// 
	if( state == true && (ofGetElapsedTimef() - t) > duration ){
		state = false;
		// Send event at the end of the trick
		event(trickIndex, false);
	}
}

verticalAcc::verticalAcc(){
	info.name = "verticalAcc";
	info.useGR = true;
	info.classId = 3;
	trickIndex = addTrick(info);
	duration = 0.5;
}

void verticalAcc::detect(){
	update();

	int g = gr->getGesture();
	if(g == info.classId){
		startTrick();
		event(trickIndex, true);
		//cout << "vert acc detected" << endl;
	}
}

legSatellite::legSatellite(){
	info.name = "legSatellite";
	info.useGR = true;
	info.classId = 1;
	trickIndex = addTrick(info);
	duration = 1.0;
}

void legSatellite::detect(){
	update();

	ofPoint* lkp_temp = leftKnee->getPos();
	ofPoint* rkp_temp = rightKnee->getPos();

	int g = gr->getGesture();
	if(g == info.classId){
		//cout << ofToString(abs(lkp_temp[0].y - rkp_temp[0].y)) << endl;
		if(abs(lkp_temp[0].y - rkp_temp[0].y)>0.2){
			startTrick();
			event(trickIndex, true);
			//cout << "leg satellite detected" << endl;
		}
	}
}

horizontalAcc::horizontalAcc(){
	info.name = "horizontalAcc";
	info.useGR = true;
	info.classId = 1;
	trickIndex = addTrick(info);
	duration = 1.0;
}

void horizontalAcc::detect(){

	update();

	ofPoint* lkp_temp = leftKnee->getPos();
	ofPoint* rkp_temp = rightKnee->getPos();

	int g = gr->getGesture();
	if(g == info.classId){
		if(abs(lkp_temp[0].y - rkp_temp[0].y)<0.1){
			startTrick();
			event(trickIndex, true);
			cout << "hor acc detected" << endl;
		}
	}
}

Elevator::Elevator(){
	info.name = "elevator";
	info.useGR = false;
	trickIndex = addTrick(info);
	duration = 2.0;
}

void Elevator::detect(){

	update();

	ofPoint* lhp_temp = leftHand->getPos();
	ofPoint* rhp_temp = rightHand->getPos();

	if(lhp_temp[0].y - rhp_temp[0].y > 0.5 || rhp_temp[0].y - lhp_temp[0].y > 0.4){
		// Threshold
		//cout << "vy : " << v[0].y << endl;
		//cout << "vx : " << v[0].x << endl;
		if(abs(lhp_temp[0].x - rhp_temp[0].x) < 0.15){
			startTrick();
			event(trickIndex, true);
			cout << "elevator detected" << endl;
		}
	}

	/*if(leftHand.getPos()[0].y - rightHand.getPos()[0].y > 200 || rightHand.getPos()[0].y - leftHand.getPos()[0].y > 200){
		// Threshold
		//cout << "vy : " << v[0].y << endl;
		//cout << "vx : " << v[0].x << endl;
		if(abs(leftHand.getPos()[0].x - rightHand.getPos()[0].x) < 20){
			// if(kick.kick()){
			// 	event("kick");

				
			// 	//ofNotifyEvent(event, "kick", this);
			// }
			cout << "elevator detected" << endl;
		}
	}*/
}

armSatellite::armSatellite(){
	info.name = "armSatellite";
	info.useGR = true;
	info.classId = 4;
	trickIndex = addTrick(info);
	duration = 1.0;
}

void armSatellite::detect(){
	update();

	int g = gr->getGesture();
	if(g == info.classId){
		startTrick();
		event(trickIndex, true);
		//cout << "arm satellite detected" << endl;
	}
}

/*void Trick::detectKick(){
	// Detect direction change
	if(v[1].y < 0){
		// Threshold
		//cout << "vy : " << v[0].y << endl;
		//cout << "vx : " << v[0].x << endl;
		if(abs(v[0].y) > 1.0 && abs(v[0].x) < 0.05){
			if(kick.kick()){
				event("kick");
				//ofNotifyEvent(event, "kick", this);
			}
		}
	}
}*/

/*void Trick::drawData(int x, int y){
	string data;
	int textX = x;
	int textY = y;

	data = "x  : " + ofToString(p[0].x, 5) + "  y  : " + ofToString(p[0].y, 5);
	ofDrawBitmapString(data, textX, textY);

	(abs(v[0].x) < 0.05) ? ofSetColor(ofColor::red) : ofSetColor(ofColor::white);
	textY += 15;
	data = "Vx : "; + 
	(v[0].x > 0) ? data += " " : data += "";
	data += ofToString(v[0].x, 5) + "  Vy : ";
	(v[0].y > 0) ? data += " " : data += "";
	data += ofToString(v[0].y, 5);
	ofDrawBitmapString(data, textX, textY);

	ofSetColor(ofColor::white);

	textY += 15;
	data = "Ax : "; + 
	(a[0].x > 0) ? data += " " : data += "";
	data += ofToString(a[0].x, 5) + "  Ay : ";
	(a[0].y > 0) ? data += " " : data += "";
	data += ofToString(a[0].y, 5);
	ofDrawBitmapString(data, textX, textY);
}*/


