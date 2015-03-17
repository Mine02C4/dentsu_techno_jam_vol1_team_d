#include "visualizer.h"

Visualizer::Visualizer() {
  initPost();
  sphere_per_second_ = 10.0;

  positions_.push_back(generatePosition());
  light_.setPosition(1000, 1000, -2000);
  sphere_mesh_ = ofMesh::sphere(20);
}

void Visualizer::initPost() {
  ofBackground(255);
  post_.init(ofGetWidth(), ofGetHeight());
  post_.createPass<FxaaPass>()->setEnabled(false);
  post_.createPass<BloomPass>()->setEnabled(false);
  post_.createPass<DofPass>()->setEnabled(false);
  post_.createPass<KaleidoscopePass>()->setEnabled(false);
  post_.createPass<NoiseWarpPass>()->setEnabled(false);
  post_.createPass<PixelatePass>()->setEnabled(false);
  post_.createPass<EdgePass>()->setEnabled(false);
  post_.createPass<VerticalTiltShifPass>()->setEnabled(false);
  post_.createPass<GodRaysPass>()->setEnabled(false);

  post_.createPass<BloomPass>()->setEnabled(true);
  post_.createPass<DofPass>()->setEnabled(true);
}

ofVec3f Visualizer::generatePosition() {
  ofVec3f vec = ofVec3f(ofRandom(-1*(kAREA_WIDTH / 2), kAREA_WIDTH / 2), -1*kAREA_HEIGHT / 2, ofRandom(-1*(kAREA_DEPTH / 2), kAREA_DEPTH / 2));
  return vec;
}

void Visualizer::update(Kansei kansei) {
  bubble_frequency_ = pow(kansei.concentration / 100 * 2, 4.0);
  velocity_ = bubble_frequency_* sphere_per_second_;
  ofSetWindowTitle(" : " + ofToString(ofGetFrameRate()) + " : concentration = " + std::to_string(kansei.concentration));
  int number_of_generate = ofRandom(bubble_frequency_ * sphere_per_second_);
  for (int i = 0; i < number_of_generate; i++) {
    positions_.push_back(generatePosition());
  }
  for (int i = 0; i < positions_.size(); i++) {
    positions_.at(i).y += velocity_;
  }
  positions_.erase(remove_if(positions_.begin(), positions_.end(), [](ofVec3f position){
    if (position.y > 300)
      return true;
    return false;
  }), positions_.end());
}

void Visualizer::renderTeam(Team team) {
  light_.enable();

  float scale = 1.0 + 0.2 * sin(ofGetElapsedTimef() * 2 * PI / (60.0 / kBPM));

  // begin scene to post process
  post_.begin(camera_);

  // draw boxes
  for (unsigned i = 0; i < positions_.size(); ++i)
  {
    ofSetColor(team.base_color);
    ofPushMatrix();
    ofTranslate(positions_[i]);
    ofScale(scale, scale, scale);
    sphere_mesh_.draw();
    ofPopMatrix();
  }

  //ofDrawAxis(100);

  // end scene and draw
  post_.end();

  // set gl state back to original
  glPopAttrib();

  ofSetColor(0, 255, 255);
  //ofDrawBitmapString("Number keys toggle effects, mouse rotates scene", 10, 20);
  /*for (unsigned i = 0; i < post_.size(); ++i)
  {
    if (post_[i]->getEnabled()) ofSetColor(0, 255, 255);
    else ofSetColor(255, 0, 0);
    ostringstream oss;
    oss << i << ": " << post_[i]->getName() << (post_[i]->getEnabled() ? " (on)" : " (off)");
    ofDrawBitmapString(oss.str(), 10, 20 * (i + 2));
  }*/
}

void Visualizer::keyPressed(int key){
  unsigned idx = key - '0';
  if (idx < post_.size()) post_[idx]->setEnabled(!post_[idx]->getEnabled());
}