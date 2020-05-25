  /**
 * Author: CP3
 * Date: 2020-02-06
 * License: CC0
 * Source: CP3
 * Description: Calculates shortest paths from $s$ in a graph that might have negative edge weights.
 * Dist should be of size $\vert$AL$\vert$ and all values initialized to inf
 * Time: O(VE)
 * Status: 
 */
#pragma once 

void bellmanFord(vector<vii>& AL, vi &dist, int s) {
  dist[s] = 0;
  int V = AL.size();
  for (int i = 0; i < V-1; ++i) {
    bool modified = false;
    for (int u = 0; u < V; ++u)
      if (dist[u] != INF) // INF = 1e9
        for (auto &[v, w] : AL[u]) {
          if (dist[u]+w >= dist[v]) continue;
          dist[v] = dist[u]+w;
          modified = true;
        }
    if (!modified) break;
  }

  // Return true if negative cycle
  for (int u = 0; u < V; ++u)
    if (dist[u] != INF)
      for (auto &[v, w] : AL[u])
        if (dist[v] > dist[u]+w)
          return true;
  return false
}