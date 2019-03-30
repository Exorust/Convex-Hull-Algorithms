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
  int total_points;
  vector<Point> point_list;

  Set();
  Set(const Set&);
  Set(vector<Point>);

  int size();
  void add(Point);
  void sorting();
  //DONT USE YET
  float median();
  pair<Set*,Set*>* partition();
  void joining(const Set*);

  bool ismin(Point*);
  bool ismax(Point*);
  

  void print_list();

};

#endif
