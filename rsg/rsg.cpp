/**
 * Provides the implementation of the full RSG application, which
 * relies on the services of the built-in string, ifstream, vector,
 * and map classes as well as the custom Production and Definition
 * classes provided with the assignment.
 */
 
#include <map>
#include <fstream>
#include <cstdlib>
#include "definition.h"
#include "production.h"
#include "assert.h"

using namespace std;

/**
 * Takes a reference to a legitimate infile (one that's been set up
 * to layer over a file) and populates the grammar map with the
 * collection of definitions that are spelled out in the referenced
 * file. 
 *
 * @param infile a valid reference to a flat text file storing the grammar.
 * @param grammar a reference to the STL map, which maps nonterminal strings
 *                to their definitions.
 */

static void readGrammar(ifstream& infile, map<string, Definition>& grammar)
{
   // Peek ahead to see what's there. 
   while (infile.peek () != EOF)
   {
       if (infile.peek () == '{')
       {
          Definition * d = new Definition (infile);
          grammar.insert (make_pair (d->getNonterminal (), *d));
       } 
       else 
       {
          infile.get (); // toss it out - it's rubbish.
       }
    }
}

/**
 * When passed the iterator for the current word being "resolved"
 * and the last word, decides whether or not we should put a space after this word.
 *
 * @params current is an iterator that is the current word that was just printed
 * @params end is the .end () call on the Production object being worked on
 */
static void spaceNeeded (Production::const_iterator current, Production::const_iterator end)
{
   // deal with the thing where, if the next word is punctuation
   // there is no space.
   // Deal with the thing where if there is no next word, there is
   // no space.
   auto nextWord = current + 1;
   if (nextWord != end)
   {
      auto test = *nextWord; 
      char c = test.at (0);
      if (c != ',' && 
          c != '.' && 
          c != '?' && 
          c != '!' && 
          c != ':')
      { 
         cout << " ";
      }
   }
   return;
}

/**
 * Given the grammar map, and a string, decides whether to attempt to
 * resolve the string (i.e. nonterminal) or just print the string (terminal)
 *
 * On resolve, it will recursively call itself on a randomly chosen
 * production of the definition of that string.
 *
 * @param grammar a reference to the STL map.
 * @param root a string we're working on
 */

static void resolveDefinition (const map<string, Definition>& grammar, const string root)
{
   // Check if root is a nonterminal or terminal
   if (root.at (0) != '<') // non-terminal
   {       
      cout << root;
      return;
   }
   else // terminal
   {
      // There must be a defintion for this nonterminal - or something is wrong
      assert (grammar.find (root) != grammar.end ()); 

      // perform a lookup for the definition
      const Definition & d = grammar.at (root);

      // get random production from it
      const Production & p = d.getRandomProduction ();

      for (auto word = p.begin (); word != p.end (); word++)
      {
         // for each word in the production, just recurse on it
         // If it's terminal - it'll just print
         // If it's not terminal - it'll attempt to resolve
         resolveDefinition (grammar, *word);
         spaceNeeded (word, p.end ());
      }
   }
   return;
}

/**
 * Takes a const reference to a grammar stored in a map and prints
 * sentences produced by applying the grammar rules. The number of
 * sentences should be as specified by the second parameter.
 *
 * @param grammar a reference to the STL map, which maps nonterminal strings
 *                to their definitions.
 * @param numSentencesNeeded number of sentences to be produced
 */
 
static void generateRandomSentences(const map<string, Definition>& grammar, 
				    int numSentencesNeeded)
{
   
   int count = 0;
   while (count < numSentencesNeeded)
   { 
      // find <start> nonterminal
      assert (grammar.find ("<start>") != grammar.end ());

      resolveDefinition (grammar, "<start>");

      cout << endl;

      if (count + 1 != numSentencesNeeded) cout << endl;

      count++;
   }

}


/**
 * Performs the rudimentary error checking needed to confirm that
 * the client provided a grammar file.  It then continues to
 * open the file, read the grammar into a map<string, Definition>,
 * and then print out the random expansions as required.
 *
 * @param argc the number of tokens making up the command that invoked
 *             the RSG executable.  There must be at least two arguments,
 *             and only the first two are used.
 * @param argv the sequence of tokens making up the command, where each
 *             token is represented as a '\0'-terminated C string.
 */

int main(int argc, char *argv[])
{
  if (argc == 1) {
    cerr << "You need to specify the name of a grammar file." << endl;
    cerr << "Usage: rsg <path to grammar text file>" << endl;
    
    return EXIT_FAILURE;
  }
  
  ifstream grammarFile(argv[1]);
  if (grammarFile.fail()) {
    cerr << "Failed to open the file named \"" << argv[1] << "\". "
            "Check to ensure the file exists." << endl;
    return EXIT_FAILURE;
  }
  
  // things are looking good...
  map<string, Definition> grammar;
  readGrammar(grammarFile, grammar);
  generateRandomSentences(grammar, 3);
  
  return EXIT_SUCCESS;
}
