#ifndef SET
#define SET
#include"point.h"
#include<iostream>
#include<string>
#include <bits/stdc++.h>
using namespace std;

class Set{
// private:
public:
  /**< Total Points present. Sort of like counter to increment. */
  int total_points;
  /**< List of points in a vector format. */
  vector<Point> point_list;

  /**
   * Empty Constructor
   */
  Set();
  /**
   * Copy Constructor for Set
   * @param Set& Set to be copied
   */
  Set(const Set&);
  Set(vector<Point>);

  /**
   * Returns the size of the Set
   * @return SIze of the set in an integer
   */
  int size();
  /**
   * Adds a point to the Set
   * @param Point The point to be added
   */
  void add(Point);

  //ONLY FOR TESTING
  void sorting();
  float median();

  /**
   * Returns the minimum point required by the upper hull
   * @return Point for the minimum of the upper hull
   */
  Point u_minimum();
  /**
   * Returns the maximum point required by the upper hull
   * @return Point for the maximum of the upper hull
   */
  Point u_maximum();

  /**
   * Partitions the set into L and R
   * @return Returns a pair of Sets
   */
  pair<Set*,Set*>* partition();
  /**
   * Joins two sets
   * @param Set joined set
   */
  void joining(const Set);

  /**
   * Confirms the minimum element of the set
   * @param  Point The point to verify if its the minimum
   * @return       Truth value
   */
  bool ismin(Point);
  /**
   * Confirms the maximum element of the set
   * @param  Point The point to verify if its the maximum
   * @return       Truth value
   */
  bool ismax(Point);

  /**
   * Prints the set
   */
  void print_list();

};

#endif
