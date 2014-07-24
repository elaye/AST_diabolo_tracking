#include "ofMain.h"
#include "OSCCommunication.h"

void OSCCommunication::setup(int port){
	//sender.setup("192.168.0.17", 12001);
	sender.setup("127.0.0.1", port);
	//receiver.setup(57120);
}

void OSCCommunication::sendPosition(ofPoint p){
	message.setAddress("/tracking/coord");
	message.addFloatArg(p.x);
	message.addFloatArg(p.y);
	sender.sendMessage(message);
	message.clear();	
}

void OSCCommunication::sendJointPosition(string jointName, ofPoint p){
	message.setAddress("/tracking/joint/" + jointName);
	message.addFloatArg(p.x);
	message.addFloatArg(p.y);
	sender.sendMessage(message);
	message.clear();	
}

void OSCCommunication::sendEvent(string event){
	message.setAddress("/tracking/event");
	message.addStringArg(event);
	sender.sendMessage(message);
	message.clear();
}

/*bool OSCCommunication::hasMessage(){
	return receiver.hasWaitingMessages();
}

void OSCCommunication::nextMessage(ofxOscMessage* message){
	if(receiver.hasWaitingMessages()){
		receiver.getNextMessage(message);		
	}
}*/
