#include</usr/local/Cellar/mpich/3.3.2_1/include/mpi.h>
#include<cmath>
#include<random>
#include<iostream>
static const double Pi=3.1415926;
class Solution 
{
   public:
   static void gemotric_probability(int n,int &local_count)
   {
       double r[3],theta[3],x[3],y[3];
       std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<> r_dis(0,1),theta_dis(0,2*Pi);
    for(int k=0;k<n;k++)
    {
        for(int i=0;i<3;i++)
      {
        r[i]=sqrt(r_dis(gen));
        theta[i]=theta_dis(gen);
        x[i]=r[i]*cos(theta[i]);
        y[i]=r[i]*sin(theta[i]);
      }
      local_count+=calc(x,y)?1:0;
    }
   }
   private:
    static inline bool calc(double x[3],double y[3])
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
int main(int argc,char**argv)
{
    double probability;
    int count,local_count=0,my_rank,comm_sz,n,n_p;
    MPI_Init(nullptr,nullptr);
    MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    if(my_rank==0)
    {
       std::cout<<"Enter Number:";
       std::cin>>n;
       n_p=n/comm_sz;
    }
    double start=MPI_Wtime();
    MPI_Bcast(&n_p,1,MPI_INTEGER,0,MPI_COMM_WORLD);
    Solution::gemotric_probability(n_p,local_count);
    MPI_Reduce(&local_count,&count,1,MPI_INTEGER,MPI_SUM,0,MPI_COMM_WORLD);
    if(my_rank==0)
    {
        probability=count/(n+0.0);
        std::cout<<"time:"<<MPI_Wtime()-start<<"s\n";
        std::cout<<"probability:"<<probability<<std::endl;
    }
    MPI_Finalize();
    return 0;
}
