// C++ linked list excercise
// March 12, 2010
// Phil Tomson
#include <iostream>

using namespace std;

template <typename T>
  class LList {
    private:
      struct Node {
	T data; 
	Node* next;
	//NOTE:  'const' required below
	Node(const T& d):data(d),next(NULL){};
      };

      Node* first;
      Node* current;
      int sz;
    public:
      // ctor:
      LList(): first(NULL), current(NULL), sz(0){};
      // copy ctor:
      LList(const LList& other): first(NULL), current(NULL), sz(0){ 
        for(const Node* i = other.head(); i != NULL; i=i->next){
	  append(i->data);
	}
      };
      // destructor
      ~LList(){
	cout << "Destructor called\n";
	Node* prev = NULL;
	current = first;
	while( current != NULL) {
	  prev = current;
	  current = current->next;
	  if(prev) { 
	    cout << "   getting rid of: " << prev->data << endl;
	    delete prev;
	    prev = NULL; 
	  }
	}
	first = NULL;
      };

      //accessors:
      Node* next(){ return current->next;};
      //NOTE: function itself has to be const:
      const Node* head() const { return first;} ;

      Node* tail(){ return current;};
      int size(){ return sz;};

      void insert_sorted(const T& d){
	if(first == NULL) {
	  first = new Node(d);
	  current = first;
	} else {
	  //make sure we're at the end:
	  Node* prev = NULL;
          Node* i = first;
	  for( i = first; i != NULL && i->data < d; prev=i, i=i->next);
	  //prev is now either NULL (prior to first item in list)
	  //or: prev < d < i
	  if(!i) cout << "is NULL! " << "d is: " << d << "\n";
	  if(prev){
	    prev->next = new Node(d);
	    prev->next->next = i;
	  } else {
            //insert at beginning of list:
	    first = new Node(d);
	    first->next = i;
	  }
	}
        sz++;	
      };

      void append(const T& d){
	if(first == NULL) {
	  first = new Node(d);
	  current = first;
	} else {
	  //make sure we're at the end:
	  while( current->next != NULL ) current = current->next;
	  current->next = new Node(d);
	  current = current->next;
	}
        sz++;	
      };

      //for testing purposes only
      int count(){
	int c = 0;
        for( Node* i = first; i != NULL; i=i->next){
          c++;
	}
	return c;
      };

      void del(const T& d, bool firstOnly=true){
	Node* prevPtr;

	// For 1st node there is no previous.
	prevPtr = NULL;
	// Visit each node, maintaining a pointer to
	// the previous node we just visited.
	for (current = first;
	     current != NULL;
	     prevPtr = current, current = current->next ) {
	  
	  if (current->data == d) {  //found it
	    if (prevPtr == NULL) {
	      //remove first item
	      first = current->next;
	    } else {
	      // skip over the removed node.
	      prevPtr->next = current->next;
	    }
	    delete current;  
	    sz--;
	    if(firstOnly) break;
	  }
        }
      };

//NOTE: without 'const char*' below, g++ returns:
//warning: deprecated conversion from string constant to ‘char*’
      void print(const char* sep = ", ") const {
	cout << "[" ;
        for( Node* i = first; i != NULL; i=i->next){
	  cout << i->data;
	  if(i->next)
	    cout << sep;
	}
	cout <<"]" << endl;
      };
  };



int main(){
  typedef LList<int> sorted_intList;
  sorted_intList lst;
  lst.append(1);
  cout << " tail is: "<< (lst.tail()->data) << endl;
  lst.append(2);
  cout << " tail is: "<< (lst.tail()->data) << endl;
  cout << " head is: "<< (lst.head()->data) << endl;
  lst.append(3);
  cout << " tail is: "<< (lst.tail()->data) << endl;
  cout << " head is: "<< (lst.head()->data) << endl;
  cout << " there are now: " << lst.size() << " items in the list\n";
  lst.print(":");
  sorted_intList lst2 = sorted_intList(lst);
  sorted_intList lst3;

  cout << "\n now delete 2" << endl;
  lst.del(2);
  lst.print(":");
  //make sure that size() and count() are returning the same thing here:
  cout << " there are now: " << lst.size() << " items in the list(size)\n";
  cout << " there are now: " << lst.count() << " items in the list(length)\n";

  cout << "\n now delete 1" << endl;
  lst.del(1);
  lst.print(":");
  cout << " there are now: " << lst.size() << " items in the list(size)\n";
  cout << " there are now: " << lst.count() << " items in the list(length)\n";

  cout << "\n now append 3" << endl;
  lst.append(3);
  lst.print(":");

  cout << "\n now delete 3" << endl;
  lst.del(3);
  lst.print(":");
  cout << " there are now: " << lst.size() << " items in the list(size)\n";
  cout << " there are now: " << lst.count() << " items in the list(length)\n";

  cout << "\n now delete 3" << endl;
  lst.del(3);
  lst.print(":");
  cout << " there are now: " << lst.size() << " items in the list(size)\n";
  cout << " there are now: " << lst.count() << " items in the list(length)\n";

  cout << endl;
  cout << "lst2 has: " << lst2.size() << " items in it(size)\n";
  lst2.print();

  lst3.insert_sorted(10);
  lst3.insert_sorted(8);
  lst3.insert_sorted(7);
  lst3.insert_sorted(17);
  cout << "\nlst3 is sorted\n";
  lst3.print();

  return 0;
};
