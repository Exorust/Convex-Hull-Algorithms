#ifndef LINESET
#define LINESET
#include"point.h"
#include"set.h"
#include<iostream>
#include<string>
#include <bits/stdc++.h>
using namespace std;

class LineSet{
// private:
public:
  int total_points;
  vector<pair<Point,Point> > point_list;

  LineSet();

  void joining(const LineSet*);
  void add(pair<Point*,Point*>*);
  void printing();

};

#endif