problem[str_String] := 
  With[{}, Export[str <> "problem.txt", 
    "#include<stdio.h>\n#include\"expr.h\"\nint main()\n{int count=0;\
\nchar b[25];\n" <> 
     StringJoin@
      Table["for(" <> "b[" <> ToString[i] <> "]=0;b[" <> ToString[i] <>
         "]<=1;" <> "b[" <> ToString[i] <> "]++)\n", {i, 0, 24}] <> 
     "{count+=(det)!=0?1:0;}\nprintf(\"count=%d\\n\",count);}"]; 
   Run["mv " <> str <> "problem.txt " <> str <> "problem.c"]];
problem@Input[];