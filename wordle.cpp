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
/*
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
      string newFloating = remainingFloating;
      newFloating.erase(i, 1);
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
*/

int count_dashes(const string& s, size_t start) {
    if (start == s.size()) return 0;
    return (s[start] == '-' ? 1 : 0) + count_dashes(s, start + 1);
}

void recurse(string& current, string& floating, const set<string>& dict, set<string>& results, size_t pos, int remaining_dashes) {
  if (pos == current.size()) {
    // All positions filled and all floating letters used
    if (remaining_dashes == 0 && floating.empty() && dict.count(current)) {
      results.insert(current);
    }
    return;
  }

  if (current[pos] != '-') {
    recurse(current, floating, dict, results, pos + 1, remaining_dashes);
    return;
  }

  // Try placing each floating letter
  char tried[26] = {0};
  for (size_t i = 0; i < floating.size(); ++i) {
    char c = floating[i];
    if (tried[c - 'a']) continue;
    tried[c - 'a'] = 1;

    current[pos] = c;
    // Remove floating[i] without copying entire string
    char last = floating.back();
    floating[i] = last;
    floating.pop_back();

    recurse(current, floating, dict, results, pos + 1, remaining_dashes - 1);

    // Restore
    floating.push_back(last);
    floating[i] = c;
    current[pos] = '-';
  }

  // Only try non-floating letters if there are more dashes than floating letters
  if (floating.size() < static_cast<size_t>(remaining_dashes)) {
    for (char c = 'a'; c <= 'z'; ++c) {
      if (tried[c - 'a'] || floating.find(c) != string::npos) continue;
      current[pos] = c;
      recurse(current, floating, dict, results, pos + 1, remaining_dashes - 1);
      current[pos] = '-';
    }
  }
}

set<string> wordle(const string& in, const string& floating, const set<string>& dict) {
  set<string> results;
  string current = in;
  string floatCopy = floating;
  int numDash = 0;
  for (char c : in) if (c == '-') ++numDash;
  recurse(current, floatCopy, dict, results, 0, numDash);
  return results;
}