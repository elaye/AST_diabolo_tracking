#pragma once

#include "ofMain.h"
#include "boost/signal.hpp"
#include "boost/bind.hpp"
#include "trackedObject.h"
#include "gestureRecognition.h"

struct trickInfo {
	string name;
	bool useGR;
	int classId;
};

class Kick {

	bool state;
	float t;
	
	public:
		bool kick(){
			if(state == false){
				t = ofGetElapsedTimef();
				state = true;
				cout << "kick" << endl;
				return true;
			}
			return false;
		} 
		void update(){
			// 
			if( state == true && (ofGetElapsedTimef() - t) > 0.4 ){
				state = false;
			}
		}
};

class Trick {

	public:
		static vector<trickInfo> tricksList;
		boost::signal<void (int, bool) > event;
		//ofEvent<string> event;

		void setup(trackedObject * lh, trackedObject * rh, trackedObject * lk, trackedObject * rk, trackedObject * d, gestureRecognition * gestureRecog);
		void drawData(int x, int y);

	protected:
		trickInfo info;
		int trickIndex;
		bool state;
		float t;
		float duration = 0;
		int addTrick(trickInfo info);
		bool startTrick();
		void update();

		static trackedObject* leftHand;
		static trackedObject* rightHand;
		static trackedObject* leftKnee;
		static trackedObject* rightKnee;
		static trackedObject* diabolo;
		static gestureRecognition* gr;

};

class verticalAcc : public Trick {
	Kick kick;
	public:
		verticalAcc();
		void detect();
};

class legSatellite : public Trick {

	public:
		legSatellite();
		void detect();
};

class horizontalAcc : public Trick {

	public:
		horizontalAcc();
		void detect();
};

class Elevator : public Trick {

	public:
		Elevator();
		void detect();
};

class armSatellite : public Trick {

	public:
		armSatellite();
		void detect();
};