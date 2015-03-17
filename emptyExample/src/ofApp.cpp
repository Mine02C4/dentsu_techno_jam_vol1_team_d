#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  //Setup teams.
  teams_.push_back(Team("読売ジャイアンツ", ofColor(232, 125, 21)));
  teams_.push_back(Team("阪神タイガース", ofColor(255, 250, 19)));
  
  visualizer_ = new Visualizer();

  //ofBackground(255);
  //post.init(ofGetWidth(), ofGetHeight());
  //post.createPass<FxaaPass>()->setEnabled(false);
  //post.createPass<BloomPass>()->setEnabled(false);
  //post.createPass<DofPass>()->setEnabled(false);
  //post.createPass<KaleidoscopePass>()->setEnabled(false);
  //post.createPass<NoiseWarpPass>()->setEnabled(false);
  //post.createPass<PixelatePass>()->setEnabled(false);
  //post.createPass<EdgePass>()->setEnabled(false);
  //post.createPass<VerticalTiltShifPass>()->setEnabled(false);
  //post.createPass<GodRaysPass>()->setEnabled(false);

  //// Setup box positions
  //for (unsigned i = 0; i < NUM_BOXES; ++i)
  //{
  //  posns.push_back(ofVec3f(ofRandom(-300, 300), -300, ofRandom(-300, 300)));
  //  cols.push_back(ofColor::fromHsb(255 * i / (float)NUM_BOXES, 255, 255, 255));
  //}

  //// Setup light
  //light.setPosition(1000, 1000, -2000);

  //// create our own box mesh as there is a bug with
  //// normal scaling and ofDrawBox() at the moment
  //boxMesh = ofMesh::box(20, 20, 20);
  //sphereMesh = ofMesh::sphere(20);

  td_client_ = new TdClient();
  //td_client_->postJob();
  //while (td_client_->checkJobFinished()) {
  //  Sleep(3000);
  //}
  td_client_->setJobId(22296165);
  td_client_->fetchResult();
  kanseis_.push_back(td_client_->kanseis_.at(0));

  realtime_ = new Realtime([this](Kansei kansei){
    this->kanseis_.push_back(kansei);
  });
}

//--------------------------------------------------------------
void ofApp::update(){
  Team team = teams_.at(0);
  // time_position_ = ofGetElapsedTimeMillis() / 1000 % td_client_->kanseis_.size();
  time_position_ = kanseis_.size() - 1;
  visualizer_->update(kanseis_.at(time_position_));
  //bubble_frequency_ = pow(kanseis_.at(time_position_).concentration / 100 * 2, 4.0);
  //velocity_ = bubble_frequency_* sphere_per_second_;
  //ofSetWindowTitle(team.name + " : " + ofToString(ofGetFrameRate()) + " : concentration = " + std::to_string(kanseis_.at(time_position_).concentration));
  // Generate
  //int number_of_generate = ofRandom(bubble_frequency_ * sphere_per_second_);
  /*for (int i = 0; i < number_of_generate; i++) {
    posns.push_back(ofVec3f(ofRandom(-300, 300), -300, ofRandom(-300, 300)));
  }*/
  // Move
  /*for (int i = 0; i < posns.size(); i++) {
    posns.at(i).y += velocity_;
  }*/
  // Vanish
  /*posns.erase(remove_if(posns.begin(), posns.end(), [](ofVec3f position){
    if (position.y > 300)
      return true;
    return false;
  }), posns.end());*/
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
  //light.enable();

  //// begin scene to post process
  //post.begin(cam);

  //// draw boxes
  //for (unsigned i = 0; i < posns.size(); ++i)
  //{
  //  //ofSetColor(cols[i%cols.size()]);
  //  ofSetColor(team.base_color);
  //  ofPushMatrix();
  //  ofTranslate(posns[i]);
  //  //boxMesh.draw();
  //  sphereMesh.draw();
  //  ofPopMatrix();
  //}

  //ofDrawAxis(100);

  //// end scene and draw
  //post.end();

  //// set gl state back to original
  //glPopAttrib();

  // draw help
  /*ofSetColor(0, 255, 255);
  ofDrawBitmapString("Number keys toggle effects, mouse rotates scene", 10, 20);
  for (unsigned i = 0; i < post.size(); ++i)
  {
    if (post[i]->getEnabled()) ofSetColor(0, 255, 255);
    else ofSetColor(255, 0, 0);
    ostringstream oss;
    oss << i << ": " << post[i]->getName() << (post[i]->getEnabled() ? " (on)" : " (off)");
    ofDrawBitmapString(oss.str(), 10, 20 * (i + 2));
  }*/

  ofSetColor(0, 0, 0);
  ofDrawBitmapString(td_client_->getStr(), 10, 10);
  //ofDrawBitmapString(std::to_string(bubble_frequency_), 100, 100);
  ofNoFill();
  ofSetColor(0, 0, 0, 255);
  ofBeginShape();
  // ofVertex(x, y);
  for (int i = 0; i < td_client_->kanseis_.size(); i++) {
    //Kansei kansei = td_client_->kanseis_.at(i);
    Kansei kansei = kanseis_.at(kanseis_.size() - 1);
    ofVertex(
      ofGetViewportWidth() * i / td_client_->kanseis_.size(),
      isnan(kansei.concentration)?
      ofGetViewportHeight() / 2:
      ofGetViewportHeight() * (100.0 - kansei.concentration) / 100.0
    );
  }
  ofEndShape();
  ofLine(ofGetViewportWidth() * time_position_ / td_client_->kanseis_.size(), 0,
    ofGetViewportWidth() * time_position_ / td_client_->kanseis_.size(), ofGetViewportHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  visualizer_->keyPressed(key);
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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}