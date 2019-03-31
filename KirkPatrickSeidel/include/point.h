#ifndef POINT
#define POINT
#include<iostream>
#include<string>
#include <bits/stdc++.h>
using namespace std;

#define MAX 1000.00

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

  bool equal(Point*);

  void print_point();
  Point & operator = (const Point &);
  bool  operator < (const Point &);
};

#endif
