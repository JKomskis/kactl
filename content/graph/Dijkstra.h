  /**
 * Author: CP3
 * Date: 2020-02-06
 * License: CC0
 * Source: CP3
 * Description: Finds the shortest path from s to all other nodes.
 * AL is an adjacency list.
 * Time: 
 * Status: 
 */
#pragma once 

vi dijkstra(vector<vii> &AL, int s) {
  priority_queue<ii, vector<ii>, greater<ii>> pq;
  vi dist(V, INF); //INF = 0x3f3f3f3f
  dist[s] = 0;
  pq.push({0, s});
  while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (d > dist[u]) continue;
    for (auto &[v, w] : AL[u]) {
      if (dist[u]+w >= dist[v]) continue;
      dist[v] = dist[u]+w;
      pq.push({dist[v], v});
    }
  }
  return dist;
}