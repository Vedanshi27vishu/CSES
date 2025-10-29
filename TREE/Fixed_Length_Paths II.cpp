// #include <bits/stdc++.h>
// using namespace std;

// using ll = long long;

// struct Fenwick {
//     int N;
//     vector<int> bit;
//     Fenwick(int n=0){init(n);}
//     void init(int n){ N = n; bit.assign(n+2,0); }
//     void add(int idx,int val){ // idx: 0..N
//         idx++; // 1-based internal
//         while(idx <= N+1){ bit[idx] += val; idx += idx & -idx; }
//     }
//     int sumPrefix(int idx){ // sum [0..idx]
//         if(idx < 0) return 0;
//         idx++;
//         int s = 0;
//         while(idx>0){ s += bit[idx]; idx -= idx & -idx; }
//         return s;
//     }
//     int rangeSum(int l,int r){
//         if(l>r) return 0;
//         if(r < 0) return 0;
//         l = max(l, 0);
//         r = min(r, N);
//         return sumPrefix(r) - (l? sumPrefix(l-1) : 0);
//     }
// };

// const int MAXN = 200000 + 5;
// int n, K1, K2;
// vector<int> g[MAXN];
// int sz[MAXN], removed[MAXN];
// Fenwick fenw;
// ll answer = 0;

// // for efficient clearing of BIT, track touched indices & counts
// vector<int> touched;
// vector<int> curCount; // curCount[d] = how many times depth d is present in fenwick for current centroid

// int dfs_size(int u,int p){
//     sz[u] = 1;
//     for(int v: g[u]) if(v!=p && !removed[v]) sz[u] += dfs_size(v,u);
//     return sz[u];
// }

// int get_centroid(int u,int p,int total){
//     for(int v: g[u]) if(v!=p && !removed[v]){
//         if(sz[v] > total/2) return get_centroid(v,u,total);
//     }
//     return u;
// }

// void collect_depths(int u,int p,int d, vector<int> &depths){
//     if(d > K2) return; // beyond interest
//     depths.push_back(d);
//     for(int v: g[u]) if(v!=p && !removed[v]) collect_depths(v,u,d+1,depths);
// }

// void add_to_fenw_and_track(int d, int val){
//     if(d > K2) return;
//     if(curCount[d] == 0) touched.push_back(d);
//     curCount[d] += val;
//     fenw.add(d, val);
// }

// void clear_touched(){
//     for(int idx: touched){
//         if(curCount[idx] != 0){
//             fenw.add(idx, -curCount[idx]);
//             curCount[idx] = 0;
//         }
//     }
//     touched.clear();
// }

// void decompose(int start){
//     int total = dfs_size(start, -1);
//     int cen = get_centroid(start, -1, total);
//     removed[cen] = 1;

//     // ensure fenwick size is n
//     // We will add the centroid itself as depth 0
//     add_to_fenw_and_track(0, 1);

//     for(int v: g[cen]){
//         if(removed[v]) continue;
//         vector<int> depths;
//         collect_depths(v, cen, 1, depths);

//         // count pairs: for each depth d in this subtree, number of previously added depths
//         // that produce total length in [K1, K2]
//         for(int d: depths){
//             int needL = K1 - d;
//             int needR = K2 - d;
//             answer += fenw.rangeSum(needL, needR);
//         }

//         // then add these depths into fenwick for future subtrees
//         for(int d: depths){
//             add_to_fenw_and_track(d, 1);
//         }
//     }

//     // clear fenwick entries used at this centroid
//     clear_touched();

//     // recurse on subtree components
//     for(int v: g[cen]){
//         if(!removed[v]){
//             decompose(v);
//         }
//     }
// }

// int main(){
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     if(!(cin >> n >> K1 >> K2)) return 0;
//     for(int i=1;i<=n;i++) g[i].clear();
//     for(int i=0;i<n-1;i++){
//         int a,b; cin >> a >> b;
//         g[a].push_back(b);
//         g[b].push_back(a);
//     }

//     fenw.init(n); // depths are at most n-1
//     curCount.assign(n+1, 0);
//     touched.clear();
//     answer = 0;
//     fill(removed, removed + n + 2, 0);

//     decompose(1);

//     cout << answer << '\n';
//     return 0;
// }
