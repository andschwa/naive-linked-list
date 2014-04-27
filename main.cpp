/* NAIVE linked list data structure implementation
 */
#include <iostream>

class List
{
public:
  // Universal brace initialization and 'nullptr' are C++11 features
  List(): head{nullptr} {}
  ~List();
  void prepend(int);
  void append(int);
  void insert(int, int);
  void remove(int);
  void reverse_sublist(int, int);
  void print();
private:
  // Since only the List uses Nodes, Node can belong to List
  struct Node
  {
    Node* next;
    int value;
    Node(): next{nullptr}, value{0} {};
    Node(int value): next{nullptr}, value{value} {}
  };
  Node* head;
};

// The destructor is automatically called when a List object goes out
// of scope; in this case it is used to delete the allocated pointers
List::~List()
{
  Node* curr = head; // Start at begining of list
  while (curr != nullptr)
    {
      Node* temp = curr->next; // Save the remaining list
      delete curr; // Delete/free the current pointer
      curr = temp; // Move to saved next node
    }
}

// Prepend value to list
void
List::prepend(int value)
{
  Node* temp = new Node{value}; // Create the new node with the given value
  temp->next = head; // Attach the current list to the new node
  head = temp; // Make the new node the head of the list
}

// Append value to list
void
List::append(int value)
{
  if (head == nullptr) // Deal with empty list case
    {
      head = new Node{value}; // Simply make a list of one node
      return;
    }
  // Otherwise traverse to last node and append a node
  Node* curr = head;
  while (curr->next != nullptr)
    curr = curr->next;
  curr->next = new Node{value};
}

// Insert value before position
void
List::insert(int pos, int value)
{
  if (head == nullptr) // Deal with empty list case
    {
      head = new Node{value};
      return;
    }
  Node* curr = head;

  for (int i{0}; i <= pos; ++i) // Traverse pos number of nodes through the list
    // If pos is beyond the end of the list, stop at end node
    { if (curr->next != nullptr) { curr = curr->next; } }

  Node* temp = new Node{value}; // Make our new node
  temp->next = curr->next; // Attach second part of list to new node
  curr->next = temp; // Attach new node to first part of list
}

// Remove node at position
void
List::remove(int pos)
{
  if (head == nullptr) { return; } // Deal with empty list case
  Node* curr = head;

  for (int i{0}; i <= pos; ++i) // Traversal is same as insert
    { if (curr->next != nullptr) { curr = curr->next; } }

  Node* target = curr->next; // Select target node
  curr->next = target->next; // Save part of list that target is linked to
  delete target; // Delete the target node
}

// Reverses a sublist between indices [m, n] in-place in one pass
void
List::reverse_sublist(int m, int n)
{
  Node* front;
  Node* last;
  Node* prev;
  Node* curr = head;
  for (int i{0}; curr != nullptr; ++i)
    {
      Node* future = curr->next;
      if (i == m - 1) // before front of sublist
	{ front = curr; }
      else if (i == m) // at front of sublist
	{ last = curr; }
      else if (i > m and i <= n) // inside sublist
	{ curr->next = prev; }
      if (i == n) // at end of sublist
	{
	  front->next = curr;
	  last->next = future;
	  return;
	}
      prev = curr;
      curr = future;
    }
}

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

int
main()
{
  List list;
  for (int i{0}; i <= 16; ++i)
    list.append(i);
  std::cout << "Original list:\n";
  list.print();
  std::cout << "Reversing from m = 2 to n = 8:\n";
  list.reverse_sublist(2, 8);
  list.print();
  std::cout << "Reversing the result from m = 0 to n = 16:\n";
  list.reverse_sublist(0, 16);
  list.print();
}
