#include"include/set.h"
#include<iostream>
#include<string>
#include <bits/stdc++.h>
using namespace std;

/**
 * Empty Constructor
 */
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

/**
 * Copy Constructor for Set
 * @param Set& Set to be copied
 */
Set::Set(const Set& input) {
  vector<Point>::const_iterator it;
  for(it = input.point_list.begin();it != input.point_list.end();it++) {
    this-> point_list.push_back(*it);
    total_points++;
  }
}

/**
 * Returns the size of the Set
 * @return SIze of the set in an integer
 */
int Set::size() {
  return point_list.size();
}

/**
 * Returns the minimum point required by the upper hull
 * @return Point for the minimum of the upper hull
 */
Point Set::u_minimum() {
  Point temp(point_list[0]);
  float x_val = temp.x;
  float y_val = temp.y;
  for(auto& it : point_list) {
    if(it.x<= x_val+0.00001 && it.x >= x_val-0.00001)
    {
      if(y_val < it.y)
      {
        temp.y= it.y;
        y_val= it.y;
      }
    }

    else if(x_val > it.x) {
      temp.x = it.x;
      x_val = it.x;
      y_val = it.y;
      temp.y = it.y;
    }
  }
  return temp;
}

/**
 * Returns the maximum point required by the upper hull
 * @return Point for the maximum of the upper hull
 */
Point Set::u_maximum() {
  Point temp(point_list[0]);
  float x_val = temp.x;
  float y_val = temp.y;
  for(auto& it : point_list) {
    if(it.x<= x_val+0.00001 && it.x >= x_val-0.00001)
    {
      if(y_val < it.y)
      {
        temp.y=it.y;
        y_val = it.y;
      }
    }

    else if(x_val < it.x) {
      temp.x =it.x;
      x_val =it.x;
      y_val =it.y;
      temp.y = it.y;
    }
  }
  return temp;
}

/**
 * Adds a point to the Set
 * @param Point The point to be added
 */
void Set::add(Point p) {
  this-> point_list.push_back(p);
  total_points++;
}

void Set::sorting() {
  sort(Set::point_list.begin(),Set::point_list.end(),Point::ValueCmp);
}


//median function----------------------------------------------------------------------------

//median function------------------------------------------------------------------------------

/**
 * Prints the set
 */
void Set::print_list() {
  vector<Point>::iterator it;
  for(it = this->point_list.begin();it != this->point_list.end();it++) {
    it->print_point();
    printf("\n" );
  }
}

/**
 * Joins two sets
 * @param Set joined set
 */
void Set::joining(const Set input) {
  vector<Point>::const_iterator it;
  for(it = input.point_list.begin();it != input.point_list.end();it++) {
    this-> point_list.push_back(*it);
    total_points++;
  }
  // sorting();
}

/**
 * Confirms the minimum element of the set
 * @param  Point The point to verify if its the minimum
 * @return       Truth value
 */
bool Set::ismin(Point p) {
  // sorting();
  vector<Point>::iterator it = this->point_list.begin();
  // if(it->x == p->x && it->y == p->y) {
  if(it->x == p.x ) {
    return true;
  }
  return false;
}

/**
 * Confirms the maximum element of the set
 * @param  Point The point to verify if its the maximum
 * @return       Truth value
 */
bool Set::ismax(Point p) {
  // sorting();
  vector<Point>::iterator it = this->point_list.end();
  it--;
  // if(it->x == p->x && it->y == p->y) {
  if(it->x == p.x ) {
    return true;
  }
  return false;
}


/**
 * Partitions the set into L and R
 * @return Returns a pair of Sets
 */
pair<Set*,Set*>* Set::partition() {
  // sorting();
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
