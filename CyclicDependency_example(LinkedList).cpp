#include <iostream>
#include <memory>

struct Node {
	int data;
	std::shared_ptr<Node>next;
	std::shared_ptr<Node>prev;
	Node(int val) : data(val) {
		std::cout << "Node " << data << " created\n";
	}
	~Node()
	{
		std::cout << "Node " << data << " deleted\n";
	}
};

int main()
{
	auto head = std::make_shared<Node>(1);
	auto second = std::make_shared<Node>(2);
	
	head->next=second;
	second->prev=head;


	return 0;
}
//============================================================================================
The Story of the Cyclic Dependency

1. Creation of Node 1:
• auto head = std::make_shared<Node>(1);
  ▪ A Node object (let's call it Node1_obj) with data=1 is created on the heap.
  ▪ A Control Block (let's call it CB1) is also created on the heap, managing Node1_obj.
  ▪ CB1's Strong Reference Count (SRC) is set to 1.
  ▪ The shared_ptr variable head (on the stack) stores a pointer to Node1_obj and a pointer to CB1.
  ▪ head now owns Node1_obj. SRC for Node1_obj is 1.



2. Creation of Node 2:
• auto second = std::make_shared<Node>(2);
  ▪ A Node object (Node2_obj) with data=2 is created on the heap.
  ▪ A Control Block (CB2) is created on the heap, managing Node2_obj.
  ▪ CB2's SRC is set to 1.
  ▪ The shared_ptr variable second (on the stack) stores a pointer to Node2_obj and a pointer to CB2.
  ▪ second now owns Node2_obj. SRC for Node2_obj is 1.



3. Linking Node 1 to Node 2:
• head->next = second;
  ▪ The next member of Node1_obj (which is a std::shared_ptr<Node>) is assigned second.
  ▪ This means Node1_obj's next now also shares ownership of Node2_obj.
  ▪ The shared_ptr copy constructor/assignment operator is invoked for Node1_obj->next.
  ▪ CB2's SRC is incremented from 1 to 2. (Owners: second variable, Node1_obj->next)



Linking Node 2 back to Node 1 (Creating the Cycle):
• second->prev = head;
  ▪ The prev member of Node2_obj (which is a std::shared_ptr<Node>) is assigned head.
  ▪ This means Node2_obj's prev now also shares ownership of Node1_obj.
  ▪ The shared_ptr copy constructor/assignment operator is invoked for Node2_obj->prev.
  ▪ CB1's SRC is incremented from 1 to 2. (Owners: head variable, Node2_obj->prev)


At this point:
◦ Node1_obj is owned by: head (stack variable) AND Node2_obj->prev (heap member). SRC = 2.
◦ Node2_obj is owned by: second (stack variable) AND Node1_obj->next (heap member). SRC = 2.

5. End of main scope - second goes out of scope:
◦ The destructor for the shared_ptr variable second is called.
◦ This decrements the SRC of the object it manages (Node2_obj).
◦ CB2's SRC is decremented from 2 to 1. (Remaining owner: Node1_obj->next)
◦ Since SRC is not 0, Node2_obj is not deleted.


6. End of main scope - head goes out of scope:
◦ The destructor for the shared_ptr variable head is called.
◦ This decrements the SRC of the object it manages (Node1_obj).
◦ CB1's SRC is decremented from 2 to 1. (Remaining owner: Node2_obj->prev)
◦ Since SRC is not 0, Node1_obj is not deleted.


The Aftermath (Memory Leak):

• Node1_obj still exists on the heap. Its Control Block CB1 has an SRC of 1, solely due to Node2_obj->prev pointing to it.
• Node2_obj still exists on the heap. Its Control Block CB2 has an SRC of 1, solely due to Node1_obj->next pointing to it.
• There are no external shared_ptr variables (like head or second were) pointing to either Node1_obj or Node2_obj.
• The objects are "orphaned" on the heap, kept alive only by each other.
• Their SRCs will never drop to 0, so their destructors will never be called, and their memory will never be freed. This is a memory leak.



Key Clarification on Your Understanding:
• "Strong ref count of both 'next' and 'prev' is now 2 each"
  ◦ It's not that next and prev themselves have a reference count of 2. next and prev are shared_ptrs.
  ◦ It's the objects they point to (Node2_obj and Node1_obj respectively) whose strong reference counts become 2 due to these additional shared_ptrs (head->next and second->prev) also pointing to them.
• "head and second now also as 2 strong ref cnt each"
  ◦ Again, head and second are shared_ptr variables. They don't "have" a reference count themselves. They contribute one strong reference to the object they manage. The object Node1_obj has an SRC of 2, and Node2_obj has an SRC of 2.

This refined storyline should give you that 100% accurate picture.

//======================================================================================================
//	After making one pointer as std::weak_ptr
//======================================================================================================

Modified Node Structure:
struct Node {
    int data;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev; // <-- CHANGED TO WEAK_PTR

    Node(int val) : data(val) { /* ... */ }
    ~Node() { /* ... */ }
};


The Story with weak_ptr (Breaking the Cycle):

1. Creation of Node 1:
◦ auto head = std::make_shared<Node>(1);
  ▪ Node1_obj (data=1) and its Control Block (CB1) created on heap.
  ▪ CB1's Strong Reference Count (SRC) = 1. Weak Reference Count (WRC) = 0.
  ▪ head (stack shared_ptr) owns Node1_obj.

2. Creation of Node 2:
◦ auto second = std::make_shared<Node>(2);
  ▪ Node2_obj (data=2) and its Control Block (CB2) created on heap.
  ▪ CB2's SRC = 1. WRC = 0.
  ▪ second (stack shared_ptr) owns Node2_obj.

3. Linking Node 1 to Node 2 (Strong Forward Link):
◦ head->next = second;
  ▪ Node1_obj's next (shared_ptr) now also shares ownership of Node2_obj.
  ▪ CB2's SRC is incremented from 1 to 2. (Owners: second variable, Node1_obj->next). WRC for CB2 remains 0.

4. Linking Node 2 back to Node 1 (Weak Back Link):
◦ second->prev = head;
  ▪ Node2_obj's prev member (which is a std::weak_ptr<Node>) is assigned from head (shared_ptr).
  ▪ This means Node2_obj's prev now observes Node1_obj.
  ▪ CB1's SRC remains 1. (Owner: head variable only).
  ▪ CB1's WRC is incremented from 0 to 1. (Observer: Node2_obj->prev).
  ▪ Crucially, second->prev does NOT increase the Strong Reference Count of Node1_obj.

At this point:
◦ Node1_obj is owned by: head (stack variable). SRC = 1. Observed by Node2_obj->prev. WRC = 1.
◦ Node2_obj is owned by: second (stack variable) AND Node1_obj->next (heap member). SRC = 2. WRC = 0.

5. End of main scope - second goes out of scope:
◦ Destructor for shared_ptr variable second is called.
◦ This decrements the SRC of Node2_obj.
◦ CB2's SRC is decremented from 2 to 1. (Remaining strong owner: Node1_obj->next).
◦ Since SRC is not 0, Node2_obj is not deleted yet.
◦ The weak_ptr member second->prev (which points to CB1) is also destroyed. CB1's WRC is decremented from 1 to 0.

6. End of main scope - head goes out of scope:
◦ Destructor for shared_ptr variable head is called.
◦ This decrements the SRC of Node1_obj.
◦ CB1's SRC is decremented from 1 to 0.
◦ Since SRC for Node1_obj is now 0, Node1_obj IS DELETED.
  ▪ The destructor ~Node() for Node1_obj is called.
  ▪ Inside ~Node() for Node1_obj, its member head->next (a shared_ptr owning Node2_obj) is destroyed.
  ▪ This decrements the SRC of Node2_obj.
  ▪ CB2's SRC is decremented from 1 to 0.
  ▪ Since SRC for Node2_obj is now 0, Node2_obj IS DELETED.
	▪The destructor ~Node() for Node2_obj is called.
	▪ (Its weak_ptr prev member was already handled when second went out of scope if we consider member destruction order, or here; its destruction doesn't affect strong counts.)

The Aftermath (No Memory Leak):
• When head goes out of scope, Node1_obj's SRC becomes 0 because Node2_obj->prev (the weak_ptr) did not contribute to its strong ownership. Node1_obj is deleted.
• The deletion of Node1_obj triggers the destruction of its next member (shared_ptr), which was the last strong reference to Node2_obj.
• This causes Node2_obj's SRC to become 0, and Node2_obj is deleted.
• Both objects and their control blocks are properly cleaned up. The cycle is broken, and there is no memory leak.

Key Change:
The weak_ptr prev; does not keep Node1_obj alive. When head (the last external shared_ptr to Node1_obj) is gone, Node1_obj can be destroyed, which then allows Node2_obj to be destroyed.
