(* ::Package:: *)

(* ::Input:: *)
(*TPD=LibraryFunctionLoad["/Users/yangyongkang/Library/Developer/Xcode/DerivedData/TPD-crtpipefvtmlccdrqownvhlittpq/Build/Products/Release/libTPD.dylib","TPD",{Real,Real,Real,Real,Real,Real},{Real,2}];*)


(* ::Input:: *)
(*plot[\[Alpha]_,xd_,xw_,xF_,q_,r_]:=Block[{k1=r/(r+1),b1=xd/(r+1),r1=(r+1)*(xF-xw)/(xd-xF)+(q-1)*(xd-xw)/(xd-xF),k2,b2,xf=((r+1)*xF+(q-1)*xd)/(r+q),yf=(r*xF+q*xd)/(r+q),t},k2=(r1+1)/r1;b2=-xw/r1;Show[Plot[{x,(x \[Alpha])/(1-x+x \[Alpha]),k1*x+b1,k2*x+b2},{x,0,1},PlotRange->{0,1},PlotTheme->"Scientific",PlotStyle->Black,Epilog->{Blue,PointSize[Medium],Point[{{xw,xw},{xf,yf},{xd,xd}}]}],ListLinePlot[TPD[\[Alpha],xw,xd,xF,q,r],PlotStyle->Red]]];*)


(* ::Input:: *)
(*Manipulate[plot[x,0.94,0.06,0.44,1.38,2],{x,2.46,5,0.01}]*)
