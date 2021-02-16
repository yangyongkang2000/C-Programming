(* ::Package:: *)

library[str_String:
"/Users/yangyongkang/Library/Developer/Xcode/DerivedData/euler_tour_path-fzkqduooxdlhcxfqscstggwyaohu/Build/Products/Release/libeuler_tour_path.dylib"]:=
EulerGraphPath=LibraryFunctionLoad[str,
"euler_tour_path",{{Integer,2}},{Integer,1}];library[]


Test[n_,m_]:=With[{g=RandomGraph[DegreeGraphDistribution@ReleaseHold@Insert[
RandomChoice[Range[2,m,2],n],
HoldForm@RandomChoice[Range[1,m+1,2]],{RandomInteger[{1,n}]}&/@Range[2]]]},
{Graph@Partition[EulerGraphPath[List@@@EdgeList@g],2,1],g}]


While[True,If[While[!ConnectedGraphQ[(t=Test[100,10])[[2]]]];!IsomorphicGraphQ@@t,Break[]]]


Benchmark[n_,m_]:=Block[
{g=RandomGraph[DegreeGraphDistribution@RandomChoice[Range[2,m,2],n]],l},
l=List@@@EdgeList@g;#&/@First/@{AbsoluteTiming[EulerGraphPath[l];],
AbsoluteTiming[FindEulerianCycle[g];]}]


ListLinePlot[
Transpose[Benchmark[#,30]&/@Range[1000,10000,1000]],
PlotTheme->"Scientific",
Mesh->All,
PlotLegends->Placed[PointLegend[{"wheel","stand"},
LegendFunction->"Frame",
LegendLayout->"Column",
LegendMarkerSize->20],
{{0.3,0.8},{0.4,1}}],
FrameLabel->{"n","time/s"}]
