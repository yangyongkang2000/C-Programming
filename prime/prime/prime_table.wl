(* ::Package:: *)

f[n_]:=Export["prime_table.txt","#ifndef prime_table_H\n#define prime_table_H\n" <>"constexpr unsigned long long int prime_table["<>ToString[n]<>"]=" <>
 ToString[Table[Prime[x], {x, 1, n}]] <>";\nconstexpr unsigned long long int NextPrime="<>ToString[Prime[n+1]]<> ";\n"<>"constexpr unsigned long long int LimitNum="<>ToString[Prime[n]^2]<>";\n#endif"];
 f[Input[]];

