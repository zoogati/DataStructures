/* Socratis Katehis
 *
 * stats.cxx
 *
 * File with implementations of Statistician class
 */

#include <iostream>
#include "stats.h"
#include<cassert>

using namespace std;


//Define all member functions here

namespace main_savitch_2C
{
	statistician::statistician()
	{
            count=0;
            total=0;
	}	

	void statistician::next(double r)
	{
            if (count<=0) 
            {
                count++;
                total=r;
                tinyest=r;
                largest=r;
                return;
            }
            else if (count>=1)
            {
                count++;
                total+=r;
                if (r<tinyest) 
                {
                    tinyest=r;
                }
                else if (r>largest)
                {
                    largest=r;
                }
            }
	}

	void statistician::reset()
	{
            count=0;
            total=0;

	}

	int statistician::length() const
	{
            return count;
	}

	double statistician::sum() const
	{
            return total;
	}

	double statistician::mean() const
	{
            assert(count>0);
            return total/count;
	}

	double statistician::minimum() const
	{
		assert(count>0);
		return tinyest;
	}

	double statistician::maximum() const
	{
		assert(count>0);
		return largest;
	}

	statistician operator +(const statistician& s1, const statistician& s2)
	{	
		if (s1.length() == 0)		//Very helpful check.
		return s2;
		if (s2.length() == 0)
		return s1;
		statistician result;
		result.total = s1.total + s2.total;
		if (s1.largest >= s2.largest)
		{
			result.largest = s1.largest;
		}
		else 
		{
			result.largest = s2.largest;
		}
		if (s1.tinyest > s2.tinyest)
		{
		 	result.tinyest = s2.tinyest;
		}
		else
		{
			result.tinyest = s1.tinyest;
		}
		result.count = (s1.count + s2.count);
		return result;
	}

	statistician operator *(double scale, const statistician& s)
	{
		statistician result; //Don't understand what's failing.
		if (s.count == 0)
		return s;
		if (scale == 0)
		return result;
		if (scale > 0)
		{
			result.total = scale * s.total;
			result.largest = scale * s.largest;
			result.tinyest = scale * s.tinyest;
			result.count = s.count;
		}
		if (scale < 0)
		{
			result.total = scale * s.total;
			result.largest = scale * s.tinyest;
			result.tinyest = scale * s.largest;
			result.count = s.count;
			if (result.largest == -0)	//For some strange reason, test would show me -0, added this to change to 0.
			{
				result.largest = 0;
			}
			if (result.tinyest == -0)
			{
				result.tinyest = 0;
			}
		}
		return result;
	}

	bool operator ==(const statistician& s1, const statistician& s2)
	{
		if(s1.length()==0 && s2.length()==0)
		{
			return true;
		}
		else if(s1.length() == s2.length()) 
		{
			if (s1.mean() == s2.mean())
			{
				if(s1.minimum() == s2.minimum())
				{
					if(s1.maximum() == s2.maximum())
					{
						if(s1.sum() == s2.sum())
						{
							return true;
						}
						else return false;
					}
					else return false;
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}
}
