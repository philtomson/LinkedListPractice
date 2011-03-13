// C++ linked list excercise
// March 12, 2010
// Phil Tomson
#include <iostream>

using namespace std;

template <typename T>
  class LList {
    private:
      struct Node {
	friend class LList;
	public:
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

      void append(const T& d){
	if(first == NULL) {
	  first = new Node(d);
	  current = first;
	} else if ( current == NULL) {
	  current = new Node(d);
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
  typedef LList<int> intList;
  intList lst;
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
  intList lst2 = intList(lst);

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

  return 0;
};
