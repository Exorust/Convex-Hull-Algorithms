#define PI 3.14159265

/**
 * A point definition
 */
typedef struct
{
   double x;
   double y;
}
API_Point;                               //point defination


std::vector<API_Point> input;
std::vector<API_Point> output;

/**
 * Calculates Jarvis Hull
 * @param  input Set of input points
 * @return       A final list of hull points
 */
std::vector<API_Point> JarvisHull(std::vector<API_Point> input)
{
  int min_i=0;
  for(int i=1;i<input.size();i++)                             //finding min y-coordinate point
  {
    if(input[i].y < input[min_i].y || (input[i].y == input[min_i].y && input[i].x > input[min_i].x))
    {
      min_i = i;
    }
  }
  long double ang1=0,ang2=0,Ang2=0;;
  long double angle,min_angle,min_point;
  std::vector<API_Point> output;

    int i;
    output.push_back(input[min_i]);

  do
  {
    min_angle=2*PI;
    min_point=0;
    ang1=Ang2-PI;
    for(i=0;i<input.size();i++)
    {
      if(input[i].x-output.back().x==0)
      {
        if(input[i].y>output.back().y)
        {
          ang2=PI/2;
        }

        else if(input[i].y<output.back().y)
        {
          ang2=-PI/2;
        }

        else
        {
          continue;
        }
      }
      else
      {
        ang2 = atan2(input[i].y-output.back().y, input[i].x-output.back().x);
      }

      if(ang2>ang1)
      {
        angle = ang2-ang1;
      }
      else
      {
        angle = 2*PI - (ang1-ang2);
      }
      if(angle<min_angle)
      {
        min_angle = angle;
        Ang2=ang2;
        min_point = i;
      }
      else if(angle==min_angle)
      {

        long double x0=output.back().x;
        long double y0=output.back().y;
        long double x1=input[min_point].x;
        long double y1=input[min_point].y;
        long double x2=input[i].x;
        long double y2=input[i].y;

        long double d1 = powl(x1-x0,2) + powl(y1-y0,2);
        long double d2 = powl(x2-x0,2) + powl(y2-y0,2);

        if(d2>d1)
        {
          min_angle = angle;
          Ang2=ang2;
          min_point = i;
        }
      }
    }
    output.push_back(input[min_point]);

  }
  while(!(output.back().x==output[0].x && output.back().y==output[0].y));
    return output;
}

/**
 * Generates random points
 * @return Vecor of the points
 */
std::vector<API_Point> genPoints()    //generating random points
{
    printf("generating random points\n");
    std::vector<API_Point> pts;
    srand (time(NULL));
    int i,max=1400,j;
    for(i=0;i<20;i++)
    {
      float a = (float)(rand()%1400 -700);
      float b = (float)(rand()%1400 -700);
      sleep(0.01);
      API_Point p;
      p.x=a;p.y=b;
      pts.push_back(p);
    }
    for(i=0;i<20;i++)
    {
      for(j=0;j<i;j++)
      {
        if(pts[i].x==pts[j].x && pts[i].y==pts[j].y )
        {
            pts[i].x+=3.14;
            pts[i].y+=3.145;
        }

      }
    }
    return pts;
}

/** /brief Jarvis March algorithm for computing convex hull.
*
*This function computes convex hull given input points.
*Convex hull is returned as vector of points.
*Only input parameter is input points.
*/
std::vector<API_Point> jarvisMarch(std::vector<API_Point> pts){
  printf("jarvis here input size: %lu \n",pts.size() );
  return JarvisHull(pts);
}
