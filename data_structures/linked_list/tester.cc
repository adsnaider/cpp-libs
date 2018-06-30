#include <iostream>

#include "linked_list.h"

using namespace std;

int main() {
  data_structures::linked_list::linked_list<int> list;
  cout << "Initial default list\n";
  cout << "Size: " << list.size() << endl;

  list.insert(list.cbegin(), 100);
  cout << "Size: " << list.size() << endl;
  cout << "Front: " << list.front() << endl;
  cout << "Back: " << list.back() << endl;

  list.insert(list.cend(), 200);
  cout << "Size: " << list.size() << endl;
  cout << "Front: " << list.front() << endl;
  cout << "Back: " << list.back() << endl;

  list.insert(++list.cbegin(), 150);
  list.insert(list.cend(), 500);
  list.insert(++list.cbegin(), 125);

  cout << "Current state of list:\n";
  for (const int &val : list) {
    cout << val << " ";
  }
  cout << endl;
  cout << "Backwards:\n";
  for (auto it = list.rbegin(); it != list.rend(); --it) {
    cout << *it << " ";
  }
  cout << endl;

  cout << "Pop the start. Pop the end.\n";
  list.pop(list.cbegin());
  list.pop(--list.cend());
  cout << "Current state of list:\n";
  for (const int &val : list) {
    cout << val << " ";
  }
  cout << endl;

  cout << "Now copying\n";
  auto copy(list);
  copy.insert(list.cbegin(), 10);

  cout << "State of copy\n";
  for (const int &val : copy) {
    cout << val << " ";
  }
  cout << endl;

  cout << "State of list\n";
  for (const int &val : list) {
    cout << val << " ";
  }
  cout << endl;
  return 0;
}
