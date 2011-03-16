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
      //ctor:
      LList(): first(NULL), current(NULL), sz(0){};
      //copy ctor:
      LList(const LList& other): first(NULL), current(NULL), sz(0){ 
        for(const Node* i = other.head(); i != NULL; i=i->next){
	  append(i->data);
	}
      };
      //TODO: destructor

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
	  if(!i) cout << "is is NULL! " << "d is: " << d << "\n";
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
	if(d == first->data){
	  Node* tmp = first;
	  first = first->next;
	  sz--;
	  delete tmp;
	} else {
	  Node* prev = first;
	  for( Node* i = first; i != NULL; prev=i, i=i->next){
	    cout << "  i->data is: " << i->data << endl;
	    if(d == i->data){
	      prev->next = i->next;
	      delete i;
	      sz--;
	      if(firstOnly) break; 
	    }
	  }
	}
      };

//NOTE: without 'const char*' below, g++ returns:
//warning: deprecated conversion from string constant to ‘char*’
      void print(const char* sep = ", ") const {
	cout << endl;
        for( Node* i = first; i != NULL; i=i->next){
	  cout << i->data;
	  if(i->next)
	    cout << sep;
	}
	cout << endl;
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
  cout << " there are now: " << lst.size() << " items in the list\n";
  cout << " there are now: " << lst.count() << " items in the list\n";

  cout << "\n now delete 1" << endl;
  lst.del(1);
  lst.print(":");
  cout << " there are now: " << lst.size() << " items in the list\n";
  cout << " there are now: " << lst.count() << " items in the list\n";

  lst.del(3);
  lst.print(":");
  cout << " there are now: " << lst.size() << " items in the list\n";
  cout << " there are now: " << lst.count() << " items in the list\n";

  cout << endl;
  cout << "lst2 has: " << lst2.size() << " items in it\n";
  lst2.print();

  lst3.insert_sorted(10);
  lst3.insert_sorted(8);
  lst3.insert_sorted(7);
  lst3.insert_sorted(17);
  cout << "\nlst3 is sorted\n";
  lst3.print();

  return 0;
};
