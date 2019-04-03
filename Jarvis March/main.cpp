
#include<bits/stdc++.h>
#include<unistd.h>
#include "jarvis.h"

int main(){
  int i;
  printf("hello\n");
  input=genPoints();
  std::vector<API_Point> outpuut;
  std::ofstream myfile;
  myfile.open("inputfile.csv");
  myfile<<'x'<<","<<"y"<<std::endl;
  for(int i=0;i<input.size();i++)
  {
  	myfile<<input[i].x<<","<<input[i].y<<std::endl;
  }
  output=jarvisMarch(input);
  myfile.close();
  std::ofstream myfile1;
  myfile1.open("outputfile.csv");
  myfile1<<'x'<<","<<"y"<<std::endl;
  for(int i=0;i<output.size();i++)
  {
  	myfile1<<output[i].x<<","<<output[i].y<<std::endl;
  }
  myfile1.close();
  return 0;
}
