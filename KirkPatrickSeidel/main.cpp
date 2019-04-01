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

bool AlmostEqualRelative(float A, float B,float maxRelDiff = FLT_EPSILON)
{
    // Calculate the difference.
    float diff = fabs(A - B);
    A = fabs(A);
    B = fabs(B);
    // Find the largest
    float largest = (B > A) ? B : A;
 
    if (diff <= largest * maxRelDiff)
        return true;
    return false;
}

pair<Point,Point> upper_bridge(Set input, float x_median) {
  pair<Point,Point> point_bridge;
  printf("U-Bridge %d START\n", input.size() );
  input.print_list();

  Set candidates;
  if(input.size() == 2) {
    Point first(input.point_list[0].x,input.point_list[0].y);
    Point second(input.point_list[1].x,input.point_list[1].y);
    point_bridge.first=first;
    point_bridge.second=second;
    printf("U-Bridge %d END (2PT)\n", input.size() );
    return point_bridge;
  }
  
  vector<pair<pair<Point,Point>,float> > LR_pairing;

  for(int index = 0;index < (input.size()/2);index++) {
    pair<pair<Point,Point>,float> temp;
    Point left,right;
    float slope;
    left = input.point_list[index];
    right = input.point_list[input.size()-1-index];
    if(left.x == right.x) {
      if(left.y >right.y) {
        candidates.add(left);
      }
      else {
        candidates.add(right);
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
  
  if(input.size()%2 !=0 ) {
    candidates.point_list.push_back(input.point_list[input.size()/2]);
  }

  sort(LR_pairing.begin(),LR_pairing.end(),sortbysec);

  
  float K_median = LR_pairing[LR_pairing.size() / 2].second;
  printf("K_median: %f\n", K_median );

  
  vector<pair<pair<Point,Point>,float> > small,equal,large;
 
  for(auto &it :LR_pairing) {
    printf("%f ", it.second );
    if(it.second < K_median) {
      small.push_back(it);
      
    }
    else if(it.second == K_median) {
      equal.push_back(it);
    }
    else if(it.second > K_median){
      large.push_back(it);
    }
    else {
      printf("What?\n");
    }
  }


  vector<Point > max;

  vector<pair<float,Point> > value_k;

  float max_value=DBL_MIN;

  for(auto &itx : input.point_list) {
    pair<float,Point> temp;
    float k_val = itx.y - K_median* (itx.x);
    temp.first=k_val;
    temp.second=itx;

    itx.print_point();
    cout<<"k_vals:" <<k_val<<endl;
    value_k.emplace_back(temp);
    if(max_value<k_val)
    {
      max_value=k_val;
    }
  }


  for(auto &itx : value_k)
  {
    if(itx.first<= max_value+0.00001 && itx.first >= max_value-0.00001)
    // if(AlmostEqualRelative(itx.first,max_value))
    {
      max.emplace_back(itx.second);
    }
  }

  //Obtain pk and pm
  sort(max.begin(),max.end(),Point::ValueCmp);

  cout<<"Max elements:"<<max.size();
  for(auto &itx: max) {
    itx.print_point();
  }
  cout<<endl;
  printf("\npkmin and pmmax");
  // Point temp = max[0].second;
  Point pk_min(max[0]);
  pk_min.print_point();
  // Point temp = max[max.size()-1].second;
  Point pm_max(max[max.size()-1]);
  pm_max.print_point();
  printf("\n");

  //Is h bridge?
  pair<Point,Point> final_val;
  if(pk_min.x < x_median && pm_max.x > x_median) {
    final_val.first = pk_min;
    final_val.second = pm_max;
    return final_val;
  }

  //h is only on the left
  if(pm_max.x <= x_median) {
    
    for(auto& it : large) {
      Point temp(it.first.second.x,it.first.second.y);
      candidates.add(temp);
    }
    for(auto& it : equal) {
      Point temp(it.first.second.x,it.first.second.y);
      candidates.add(temp);
    }
    for(auto& it : small) {
      Point tempf(it.first.first.x,it.first.first.y);
      candidates.add(tempf);
      Point temps(it.first.second.x,it.first.second.y);
      candidates.add(temps);
    }
  }

  //h is on the right
  if(pk_min.x > x_median ) {
    for(auto& it : large) {
      Point tempf(it.first.first.x,it.first.first.y);
      candidates.add(tempf);
      Point temps(it.first.second.x,it.first.second.y);
      candidates.add(temps);
    }
    for(auto& it : equal) {
      Point temp(it.first.first.x,it.first.first.y);
      candidates.add(temp);
    }
    for(auto& it : small) {
      Point temp(it.first.first.x,it.first.first.y);
      candidates.add(temp);
    }
  }

  printf("U-Bridge %d END\n", input.size() );
  return upper_bridge(candidates,x_median);
}

////upper hull algo

LineSet upper_hull(Point p_min, Point p_max, Set input) {
  printf("U-Hull %d START\n", input.size() );
  input.print_list();

  LineSet con_hull;
  float x_median = input.median();
  
  if(p_min.x == p_max.x && p_min.y == p_max.y ) {
    con_hull.add(p_min);
    printf("Hit edge\n");
    return con_hull;
  }

  if(input.size() == 1 ) {
    con_hull.add(input.point_list[0]);
    printf("Hit edge\n");
    return con_hull;
  }

  pair<Point,Point> point_bridge = upper_bridge(input,x_median);
  printf("POINT BRIDGE OBTAINED\n");
  point_bridge.first.print_point();
  point_bridge.second.print_point();
  cout<<endl;
  Point i = point_bridge.first;
  Point j = point_bridge.second;

  Set L_dash;
  Set R_dash;

  Point tempi(i.x,i.y);
  Point tempj(j.x,j.y);
  L_dash.add(tempi);
  R_dash.add(tempj);

  //L_dash
  for(auto& it :input.point_list) {
    Point n(it.x-p_min.x,it.y-p_min.y);
    Point m(i.x-p_min.x,i.y-p_min.y);
    float left_sign = n.x*m.y - n.y*m.x;
    if(left_sign < 0) {
      Point temp(it.x,it.y);
      L_dash.add(temp);
    }
  }
  cout<<"printing l dash"<<endl;
  L_dash.print_list();

  //R_dash
  for(auto& it :input.point_list) {
    Point n(it.x-p_max.x,it.y-p_max.y);
    Point m(j.x-p_max.x,j.y-p_max.y);
    float right_sign = n.x*m.y - n.y*m.x;
    if(right_sign > 0) {
      Point temp(it.x,it.y);
      R_dash.add(temp);
    }
  }
  
  cout<<"printing r dash"<<endl;
  R_dash.print_list();  

    LineSet L_upper_hull = upper_hull(p_min, i, L_dash);
    cout<<"L uh";
    L_upper_hull.printing();
    cout<<endl;
    LineSet R_upper_hull = upper_hull(j, p_max, R_dash);
    cout<<"R uh";
    R_upper_hull.printing();
    cout<<endl;
    con_hull.joining(L_upper_hull);
    // DONT ADD PT BRIDGE
    // con_hull->add(point_bridge);
    con_hull.joining(R_upper_hull);

    cout<< "SIZE CON HULL"<<con_hull.point_list.size()<<endl;

  printf("U-Hull %d END\n ",input.size());


  return con_hull;

}

LineSet kirk_patrick_seidel(Set input) {

  //TODO: Change a new Con hull object`
  Point u_min = input.minimum();
  Point u_max = input.maximum();
  LineSet upper = upper_hull(u_min,u_max,input);
  // upper.add(u_min);
  // upper.add(u_max);
  // Set* lower = lower_hull(input);
  // upper->join(lower);
  return upper;
}


int main(int argc, char const *argv[]) {
  printf("Enter the number of points\n");
  int total_points;
  scanf("%d",&total_points);
  Set all_points;
  for(int index = 0;index<total_points;index++) {
    float x,y;
    scanf("%f %f", &x,&y );
    Point p(x,y);
    all_points.add(p);
  }
  all_points.sorting();

  // //Testing
  // all_points->sorting();
  // all_points->print_list();
  // printf("======\n");
  // pair<Set*,Set*>* p = all_points->partition();
  // p->first->print_list();
  // printf("======\n");
  // p->second->print_list();

  LineSet result = kirk_patrick_seidel(all_points);
  result.printing();


  return 0;
}
