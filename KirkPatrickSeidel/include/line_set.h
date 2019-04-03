#ifndef LINESET
#define LINESET
#include"point.h"
#include"set.h"
#include<iostream>
#include<string>
#include <bits/stdc++.h>
using namespace std;

/**
 * [LineSet description]
 */
class LineSet{
public:
  /**< Total Points present. Sort of like counter to increment. */
  int total_points;
  /**< List of points in a vector format. */
  vector<Point> point_list;

  /**
   * Constructor for the LineSet
   */
  LineSet();

  /**
   * Joins two line set and returns the line set.
   * @param LineSet the LineSet to be joined
   */
  void joining(const LineSet);

  /**
   * Adds a point to the LineSet
   * @param Point The point to be added
   */
  void add(Point);

  /**
   * Adds a pair of points to the LineSet
   * @param  pair<Point, Point> A pair of points to be added.
   */
  void add(pair<Point, Point>);
  /**
   * Prints the points
   */
  void printing();

};

#endif
