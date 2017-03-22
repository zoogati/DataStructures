//Implementation file for Sequence Part 3
//
// Socratis Katehis
//
//Invariants: -  Empty Sequence has all node private members set to NULL.
//	      -  Number of nodes stored in many_nodes.
//	      -  Head and Tail pointers access the data through the sequence.
//	      -  Current Item stored in cursor. Item before current stored in
//	         precursor. If precursor is last node, cursor is NULL. If 
//	         cursor is first node, precursor is NULL.
//	      -  Sequence is being implemented with the node class (linked
//		 list datatype).
//
// I added the list_piece() code from node2.h from the text. It made copy and assignment much easier.

#include<cassert>
#include<cstdlib>
#include"sequence3.h"
#include"node1.h"

using namespace std;

namespace main_savitch_5
{
	// Sequence Constructor: starting sequence with no entries.
	sequence::sequence()
	{
	  //Big O Notation: O(1)
		head_ptr = NULL;
		tail_ptr = NULL;
		precursor = NULL;
		cursor = NULL;
		many_nodes = 0;
	}
	// Copy Constructor: Copy empty,1 node, and more than one node. 
	sequence::sequence(const sequence& source)
	{
	   //Big O Notation: O(N)
		if (source.many_nodes == 0)
		{
			head_ptr = NULL;
			tail_ptr = NULL;
			precursor = NULL;
			cursor = NULL;
		}
		else if (source.head_ptr == source.cursor) // Only one node.
		{
			list_copy(source.head_ptr, head_ptr, tail_ptr);	
			cursor = head_ptr;
		}
		else
		{
			if (source.cursor == NULL)
			{
				list_piece(source.head_ptr, source.cursor, head_ptr, precursor);
				cursor = precursor->link();
			}
			else 
			{
				list_piece(source.head_ptr, source.cursor, head_ptr, precursor);
				list_piece(source.cursor, NULL, cursor, tail_ptr);
				precursor -> set_link(cursor);
			}
		}
		many_nodes = source.many_nodes;
	}
	// Destructor: Just call from node class.
	sequence::~sequence()
	{
	   //Big O Notation: O(N)
		list_clear(head_ptr); //Function from node class takes care of everything.
		many_nodes = 0;
	}
	void sequence::start()
	{
	   //Big O Notation: O(1)
		cursor = head_ptr;
		precursor = NULL;
	}
	void sequence::advance()
	{
	   //Big O Notation: O(1)
		assert(is_item());
		precursor = cursor;
		cursor = cursor->link();
	}
	void sequence::insert(const value_type& entry)
	{
	   //Big O Notation: O(1)
		if(!is_item() || precursor == NULL) //Inserting in the front of the sequence.
		{
			list_head_insert(head_ptr, entry);
			cursor = head_ptr;
			if (many_nodes == 0)
			{
				tail_ptr = head_ptr;
			}
		}
		else 			       	    //Inserting at precursor position.
		{
			list_insert(precursor, entry);
			cursor = precursor->link();
		}
		many_nodes++;
	}
	void sequence::attach(const value_type& entry)
	{
	   //Big O Notation: O(N) (Locate requirement)
		if(!is_item())
		{
			if(many_nodes == 0) 
			{
				list_head_insert(head_ptr, entry);
				cursor = head_ptr;
				precursor = NULL;
				tail_ptr = head_ptr;
			}
			else
			{
				precursor = list_locate(head_ptr,list_length(head_ptr));
				list_insert(precursor, entry);
				cursor = precursor->link();
				tail_ptr = tail_ptr->link();
			}
		}
		else if (is_item())
		{
			if(cursor == tail_ptr)
			{
				list_insert(cursor, entry);
				precursor = cursor;
				cursor = cursor->link();
				tail_ptr = tail_ptr->link();
			}
			else
			{
				list_insert(cursor, entry);
				precursor = cursor;
				cursor = cursor->link();
			}
		}
		many_nodes++;	
	}
	void sequence::remove_current()
	{
	   //Big O Notation: O(1) (Went over in class, dont have to traverse list)
		assert(is_item());
		if(cursor == head_ptr)
		{
			if(many_nodes == 1) 
			{
				list_head_remove(head_ptr);
				head_ptr = NULL;
				tail_ptr = NULL;
				cursor = NULL;
				precursor = NULL;
			}
			else
			{
				list_head_remove(head_ptr);
				cursor = head_ptr;
				precursor = NULL;
			}
		}
		else
		{
			cursor = cursor->link();
			list_remove(precursor);
		}
		many_nodes--;
	}
	void sequence::operator=(const sequence& source) 
	{
	   //Big O Notation: O(N) (Same as copy constructor)
		if(this == &source) return;
		list_clear(head_ptr);
		if(source.many_nodes == 0)
		{
			head_ptr = NULL;
			tail_ptr = NULL;
			cursor = NULL;
			precursor = NULL;
		}
		else if(source.many_nodes == 1 || source.head_ptr == source.cursor)
		{
			list_copy(source.head_ptr,head_ptr,tail_ptr);
			cursor = head_ptr;
			precursor = NULL;
		}
		else 
		{
			if (source.cursor == NULL)
			{
				list_piece(source.head_ptr, source.cursor, head_ptr, precursor);
				cursor = precursor->link();
			}
			else
			{
			list_piece(source.head_ptr, source.cursor, head_ptr, precursor);
			list_piece(source.cursor, NULL, cursor, tail_ptr);
			precursor->set_link(cursor);
			}
		}
		many_nodes = source.many_nodes;
	}
	size_t sequence::size() const
	{
	   //Big O Notation: O(1)
		return many_nodes;
	}
	bool sequence::is_item() const
	{
	   //Big O Notation: O(1)
		return cursor!=NULL;
	}
	sequence::value_type sequence::current() const
	{
	   //Big O Notation: O(1)
	return cursor->data();
	}
}
			


