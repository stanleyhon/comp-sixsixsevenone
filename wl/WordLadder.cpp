/*
 * File: WordLadder.cpp
 * --------------------
 * Name: [TODO: enter name here]
 * This file is the starter project for the word ladder problem on Assignment #1.
 */

#include "genlib.h"
#include "lexicon.h"
#include <queue>
#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <ctype.h> // for tolower ()
#include <assert.h>
#include <algorithm> // for sort

using namespace std;

// word ladders are vectors of strings
typedef vector<string> ladder_t;

// the queue elements are word ladders and an integer indicating the ladder's level
typedef pair<ladder_t, int> queueItem_t;
// The queue itself is of a queue of those items
typedef queue<queueItem_t> queue_t;

// a map maps words to when they were seen 
typedef map<string, int> map_t;

bool findWord (string s, int level);
void generateNextWord (ladder_t baseLadder, int level);
bool serviceQueue (void);
void printResults (void);

const string alphabet = "abcdefghijklmnopqrstuvwxyz";
string startWord;
string destinationWord;
map_t seenWords; // map used to keep track of seen words
queue_t q; // queue used to implement BFS
Lexicon dictionary ("EnglishWords.dat"); 
bool firstResult = true;

// store results in a list so we can sort them before printing
list<ladder_t> results;

int main() {
    cout << "Enter start word (RETURN to quit): ";
    cin >> startWord;

    if (startWord.length () == 0) return EXIT_SUCCESS;

    cout << "Enter destination word: ";
    cin >> destinationWord;

    if (destinationWord.length () != startWord.length ()) {
        cout << "No ladder found.\n";
        return EXIT_SUCCESS;
    }

    if (destinationWord.length () == 0) {
        cout << "No ladder found.\n";
        return EXIT_SUCCESS;
    }

    // Lowercase them both
    for (auto c = startWord.begin (); c != startWord.end (); c++) {
        *c = tolower (*c);
    }
    for (auto c = destinationWord.begin (); c != destinationWord.end (); c++) {
        *c = tolower (*c);
    }


    // Put the first element on
    ladder_t wordLadder;
    wordLadder.push_back (startWord);
    queueItem_t firstItem = make_pair (wordLadder, 0);
    q.push (firstItem);

    bool solutionFound = false;
    while (q.empty () == false) {
        // service queue
        // logical OR, so if it ever becomes true it will stay true
        bool result = serviceQueue ();

        if (result == true) {
            solutionFound = true;
        }
    }

    if (solutionFound == false) {
        cout << "No ladder found.\n";
    } else {
        // print the results
        printResults ();
    }

    return EXIT_SUCCESS;
}


bool serviceQueue (void) {
    assert (q.empty () == false);
    queueItem_t currentItem = q.front ();
    q.pop ();

    // First is of type ladder_t (wordLadder)
    // Second is of type int (level)
    ladder_t currentLadder = currentItem.first;
    int level = currentItem.second;
    assert (currentLadder.size () != 0 && level >= 0);

    if (level != 0) { // see if it's already a solution
        if (currentLadder.back ().compare (destinationWord) == 0) { // Found a solution!
#ifdef DEBUG
            cout << "Found a solution!\n";
#endif
            if (firstResult == true) {
                cout << "Found ladder: ";
                firstResult = false;
            }

            results.push_back (currentLadder);

            return true;
        }
    } else { // level is 0
        if (currentLadder.back ().compare (destinationWord) == 0) { // start and dest are same
            cout << "Found ladder: ";

            // push the word itself on as well
            currentLadder.push_back (currentLadder.back ());

            for (auto word = currentLadder.begin (); word != currentLadder.end (); word++) {
                cout << *word;
                if (word + 1 != currentLadder.end ()) {
                    cout << " ";
                }
            }
            cout << endl;

            return true;
        }
    }

    // this one isn't a solution. generate 1 step words and push into queue.
    // simply don't generate any more possibilities after we've found a solution
    if (firstResult == true) {
        generateNextWord (currentLadder, level);
    }

    // return false to indicate no success yet
    return false;
}

void generateNextWord (ladder_t baseLadder, int level) {
    assert (level >= 0);
    string s = baseLadder.back ();
    int nextLevel = level + 1;

    // put ourselves on the seen list.
    findWord (s, level);

    // for each character in the workingString
    for (auto sChar = s.begin (); sChar != s.end (); sChar++) {

        char original = *sChar; // save the character it was originally

        // substitute for each alphabet character
        for (auto alphabetChar = alphabet.begin (); alphabetChar != alphabet.end (); alphabetChar++) {

            // skip if same as original
            if (*alphabetChar == *sChar) continue;

            // replace "sChar"-th in s, with "alphabetChar" in alphabet
            *sChar = *alphabetChar;

            // check if we've seen this before.
            if (dictionary.containsWord (s) == true) { // word is valid too, good to queue
                // check if it's a valid word
                if (findWord (s, nextLevel) == false) { // not found, good to queue
#ifdef DEBUG
                    cout << "Generated a valid word " << s << endl;
#endif
                    ladder_t newLadder = baseLadder;
                    // add our new word to the ladder
                    newLadder.push_back (s);
                    // make the queue item
                    queueItem_t item = make_pair (newLadder, nextLevel);
                    // put it on
                    q.push (item);
                }
            }
        }
        
        // Put back the original letter in that spot
        *sChar = original;
    }
    return;
}

// if not found, puts it in
bool findWord (string s, int level) {
#ifdef DEBUG
    assert (s.length () != 0);
    assert (level >= 0);
    cout << "finding [" << s << "]\n";
#endif
    auto lookup = seenWords.find (s);
    if (lookup == seenWords.end ()) {
#ifdef DEBUG
        cout << "not found\n";
#endif
        seenWords.insert (make_pair (s, level));
        return false;
    } else {
        // compare it's level with ours.
        int lookupLevel = lookup->second;
        if (lookupLevel == level) {
            // if the levels are equal, we've reached this word just as efficiently.
            // so return false to indicate that the word is not really here
#ifdef DEBUG
            cout << "found but returning false for same level\n";
#endif
            return false;
        }
    }
    // but if the level is lower, we've seen it before so return true
#ifdef DEBUG
    cout << "found\n";
#endif
    return true;
}

// sort the results list 
// print it
void printResults (void) {
    list<string> printList;

    // for each result in the results 
    for (auto result = results.begin (); result != results.end (); result++) {
        string newString = "";
        // combine each of the strings into one big result string
        for (auto s = result->begin (); s != result->end (); s++) {
            newString.append (*s);
            if (s + 1 != result->end ()) {
                newString.append (" ");
            }
        }

        // and put it on the printlist
        printList.push_back (newString);
    }

    // sort the printlist
    printList.sort();

    // print it in the format they want.
    for (auto r = printList.begin (); r != printList.end (); r++) {
        cout << *r << "\n";
    }

    return;
}



