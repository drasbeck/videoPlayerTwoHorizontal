#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofSetCircleResolution(100);

	Tweenzor::init();
	
	// filmene loades, husk at tage højde for om det er VideoPlayer eller HapPlayer
	one.loadMovie("1.mov");
	two.loadMovie("2.mov");
    one.setLoopState(OF_LOOP_NONE);
    two.setLoopState(OF_LOOP_NONE);

	// filmenes banner loades, husk at tage højde for filtype
	// banneret er sat til at have aspektet ofGetWindowsWidth * ofGetWindowHeight / 2
	bannerOne.loadImage("1.png");
	bannerTwo.loadImage("2.png");

	// hvis aspekt er vigtigt
	oneAspect = one.getWidth() / one.getHeight();
	twoAspect = two.getWidth() / two.getHeight();
	bannerOneAspect = bannerOne.getWidth() / bannerOne.getHeight();
	bannerTwoAspect = bannerTwo.getWidth() / bannerTwo.getHeight();

	// sætter filmenes y-pos
	yOne = 0;
	yTarget = ofGetWindowHeight() / 2;

	one.play();
	two.play();
    one.stop();
    two.stop();
    
	// home button
	screenHome = true;
	homeButton.loadImage("homeButton.png");
	homeX = ofGetWindowWidth() - 125;
	homeY = ofGetWindowHeight() - 125;
	homeRadius = 100;

	// play button
	playAlpha = 200.f;
	playButton.loadImage("playButton.png");
}

//--------------------------------------------------------------
void ofApp::update() {
	one.update();
	two.update();
	Tweenzor::update(ofGetElapsedTimeMillis());

	if (one.getIsMovieDone() || two.getIsMovieDone()) {
		if (!screenHome) {
			homePressed();
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofBackground(0);
	
	// filmen og animationen opdateres
	ofSetColor(255);
	if (!one.isPlaying() && !two.isPlaying()) {
		bannerOne.draw(0, yOne);
		bannerTwo.draw(0, yOne + ofGetWindowHeight() / 2);
	} else if (one.isPlaying() && !two.isPlaying()) {
		one.draw((ofGetWindowWidth() / 2) - ((ofGetWindowHeight() * oneAspect) / 2), yOne - ofGetWindowHeight() / 2, ofGetWindowHeight() * oneAspect, ofGetWindowHeight());
		bannerTwo.draw(0, yOne + ofGetWindowHeight() / 2);
	} else if (!one.isPlaying() && two.isPlaying()) {
		bannerOne.draw(0, yOne);
		two.draw((ofGetWindowWidth() / 2) - ((ofGetWindowHeight() * twoAspect) / 2), yOne + ofGetWindowHeight() / 2, ofGetWindowHeight() * twoAspect, ofGetWindowHeight());
	}

	// home button
	ofSetColor(255, 255, 255, ceil(homeAlpha));
	homeButton.draw(homeX - homeButton.getHeight() / 2, homeY - homeButton.getHeight() / 2);

	// play buttons
	ofSetColor(255, 255, 255, ceil(playAlpha));
	playButton.draw(ofGetWindowWidth() / 2 - playButton.getWidth() / 2, ofGetWindowHeight() / 4 - playButton.getHeight() / 2);
	playButton.draw(ofGetWindowWidth() / 2 - playButton.getWidth() / 2, ofGetWindowHeight() - (ofGetWindowHeight() / 4) - playButton.getWidth() / 2);

	if (one.isPlaying() && !screenHome) {
		ofSetColor(0, 0, 0, 75);
		ofRect((ofGetWindowWidth() / 2) - ((ofGetWindowHeight() * oneAspect) / 2), ofGetWindowHeight() - 4, ofGetWindowHeight() * oneAspect, ofGetWindowHeight());
		ofSetColor(255);
		ofRect((ofGetWindowWidth() / 2) - ((ofGetWindowHeight() * oneAspect) / 2), ofGetWindowHeight() - 4, ofGetWindowHeight() * oneAspect * one.getPosition(), ofGetWindowHeight());
	}
	if (two.isPlaying() && !screenHome) {
		ofSetColor(0, 100);
		ofRect((ofGetWindowWidth() / 2) - ((ofGetWindowHeight() * twoAspect) / 2), ofGetWindowHeight() - 4, ofGetWindowHeight() * twoAspect, ofGetWindowHeight());
		ofSetColor(255, 200);
		ofRect((ofGetWindowWidth() / 2) - ((ofGetWindowHeight() * twoAspect) / 2), ofGetWindowHeight() - 4, ofGetWindowHeight() * twoAspect * two.getPosition(), ofGetWindowHeight());
	}
	
	// debug
	//ofSetColor(255);
	//fpsStr = "frame rate: " + ofToString(ofGetFrameRate(), 2);
	//ofDrawBitmapString(fpsStr, 5, 13);
}

//==============================================================
void ofApp::oneStarted() {
	screenHome = false;
    if (yTarget < 0) {
		yTarget *= -1;
	}
	Tweenzor::add(&playAlpha, playAlpha, 0.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
	Tweenzor::add(&yOne, yOne, yTarget, 0.f, 0.5f, EASE_IN_OUT_QUINT);
	Tweenzor::add(&homeAlpha, homeAlpha, 200.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
    
	one.play();
}

void ofApp::twoStarted() {
	screenHome = false;
	if (yTarget > 0) {
		yTarget *= -1;
	}
    Tweenzor::add(&playAlpha, playAlpha, 0.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
	Tweenzor::add(&yOne, yOne, yTarget, 0.f, 0.5f, EASE_IN_OUT_QUINT);
	Tweenzor::add(&homeAlpha, homeAlpha, 200.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
    
	two.play();
}

void ofApp::homePressed() {
	screenHome = true;

    Tweenzor::add(&yOne, yOne, 0.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&yOne), this, &ofApp::onComplete);
    Tweenzor::add(&homeAlpha, homeAlpha, 0.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
}

void ofApp::onComplete(float* arg) {
    Tweenzor::add(&playAlpha, playAlpha, 200.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
	one.setFrame(0);
	two.setFrame(0);
	one.stop();
	two.stop();
}

void ofApp::exit() {
	Tweenzor::destroy();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	if (!one.isPlaying() && !two.isPlaying()) {
		if (y < ofGetWindowHeight() / 2) {
			oneStarted();
		}
		else {
			twoStarted();
		}
	}
	else if (one.isPlaying() || two.isPlaying()) {
		if (x > homeX - homeRadius && x < homeX + homeRadius && y > homeY - homeRadius && y < homeY + homeRadius) {
			homePressed();
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}