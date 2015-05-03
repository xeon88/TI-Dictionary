#include "Node.h"

class Level_Queue
{
    struct Node_queue
    {
        pNode Node;
        Node_queue * next;
        Node_queue(pNode p);
        ~Node_queue();
    };

    typedef struct Node_queue * h_queue;

    h_queue head;

    bool isEmpty(h_queue head);

    h_queue add_elem(h_queue root,pNode p);

    h_queue extract_elem();

    h_queue get_first_elem();

    void print_queue(h_queue head);

	public:
    /*
        constructor
    */
    Level_Queue();

    /*
        to control if queue is empty
    */
    bool isEmpty();

    void add(pNode p);

    pNode extract();

    pNode get_first();

    void print_queue();
};

