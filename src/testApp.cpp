#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    serial.setup("/dev/tty.usbserial-AD026BCW", 115200);
    serial.startContinuousRead();
    ofAddListener(serial.NEW_MESSAGE, this, &testApp::gotMessage);

    message = "";

    sender.setup(HOST, PORT);

    values = new int[ofGetWidth()];
    value = 512;

    for(int i=0; i < ofGetWidth(); i++){
        values[i] = ofRandom(1024);
    }

    threshold = 50;
}

void testApp::update(){
    serial.sendRequest();
    x = x % ofGetWidth();
    values[x++] = value;

    // if we have passed a threshold, send an osc message
    if(value>threshold){
        ofxOscMessage m;
        m.setAddress("/pad");
        m.addIntArg(value);
        sender.sendMessage(m);
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    for(int x=0; x<ofGetWidth()-1; x++){
        int y  = ofMap(values[x]  ,0,1024,0,ofGetHeight());
        int yy = ofMap(values[x+1],0,1024,0,ofGetHeight());
        ofLine(x,y,x+1,yy);
    }
    ofDrawBitmapString(ofToString(value), 0, 0);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(string & msg){
    cout << "message: " << msg << endl;

    value = (msg[13] * 256) + msg[12];
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
