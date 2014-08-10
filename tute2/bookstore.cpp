#include <iostream>
#include <map>
#include <list>

class title {
    private:
        static int next_id;
        int id;

    public:
        std::string name;
};

class price {
    private:
        static int next_id;
        int id;
    public:
        double price;

        price ();
        price (double p) {
            price = p;
        }
};


int main (void) {
    title::next_id = 0;
    price::next_id = 0;
    std::list<int> test;

    std::list<std::map<title, price>> l;

    title t;
    t.name = "how to dote";
    price p;
    p.price = 9001.99;
    std::map<title, price> m = {t, p};

    l.push_back(m);

    return 0;
}
