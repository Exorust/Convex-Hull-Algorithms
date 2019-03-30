#include"include/point.h"
#include"include/set.h"
#include"include/line_set.h"
#include<iostream>
#include<string>
#include <bits/stdc++.h>
using namespace std;

LineSet::LineSet() {
  total_points = 0;
}


void LineSet::joining(const LineSet* input) {
  vector<pair<Point,Point> >::const_iterator it;
  for(it = input->point_list.begin();it != input->point_list.end();it++) {
    this-> point_list.push_back(*it);
  }
}

void LineSet::add(pair<Point*,Point*>* input) {
  pair<Point,Point> p_temp;
  // p_temp.first = *(input->first);
  // p_temp.second = *(input->second);
  this-> point_list.push_back(p_temp);
}

void LineSet::printing() {
  vector<pair<Point,Point> >::const_iterator it;
  for(it = this->point_list.begin();it != this->point_list.end();it++) {
    printf("(%f %f)   (%f %f)\n", it->first.x,it->first.y,it->second.x,it->second.y );
    // it->first.print_point();
    // printf("\t\t");
    // it->second.print_point();
  }
}
