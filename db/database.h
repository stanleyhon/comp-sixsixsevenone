#ifndef DATABASE_H
#define DATABASE_H

#include "record.h"
#include <list>
// Your database class definition goes here
template <class value>
class Database {

    // Using vector, so that selection operations
    // occur fast regardless of how many things selected,
    // we simply keep track of which indexes are "selected"
    // and run selected operations on those.

    // vectors offer fast random access where as list doesn't.
    std::vector <Record <value>> records_;
    int numRecords_;
    int numSelected_;

    // this linked list stores indexes who are "selected".
    std::list<unsigned int> selected_; 

    public:
        Database (); // empty constructor
        ~Database (); // Destructor

        // inlined simple functions
        int numRecords () const { return numRecords_; };
        int numSelected () const { return numSelected_; };

        void write (ostream& out, DBScope scope) const;

        void read (istream& in);

        void deleteRecords (DBScope scope);

        void selectAll ();
        void deselectAll ();

        void select (DBSelectOperation selOp, const string& attr, 
                DBQueryOperator op, const value& val);
};

#include "database.tem"

#endif
