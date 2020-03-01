#ifndef __ENIGMA_SEARCHMODELHPP__
#define __ENIGMA_SEARCHMODELHPP__

#include <string>
#include <memory>
#include "search/error_models.hpp"
#include "search/lang_models.hpp"

namespace enigma {

namespace search {

/**
 * assesses correction ratios between pairs of words.
 * Models are configurable. represents: Pr(w | c)
 * 
 */
class search_model {
   public:
      search_model(lang_model *lang, error_model *err) 
      : _lang{lang}, _err{err} {}
      ~search_model() {}
      search_model(const search_model&) =default;
      search_model(search_model&&) =default;
      search_model &operator=(const search_model&) =default;
      search_model &operator=(search_model&&) =default;

      /**
       * performs calculation
       * parameters:
       *    pattern -> search parameter, the pattern to search for
       *    text -> possible correction for the given pattern
       */
      double operator()(const std::string &pattern, const std::string &text) const {
         return (*_lang)(text) * (*_err)(pattern, text);
      }
   private:
      std::unique_ptr<lang_model> _lang;
      std::unique_ptr<error_model> _err;
};

} // search

} // enigma

#endif