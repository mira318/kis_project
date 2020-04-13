#include <algorithm>
#include <iostream>
#include <vector>


struct vertix{
  int prior;
  int level;
  int total_close;
  int index;
  std::vector<std::string> from;
  std::vector<int> came;
  bool done;
};
const int COURSES = 100;
vertix Graph[COURSES];

void compute(vertix v) {
  if(v.done == false){
    for(int i = 0; i < v.from.size(); ++i) {
      int max_prior = 0;
      int j = 0;
      int cur_num = 0;
      int cur_b = 0;
      int b;
      int best_am = COURSES;
      while (j < v.from[i].size()) {
        while (v.from[i][j] != '/' && v.from[i][j] != '\0') {
          cur_b = cur_b * cur_num + v.from[i][j] - '0';
          cur_num += 10;
          j++;
        }
        compute(Graph[cur_b]);
        if (best_am >= Graph[cur_b].total_close) {
          if (best_am > Graph[cur_b].total_close || Graph[cur_b].prior >= max_prior) {
            max_prior = Graph[cur_b].prior;
            best_am = Graph[cur_b].total_close;
            b = cur_b;
          }
          cur_b = 0;
          j++;
        }
      }
      v.prior += max_prior;
      if(b != 0){
        v.came.push_back(b);
        for(int t = 0; t < Graph[b].came.size(); ++t){
          v.came.push_back(Graph[b].came[t]);
        }
      }
    }
    v.total_close +=1;
    v.done = true;
  }
}

void dfs(int v, std::vector<int>& ans) {
  for(int i = 0; i < Graph[v].came.size(); ++i) {
    std::cout << Graph[v].came[i] << " ";
  }
  std::cout << std::endl;
  for(int i = 0; i < Graph[v].came.size(); ++i) {
    dfs(Graph[v].came[i], ans);
  }
  ans.push_back(v);
}
int main() {
  int n, m;
  std::cin >> n >> m;
  int num_2 = 0;
  int a;
  for(int i = 0; i < n; ++i){
    std::cin >> a;
    std::cin >> Graph[a].level;
    Graph[a].index = i;
    if(Graph[a].level == 2){
      num_2++;
    }
    Graph[a].prior = 0;
    Graph[a].total_close = 0;
    Graph[a].done = false;
  }
  for(int i = 0; i < num_2; ++i){
    std::cin >> a;
    std::cin >> Graph[a].prior;
  }
  std::string s;
  for(int i = 0; i < m; ++i){
    std::cin >> a;
    std::cin >> s;
    Graph[a].from.push_back(s);
  }
  for(int i = 0; i < n; ++i) {
    compute(Graph[i]);
  }
  int lev3_1;
  int lev3_2;
  int lev5_1;
  std::cin >> lev3_1 >> lev3_2 >> lev5_1;
  std::vector<int> ans;
  dfs(lev3_1, ans);
  dfs(lev3_2, ans);
  dfs(lev5_1, ans);
  sort(ans.begin(), ans.end());
  std::cout << ans[0] << " ";
  for(int i = 1; i < ans.size(); ++i){
    if(ans[i] != ans[i - 1]) {
      std::cout << ans[i] << " ";
    }
  }
  return 0;
}
