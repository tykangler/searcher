#ifndef __ENIGMA_SEARCHRESULTSHPP__
#define __ENIGMA_SEARCHRESULTSHPP__

#include <string>
#include <string_view>
#include <iostream>
#include <set>

#include "search/search_model.hpp"

namespace enigma {

namespace search {

class submatch {
   friend std::ostream &operator<<(std::ostream &stream, const submatch &match);
   friend struct submatch_greater;
   public:
      submatch(std::string_view str_v);
      submatch(std::string_view str_v, const double score);
      ~submatch() {}
      submatch(const submatch&) =default;
      submatch(submatch&&) =default;
      submatch &operator=(const submatch&) =default;
      submatch &operator=(submatch&&) =default;

      using iterator = std::string::iterator;
      using const_iterator = std::string::const_iterator;

      const char &operator[](const int offset) const;
      char &operator[](const int offset);

      iterator begin() noexcept;
      const_iterator begin() const noexcept;
      iterator end() noexcept;
      const_iterator end() const noexcept;
      const std::string &str() const noexcept;
      std::string &str() noexcept;

      std::size_t size() const noexcept;      

   private:
      std::string _str;
      double _score;
};

struct submatch_greater {
   bool operator()(const submatch &left, const submatch &right) const noexcept {
      return left._score > right._score;
   } 
};

/** 
 * the results of applying the pattern matching algorithm to a base string.
*/
class search_results {
   template<typename InputIt>
   friend search_results search_strings(InputIt first, InputIt last, 
                                        const std::string &pattern, const search_model &cscore, 
                                        const double lower_bound, const int max);
   friend std::ostream &operator<<(std::ostream &stream, const search_results &results);
   public:
      search_results(std::string_view pattern_used);
      ~search_results() {}
      search_results(const search_results&) =default;
      search_results(search_results&&) =default;
      search_results &operator=(const search_results&) =default;
      search_results &operator=(search_results&&) =default;
      
      using iterator = std::set<submatch, submatch_greater>::iterator;
      using const_iterator = std::set<submatch, submatch_greater>::const_iterator;

      int size() const;
      const std::string &pattern() const;
      iterator begin() noexcept;
      const_iterator begin() const noexcept;
      iterator end() noexcept;
      const_iterator end() const noexcept;

   private:
      const std::string _pattern_used;
      std::multiset<submatch, submatch_greater> _matched;
};

} // search

} // enigma

#endif