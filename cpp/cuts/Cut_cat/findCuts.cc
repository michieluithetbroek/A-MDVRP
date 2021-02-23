#include "./Cut_cat.ih"

vector<CutReturn> Cut_cat::findCuts(vector<vector<double>> const &x)
{
  vector<CutReturn> cuts;
  
  ListGraph graph;
  
  map<int, pair<int, int>> map = create_edge_map(x, graph);
  
  bool const empty_graph = create_incompatible_graph(x, graph, map);
   
  if (empty_graph)
    return cuts;
  
  ListGraph::EdgeMap<double> valEdge(graph);
  create_valEdge(x, graph, map, valEdge); 
  
  /* edge-weighted graph is constructed
   * - graph : the actual edge-weighted graph
   * - valEdge: the values of the edges in graph   
   *
   * For every edge, compute minimum weight cycle in edge-weighted graph:
   */
  
  // create biparte graph from 'graph' to find cycles of odd length
  ListGraph bipart_graph;
  ListGraph::NodeMap<tuple<int, int>> valNode(bipart_graph);
  
  int const nNodes = create_bipart_graph(bipart_graph, graph, valNode, map);
  
  ListGraph::EdgeMap<double> val_edge(bipart_graph);
  set_bipart_val_edge(val_edge, valEdge, valNode, bipart_graph, graph);
                         
  
  
  // first get connected components
  ListGraph::NodeMap<int> cc_map(bipart_graph);
  
  connectedComponents(bipart_graph, cc_map);

  
  /* Bipartite graph is constructed
   * - bipart_graph : the actual bipartite edge-weighted graph
   * - val_edge: the values of the edges in bip. graph   
   * - valNode maps node of bipart_graph to node of edge_weighted graph + side
   * - cc_map: connected components
   * 
   * For every edge in bipart_graph graph, solve shortest path to find odd sized CAT.
   */
  
  
  for (ListGraph::NodeIt u(bipart_graph); u != INVALID; ++u)
  {
    // only from 0 to 0
    if (get<1>(valNode[u]) == 1)
      continue;
    
    for (ListGraph::NodeIt v(bipart_graph); v != INVALID; ++v)
    { 
      
      // only from 0 to 0
      if (get<1>(valNode[v]) == 1)
        continue;
      
      // if not connected, never odd weight cycle.
      if (cc_map[u] != cc_map[v])
        continue;
      
      // if u not connected to v'' -> stop,
      // as we only need to identify cycles through each edge that actual EXISTS
      
      ListGraph::Node vprime = bipart_graph.nodeFromId(bipart_graph.id(v) - nNodes);
      
      if (not incident(u, v, vprime, bipart_graph, nNodes))
        continue;
            
      if (bipart_graph.id(u) >= bipart_graph.id(v))
        continue;
      
      // u and v are two different nodes (corresponding to edges in original graph of lp relaxation)
      
      Dijkstra<ListGraph, ListGraph::EdgeMap<double>> dijk(bipart_graph, val_edge);
      dijk.run(u,v); 
      
      double dist = dijk.dist(v);
      
      // add v' to u'' -> u'' = u - n_nodes 
      ListGraph::Node uprime = bipart_graph.nodeFromId(bipart_graph.id(u) - nNodes);
      for (ListGraph::IncEdgeIt e(bipart_graph, uprime); e != INVALID; ++e)
        if (v == bipart_graph.u(e) or v == bipart_graph.v(e) )
        {
          dist += val_edge[e];
          break;
        }
        
      double LB = (1.0 - dist)/2;
      
      if (LB < -0.5)
        continue;
      
//       cout << "path between " << bipart_graph.id(u) << " and " << bipart_graph.id(v) << " --- VIOLATION: " << LB << endl;
//       cout << "is path in original nodes between: " << get<0>(valNode[u]) << " - " << get<0>(valNode[v]) << endl;

      vector<int> cycle;
      
//       cout << bipart_graph.id(v) << " ";
      cycle.push_back(get<0>(valNode[v]));
     
      auto n = dijk.predNode(v); 
//       cout << bipart_graph.id(n) << " ";
      cycle.push_back(get<0>(valNode[n]));
      while (true)
      {
        n = dijk.predNode(n);       
//         cout << bipart_graph.id(n) << " ";
        cycle.push_back(get<0>(valNode[n]));
        if (n == INVALID or bipart_graph.id(n) == bipart_graph.id(u))
          break;
       
      }
      cycle.push_back(get<0>(valNode[v]));
//       cout << " cycle: ";
//       for (auto el: cycle)
//         cout << el << " ";
//       cout << endl;
     
      // Check if cycle is chordless and simple -> involved nodes cannot have uitstekels and no tours within cycle
      if (not is_simple(cycle))
        continue;
//       cout << "===== simple\n";
      
      // check if chordless. loop over all incident edges of all nodes in cycle, and check whether there are edges to 
      // nodes in the cycle not belonging to the cycle :D
      
      bool chordless = true;
      
      if (cycle.size() > 4) // cycle with 3 nodes is always chordless
      {
        for (auto el: cycle)
        {
          auto node = graph.nodeFromId(el);
          for (ListGraph::IncEdgeIt e(graph, node); e != INVALID; ++e)
          { 
            auto node2 = (graph.u(e) == node ? bipart_graph.v(e): graph.u(e));
            
            int el1 = graph.id(node2);
            
            // check if in cycle
            if (find(cbegin(cycle), cend(cycle), el1) == cend(cycle))
              continue;
            
            chordless = false;
            for (size_t i = 0; i != cycle.size() - 1; ++i)
            {
              if (el == cycle[i] and el1 == cycle[i + 1])
              {
                chordless = true;
                break;
              }
            }
          }      
        }
      }
      
      if (not chordless)
        continue;
      
//       cout << "===== chordless: \n";

      
      // check real cut value:
      double lhs = 0.0;
      vector<int> source(d_nNodes, 0);
      vector<int> sink(d_nNodes, 0);
      
      
      for (size_t i = 0; i != cycle.size() - 1; ++i)
      {
        int node = cycle[i];
        
        pair<int, int> edge = map[node];
        lhs += x[edge.first][edge.second];
        
        source[edge.first]++;
        sink[edge.second]++;
      }
    
//       cout << "LHS (T): " << lhs << endl;
      
     // add edges from source to sink
      
      for (size_t idx = 0; idx != source.size(); ++idx)
        {
          if (source[idx] != 2)
            continue;
          
          for (size_t jdx = 0; jdx != sink.size(); ++jdx)
          {
            if (sink[jdx] != 2)
              continue;
            
            if (idx == jdx)
              continue;
            
            bool adj = false;
            
            for (size_t i = 0, len = cycle.size() - 1; i < len; ++i)
              if (map[cycle[i]].first == (int) idx and map[cycle[i]].second == (int) jdx)
              {
                adj = true;
                break;
              }
              
            if (not adj)
              lhs += x[idx][jdx];
          }
        }
      
//       cout << "LHS (T + Q): " << lhs << endl;
      
      double const rhs = ( (double)cycle.size() - 2.0 ) / 2.0;
      
//       cout.clear();
      if (lhs > rhs + 0.0001)
      {
//         cout << "CAT INEQUALITY FOUND!!\n";
//         cout << "LHS: " << lhs << '\n' << "RHS: " << rhs << endl;
//         for (auto el: cycle)
//           cout << el << " ";
//         cout << endl;
//         
//         for (auto el: cycle)
//           cout << "(" << map[el].first << "," << map[el].second << ")  ";
//         cout << endl << endl;
        
        
        // Remove edge (u,v) from edge weighted directed graph
        bipart_graph.erase(uprime);
        bipart_graph.erase(vprime); 
        bipart_graph.erase(u);
        bipart_graph.erase(v);
        
        // add and create cut

        CutReturn cut;
        
        for (size_t i = 0; i != cycle.size() - 1; ++i)
        {
          int const node = cycle[i];
          pair<int, int> const &edge = map[node];
          
          cut.add(1, edge.first, edge.second);
//           cout << edge.first << "-" << edge.second << " -- " <<  x[edge.first][edge.second] << endl;
        }
      
        // add edges from source to sink
        
        for (size_t idx = 0; idx != source.size(); ++idx)
        {
          if (source[idx] != 2)
            continue;
          
          for (size_t jdx = 0; jdx != sink.size(); ++jdx)
          {
            if (sink[jdx] != 2)
              continue;
            
            if (idx == jdx)
              continue;
            
            bool adj = false;
            
            for (size_t i = 0, len = cycle.size() - 1; i < len; ++i)
            {
              if (map[cycle[i]].first == (int) idx and map[cycle[i]].second == (int) jdx)
              {
                adj = true;
                break;
              }
            }
            
            if (not adj)
              cut.add(1, idx, jdx);
          }
        }
        
//         cout << expr << endl;
//         cout << "RHS: " << rhs << endl;
//         cout << "LHS: " << lhs << endl;

        cut.rhs = rhs;
        cuts.push_back(cut);
      }
    }
  }
  
  return cuts;
}
