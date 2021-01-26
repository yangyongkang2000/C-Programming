export[str_String :
   "/Users/yangyongkang/Library/Developer/Xcode/DerivedData/\
BarnsleyFern-azczmyhbrzlprfcxjphjblgvxfmr/Build/Products/Release/\
libBarnsleyFern.dylib", "BarnsleyFernPlot",str1_String:"BernsleyFernPlot"] :=
 BarnsleyFernPlot =
  LibraryFunctionLoad[
   str,str1, {{Real, 2}, {Real, 1}, {Real, 1}, {Real, 2}, {Integer,
     1}, {Integer, 1}, Integer, Integer},
   LibraryDataType[Image, "Byte"]];
(*example*)
BarnsleyFernPlot[{{0., 0., 0, 0, 0.16, 0}, {0.85, 0.04, 0, -0.04,
   0.85, 1.6}, {0.2, -0.26, 0, 0.23, 0.22, 1.6}, {-0.15, 0.28, 0,
   0.26, 0.24, 0.44}}, {.07, 0.85, 0.01, 0.07}, {0,
  0}, {{-2.182, 2.6558}, {0, 10.1}}, {500, 500}, {34, 139,
  34}, 255, 10000000]
(*example*)
BarnsleyFernPlot[{{0.05, 0, 0, 0, 0.6, 0}, {0.05, 0, 0, 0, -0.5,
   1}, {0.46, -0.15, 0, 0.39, 0.38, 0.6}, {0.47, -0.15, 0.0, 0.17,
   0.42, 1.1}, {0.43, 0.28, 0, -0.25, 0.45, 1.}, {0.42, 0.26,
   0, -0.35, 0.31, 0.37}}, {0.1, 0.1, 0.2, 0.2, 0.2, 0.2}, {0,
  0}, {{-1, 1}, {0, 2}}, {500, 500}, {34, 134, 200}, 255, 110000]
(*example*)
BarnsleyFernPlot[{{0.195, -0.488, 0.4431, 0.344, 0.433,
   0.2452}, {0.462, 0.414, 0.2511, -0.252, 0.361,
   0.5692}, {-0.058, -0.07, 0.5976, 0.453, -0.111, 0.0969}, {-0.035,
   0.07, 0.4884, -0.469, -0.022, 0.5069}, {-0.637, 0, 0.8562, 0,
   0.501, 0.2513}}, {0.25, 0.25, 0.25, 0.2, 0.05}, {0,
  0}, {{0, 1}, {0, 1}}, {1000, 1000}, {34, 134, 200}, 255, 11000000]
