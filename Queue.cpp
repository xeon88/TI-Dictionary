#include "Queue.h"

Level_Queue::Node_queue::Node_queue(pNode p) : Node(p) , next(NULL){}

/*
    Private functions;
*/

Level_Queue::Node_queue::~Node_queue()
{
    //delete head;
}

Level_Queue::Level_Queue()
{
    head=NULL;
}

bool Level_Queue::isEmpty(h_queue head)
{
	return head==NULL;
}


Level_Queue::h_queue Level_Queue::add_elem(h_queue head ,pNode elem)
{

    h_queue * it =&head;
    if(*it==NULL)
    {
        *it=new Node_queue(elem);
    }
    else
    {

        while((*it)->next!=NULL)
        {
        it=&((*it)->next);
        }

        (*it)->next=new Node_queue(elem);

    }

    return head;
}



Level_Queue::h_queue  Level_Queue::extract_elem()
{
    Level_Queue::h_queue first=head;
    delete head;
    head=first->next;
	return first;
}

Level_Queue::h_queue Level_Queue::get_first_elem()
{
    h_queue first= new Node_queue(head->Node);
    //print_node(first->Node);
    return first;

}



/*
    Public functions
*/



bool Level_Queue::isEmpty()
{
    return isEmpty(head);
}

void Level_Queue::add(pNode p)
{
    head=add_elem(head,p);
}

pNode Level_Queue::get_first()
{
    Level_Queue::h_queue r=get_first_elem();
    pNode first=r->Node;
    return first;

}

void Level_Queue::print_queue()
{
    print_queue(head);

}

pNode Level_Queue::extract()
{

    Level_Queue::h_queue r=extract_elem();
    pNode first=r->Node;
    return first;
}



void Level_Queue::print_queue(Level_Queue::h_queue root)
{

    cout << "\n======QUEUE========\n";
    h_queue * it = &root;
    while(*it!=NULL)
    {
       print_node((*it)->Node);
       it=&((*it)->next);

    }

    cout << "\n======END QUEUE=====\n";
}
