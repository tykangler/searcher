#ifndef __ENIGMA_SEARCHSTRINGSHPP__
#define __ENIGMA_SEARCHSTRINGSHPP__

#include <algorithm>
#include <string>
#include "search/search_results.hpp"
#include "search/search_model.hpp"

namespace enigma {

namespace search {

template<typename InputIt>
search_results search_strings(InputIt first, InputIt last, const std::string &pattern, 
                              const search_model &cscore,
                              const double lower_bound, const int max) {
   search_results results{pattern};
   while (first != last && results.size() < max) {
      if (double score = cscore(pattern, *first); score >= lower_bound) {
         results._matched.insert({*first, score});
      }
      ++first;
   }
   return results;
}

}

}

#endif