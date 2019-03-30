#include"include/point.h"
#include"include/set.h"
#include"include/line_set.h"
#include<iostream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

bool sortbysec(const pair<pair<Point,Point>,float> &a, const  pair<pair<Point,Point>,float> &b) {
    return (a.second < b.second);
}


bool sortbysecpf(const pair<float,Point> &a, const  pair<float,Point> &b) {
    return (a.first < b.first);
}

pair<Point*,Point*>* upper_bridge(Set* input, float x_median) {

  pair<Point*,Point*>* point_bridge;

  Set* candidates = new Set(); //?? Or not pointer?
  if(input->size() == 2) {
    Point* temp1 = new Point(input->point_list[0].x,input->point_list[0].y);
    Point* temp2 = new Point(input->point_list[1].x,input->point_list[1].y);
    point_bridge->first = temp1;
    point_bridge->second = temp2;
    return point_bridge;
  }
  if(input->size() == 1) {
    Point* temp1 = new Point(input->point_list[0].x,input->point_list[0].y);
    Point* temp2 = new Point(1000.00,1000.00);
    point_bridge->first = temp1;
    point_bridge->second = temp2;
    return point_bridge;
  }
  //FILL
  //define vector
  vector<pair<pair<Point,Point>,float> > LR_pairing;

  for(int index = 0;index < (input->size()/2);index++) {
    pair<pair<Point,Point>,float> temp;
    Point left,right;
    float slope;
    left = input->point_list[index];
    right = input->point_list[input->size()-1-index];
    if(left.x == right.x) {
      if(left.y >right.y) {
        candidates->add(left);
      }
      else {
        candidates->add(right)
;      }
    }
    else {
      slope = (right.y-left.y)/(right.x-left.x);
      temp.first.first = left;
      temp.first.second = right;
      temp.second = slope;
      LR_pairing.push_back(temp);
    }
  }
  // If odd add the point inside
  if(input->size()%2 !=0 ) {
    candidates->point_list.push_back(input->point_list[input->size()/2]);
  }

  sort(LR_pairing.begin(),LR_pairing.end(),sortbysec);

  //Find K
  float K_median = LR_pairing[LR_pairing.size() / 2].second;

  //Find small, equal, large
  vector<pair<pair<Point,Point>,float> > small,equal,large;
  vector<pair<pair<Point,Point>,float> >::iterator it;
  for(it = LR_pairing.begin();it != LR_pairing.end();it++) {
    if((*it).second < K_median) {
      small.push_back(*it);
    }
    else if((*it).second == K_median) {
      equal.push_back(*it);
    }
    else if((*it).second < K_median){
      large.push_back(*it);
    }
    else {
      // abort();
      printf("What?\n");
    }
  }

  //Find a supporting line
  vector<pair<float,Point> > max;
  vector<Point>::iterator itx;
  for(itx = input->point_list.begin();itx != input->point_list.end();itx++) {
    pair<float,Point> temp;
    float k_val = itx->y - K_median* (itx->x);
    if(max.size() == 0) {
      temp.first = k_val;
      temp.second = *itx;
      max.push_back(temp);
    }
    else {
      if(max[0].first < k_val ) {
        max.clear();
        temp.first = k_val;
        temp.second = *itx;
        max.push_back(temp);
      }
      else if( max[0].first == k_val ) {
        temp.first = k_val;
        temp.second = *itx;
        max.push_back(temp);
      }
    }
  }

  //Obtain pk and pm
  sort(max.begin(),max.end(),sortbysecpf);
  // Point temp = max[0].second;
  Point* pk_min = new Point(max[0].second);
  // Point temp = max[max.size()-1].second;
  Point* pm_max = new Point(max[max.size()-1].second);

  //Is h bridge?
  pair<Point*,Point*>* final_val;
  if(pk_min->x < x_median && pm_max->x > x_median) {
    final_val->first = pk_min;
    final_val->second = pm_max;
    return final_val;
  }

  //h is only on the left
  if(pm_max->x <= x_median) {
    vector<pair<pair<Point,Point>,float> >::iterator it;
    for(it = large.begin();it != large.end();it++) {
      Point temp(it->first.second.x,it->first.second.y);
      candidates->add(temp);
    }
    for(it = equal.begin();it != equal.end();it++) {
      Point temp(it->first.second.x,it->first.second.y);
      candidates->add(temp);
    }
    for(it = small.begin();it != small.end();it++) {
      Point tempf(it->first.first.x,it->first.first.y);
      candidates->add(tempf);
      Point temps(it->first.second.x,it->first.second.y);
      candidates->add(temps);
    }
  }

  //h is on the right
  if(pk_min->x > x_median ) {
    vector<pair<pair<Point,Point>,float> >::iterator it;
    for(it = large.begin();it != large.end();it++) {
      Point tempf(it->first.first.x,it->first.first.y);
      candidates->add(tempf);
      Point temps(it->first.second.x,it->first.second.y);
      candidates->add(temps);
    }
    for(it = equal.begin();it != equal.end();it++) {
      Point temp(it->first.first.x,it->first.first.y);
      candidates->add(temp);
    }
    for(it = small.begin();it != small.end();it++) {
      Point temp(it->first.first.x,it->first.first.y);
      candidates->add(temp);
    }
  }


  return upper_bridge(candidates,x_median);
}

LineSet* upper_hull(Set* input) {
  //TODO: Change a new Con hull object`
  LineSet* con_hull = new LineSet();
  // pair<Set*,Set*>* LR_pair = input->partition();
  float x_median = input->median();
  printf("%d\n",input->total_points);
  // printf("%f\n", x_median);
  pair<Point*,Point*>* point_bridge = upper_bridge(input,x_median);
  Point* i = point_bridge->first;
  Point* j = point_bridge->second;
  Set* L_dash = new Set();
  Set* R_dash = new Set();

  // Generate L_dash and R_dash
  Point tempi(i->x,i->y);
  Point tempj(j->x,j->y);
  L_dash->add(tempi);
  R_dash->add(tempj);
  vector<Point>::iterator it;
  for(it = input->point_list.begin();it != input->point_list.end();it++) {
    if(it->x < i->x) {
      Point temp(it->x,it->y);
      L_dash->add(temp);
    }
    if(it->x > j->x) {
      Point temp(it->x,it->y);
      R_dash->add(temp);
    }
  }

  if(input->ismin(i)) {
    //TODO
    i->print_point();
  }
  else {
    LineSet* L_upper_hull = upper_hull(L_dash);
    con_hull->joining(L_upper_hull);
  }
  if(input->ismax(j)) {
    //TODO
    j->print_point();
  }
  else {
    LineSet* R_upper_hull = upper_hull(R_dash);
    con_hull->joining(R_upper_hull);
  }

  //TODO: Check if both i and j are same?
  con_hull->add(point_bridge);

  // //Freeing
  // free (L_dash);
  // free (R_dash);
  // free (L_upper_hull);
  // free (R_upper_hull);

  return con_hull;

}

LineSet* kirk_patrick_seidel(Set* input) {

  //TODO: Change a new Con hull object`
  LineSet* upper = upper_hull(input);
  // Set* lower = lower_hull(input);
  // upper->join(lower);
  return upper;
}


int main(int argc, char const *argv[]) {
  printf("Enter the number of points\n");
  int total_points;
  scanf("%d",&total_points);
  Set* all_points = new Set();
  for(int index = 0;index<total_points;index++) {
    float x,y;
    scanf("%f %f", &x,&y );
    Point p(x,y);
    all_points->add(p);
  }

  // //Testing
  // all_points->sorting();
  // all_points->print_list();
  // printf("======\n");
  // pair<Set*,Set*>* p = all_points->partition();
  // p->first->print_list();
  // printf("======\n");
  // p->second->print_list();

  LineSet* result = kirk_patrick_seidel(all_points);
  result->printing();


  return 0;
}
