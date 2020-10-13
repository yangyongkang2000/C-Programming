probability = 
 LibraryFunctionLoad[
  "/Users/yangyongkang/desktop/geometric_probability/wolfram_\
geometric_probability.dylib", 
  "wolfram_geometric_probability", {{Real, 3}}, Real];
  probability@RandomPoint[Disk[], {1000000, 3}] // AbsoluteTiming//Print