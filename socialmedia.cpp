#include <bits/stdc++.h>
using namespace std;
class adjlist
{
public:
    int frd;
    adjlist *link;
};
class nodelist
{
public:
    int node;
    nodelist *next;
    adjlist *adj;
    nodelist() : next(nullptr), adj(nullptr) {}
};
class frdct
{
public:
    int id;
    int frd;
    frdct *next;
    frdct() : next(nullptr) {}
};
nodelist *head = nullptr;
nodelist *curr = nullptr;
frdct *head_frd = nullptr;
void add_member()
{
    nodelist *newnode = new nodelist();
    int id;
    cout << "Enter the ID of new member: ";
    cin >> id;
    newnode->node = id;
    if (head == nullptr)
    {
        head = newnode;
        curr = newnode;
    }
    else
    {
        curr->next = newnode;
        curr = newnode;
    }

    cout << "->Member added successfully" << endl;
}
void add_edge()
{
    int m1, m2;
    cout << "Enter the ID of Current member: ";
    cin >> m1;
    cout << "Enter the ID of friend member: ";
    cin >> m2;
    nodelist *temp = head;
    while (temp->node != m1)
    {
        temp = temp->next;
    }
    adjlist *adjlistnode = new adjlist();
    adjlistnode->frd = m2;
    if (temp->adj == nullptr)
    {
        temp->adj = adjlistnode;
        adjlistnode->link = nullptr;
        frdct *new_frdlist = new frdct();
        new_frdlist->id = m1;
        new_frdlist->frd = 1;
        if (head_frd == nullptr)
        {
            head_frd = new_frdlist;
        }
        else
        {
            frdct *tt = head_frd;
            while (tt->next != nullptr)
            {
                tt = tt->next;
            }
            tt->next = new_frdlist;
        }
    }
    else
    {
        adjlist *t = temp->adj;
        while (t->link != nullptr)
        {
            t = t->link;
        }
        t->link = adjlistnode;
        adjlistnode->link = nullptr;
        frdct *tt = head_frd;
        while (tt->id != m1)
        {
            tt = tt->next;
        }
        tt->frd += 1;
    }
    cout << "->Friend added successfully" << endl;
}
adjlist *partition(adjlist *first, adjlist *last)
{
    adjlist *pivot = first;
    adjlist *front = first;
    int temp = 0;
    while (front != nullptr && front != last)
    {
        if (front->frd < last->frd)
        {
            pivot = first;

            temp = first->frd;
            first->frd = front->frd;
            front->frd = temp;

            first = first->link;
        }
        front = front->link;
    }
    temp = first->frd;
    first->frd = last->frd;
    last->frd = temp;
    return pivot;
}
void quick_sort(adjlist *first, adjlist *last)
{
    if (first == last)
    {
        return;
    }
    adjlist *pivot = partition(first, last);

    if (pivot != nullptr && pivot->link != nullptr)
    {
        quick_sort(pivot->link, last);
    }

    if (pivot != nullptr && first != pivot)
    {
        quick_sort(first, pivot);
    }
}
adjlist *last_node(adjlist *head)
{
    adjlist *temp = head;
    while (temp != nullptr && temp->link != nullptr)
    {
        temp = temp->link;
    }
    return temp;
}
adjlist *first_node(int m)
{
    nodelist *temp = head;
    while (temp->node != m)
    {
        temp = temp->next;
    }
    return temp->adj;
}
nodelist *m_node(int m)
{
    nodelist *temp = head;
    while (temp->node != m)
    {
        temp = temp->next;
    }
    return temp;
}
void sortedIntersect(adjlist *a, adjlist *b)
{
    cout << "\n->Mutual friends of the two members are: ";
    while (a != nullptr && b != nullptr)
    {
        if (a->frd == b->frd)
        {
            cout << a->frd << " ";
            a = a->link;
            b = b->link;
        }
        else if (a->frd < b->frd)
        {
            a = a->link;
        }
        else
        {
            b = b->link;
        }
    }
    cout << endl
         << endl;
}
void mutual_frd()
{
    int m1, m2;
    cout << "Enter the ID of member 1: ";
    cin >> m1;
    cout << "Enter the ID of member 2: ";
    cin >> m2;

    adjlist *fn1 = first_node(m1);
    adjlist *ln1 = last_node(fn1);
    quick_sort(fn1, ln1);

    adjlist *fn2 = first_node(m2);
    adjlist *ln2 = last_node(fn2);
    quick_sort(fn2, ln2);

    sortedIntersect(first_node(m1), first_node(m2));
}
void max_conn()
{
    frdct *tt = head_frd;
    int ct = 0, max_id;
    while (tt->next != nullptr)
    {
        if (ct < tt->frd)
        {
            ct = tt->frd;
            max_id = tt->id;
        }
        tt = tt->next;
    }
    if (ct < tt->frd)
    {
        ct = tt->frd;
        max_id = tt->id;
    }
    tt = tt->next;
    cout << "\n->" << max_id << " has maximum connections" << endl
         << endl;
}
void display()
{
    cout << "\nMember   -    Friends" << endl;
    cout << "---------------------" << endl;
    nodelist *temp = head;
    while (temp->next != nullptr)
    {
        cout << temp->node << " - ";
        adjlist *t = temp->adj;
        while (t->link != nullptr)
        {
            cout << t->frd << " ,";
            t = t->link;
        }
        cout << t->frd << " ";
        temp = temp->next;
        cout << endl;
    }
    cout << temp->node << " - ";
    adjlist *t = temp->adj;
    while (t->link != nullptr && t != nullptr)
    {
        cout << t->frd << " ,";
        t = t->link;
    }
    cout << t->frd << endl
         << endl;
}
void display_frd_list()
{
    int m;
    cout << "Enter the ID of the member whose friend is to displayed: ";
    cin >> m;

    nodelist *temp = head;
    while (temp->node != m)
    {
        temp = temp->next;
    }
    cout << "\nFriend list - ";
    adjlist *t = temp->adj;
    while (t->link != nullptr)
    {
        cout << t->frd << " ";
        t = t->link;
    }
    cout << t->frd << endl
         << endl;
}
int main()
{
    cout << "Working on initial network...." << endl;
    add_member();
    add_member();
    add_edge();
    add_edge();
    display();
    cout << "------------Welcome to Social Network functionality Program-----------------" << endl;
    cout << "You can perform the following functions in the network: " << endl;
    cout << "1. Add a new member to the network." << endl;
    cout << "2. Make friend." << endl;
    cout << "3. Display the friend list of a member." << endl;
    cout << "4. Find the mutual friends of any two member" << endl;
    cout << "5. Find a member with maximum number of connections" << endl;
    cout << "6. Display the graph which represent the current network" << endl;
    cout << "7. Exit" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;

    int ans = 1;
    while (ans)
    {
        int ch;
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            add_member();
            cout << "For a new member you need to add at least one friend" << endl;
            add_edge();
            break;
        case 2:
            add_edge();
            break;
        case 3:
            display_frd_list();
            break;
        case 4:
            mutual_frd();
            break;
        case 5:
            max_conn();
            break;
        case 6:
            display();
            break;
        case 7:
            ans = 0;
            break;
        default:
            cout << "Enter a valid choice !!" << endl;
        }
    }
    return 0;
}
