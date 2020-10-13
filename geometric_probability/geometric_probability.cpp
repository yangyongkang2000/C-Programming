#include<cmath>
#include<random>
#include<iostream>
static const double Pi=3.1415926;
class Solution 
{
   public:
   double gemotric_probability(int n)
   {
       std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<> r_dis(0,1),theta_dis(0,2*Pi);
    int count=0;
    for(int k=0;k<n;k++)
    {
        for(int i=0;i<3;i++)
      {
        r[i]=sqrt(r_dis(gen));
        theta[i]=theta_dis(gen);
        x[i]=r[i]*cos(theta[i]);
        y[i]=r[i]*sin(theta[i]);
      }
      count+=calc(x,y)?1:0;
    }
   return probability=count/(n+0.0);
   }
   private:
   double probability,r[3],theta[3],x[3],y[3];
    inline bool calc(double x[3],double y[3])
    {
      return pow(pow(x[2],2)*(y[0] - y[1]) + (pow(x[0],2) + (y[0] - y[1])*(y[0] - \
y[2]))*(y[1] - y[2]) + pow(x[1],2)*(-y[0] + \
y[2]),2)/(4.*pow(x[2]*(y[0] - y[1]) + x[0]*(y[1] - y[2]) + \
x[1]*(-y[0] + y[2]),2)) + pow(2*(x[0] - x[2])*(pow(x[1],2) - \
pow(x[2],2) + pow(y[1],2) - pow(y[2],2)) + 2*(x[1] - \
x[2])*(-pow(x[0],2) + pow(x[2],2) - pow(y[0],2) + \
pow(y[2],2)),2)/pow(-4*(x[1] - x[2])*(y[0] - y[2]) + 4*(x[0] - \
x[2])*(y[1] - y[2]),2) < pow(-1 + sqrt(pow(pow(x[2],2)*(y[0] - y[1]) \
+ pow(x[1],2)*(y[0] - y[2]) + 2*x[0]*x[2]*(y[1] - y[2]) - \
(pow(x[0],2) + (y[0] - y[1])*(y[0] - y[2]))*(y[1] - y[2]) + \
2*x[1]*x[2]*(-y[0] + y[2]),2)/(4.*pow(x[2]*(-y[0] + y[1]) + \
x[1]*(y[0] - y[2]) + x[0]*(-y[1] + y[2]),2)) + pow(y[2] - (2*(x[0] - \
x[2])*(pow(x[1],2) - pow(x[2],2) + pow(y[1],2) - pow(y[2],2)) + \
2*(x[1] - x[2])*(-pow(x[0],2) + pow(x[2],2) - pow(y[0],2) + \
pow(y[2],2)))/(-4*(x[1] - x[2])*(y[0] - y[2]) + 4*(x[0] - x[2])*(y[1] \
- y[2])),2)),2);
    }
};
int main()
{
  Solution s;
  std::cout<<s.gemotric_probability(1000000)<<std::endl;
}