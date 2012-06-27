#include "LinkNode.h"

LinkNode::LinkNode(float x, float y)
{
    next = 0;
    xCord = x;
    yCord = y;
}

LinkNode* LinkNode::getNext()
{
    return next;
}

void LinkNode::setNext(LinkNode* newNext)
{
    next = newNext;
    
    return;
}
