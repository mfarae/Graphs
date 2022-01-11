// Muhammad Farae 2020292
// CS221
// LAB TASK GRAPHS

#include <iostream>
using namespace std;

struct node;
struct edge; // struct prototyping
struct node
{
    int name;
    node *next; // adjency list node implementation, which are vertices
    edge *EHead;
    edge *ETail;
}*head, *tail; // global declarations

int graph_size = 0;

struct edge // edge definition
{
    int adj_node;
    int cost;
    edge* next_edge;
};

struct queue // queue used for the implementation of bfs. It is implemented using dynamic array
{
    int *q;
    int size, front, rear;
    queue(int size)
    {
        q = new int[size];
        front = rear = -1;
    }
    void enqueue(int val)
    {
        q[++rear] = val;
        front = 0;
    }
    int dequeue()
    {
        if (rear == -1)
            return -1; // empty conditon
        int de_val = q[front];
        for (int i = 0; i < rear; i++)
        {
            //cout << q[i] << " replaced with " << q[i+1] << endl;
            q[i] = q[i+1]; // shifting right to overwrite the frontmost value
        }
        rear--; // decrease rear by 1
        return de_val; // return dequeued value.
    }
    void display() // display the entire queue
    {
        for (int i = 0; i <= rear; i++)
        {
            cout << q[i] << " ";
        }
        cout << endl;
    }
};


struct stack // stack implementation used for dfs.
{
    int top;
    int *st;
    int size; // dynamic array

    stack(int s)
    {   
        size = s;
        top = -1;
        st = new int[size];        
    }
    bool empty()
    {
        if (top == -1)
            return true;
        else
            return false;
    }
    void push(int val)
    {
        st[++top] = val;
    }
    int pop()
    {
        if (empty())
        {
            cout << "Empty" << endl;
            return -1;
        }
        int popped = st[top--];
        return popped;
    }
    void display()
    {
        for (int i = top; i != -1; i--)
        {
            cout << st[i] << " ";
        }
        cout << endl;
    }
};


void append(int name) // code ton define vertex
{
    if (head == nullptr)
    {
        head = new node;
        head->name = name;
        head->EHead = new edge;
        head->EHead->next_edge = nullptr;
        head->ETail = head->EHead;
        head->next = nullptr;
        tail = new node;
        tail->next = head;
        tail = head;
        return;
    }
    
    node *ptr = new node;
    ptr->name = name;
    ptr->EHead = new edge;
    ptr->EHead->next_edge = nullptr;
    ptr->ETail = ptr->EHead;
    ptr->next = nullptr;
    tail->next = ptr;
    tail = ptr;
}

edge* add_edge(int adj_node, int cost, edge* ETail) // code to define edge
{
    edge *E = new edge;
    E->cost = cost;
    E->adj_node = adj_node;
    E->next_edge = nullptr;
    ETail->next_edge = E;
    ETail = E;
    return ETail;
}


void display_graph() // code to iteratively traverse the adjacency list and display the entire the graph
{
    node *ptr = head;
    while (ptr != nullptr)
    {
        cout << ptr->name << " connects with: ";
        edge* e = ptr->EHead->next_edge;
        while (e != nullptr)
        {
            cout << e->adj_node << " ";
            e = e->next_edge;
        }
        ptr = ptr->next;
        cout << endl;
    }
}


void bfs(int starting_node)
{
    queue q(0);
    int *status = new int[graph_size]; //0 means unvisited, 1 means unprocessed, 2 means processed
    for (int i = 0; i < graph_size; i++) // initialize with zero
    {
        status[i] = 0;
    }
    node *ptr = head;
    bool all_processed = 0;
    int dequeued = starting_node;
    cout << dequeued << " dequeued" << endl;
    status[dequeued-1] = 2; // update the starting node status to be processed
    while (all_processed == false)
    {
        ptr = head;
        all_processed = true;
        while (ptr->name != dequeued)
        {
            ptr = ptr->next; // traverse the node until the vertex that was dequeued
        }
        edge *e = ptr->EHead->next_edge; // declare a traversal pointer to enqueue all nodes it connects with
        while (e != nullptr)
        {
            if (status[e->adj_node-1] != 0) // if the node has already been processed or visited before, skip enqueing
            {
                e = e->next_edge;
                continue;
            }
            q.enqueue(e->adj_node); // otherwise enqueue
            status[e->adj_node-1] = 1;
            e = e->next_edge; // traverse next until nullptr
        }
        dequeued = q.dequeue(); // dequeue the first element
        cout << dequeued << " dequeued" << endl;
        status[dequeued-1] = 2; // update status to processed

        for (int i = 0; i < graph_size; i++) // check if all nodes have been processed
        {
            if (status[i] != 2)
            {
                all_processed = false;
            }
        }
    }
    delete []status; //deallocate memory from heap to avoid memory leak
}


void dfs(int starting_node) // commenting has been limited for dfs as it's the same code as bfs except stack is used instead of queue
{ // therefore, pop replaces dequeue, and push replaces enqueue. LIFO is followed in stack (depth-first), FIFO in queue (breadth-first).
    stack st(graph_size);
    int *status = new int[graph_size];
    bool all_processed = false;
    node *ptr = head;
    for (int i = 0; i < graph_size; i++)
    {
        status[i] = 0; // 0 means unvisisted, 1 means unprocessed, 2 means processed
    }
    st.push(starting_node);
    cout << starting_node << " pushed" << endl;
    status[starting_node-1] = 1;
    int popped = st.pop();
    status[starting_node-1] = 2;
    while (all_processed == false)
    {
        all_processed = true;
        ptr = head;
        while (ptr->name != popped)
        {
            ptr = ptr->next;
        }
        edge *e = ptr->EHead->next_edge;
        while (e != nullptr)
        {
            if (status[e->adj_node-1] != 0)
            {
                e = e->next_edge;
                continue;
            }
            cout << e->adj_node << " pushed" << endl;
            st.push(e->adj_node);
            status[e->adj_node-1] = 1;
            e = e->next_edge;
        }
        popped = st.pop();
        status[popped-1] = 2;

        for (int i = 0; i < graph_size; i++)
        {
            if (status[i] != 2)
            {
                all_processed = false;
            }
        }
    }
    delete []status;
}


int main()
{

    append(1);
    append(2);
    append(3);
    append(4);
    append(5);
    graph_size = 5;

    //establishing connections
    node* ptr = head;
    cout << ptr->name << endl;
    ptr->ETail = add_edge(2, 1, ptr->ETail); //ptr at 1
    ptr->ETail = add_edge(3, 1, ptr->ETail);
    ptr->ETail = add_edge(4, 1, ptr->ETail);

    ptr = ptr->next; // ptr at 2
    cout << ptr->name << endl;
    ptr->ETail = add_edge(1, 1, ptr->ETail);
    ptr->ETail = add_edge(3, 1, ptr->ETail);
    ptr->ETail = add_edge(5, 1, ptr->ETail);

    ptr = ptr->next; // ptr at 3
    cout << ptr->name << endl;
    ptr->ETail = add_edge(1, 1, ptr->ETail);
    ptr->ETail = add_edge(2, 1, ptr->ETail);

    ptr = ptr->next;//ptr at 4
    cout << ptr->name << endl;
    ptr->ETail = add_edge(1, 1, ptr->ETail);

    ptr = ptr->next; // ptr at 5
    cout << ptr->name << endl;
    ptr->ETail = add_edge(2, 1, ptr->ETail);

    display_graph();


    cout << "\n\n" << endl;
    bfs(5); // bfs starting from node 5

    cout << "\n\n" << endl;
    dfs(4); // dfs starting from node 4
    return 0;
}