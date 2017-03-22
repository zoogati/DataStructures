// Implementation File for Sequences
// 
// Socratis Katehis

#include<iostream>
#include<cstdlib>
#include<cassert>
#include "sequence1.h"

using namespace std;

namespace main_savitch_3
{
	// The following are our typedef values for our private members. 
	//	typedef double value_type;
	//	typedef size_t size_type;
	// Sequence Constructor: starting a Sequence with no entries.
	sequence::sequence()
	{
		position = 0;
		used = 0;
	}
	// Starts at the first entry in the Sequence.
	void sequence::start()
	{
		position = 0;
	}
	// Moves to the next entry (if there is one).
	void sequence::advance()
	{
		if (is_item() == false) return;
		position++;
	}
	// Inserts an entry before the current position. Checks if Sequence is already 
	// max and if there is a current position.
	void sequence::insert(const value_type& entry)
	{
		assert(used < CAPACITY);
		//Check is_item first to put in front of sequence.
		if (is_item() == false)
		{
			position = 0;
		}
		for (unsigned int i = used; i > position; i--)
		{
			data[i] = data[i-1];
		}
		data[position] = entry;
		used++;
	}
	// Inserts an entry after the current position. Checks if Sequence is already
	// max and if there is a current position.
	void sequence::attach(const value_type& entry)
	{
		assert(used <= CAPACITY);
		// Check is_item first to put at end of sequence.
		if (is_item() == false)
		{
			data[used] = entry;
		}
		else
		{
			//Position+1 to be to one entry to the left.
			for (unsigned int i = used; i > position+1; i--)
			{
				data[i] = data[i-1];
			}
			data[position+1] = entry;
			position++;
		}
		used++;
	}
	// Removes the current entry (if there is one).
	void sequence::remove_current()
	{
		if(is_item() == true)
		{
			// Easier to go from left to right and bring entries back
			for (unsigned int i = position; i < used; i++)
			{
				data[i] = data[i+1];
			}
			used--;
		}
	}
	// Returns the size of the Sequence.
	sequence::size_type sequence::size() const 
	{
		return used;
	}
	// Checks if there is a legitimate current entry.
	bool sequence::is_item() const
	{
		if (position < used) return true;
		else return false;
	}
	// Returns the current entry.
	sequence::value_type sequence::current() const 
	{
		return data[position];
	}
}
