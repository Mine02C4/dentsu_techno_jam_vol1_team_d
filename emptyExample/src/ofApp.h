#pragma once

#include "ofMain.h"
#include "td_client.h"
#include "realtime.h"
#include "visualizer.h"
#include "types.h"
#include "../ofx/PostProcessing/src/ofxPostProcessing.h"
#include <cmath>

class ofApp : public ofBaseApp{
    TdClient* td_client_;
    vector<Team> teams_;
    int time_position_;

    Realtime* realtime_;
    Visualizer* visualizer_;
    vector<Kansei> kanseis_;

    ofSoundPlayer player;

	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
};
