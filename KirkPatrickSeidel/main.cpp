#include"include/point.h"
#include"include/set.h"
#include"include/line_set.h"
#include<iostream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

ofstream myfile;
ofstream inputfile;


Point calpk_min(vector<Point>max){
  Point min_point(max[0].x,max[0].y);
  for(auto &it:max)
  {
    if(min_point.x>it.x)
    {
      min_point.x=it.x;
      min_point.y=it.y;
    }
  }
  return min_point;
}

Point calpm_max(vector<Point>max){
  Point min_point(max[0].x,max[0].y);
  for(auto &it:max)
  {
    if(min_point.x<it.x)
    {
      min_point.x=it.x;
      min_point.y=it.y;
    }
  }
  return min_point;
}
bool float_equal(float x, float y)
{
  if(x<= y+0.00001 && x >= y-0.00001)
    return true;
  return false;
}



//median-------------------------------------------------------------------------------------
void swap(float *a, float *b)
{
    float temp = *a;
    *a = *b;
    *b = temp;
}

// It searches for x in arr[l..r], and partitions the array
// around x.
int partition(float arr[], int l, int r, float x)
{
    // Search for x in arr[l..r] and move it to end
    int i;
    for (i=l; i<r; i++)
        if (arr[i] == x)
           break;
    swap(&arr[i], &arr[r]);

    // Standard partition algorithm
    i = l;
    for (int j = l; j <= r - 1; j++)
    {
        if (arr[j] <= x)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[r]);
    return i;
}


// A simple function to find median of arr[].  This is called
// only for an array of size 5 in this program.
float findMedian(float arr[], int n)
{
    sort(arr, arr+n);  // Sort the array
    return arr[n/2];   // Return middle element
}

// Returns k'th smallest element in arr[l..r] in worst case
// linear time. ASSUMPTION: ALL ELEMENTS IN ARR[] ARE DISTINCT
float kthSmallest(float arr[], int l, int r, int k)
{
    // If k is smaller than number of elements in array
    if (k > 0 && k <= r - l + 1)
    {
        int n = r-l+1; // Number of elements in arr[l..r]

        // Divide arr[] in groups of size 5, calculate median
        // of every group and store it in median[] array.
        int i;
        float median[(n+4)/5]; // There will be floor((n+4)/5) groups;
        for (i=0; i<n/5; i++)
            median[i] = findMedian(arr+l+i*5, 5);
        if (i*5 < n) //For last group with less than 5 elements
        {
            median[i] = findMedian(arr+l+i*5, n%5);
            i++;
        }

        // Find median of all medians using recursive call.
        // If median[] has only one element, then no need
        // of recursive call
        float medOfMed = (i == 1)? median[i-1]:
                                 kthSmallest(median, 0, i-1, i/2);

        // Partition the array around a random element and
        // get position of pivot element in sorted array
        int pos = partition(arr, l, r, medOfMed);

        // If position is same as k
        if (pos-l == k-1)
            return arr[pos];
        if (pos-l > k-1)  // If position is more, recur for left
            return kthSmallest(arr, l, pos-1, k);

        // Else recur for right subarray
        return kthSmallest(arr, pos+1, r, k-pos+l-1);
    }

    // If k is more than number of elements in array
    return FLT_MAX;
}


float median(Set input) {
  int len = input.point_list.size();
  float arr[len];
  int i=0;

  for(auto it:input.point_list)
  {
    arr[i++]=it.x;
  }
  // Median irrespective of odd/even
  return kthSmallest(arr,0,len-1,len/2+1);
}

float median(vector<pair<pair<Point,Point>,float> > input) {
  int len = input.size();
  float arr[len];
  int i=0;

  for(auto it:input)
  {
    arr[i++]=it.second;
  }
  // Median irrespective of odd/even
  return kthSmallest(arr,0,len-1,len/2+1);
}
//median------------------------------------------------------------------------



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

pair<Point,Point> upper_bridge(Set input, float x_median) {
  pair<Point,Point> point_bridge;
  printf("U-Bridge %d START\n", input.size() );
  input.print_list();

  Set candidates;
  if(input.size()==1)
  {
    return make_pair(input.point_list[0],input.point_list[0]);
  }

  if(input.size() == 2) {
    Point first(input.point_list[0].x,input.point_list[0].y);
    Point second(input.point_list[1].x,input.point_list[1].y);
    if(first.x<second.x)
    {
      point_bridge.first=first;
      point_bridge.second=second;
    }
    else
    {
      point_bridge.first=second;
      point_bridge.second=first;
    }
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
      if(left.x<right.x)
      {
        temp.first.first=left;
        temp.first.second=right;
      }
      else
      {
        temp.first.first=right;
        temp.first.second=left;
      }

      temp.second = slope;
      LR_pairing.push_back(temp);
    }
  }

  if(input.size()%2 !=0 ) {
    candidates.point_list.push_back(input.point_list[input.size()/2]);
  }

  // sort(LR_pairing.begin(),LR_pairing.end(),sortbysec);
  if(LR_pairing.size()==0)
  {
    return upper_bridge(candidates,x_median);
  }
  float K_median = median(LR_pairing);
  printf("K_median: %f\n", K_median );


  vector<pair<Point,Point> > small,equal,large;

  for(auto &it :LR_pairing) {
    printf("%f ", it.second );
    if(it.second < K_median) {
      small.push_back(it.first);
    }
    else if(float_equal(it.second,K_median)) {
      equal.push_back(it.first);
    }
    else if(it.second > K_median){
      large.push_back(it.first);
    }
  }

  cout<<endl<<"small:"<<endl;
  for(auto &it :small)
  {
    cout<<it.first.x<<" "<<it.first.y<<"\t"<<it.second.x<<" "<<it.second.y<<endl;
  }
  cout<<endl<<"small ended:"<<endl;
  cout<<endl<<"equal:"<<endl;
  for(auto &it :equal)
  {
    cout<<it.first.x<<" "<<it.first.y<<"\t"<<it.second.x<<" "<<it.second.y<<endl;
  }
  cout<<endl<<"equal ended:"<<endl;
  cout<<endl<<"large:"<<endl;
  for(auto &it :large)
  {
    cout<<it.first.x<<" "<<it.first.y<<"\t"<<it.second.x<<" "<<it.second.y<<endl;
  }
  cout<<endl<<"large ended:"<<endl;

  vector<Point> max;

  vector<pair<float,Point> > value_k;

  float max_value= - FLT_MAX;

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
  // sort(max.begin(),max.end(),Point::ValueCmp);

  cout<<"Max elements:"<<max.size();
  for(auto &itx: max) {
    itx.print_point();
  }
  cout<<endl;
  printf("\npkmin and pmmax");
  // Point temp = max[0].second;
  Point pk_min=calpk_min(max);
  pk_min.print_point();
  // Point temp = max[max.size()-1].second;
  Point pm_max=calpm_max(max);
  pm_max.print_point();
  printf("\n");
  cout<<"x median: "<<x_median<<endl;
  //Is h bridge?
  pair<Point,Point> final_val;
  if(pk_min.x <= x_median && pm_max.x > x_median) {
    final_val.first = pk_min;
    final_val.second = pm_max;
    return final_val;
  }

  //h is only on the left
  if(pm_max.x <= x_median) {

    for(auto& it : large) {
      Point temp(it.second.x,it.second.y);
      candidates.add(temp);
    }
    for(auto& it : equal) {
      Point temp(it.second.x,it.second.y);
      candidates.add(temp);
    }
    for(auto& it : small) {
      Point tempf(it.first.x,it.first.y);
      candidates.add(tempf);
      Point temps(it.second.x,it.second.y);
      candidates.add(temps);
    }
  }

  //h is on the right
  if(pk_min.x > x_median ) {
    for(auto& it : large) {
      Point tempf(it.first.x,it.first.y);
      candidates.add(tempf);
      Point temps(it.second.x,it.second.y);
      candidates.add(temps);
    }
    for(auto& it : equal) {
      Point temp(it.first.x,it.first.y);
      candidates.add(temp);
    }
    for(auto& it : small) {
      Point temp(it.first.x,it.first.y);
      candidates.add(temp);
    }
  }

  cout<<"candidates:"<<endl;
  candidates.print_list();
  cout<<endl<<endl;
  printf("U-Bridge %d END\n", input.size() );
  return upper_bridge(candidates,x_median);
}

////upper hull algo

LineSet upper_hull(Point p_min, Point p_max, Set input) {
  LineSet con_hull;
  if((p_min.x == p_max.x && p_min.y == p_max.y) || (input.size()==1)) {
    con_hull.add(p_min);
    printf("Hit edge Equality \n");
    return con_hull;
  }

  printf("U-Hull %d START\n", input.size() );
  // input.print_list();

  float x_median = median(input);

  pair<Point,Point> point_bridge = upper_bridge(input,x_median);
  printf("POINT BRIDGE OBTAINED---------------------------\n");
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
  //See
  L_dash.add(p_min);
  R_dash.add(p_max);

  cout<<"x_median:"<<x_median<<endl;
  cout<<"p_min:";
  p_min.print_point();
  cout<<"p_max:";
  p_max.print_point();

  //L_dash
  for(auto& it :input.point_list) {
      float left_sign =(it.y-p_min.y)*(tempi.x-p_min.x) - (it.x-p_min.x)*(tempi.y-p_min.y) ;
      if(left_sign > 0) {
        L_dash.add(it);
     }
  }
  cout<<"printing l dash"<<endl;
  L_dash.print_list();

  //R_dash
  for(auto& it :input.point_list) {
      float left_sign =(it.y-p_min.y)*(tempi.x-p_min.x) - (it.x-p_min.x)*(tempi.y-p_min.y) ;
      if(left_sign > 0) {
        R_dash.add(it);
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

    con_hull.joining(R_upper_hull);

    cout<< "SIZE CON HULL"<<con_hull.point_list.size()<<endl;

  printf("U-Hull %d END\n ",input.size());


  return con_hull;

}

LineSet kirk_patrick_seidel(Set input) {

  cout<<endl<<"upper:"<<endl;
  Point u_min = input.u_minimum();
  Point u_max = input.u_maximum();
  u_max.print_point();
  u_min.print_point();

  LineSet upper = upper_hull(u_min,u_max,input);
  cout<<"upper ended"<<endl<<endl<<endl;


  Set reflect_input;
  for(auto &it:input.point_list){
      Point temp(-it.x,-it.y);
      reflect_input.add(temp);
  }

  cout<<"lower:"<<endl;
  Point l_min = reflect_input.u_minimum();
  Point l_max = reflect_input.u_maximum();
  l_max.print_point();
  l_min.print_point();
  LineSet lower = upper_hull(l_min,l_max,reflect_input);
  cout<<"lower ended"<<endl<<endl<<endl;

  int count=0;
  int n_lower=lower.point_list.size();

  for(auto &it:lower.point_list){
      it.x=-it.x;
      it.y=-it.y;
      if(count==(n_lower-1))
      {
        if(!it.equal(u_min))
          upper.add(it);
      }

      else if(count==0)
      {
        if(!it.equal(u_max))
          upper.add(it);
      }
      else
        upper.add(it);
      count++;
  }
  return upper;
}


int main(int argc, char const *argv[]) {

  myfile.open("example.csv");
  inputfile.open("input.csv");
  myfile<<"x,y"<<endl;
  inputfile<<"x,y"<<endl;

  printf("Enter the number of points\n");
  int total_points;
  scanf("%d",&total_points);
  Set all_points;
  // Set rev_points;
  for(int index = 0;index<total_points;index++) {
    float x,y;
    scanf("%f %f", &x,&y );
    Point p(x,y);
    inputfile<<x<<","<<y<<endl;
    // Point rev(x,-y);
    all_points.add(p);
    // rev_points.add(rev);
  }

  LineSet result = kirk_patrick_seidel(all_points);


  for(auto &it: result.point_list)
  {
    myfile<<it.x<<","<<it.y<<endl;
  }
  myfile<<result.point_list[0].x<<","<<result.point_list[0].y<<endl;
  result.printing();

  myfile.close();
  inputfile.close();

  return 0;
}
