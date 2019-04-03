#include<bits/stdc++.h>
using namespace std;

ofstream myfile;

/**
 * Class for a Point
 */
class Point{
	public:
		int x;
		int y;
		int discard;
		void swap_pt(Point* p);
		int dist(Point zero);
		int polar(Point &pt2,Point zero);
};

/**
 * Stack for the points
 */
class Stack
{
    int top;
    int capacity;
public:
    int *pt;    //Maximum size of Stack

  	Stack(int capacity);
    bool push(int x);
    void pop();
    int toppt();
    bool empty();
    int nextToTop();
};

class Scatter{
	Point *points;
	int n;
public:
	Scatter(Point points[],int n);
	int partition(int low , int high);
	void point_sort(int low,int high);
	void graham_scan();
};



/**
 * Swaps points
 * @param p [description]
 */
void Point::swap_pt(Point* pt)
{
	this->x=this->x+pt->x-(pt->x=this->x);
	this->y=this->y+pt->y-(pt->y=this->y);
	this->discard=this->discard+pt->discard-(pt->discard=this->discard);
}

/**
 * calculating distance from another point
 * @param  zero Specified point of the null
 * @return     	The distance of the point
 */
int Point::dist(Point zero)
{
	return (this->x-zero.x)*(this->x-zero.x)+(this->x-zero.x)*(this->x-zero.x);
}

/**
 * Calculates the polar value
 * @param  pt2  the point whose polar we want
 * @param  zero Origin point
 * @return      Polar value
 */
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



/**
 * Constructor
 * @param capacity Size of the stack
 */
Stack::Stack(int capacity)
{
	this->top=-1;
	this->capacity=capacity;
	this->pt= new int[capacity];
}

/**
 * Pushes the into the stack
 * @param  x integer to insert
 * @return   Success value
 */
bool Stack::push(int x)
{
    this->pt[++top] = x;
    return true;
}

/**
 * The top value of the stack
 * @return the top of the stack
 */
int Stack::toppt()
{
    int x = this->pt[top];
    return x;
}

/**
 * Pops the top of the stack
 */
void Stack::pop()
{
    if (top < 0)
    {
        cout << "Stack Underflow";
    }

    else
    {
        top--;
    }
}
/**
 * Checks if the stack is empty
 * @return [description]
 */
bool Stack::empty()
{
    return (top < 0);
}


/**
 * To find next to top element in stack
 * @return the next to top element
 */
int Stack::nextToTop()
{

    int p = this->toppt();
    this->pop();
    int res = this->toppt();
    this->push(p);
    return res;
}


/**
 * constructor of scatter
 * @param points The set of points
 * @param n			 the total points
 */
Scatter::Scatter(Point points[],int n)
{
	this->points=points;
	this->n=n;
}

/**
 * util for point_sort function
 * @param  low  Max value
 * @param  high Min value
 * @return low  The lowest partition
 */
int Scatter::partition (int low, int high)
{
    Point *pivot = &this->points[high];

  	high--;
    while(low <= high)
    {
    	if(this->points[low].polar(*pivot , this->points[0]))
    		this->points[low].swap_pt(&this->points[high--]);

    	else
    		low++;
    }
    this->points[low].swap_pt(pivot);

    return low;
}

/**
 * sorting the point w.r.t pt0 anticlockwise direction
 * @param low  Current Low
 * @param high Current High
 */
void Scatter::point_sort(int low,int high)
{
	if(low < high)
	{
		int pi=partition(low,high);
		Scatter::point_sort(low,pi-1);
		Scatter::point_sort(pi+1,high);
	}
}

/**
 * function for finding hull
 */
void Scatter::graham_scan()
{
	point_sort(1,this->n-1);
	Stack st(this->n);

	int i=0,k=0;
	while(k<3 && i<this->n)
	{
		if(!(this->points[i].discard))
		{
			st.push(i);
			k++;
		}
		i++;
	}

	if(k<3)
	{
		cout<<"can't be made"<<endl;
		return;
	}

	for (int i = 3; i < this->n; i++)
   	{
   		if(!(this->points[i].discard))
   		{
      		while ((points[st.toppt()].polar(points[i],points[st.nextToTop()])))
      		{
      			points[st.toppt()].discard=1;
         		st.pop();
         	}
      		st.push(i);
      	}
   	}


   	for (int i = 0; i < this->n; ++i)
   	{
   		Point p=points[i];
   		myfile<<(p.x)<<","<<(p.y)<<","<<(p.discard)<<endl;
   	}
   	myfile<<(points[0].x)<<","<<(points[0].y)<<","<<(points[0].discard)<<endl;
}

int main()
{
	int n;
	cin>>n;

	Point points[n];
	myfile.open("example.csv");
	myfile<<"x,y,discard"<<endl;


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

	Scatter s(points,n);
	s.graham_scan();
	myfile.close();
}

/*testcase
8
0 3
1 1
2 2
4 4
0 0
1 2
3 1
3 3
*/
