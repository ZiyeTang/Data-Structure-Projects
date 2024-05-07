/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;
using std::sort;
/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream wordsFile(filename);
    string word;
    if (wordsFile.is_open()) 
    {
        /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, word)) 
        {
            string sorted=word;
            std::sort(sorted.begin(), sorted.end());
            dict[sorted].push_back(word);
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for(auto word=words.begin(); word!=words.end(); word++)
    {
        string sorted = *word;
        std::sort(sorted.begin(), sorted.end());
        dict[sorted].push_back(*word);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    vector<string> ret;
    string sorted=word;
    sort(sorted.begin(), sorted.end());
    if(dict.find(sorted)!=dict.end())
    {
        ret=dict.find(sorted)->second;
        /*for(auto it=ret.begin(); it!=ret.end(); it++)
        {
            if(*it==word)
            {
                ret.erase(it);
                break;
            }
        }*/
        return ret;
    }
    return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> ret;
    for (auto it = dict.begin(); it != dict.end(); it++)
    {
        if(it->second.size()>1)
        {
            ret.push_back(it->second);
        }
    }
    return ret;
}


bool AnagramDict::areAnagrams(const string word1, const string word2)
{
    string sorted1=word1;
    sort(sorted1.begin(),sorted1.end());
    string sorted2=word2;
    sort(sorted2.begin(),sorted2.end());
    return sorted1==sorted2;
}