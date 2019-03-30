#include<bits/stdc++.h>
using namespace std;

class Point{
	public:
		int x;
		int y;
		int discard;
		void swap_pt(Point* p);
		int dist(Point zero);
		int polar(Point &pt2,Point zero);
};

void Point::swap_pt(Point* pt)
{
	this->x=this->x+pt->x-(pt->x=this->x);
	this->y=this->y+pt->y-(pt->y=this->y);
	this->discard=this->discard+pt->discard-(pt->discard=this->discard);
}

int Point::dist(Point zero)
{
	return (this->x-zero.x)*(this->x-zero.x)+(this->x-zero.x)*(this->x-zero.x);
}

int Point::polar(Point &pt2,Point zero)
{
	int slope_diff=((this->y-zero.y)*(pt2.x-zero.x)-(pt2.y-zero.y)*(this->x-zero.x));
	if(slope_diff==0)
	{
		if((this->dist(zero)-pt2.dist(zero))<0)
			this->discard=1;
		else
			pt2.discard=1;
	}

	if(slope_diff>0)
		return 1;

	return 0;
}

class Scatter{
	Point *points;
	int n;
public:
	int partition(int low , int high);
	int point_sort(int low,int high);
	void graham_scan();
}


int Scatter::partition (Point points[], int low, int high) 
{ 
    Point *pivot = &points[high]; 
  	
  	high--;
    while(low <= high)
    {
    	if(points[low].polar(*pivot , points[0]))
    		points[low].swap_pt(&points[high--]);

    	else
    		low++;
    }
    points[low].swap_pt(pivot);

    return low;    
}

void Scatter::point_sort(Point points[],int low,int high)
{
	if(low < high)
	{
		int pi=partition(points,low,high);
		point_sort(points,low,pi-1);
		point_sort(points,pi+1,high);
	}
}


void Scatter::graham_scan(int n,Point points[])
{
	point_sort(points,1,n-1);
	stack<Point>st;

	int i=0,k=0;
	while(k<3 && i<n)
	{
		if(!points[i].discard)
		{
			st.push(points[i++]);
			k++;
		}
		else
			i++;
	}

	if(k<3)
	{
		cout<<"can't be made"<<endl;
		return;
	}

	while(i<n)
	{
		if()
	}
}

int main()
{
	int n;
	cin>>n;

	Point points[n];
	int min_index=0;


	for (int i = 0; i < n; ++i)
	{
		points[i].discard=0;
		cin>>points[i].x;
		cin>>points[i].y;

		if(points[min_index].y==points[i].y && points[min_index].x>points[i].x)
			min_index=i;
		else if(points[min_index].y>points[i].y)
			min_index=i;
	}

	points[0].swap_pt(&points[min_index]);
	graham_scan(n,points);
}