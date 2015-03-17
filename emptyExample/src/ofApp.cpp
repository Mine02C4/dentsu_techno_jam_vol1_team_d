#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  //Setup teams.
  teams_.push_back(Team("読売ジャイアンツ", ofColor(232, 125, 21)));
  teams_.push_back(Team("阪神タイガース", ofColor(255, 250, 19)));
  
  visualizer_ = new Visualizer();

  td_client_ = new TdClient();
  td_client_->setJobId(22296165);
  td_client_->fetchResult();
  Kansei kansei;
  kansei.interest = 0;
  kansei.drowsiness = 0;
  kansei.concentration = 0;
  kansei.stress = 0;
  kansei.like = 0;
  kanseis_.push_back(kansei);

  realtime_ = new Realtime([this](Kansei kansei){
    this->kanseis_.push_back(kansei);
  });

  player.loadSound("bgm.mp3");
  player.setLoop(true);
  player.play();
}

//--------------------------------------------------------------
void ofApp::update(){
  Team team = teams_.at(0);
  time_position_ = kanseis_.size() - 1;
  visualizer_->update(kanseis_.at(time_position_));
}

//--------------------------------------------------------------
void ofApp::draw(){
  Team team = teams_.at(0);
  // copy enable part of gl state
  glPushAttrib(GL_ENABLE_BIT);

  // setup gl state
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  visualizer_->renderTeam(team);

  ofSetColor(0, 0, 0);
  //ofDrawBitmapString(td_client_->getStr(), 10, 10);
  ofNoFill();
  ofSetColor(0, 0, 0, 255);
  ofBeginShape();
  for (int i = 0; i < kanseis_.size(); i++) {
    Kansei kansei = kanseis_.at(i);
    ofVertex(
      ofGetViewportWidth() * i / kanseis_.size(),
      isnan(kansei.concentration)?
      ofGetViewportHeight() / 2:
      ofGetViewportHeight() * (100.0 - kansei.concentration) / 100.0
    );
  }
  ofEndShape();
  ofLine(ofGetViewportWidth() * time_position_ / kanseis_.size(), 0,
    ofGetViewportWidth() * time_position_ / kanseis_.size(), ofGetViewportHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  //visualizer_->keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
  visualizer_->initPost();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}