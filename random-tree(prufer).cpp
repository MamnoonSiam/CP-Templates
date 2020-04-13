namespace prufer {
  /*
    source: e-maxx-eng
    everything is 0 based
  */
  vector<vector<int>> adj;
  vector<int> parent;

  void dfs(int v) {
    for (int u : adj[v]) {
      if (u != parent[v]) {
        parent[u] = v;
        dfs(u);
      }
    }
  }

  vector<int> encode() {
    int n = adj.size();
    parent.assign(n, 0);
    parent[n-1] = -1;
    dfs(n-1);

    int ptr = -1;
    vector<int> degree(n);
    for (int i = 0; i < n; i++) {
      degree[i] = adj[i].size();
      if (degree[i] == 1 && ptr == -1)
        ptr = i;
    }

    vector<int> code(n - 2);
    int leaf = ptr;
    for (int i = 0; i < n - 2; i++) {
      int next = parent[leaf];
      code[i] = next;
      if (--degree[next] == 1 && next < ptr) {
        leaf = next;
      } else {
        ptr++;
        while (degree[ptr] != 1)
          ptr++;
        leaf = ptr;
      }
    }

    return code;
  }
  vector<int> encode(vector<vector<int>> &G) {
    adj = G;
    return encode();
  }
  vector<int> encode(vector<int> *G, int n) {
    adj.clear();
    for(int i = 0; i < n; i++) {
      adj.emplace_back(G[i]);
    }
    return encode();
  }

  /*
    source: e-maxx-eng
    0-based, returnes code.size() + 1 edges, 0-based
  */
  vector<pair<int, int>> decode(vector<int> const& code) {
    int n = code.size() + 2;
    vector<int> degree(n, 1);
    for (int i : code)
      degree[i]++;

    int ptr = 0;
    while (degree[ptr] != 1)
      ptr++;
    int leaf = ptr;

    vector<pair<int, int>> edges;
    for (int v : code) {
      edges.emplace_back(leaf, v);
      if (--degree[v] == 1 && v < ptr) {
        leaf = v;
      } else {
        ptr++;
        while (degree[ptr] != 1)
          ptr++;
          leaf = ptr;
      }
    }
    edges.emplace_back(leaf, n-1);
    return edges;
  }

  vector<pair<int, int>> random_tree(int n, int idx) { // tree size, 0/1-indexed
    vector<pair<int, int>> ret;
    if(n > 1) {
      vector<int> code;
      if(n > 2) {
        code = rnd.perm(n-2, 0);
      }
      vector<pair<int, int>> tmp = decode(code);
      for(auto pr : tmp) {
        ret.emplace_back(pr.first + idx, pr.second + idx);
      }
    } return ret;
  }
}
