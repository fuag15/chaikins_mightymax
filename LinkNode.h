#ifndef __LinkNode_h__
#define __LinkNode_h__

class LinkNode
{
    //Q_OBJECT

  public:
    LinkNode(float x, float y);
    LinkNode* getNext();
    void setNext(LinkNode* newNext);
    LinkNode* next;
    float xCord;
    float yCord;
};

#endif