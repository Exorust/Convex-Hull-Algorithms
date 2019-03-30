#include"include/point.h"
#include<iostream>
#include<string>
#include <bits/stdc++.h>
using namespace std;

Point::Point() {
  this->x = 0;
  this->y = 0;
}

Point::Point(const Point& p) {
  this->x = p.x;
  this->y = p.y;
}

Point::Point(float x,float y) {
  this->x = x;
  this->y = y;
}

void Point::print_point() {
  printf("(%f %f) ", this->x,this->y );
}

Point & Point::operator = (const Point &p) {
  // Check for self assignment
  if(!(this->x == p.x && this->y == p.y)){
    this->x = p.x;
    this->y = p.y;
  }
  return *this;
}

bool  Point::operator < (const Point &p) {
  // Check for self assignment
  if(this->x != p.x){
    if(this->x < p.x)
      return true;
    else
      return false;
  }
  else {
    if(this->y<p.y)
      return true;
    else
      return false;
  }
}
