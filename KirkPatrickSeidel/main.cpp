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

float sign(Point* p1, Point* p2, Point* p) {
  Point n(p->x-p1->x,p->y-p1->y);
  Point m(p2->x-p1->x,p2->y-p1->y);
  float d = n.x*m.y - n.y*m.x;
  return d;
}

pair<Point*,Point*>* upper_bridge(Set* input, float x_median) {
  pair<Point*,Point*>* point_bridge = new pair<Point*,Point*>();
  printf("U-Bridge %d START\n", input->size() );
  input->print_list();

  Set* candidates = new Set();
  if(input->size() == 2) {
    point_bridge->first = new Point(input->point_list[0].x,input->point_list[0].y);
    point_bridge->second = new Point(input->point_list[1].x,input->point_list[1].y);
    printf("U-Bridge %d END (2PT)\n", input->size() );
    return point_bridge;
  }
  // if(input->size() == 1) {
  //   // Point* temp1 = new Point(input->point_list[0].x,input->point_list[0].y);
  //   // Point* temp2 = new Point(MAX,MAX);
  //   // point_bridge->first = temp1;
  //   // point_bridge->second = temp2;
  //   // return point_bridge;
  //   input->print_list();
  // }
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
        candidates->add(right);
      }
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
  // float K_median =0.0;
  // if(LR_pairing.size()%2 == 0) {
  //   K_median += LR_pairing[LR_pairing.size() / 2].second;
  //   K_median += LR_pairing[(LR_pairing.size() / 2)-1].second;
  //   K_median /=2;
  // }
  // else {
  //   K_median = LR_pairing[LR_pairing.size() / 2].second;
  // }

  float K_median = LR_pairing[LR_pairing.size() / 2].second;
  printf("K_median: %f\n", K_median );

  //Find small, equal, large
  vector<pair<pair<Point,Point>,float> > small,equal,large;
  vector<pair<pair<Point,Point>,float> >::iterator it;
  for(it = LR_pairing.begin();it != LR_pairing.end();it++) {
    printf("%f ", (*it).second );
    if((*it).second < K_median) {
      small.push_back(*it);
      // printf("s\n" );
    }
    else if((*it).second == K_median) {
      equal.push_back(*it);
      // printf("eq\n" );

    }
    else if((*it).second > K_median){
      large.push_back(*it);
      // printf("l\n" );

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
  printf("\npkmin and pmmax");
  // Point temp = max[0].second;
  Point* pk_min = new Point(max[0].second);
  pk_min->print_point();
  // Point temp = max[max.size()-1].second;
  Point* pm_max = new Point(max[max.size()-1].second);
  pk_min->print_point();
  printf("\n");

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

  printf("U-Bridge %d END\n", input->size() );
  return upper_bridge(candidates,x_median);
}

LineSet* upper_hull(Point* p_min, Point* p_max, Set* input) {
  printf("U-Hull %d START\n", input->size() );
  input->print_list();

  //TODO: Change a new Con hull object
  LineSet* con_hull = new LineSet();
  // pair<Set*,Set*>* LR_pair = input->partition();
  float x_median = input->median();
  // printf("%d\n",input->total_points);
  // printf("%f\n", x_median);

  //Abort for 1 pt.
  if(input->size() == 1 ) {
    // con_hull->add(input->point_list[0]);
    printf("Hit error\n");
    // return con_hull;
    // input->print_list();
  }

  // // Abort for 2 pt.
  // if(input->size() == 2 ) {
  //   con_hull->add(input->point_list[0]);
  //   con_hull->add(input->point_list[1]);
  //   printf("Hit edge\n");
  //   return con_hull;
  // }

  // pmin == pmax Condition
  if(p_min->x == p_max->x && p_min->y == p_max->y ) {
    con_hull->add(p_min);
    // con_hull->add(p_max);
    printf("Hit edge\n");
    return con_hull;
  }

  pair<Point*,Point*>* point_bridge = upper_bridge(input,x_median);
  printf("POINT BRIDGE OBTAINED\n");
  point_bridge->first->print_point();
  point_bridge->second->print_point();
  Point* i = point_bridge->first;
  Point* j = point_bridge->second;

  Set* L_dash = new Set();
  Set* R_dash = new Set();

  vector<Point>::iterator it;

  Point tempi(i->x,i->y);
  Point tempj(j->x,j->y);
  L_dash->add(tempi);
  R_dash->add(tempj);

  //L_dash
  for(it = input->point_list.begin();it != input->point_list.end();it++) {
    Point n(it->x-p_min->x,it->y-p_min->y);
    Point m(i->x-p_min->x,i->y-p_min->y);
    float left_sign = n.x*m.y - n.y*m.x;
    if(left_sign < 0) {
      Point temp(it->x,it->y);
      L_dash->add(temp);
    }
  }

  //R_dash
  for(it = input->point_list.begin();it != input->point_list.end();it++) {
    Point n(it->x-p_max->x,it->y-p_max->y);
    Point m(j->x-p_max->x,j->y-p_max->y);
    float right_sign = n.x*m.y - n.y*m.x;
    if(right_sign > 0) {
      Point temp(it->x,it->y);
      R_dash->add(temp);
    }
  }


  // // Generate L_dash and R_dash
  // Point tempi(i->x,i->y);
  // Point tempj(j->x,j->y);
  // L_dash->add(tempi);
  // R_dash->add(tempj);
  // vector<Point>::iterator it;
  // for(it = input->point_list.begin();it != input->point_list.end();it++) {
  //   if(it->x < i->x) {
  //     Point temp(it->x,it->y);
  //     L_dash->add(temp);
  //   }
  //   if(it->x > j->x) {
  //     Point temp(it->x,it->y);
  //     R_dash->add(temp);
  //   }
  // }

  // if(input->ismin(i)) {
  //   //TODO
  //   i->print_point();
  // }
  // else {
  //   LineSet* L_upper_hull = upper_hull(L_dash);
  //   con_hull->joining(L_upper_hull);
  //
  // }
  //
  // con_hull->add(point_bridge);
  //
  // if(input->ismax(j)) {
  //   //TODO
  //   j->print_point();
  // }
  // else {
  //   LineSet* R_upper_hull = upper_hull(R_dash);
  //   // con_hull->add(point_bridge);
  //   con_hull->joining(R_upper_hull);
  //
  // }

    LineSet* L_upper_hull = upper_hull(p_min, i, L_dash);
    LineSet* R_upper_hull = upper_hull(j, p_max, R_dash);
    con_hull->joining(L_upper_hull);
    // con_hull->add(point_bridge);
    con_hull->joining(R_upper_hull);

  //TODO: Check if both i and j are same?
  // con_hull->add(point_bridge);

  // //Freeing
  // free (L_dash);
  // free (R_dash);
  // free (L_upper_hull);
  // free (R_upper_hull);
  printf("U-Hull %d END\n ",input->size());


  return con_hull;

}

LineSet* kirk_patrick_seidel(Set* input) {

  //TODO: Change a new Con hull object`
  Point* u_min = input->minimum();
  Point* u_max = input->maximum();
  LineSet* upper = upper_hull(u_min,u_max,input);
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
  all_points->sorting();

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
