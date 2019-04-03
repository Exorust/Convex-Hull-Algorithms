#include"include/point.h"
#include"include/set.h"
#include"include/line_set.h"
#include<iostream>
#include<string>
#include <bits/stdc++.h>
using namespace std;

/**
 * Constructor for the LineSet
 */
LineSet::LineSet() {
  total_points = 0;
}

/**
 * Joins two line set and returns the line set.
 * @param input The LineSet to be joined
 */
void LineSet::joining(const LineSet input) {
  for(auto& it : input.point_list) {
    this-> point_list.push_back(it);
  }
}

/**
 * Adds a point to the LineSet
 * @param input The pair of points to be added
 */
void LineSet::add(pair<Point, Point> input) {
  // Point p_temp;
  // p_temp.x = input->first->x;
  // p_temp.y= input->first->y;
  // this-> point_list.push_back(p_temp);
  this->add(input.first);
  this->add(input.second);
}

/**
 * Adds a point to the LineSet
 * @param input The point to be added
 */
void LineSet::add(Point input) {
  Point p_temp;
  p_temp.x = input.x;
  p_temp.y= input.y;
  this-> point_list.push_back(p_temp);
}

/**
 * Prints the points
 */
void LineSet::printing() {
  vector<Point>::iterator it;
  for(it = this->point_list.begin();it != this->point_list.end();it++) {
    // printf("(%f %f)   (%f %f)\n", it->first.x,it->first.y,it->second.x,it->second.y );
    it->print_point();
    // printf("\t\t");
    // it->second.print_point();
  }
}
