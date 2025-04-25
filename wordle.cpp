#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

void wordleHelper(string& current, size_t index, string remainingFloating, const string& in, const set<string>& dict, set<string>& results) {
  if (index == in.size()) { // Base case
    if (remainingFloating.empty() && dict.find(current) != dict.end()) {
      results.insert(current);
    }
    return;
  }

  if (in[index] != '-') { // Fixed character
    current[index] = in[index];
    wordleHelper(current, index + 1, remainingFloating, in, dict, results);
  }
  else { // Try floating characters first
    for (size_t i = 0; i < remainingFloating.size(); ++i) {
      char c = remainingFloating[i];
      current[index] = c;
      string newFloating;
      for (size_t j = 0; j < remainingFloating.size(); ++j) {
        if (j != i) {
        newFloating += remainingFloating[j];
      }
    }
    wordleHelper(current, index + 1, newFloating, in, dict, results);
    }
    // More blanks than floating letters -> try other letters
    if (remainingFloating.size() < in.size() - index) {
      for (char c = 'a'; c <= 'z'; ++c) {
        if (remainingFloating.find(c) != string::npos) continue; //Already tried
        current[index] = c;
        wordleHelper(current, index + 1, remainingFloating, in, dict, results);
      }
    }
  }
}

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code 
    set<string> results;
    string current = in;
    wordleHelper(current, 0, floating, in, dict, results);
    return results;
}

// Define any helper functions here
