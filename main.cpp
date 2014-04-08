/* NAIVE linked list data structure implementation
 */
#include <iostream>

struct Node
{
  Node* next;
  double value;
  Node(): next{nullptr}, value{0} {};
  Node(double value): next{nullptr}, value{value} {}
};

struct List
{
  Node* head;
  void print();
  void append(double);
  void insert(int, double);
  void erase(int);
  void reverse_sublist(int, int);
  List(): head{nullptr} {}
};

void
List::print()
{
  if (head == nullptr)
    {
      std::cout << "Empty list\n";
      return;
    }
  Node* curr = head;
  while (curr != nullptr)
    {
      std::cout << curr->value;
      if (curr->next != nullptr) std::cout << ", ";
      curr = curr->next;
    }
  std::cout << "\n";
}

void
List::append(double value)
{
  if (head == nullptr)
    {
      head = new Node{value};
      return;
    }
  Node* curr = head;
  while (curr->next != nullptr)
    curr = curr->next;
  curr->next = new Node{value};
}

// insert before pos
void
List::insert(int pos, double value)
{
  if (head == nullptr)
    {
      head = new Node{value};
      return;
    }
  Node* curr = head;
  for (int i{0}; i < pos - 1; ++i)
    // if pos is greater than list, stop at end node
      if (curr->next != nullptr)
	curr = curr->next;
  Node* temp = new Node{value};
  temp->next = curr->next;
  curr->next = temp;
}

// erase at pos
void
List::erase(int pos)
{
  if (head == nullptr)
      return;
  Node* curr = head;
  for (int i{0}; i < pos - 1; ++i)
    if (curr->next != nullptr)
      curr = curr->next;
  Node* target = curr->next;
  curr->next = target->next;
  delete target;
}

// reverses a sublist between indices m, n in-place in one pass
void
List::reverse_sublist(int m, int n)
{

}

int
main()
{
  List list;
  for (int i{1}; i <= 16; ++i)
    list.append(i);
  list.print();
}
