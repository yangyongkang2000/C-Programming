(* ::Package:: *)

(* ::Input:: *)
(*N[Flatten[MatrixPower[{{1,1},{1,0}},n-1]][[1]]]*)


(* ::Input:: *)
(*expr=Sum[Evaluate[#1*x/k+#1+(x-#1)*#1&[Min[x,(2^64-1)/(10^m-1)^2]]/.{x->(Log[N[Flatten[MatrixPower[{{1,1},{1,0}},2^n-1]][[1]]]]/Log[10.]+1)/(m+1.0)}],{n,1,Floor[Log[u]/Log[2]]}];*)


(* ::Input:: *)
(*c=Compile[{{u,_Real},{m,_Real},{k,_Real}},Evaluate[expr]]*)


(* ::Input:: *)
(*file=CCodeGenerate[c,"time_anaysis","/Users/yangyongkang/Documents/C-Programming/FibonacciSequence/Performance_Test/time_anaysis.c"]*)


(* ::Input:: *)
(*time=Compile[{{u,_Real},{m,_Real},{k,_Real}},Evaluate[expr],CompilationTarget->"C"]*)


(* ::Input:: *)
(**)
