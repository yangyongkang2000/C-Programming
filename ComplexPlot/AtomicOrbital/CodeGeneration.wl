result[ll_] := 
  Flatten[Table[{n, l, m, 
     N[HornerForm[((1 + 2 l) (l - m)!)/(4 \[Pi] (l + m)!)*
         LegendreP[l, m, x]^2, x]*
       HornerForm[LaguerreL[n - l - 1, 1 + 2*l, y]^2, y]]}, {n, 2, 
     ll}, {l, 1, n - 1}, {m, 0, l}], 2];
CodeGeneration[file_String, n_Integer] := 
 Block[{}, 
  Export[file <> ".txt", 
   StringReplace[
    "#ifndef _template_h\n#define _template_h\n" <> 
     "template<int n,int l,int  m>  inline double  composite_function \
(const double x,const double y);\n" <> 
     StringJoin[
      StringReplace[
         "template<>  inline double \
composite_function<nn,ll,mm>(const double x,const double y){return \
EXPR;}\n", 
         MapThread[#1 -> #2 &, {{"nn", "ll", "mm", "EXPR"}, 
           ToString /@ CForm /@ #}]] & /@ result[n]] <> 
     "#endif", {"Power" -> "pow", "Sqrt" -> "sqrt"}]];
  Run["mv " <> file <> ".txt " <> file <> ".hpp"]];
  CodeGeneration["special_function",20]