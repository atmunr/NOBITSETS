#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>

const int MAXN = 2e5+1;
const int MAXK = 2e5+1;
int seq[MAXN];
int quan[MAXN];
int n, k;

using namespace std;

class menor {
public:
  bool operator () (pair<int,int> a, pair<int,int> b) {
    return a.first > b.first || a.first == b.first && a.second > b.second;
  }
};

/*
class menor M;
M(a, b)
T = class menor;
T::operator(a, b);
*/

int main() {
  cin >> n >> k;

  for (int i = 0; i < n; i++) {
    cin >> seq[i];
    quan[seq[i]]++;
  }

  vector<int> sub;
  set<int> sub_contents;
  int pos_sub = 0;

  priority_queue<pair<int,int>, vector<pair<int,int>>, menor> sweep;

  for (int pos_sweep = 0; pos_sweep < n; quan[seq[pos_sweep]]--, pos_sweep++) {
    int numero_sweep = seq[pos_sweep];
    sweep.push(make_pair(numero_sweep, pos_sweep));

    if (quan[numero_sweep] == 1) { // numero_sweep tiene que estar en sub
      while (!sub_contents.count(numero_sweep)) {
        int smallest = sweep.top().first;
        int pos_smallest = sweep.top().second;

        sweep.pop();

        if (pos_smallest < pos_sub || sub_contents.count(smallest))
          continue;

        sub.push_back(smallest);
        sub_contents.insert(smallest);
        pos_sub = pos_smallest;
      }
    }
  }

  for (int i = 0; i < k; i++)
    cout << sub[i] << " ";
  cout << endl;
}
