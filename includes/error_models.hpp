#ifndef __ENIGMA_ERRORMODELHPP__
#define __ENIGMA_ERRORMODELHPP__

#include <string>

namespace enigma {

namespace search {

/**
 * represents the chance that a person will mistype <text> and instead type <pattern>.
 * the more similar two strings are, the greater this chance is
 */
struct error_model {
   virtual ~error_model() {}
   virtual double operator()(const std::string &pattern, const std::string &text) const =0; 
};

/** 
 * error model based on the edit distance between two strings
*/
struct edit_similarity : public error_model {
   ~edit_similarity() {}
   virtual double operator()(const std::string &pattern, const std::string &text) const final;
};

/**
 * error model based on longest common subsequence
 */
struct lcs_similarity : public error_model {
   ~lcs_similarity() {}
   virtual double operator()(const std::string &pattern, const std::string &text) const final;
};

} // search

} // enigma

#endif