#include "LinkNodeHolder.h"

LinkNodeHolder::LinkNodeHolder() // initialize to null
{
    start = 0;
    end = 0;
    cursor = 0;
    next = 0;
}

void LinkNodeHolder::reset() // puts cursor at first node
{
    cursor = start;
}

LinkNodeHolder* LinkNodeHolder::getNext()
{
    return next;
}

void LinkNodeHolder::setNext(LinkNodeHolder* newNext)
{
    next = newNext;
    return;
}

bool LinkNodeHolder::advance() // advances cursor, true successfull
{
    if(cursor -> getNext() != 0)
    {
	cursor = cursor -> getNext();
	return true;
    }
    return false;
}

bool LinkNodeHolder::hasCurent() // true if there is a current
{
    if(cursor != 0)
    {
      return true;
    }
    return false;
}

bool LinkNodeHolder::hasNextCursor() //true if there is a next
{
    return next;
}

bool LinkNodeHolder::hasNext() //true if there is a next
{
    if(cursor -> getNext() != 0)
    {;
	return true;
    }
    return false;
}

LinkNode* LinkNodeHolder::getCurrent() // returns a pointer to the current cursor
{
    return cursor;
}

void LinkNodeHolder::add(float x, float y) // adds a new LinkNode with values x and y
{
    if(start == 0) // special cas if its the start
    {
	start = new LinkNode(x, y);
	end = start;
	cursor = start;
    }
    else // otherwise
    {
	cursor -> setNext(new LinkNode(x, y));
	cursor = cursor -> getNext();
	end = cursor;
    }
}

float LinkNodeHolder::getX()
{
    return cursor -> xCord;
}

float LinkNodeHolder::getY()
{
    return cursor -> yCord;
}

LinkNodeHolder::~LinkNodeHolder()
{
    cursor = start;
    while(cursor -> getNext() != 0)
    {
	temp = cursor;
	cursor = cursor -> getNext();
	delete temp;
    }
    
    if(cursor != 0) // special case if its empty
    {
	delete cursor;
    }
    
    return;
}

//LinkNode* start;
//LinkNode* end;
//LinkNode* cursor;