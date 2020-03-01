#include "search/search_results.hpp"

namespace enigma {

namespace search {

/* ----------------------- *\
|          submatch         |
\* ----------------------- */

submatch::submatch(std::string_view str_v) : submatch{str_v, 0} {}

submatch::submatch(std::string_view str_v, const double score) : 
_str(str_v.begin(), str_v.end()), _score{score} {}

std::ostream &operator<<(std::ostream &stream, const submatch &match) {
   stream << '[' << match._str << ", " << match._score << ']'; 
   return stream;
}

const char &submatch::operator[](const int offset) const {
   return _str[offset];
}

char &submatch::operator[](const int offset) {
   return _str[offset];
}

submatch::iterator submatch::begin() noexcept {
   return _str.begin();
}

submatch::const_iterator submatch::begin() const noexcept {
   return _str.begin();
}

submatch::iterator submatch::end() noexcept {
   return _str.end();
}

submatch::const_iterator submatch::end() const noexcept {
   return _str.end();
}

const std::string &submatch::str() const noexcept {
   return _str;
}

std::string &submatch::str() noexcept {
   return _str;
}

std::size_t submatch::size() const noexcept {
   return _str.size();
}

/* ----------------------- *\
|        search_results     |
\* ----------------------- */

search_results::search_results(std::string_view pattern_used)
: _pattern_used(pattern_used.begin(), pattern_used.end()) {}

int search_results::size() const {
   return _matched.size();
}

const std::string &search_results::pattern() const {
   return _pattern_used;
}

search_results::iterator search_results::begin() noexcept {
   return _matched.begin();
}

search_results::const_iterator search_results::begin() const noexcept {
   return _matched.begin();
}

search_results::iterator search_results::end() noexcept {
   return _matched.end();
}

search_results::const_iterator search_results::end() const noexcept {
   return _matched.end();
}

std::ostream &operator<<(std::ostream &stream, const search_results &results) {
   for (auto &match : results) {
      stream << match << ' ';
   }
   return stream;
}

} // search

} // enigma