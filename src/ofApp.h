#pragma once

#include "ofMain.h"
#include "ofxTweenzor.h"
#include "ofxHapPlayer.h"


class ofApp : public ofBaseApp {

public:
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
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofxHapPlayer one;
	ofxHapPlayer two;

	//ofVideoPlayer one;
	//ofVideoPlayer two;

	ofImage bannerOne, bannerTwo, playButton, homeButton;

	float yOne, yTarget, homeAlpha, playAlpha;
	int h, w, homeX, homeY, homeRadius;

	float oneAspect, twoAspect, bannerOneAspect, bannerTwoAspect;

	bool screenHome;

	void oneStarted();
	void twoStarted();
	void homePressed();
    void onComplete(float* arg);

	string fpsStr;
};
