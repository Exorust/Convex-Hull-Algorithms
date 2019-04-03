#include"include/point.h"
#include<iostream>
#include<string>
#include <bits/stdc++.h>
using namespace std;

/**
 * Empty constructor.
 * An empty constructor.
 */
Point::Point() {
  this->x = 0;
  this->y = 0;
}

/**
 * A Point& constructor.
 * A constructor given a point.
 */
Point::Point(const Point& p) {
  this->x = p.x;
  this->y = p.y;
}

/**
 * A constructor given the x and y value.
 * A constructor given the x and y value.
 */
Point::Point(float x,float y) {
  this->x = x;
  this->y = y;
}

/**
 * Prints the point
 */
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

/**
 * Checks the equality of points
 * @param  Point Point to check equality
 * @return       boolean value of euqlity
 */
bool Point::equal(Point p) {
  if(this->x == p.x && this->y == p.y) {
    return true;
  }
  return false;
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
