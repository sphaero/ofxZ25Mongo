#include "testApp.h"

//-------------------------------------------------------------
void testApp::setup(){
    
    mClient.connect("cherry.z25.org");
    mClient.cursor = mClient.query("lustrumcongress.tweets", mongo::BSONObj());
}

//--------------------------------------------------------------
void testApp::update(){
    if (mClient.cursor->more()) {
        std::cout << mClient.cursor->next().toString() << std::endl;
	}
}

//--------------------------------------------------------------
void testApp::draw(){

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
