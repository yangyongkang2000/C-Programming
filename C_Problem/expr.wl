func[str_String]:=With[{},Export[str<>"expr.txt", 
 "#ifndef _expr_\n#define _expr_\n#define det " <> 
  StringJoin[
 If[# != "-" && # != "+", 
    "(" <> # <> 
     ")", #] & /@ (StringReplace[#, {"(" -> "[", ")" -> "]", 
       "*" -> "&"}] & /@ 
    StringSplit[
     ToString@
      CForm@Expand@Det[Table[b[i], {i, 0, 24}]~Partition~5], {"-" :> 
       "-", "+" :> "+"}])] <> 
  "\n#endif"]; Run["mv "<>str<>"expr.txt "<>str<>"expr.h"]];
  func@Input[];