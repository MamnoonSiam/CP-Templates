template<typename T>
string to_string(T x) {
  return std::to_string(x);
}
string to_string(char ch) {
  return string(1, ch);
}
string to_string(string s) {
  return '"' + s + '"';
}
string to_string(const char* s) {
  return to_string((string) s);
}
string to_string(bool b) {
  return (b ? "true" : "false");
}
template<typename A, typename B>
string to_string(pair<A,B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}
template<size_t N>
string to_string(bitset<N> bs) {
  return bs.to_string();
}
template<typename T>
string to_string(vector<T> v) {
  bool first = true;
  string res = "{";
  for(int i = 0; i < (int)v.size(); ++i) {
    if(!first) res += ", ";
    first = false;
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}
template <typename A>
string to_string(A v) {
  bool first = true;
  string res = "{";
  for (auto x : v) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(x);
  }
  res += "}";
  return res;
}
template<typename T>
string to_string(stack<T> stk) {
  vector<T> v_stk;
  while(!stk.empty()) {
    v_stk.push_back(stk.top());
    stk.pop();
  }
  reverse(v_stk.begin(), v_stk.end());
  return to_string(v_stk);
}
template<typename T>
string to_string(queue<T> qu) {
  vector<T> v_qu;
  while(!qu.empty()) {
    v_qu.push_back(qu.front());
    qu.pop();
  }
  return to_string(v_qu);
}
template<typename T>
string to_string(std::priority_queue<T> pq) {
  vector<T> v_pq;
  while(!pq.empty()) {
    v_pq.push_back(pq.top());
    pq.pop();
  }
  return to_string(v_pq);
}
template<typename T>
string to_string(std::priority_queue<T, vector<T>, greater<T>> pq) {
  vector<T> v_pq;
  while(!pq.empty()) {
    v_pq.push_back(pq.top());
    pq.pop();
  }
  return to_string(v_pq);
}

void debug_out() { cerr << endl; }

template<typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)