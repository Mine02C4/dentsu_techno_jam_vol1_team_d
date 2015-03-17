#pragma once

#include <vector>

#include "ofMain.h"
#include "../ofx/PostProcessing/src/ofxPostProcessing.h"
#include "types.h"
#include "td_client.h"

class Visualizer {
  static const int kAREA_WIDTH = 600;
  static const int kAREA_HEIGHT = 600;
  static const int kAREA_DEPTH = 600;

  ofxPostProcessing post_;
  ofEasyCam camera_;
  ofLight light_;
  ofVboMesh sphere_mesh_;
  vector<ofVec3f> positions_;
  static ofVec3f generatePosition();

  double bubble_frequency_;
  double velocity_;
  double sphere_per_second_;
public:
  Visualizer();
  void initPost();
  void update(Kansei);
  void renderTeam(Team);
  void keyPressed(int);
};