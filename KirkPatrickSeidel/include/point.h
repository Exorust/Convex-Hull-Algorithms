#ifndef POINT
#define POINT
#include<iostream>
#include<string>
#include <bits/stdc++.h>
using namespace std;

class Point {
private:
public:
  float x;
  float y;
  Point();
  Point(float,float);
  Point(const Point&);
  bool static ValueCmp(Point const & a, Point const & b) {
    if(a.x != b.x){
      return a.x < b.x;
    }
    else {
      return a.y<b.y;
    }
  }
  void print_point();
  Point & operator = (const Point &);
  bool  operator < (const Point &);
};

#endif
