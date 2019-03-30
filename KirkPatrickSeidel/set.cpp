#include"include/set.h"
#include<iostream>
#include<string>
#include <bits/stdc++.h>
using namespace std;

Set::Set() {
  total_points = 0;
}

Set::Set(vector<Point> input) {
  vector<Point>::iterator it;
  for(it = input.begin();it != input.end();it++) {
    this-> point_list.push_back(*it);
    total_points++;
  }
}

Set::Set(const Set& input) {
  vector<Point>::const_iterator it;
  for(it = input.point_list.begin();it != input.point_list.end();it++) {
    this-> point_list.push_back(*it);
    total_points++;
  }
}

int Set::size() {
  return point_list.size();
}

void Set::add(Point p) {
  this-> point_list.push_back(p);
  total_points++;
}

void Set::sorting() {
  sort(Set::point_list.begin(),Set::point_list.end(),Point::ValueCmp);
}

float Set::median() {
  sorting();
  int len = point_list.size();
  // Median irrespective of odd/even
  return point_list[len/2].x;
}

void Set::print_list() {
  vector<Point>::iterator it;
  for(it = this->point_list.begin();it != this->point_list.end();it++) {
    it->print_point();
  }
}

void Set::joining(const Set* input) {
  vector<Point>::const_iterator it;
  for(it = input->point_list.begin();it != input->point_list.end();it++) {
    this-> point_list.push_back(*it);
    total_points++;
  }
}

bool Set::ismin(Point* p) {
  vector<Point>::iterator it = this->point_list.begin();
  if(it->x == p->x && it->y == p->y) {
    return true;
  }
  return false;
}

bool Set::ismax(Point* p) {
  vector<Point>::iterator it = this->point_list.end();
  it--;
  if(it->x == p->x && it->y == p->y) {
    return true;
  }
  return false;
}



pair<Set*,Set*>* Set::partition() {
  sorting();
  int len = point_list.size();

  vector<Point> lv(point_list.begin(),point_list.begin() + (len/2));
  Set* L = new Set(lv);

  vector<Point> rv(point_list.begin()+(len/2)+1,point_list.end());
  Set* R = new Set(rv);

  pair<Set*,Set*>* partition = new pair<Set*,Set*>;
  partition->first = L;
  partition->second = R;

  return partition;

}
