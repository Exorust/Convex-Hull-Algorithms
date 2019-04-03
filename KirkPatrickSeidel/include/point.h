#ifndef POINT
#define POINT
#include<iostream>
#include<string>
#include <bits/stdc++.h>
using namespace std;

#define MAX 1000.00
/**
 *  Point. Point class for the Kirk Patrick Seidel.
 */
class Point {
private:
public:
  /**< x value of the point */
  float x;
  /**< y value of the point */
  float y;
  /**
   * Empty constructor.
   * An empty constructor.
   */
  Point();

  /**
   * A constructor given the x and y value.
   * A constructor given the x and y value.
   */
  Point(float,float);

  /**
   * A Point& constructor.
   * A constructor given a point.
   */
  Point(const Point&);

    /**
   * A function which compares two points whether they are equal
   * @param a reference Point1.
   * @param b reference Point2.
   * @return true value if points are equal
   */
  bool static ValueCmp(Point const & a, Point const & b) {
    if(a.x != b.x){
      return a.x < b.x;
    }
    else {
      return a.y<b.y;
    }
  }
  /**
   * Checks the equality of points
   * @param  Point Point to check equality
   * @return       boolean value of euqlity
   */
  bool equal(Point);
  /**
   * Prints the point
   */
  void print_point();


  Point & operator = (const Point &);
  bool  operator < (const Point &);
};

#endif
