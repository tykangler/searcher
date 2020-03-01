#include "search/lang_models.hpp"

namespace enigma {

namespace search {

double basic_model::operator()(const std::string &text) const {
   return 1;
}

} // search

} // enigma