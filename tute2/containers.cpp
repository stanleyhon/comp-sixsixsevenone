#include <iostream>
#include <deque>
#include <list>

void print_all (std::deque<double> * dq1, std::deque<int> * dq2, std::list<int> * list);

int main (void) {
    std::deque<double> dq1;
    std::deque<int> dq2;
    std::list<int> list;


    dq1.push_back (500);
    dq1.push_back (500);
    dq1.push_back (500);
    dq1.push_back (500);
    dq1.push_back (500);

    dq2.push_back (4);
    dq2.push_back (4);
    dq2.push_back (4);
    dq2.push_back (4);
    dq2.push_back (4);
    dq2.push_back (4);

    list.push_back (12);
    list.push_back (12);
    list.push_back (12);
    list.push_back (12);
    
    dq1.assign (list.begin (), list.end ());

    list.assign (dq2.begin (), dq2.end ());

    print_all (&dq1, &dq2, &list);

    return 0;
}

void print_all (std::deque<double> * dq1, std::deque<int> * dq2, std::list<int> * list) {
    std::cout << "DQ1:\n";
    for (auto i = (*dq1).begin (); i != (*dq1).end (); i++) {
        std::cout << *i << std::endl;
    }
    std::cout << "\nDQ2:\n";
    for (auto i = (*dq2).begin (); i != (*dq2).end (); i++) {
        std::cout << *i << std::endl;
    }
    std::cout << "\nlist:\n";
    for (auto i = (*list).begin (); i != (*list).end (); i++) {
        std::cout << *i << std::endl;
    }
    return;
}
