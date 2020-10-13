StringReplace[
 ToString[(Total[
        TriangleCenter[#, 
          "Circumcenter"]^2] < (TriangleMeasurement[#, 
           "Circumradius"] - 1)^2) &@Table[{x[k], y[k]}, {k, 3}] // 
   CForm], {"Power" -> "pow", "Sqrt" -> "sqrt", 
  "y(" ~~ index_ ~~ ")" :> 
   "y[" ~~ ToString[ToExpression[index] - 1] ~~ "]", 
  "x(" ~~ index_ ~~ ")" :> 
   "x[" ~~ ToString[ToExpression[index] - 1] ~~ "]"}]