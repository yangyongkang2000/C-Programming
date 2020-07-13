JuliaMandelbrotSetPlot[Prgm_String, GraphStyle_String, c_String, 
   Iteration_String, filename_String] := 
  Module[{}, 
   Run[Prgm <> " " <> GraphStyle <> " " <> c <> " " <> Iteration <> 
     " " <> filename]; Get[filename]];