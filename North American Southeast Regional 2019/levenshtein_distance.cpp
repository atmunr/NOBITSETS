#include <iostream>
#include <set>

using namespace std;

int main() {
  string alph, s, edit;
  cin >> alph >> s;

  set<string> others;

  edit.resize(s.size() + 1);
  for (int i = 0; i < s.size()+1; i++) { // add a character
    for (int j = 0; j < alph.size(); j++) {
      for (int edit_p = 0; edit_p < s.size()+1; edit_p++) {
        if (edit_p < i)
          edit[edit_p] = s[edit_p];
        else if (edit_p == i)
          edit[i] = alph[j];
        else
          edit[edit_p] = s[edit_p-1];
      }
      others.insert(edit);
    }
  }

  edit.resize(s.size() - 1);
  for (int i = 0; i < s.size(); i++) { // remove a character
    for  (int edit_p = 0; edit_p < s.size()-1; edit_p++) {
      if (edit_p < i)
        edit[edit_p] = s[edit_p];
      else
        edit[edit_p] = s[edit_p+1];
    }
    others.insert(edit);
  }

  edit = s;
  for (int i = 0; i < s.size(); i++) { // change a character
    for (int j = 0; j < alph.size(); j++) {
      if (edit[i] != alph[j]) {
        edit[i] = alph[j];
        others.insert(edit);
        edit[i] = s[i]; // discard the change
      }
    }
  }

  for (string o : others) {
    cout << o << endl;
  }
}
