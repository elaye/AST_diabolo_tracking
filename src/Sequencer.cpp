#include "Sequencer.h"

void Sequencer::setup(vector<trickInfo> list, OSCCommunication * oscServer, trackedObject * d){

	diabolo = d;

	trickOn = false;

	osc = oscServer;
	oscSC.setup(57121);

	seqLength = 20;
	seqIndex = 0;
	//tricksList.push_back("vertAcc");	
	//tricksList.push_back("horAcc");
	tricksList = list;


	gui = new ofxUISuperCanvas("Sequencer");
	gui->setPosition(0, 480);
	gui->addSpacer();
	trickInfoWidget = gui->addTextArea("trick", ofToString(0));
	gui->addSpacer();
	gui->setGlobalButtonDimension(24);
	//gui->addLabel("MATRIX", OFX_UI_FONT_MEDIUM);
	//string tricksListText = "Vertical acceleration\n\nHorizontal acceleration\n\n3\n\n4\n\n5\n\n6\n\n7";
	//ofxUITextArea(string _name, string _textstring, float w, float h = 0, float x = 0, float y = 0, int _size = OFX_UI_FONT_MEDIUM);
	for(int i=0; i<tricksList.size();i++){
		//ofxUITextArea * t = new ofxUITextArea(tricksList.at(i), tricksList.at(i), 28, 22, 0, i*22);
		//gui->addWidget(t);
		//delete t;
		gui->addTextArea("textarea", tricksList.at(i).name);
	}
	//delete t;
	//gui->addTextArea("textarea", tricksListText);
	for(int i=0; i<seqLength; i++){
		//gui->addWidgetEastOf(gui->addToggleMatrix("MATRIX"+i, 20, 1),"MATRIX"+i);
		ofxUIToggleMatrix * m = new ofxUIToggleMatrix(210 + i*18, 50, 16, 16, tricksList.size(), 1, ofToString(i));
		m->setAllowMultiple(false);
		m->setToggle(0,0,true);
		if(i==0){
			m->setDrawFill(true);
			curSeqWidget = m;	
		}
		gui->addWidget(m);
		sequences.push_back(0);
		// ofxUIToggleMatrix * m = new ofxUIToggleMatrix(200 + i*22, 25, 20, 20, tricksList.size(), 1, "MATRIX"+i);

		// sequences.push_back(m);
		// m->setAllowMultiple(false);
		// gui->addWidget(m);
	}
	gui->addLabelButton("Restart", false);
	//delete m;
	gui->autoSizeToFitWidgets();
	ofAddListener(gui->newGUIEvent, this, &Sequencer::guiEvent);

}

void Sequencer::update(){
	if(trickOn == true && tricksList[sequences.at(seqIndex)].name == "legSatellite"){
		ofPoint * p = diabolo->getPos();
		if(lastClicPos.distance(p[0]) > 5){
			ofLog() << "clic";
			oscSC.sendEvent("clic");			
		}
	}
}

void Sequencer::trickEvent(int i, bool state){
	if(i == sequences.at(seqIndex) && state == false){
		trickOn = false;
		//ofxUIWidget * pmat = gui->getWidget(ofToString(seqIndex));
		curSeqWidget->setDrawFill(false);
		if(seqIndex == seqLength-1){
			seqIndex = 0;
		}
		else{
			seqIndex++;
		}
		curSeqWidget = gui->getWidget(ofToString(seqIndex));
		curSeqWidget->setDrawFill(true);

		trickInfoWidget->setTextString(tricksList[i].name + " end");
	}
	if(i == sequences.at(seqIndex) && state == true){
		trickOn = true;
		ofPoint * p = diabolo->getPos();
		lastClicPos = p[0];
		trickInfoWidget->setTextString(tricksList[i].name + " start");
		oscSC.sendEvent(tricksList[i].name);		
	}	
}

void Sequencer::guiEvent(ofxUIEventArgs &e){
	string name = e.getName();
	// if(ofToInt(name)){
	// 	ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
	// 	int val = toggle->getValue();
	// 	sequences.at(ofToInt(name)) = val;
	// 	ofLog() << val;
	// }
	if(name == "Restart"){
		curSeqWidget->setDrawFill(false);
		curSeqWidget = gui->getWidget("0");
		curSeqWidget->setDrawFill(true);
		seqIndex = 0;
	}
	for(int j=0; j<seqLength; j++){
		for(int i=0; i<tricksList.size(); i++){
			if(name == ofToString(j)+"(0,"+ofToString(i)+")"){
				//ofLog() << name;
				// ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
				// int val = toggle->getValue();
				sequences.at(j) = i;
				//break;
			}			
		}

	}
}