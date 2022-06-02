#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

void add_names(map<string, double> &costs, int &size) {
  costs["Kim"] = 0;
  costs["Britney"] = 0;
  costs["Lily"] = 0;
  costs["Julia"] = 0;

  size = 4;
}
double get_total(map<string, double> &costs) {
  double total = 0;
  while (true) {
    string paid;
    cout << "Who Paid? (Input 'q' if you want to end)... ";
    cin >> paid;
    if (paid == "q")
      break;

    double curr;
    cout << "How much? ";
    cin >> curr;

    total += curr;
    costs[paid] += curr;
  }
  return total;
}
void real_cost(double total, map<string, double> &costs, int size) {
  double per_person = total / size;
  for (auto x : costs) {
    x.second -= per_person;
    cout << x.first << ": " << x.second << endl;
    string it = x.first;
    double c = x.second;
    costs[it] = c;
  }
}
void print_pay(vector<pair<string, double>> pos, vector<pair<string, double>> neg) {
  cout << endl << endl << "--Payments--" << endl;
  while (!pos.empty() && !neg.empty()) {
    if (pos[0].second >= (-1)*neg[0].second) {
      cout << neg[0].first << " -> " << pos[0].first << " (+" << (-1)*neg[0].second << ")" << endl;
      pos[0].second -= neg[0].second;
      neg.erase(neg.begin(), neg.begin()+1);
      if (pos[0].second == 0)
        pos.erase(pos.begin(), pos.begin()+1);
    }
    else {
      cout << neg[0].first << " -> " << pos[0].first << " (+" << pos[0].second << ")" << endl;
      neg[0].second += pos[0].second;
      pos.erase(pos.begin(), pos.begin()+1);
    }
  }
}
void payments(map<string, double> &costs) {
  vector<pair<string, double>> pos;
  vector<pair<string, double>> neg;
  for (auto x : costs) {
    if (x.second > 0) {
      pair<string, double> curr = {x.first, x.second};
      pos.push_back(curr);
    }
    else if (x.second < 0) {
      pair<string, double> curr = {x.first, x.second};
      neg.push_back(curr);
    }
  }
  print_pay(pos, neg);
}


int main() {
  int size;
  map<string, double> costs;
  add_names(costs, size);

  double total = get_total(costs);
  cout << endl << endl << "--Real Cost per Person--" << endl;
  real_cost(total, costs, size);

  payments(costs);
}