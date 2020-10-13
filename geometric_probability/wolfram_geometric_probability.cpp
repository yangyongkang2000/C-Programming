#include<WolframLibrary.h>
#include<cmath>
#include<random>
EXTERN_C DLLEXPORT mint WolframLibrary_getVersion( ) { return WolframLibraryVersion; }
EXTERN_C DLLEXPORT int WolframLibrary_initialize( WolframLibraryData libData) { return 0; }
EXTERN_C DLLEXPORT void WolframLibrary_uninitialize( WolframLibraryData libData) { return; }
EXTERN_C DLLEXPORT inline bool calc(double *v)
{
  return pow(pow(v[4],2)*(v[1] - v[3]) + (pow(v[0],2) + (v[1] - v[3])*(v[1] - \
v[5]))*(v[3] - v[5]) + pow(v[2],2)*(-v[1] + \
v[5]),2)/(4.*pow(v[4]*(v[1] - v[3]) + v[0]*(v[3] - v[5]) + \
v[2]*(-v[1] + v[5]),2)) + pow(2*(v[0] - v[4])*(pow(v[2],2) - \
pow(v[4],2) + pow(v[3],2) - pow(v[5],2)) + 2*(v[2] - \
v[4])*(-pow(v[0],2) + pow(v[4],2) - pow(v[1],2) + \
pow(v[5],2)),2)/pow(-4*(v[2] - v[4])*(v[1] - v[5]) + 4*(v[0] - \
v[4])*(v[3] - v[5]),2) < pow(-1 + sqrt(pow(pow(v[4],2)*(v[1] - v[3]) \
+ pow(v[2],2)*(v[1] - v[5]) + 2*v[0]*v[4]*(v[3] - v[5]) - \
(pow(v[0],2) + (v[1] - v[3])*(v[1] - v[5]))*(v[3] - v[5]) + \
2*v[2]*v[4]*(-v[1] + v[5]),2)/(4.*pow(v[4]*(-v[1] + v[3]) + \
v[2]*(v[1] - v[5]) + v[0]*(-v[3] + v[5]),2)) + pow(v[5] - (2*(v[0] - \
v[4])*(pow(v[2],2) - pow(v[4],2) + pow(v[3],2) - pow(v[5],2)) + \
2*(v[2] - v[4])*(-pow(v[0],2) + pow(v[4],2) - pow(v[1],2) + \
pow(v[5],2)))/(-4*(v[2] - v[4])*(v[1] - v[5]) + 4*(v[0] - v[4])*(v[3] \
- v[5])),2)),2);
}
EXTERN_C DLLEXPORT int wolfram_geometric_probability(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    MTensor tensor=MArgument_getMTensor(Args[0]);
    double *v=libData->MTensor_getRealData(tensor);
    const mint *dims=libData->MTensor_getDimensions(tensor);
    mint count=0;
    for(int i=0;i<*dims;i++)
    {
       count+=calc(v+6*i)?1:0;
    }
   MArgument_setReal(Res,count/(*dims+0.0));
    return LIBRARY_NO_ERROR;
}