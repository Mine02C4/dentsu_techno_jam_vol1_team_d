#pragma once

#include "ofMain.h"
#include <string>

struct Team{
  std::string name;
  ofColor base_color;
  Team(std::string name, ofColor base_color){
    this->name = name;
    this->base_color = base_color;
  }
};