#include "search/error_models.hpp"

#include <string_view>
#include <algorithm>
#include <numeric>
#include <vector>

namespace enigma {

namespace search {

namespace {

double edit_distance(std::string_view pattern, std::string_view text) {
   std::vector<int> v0(pattern.size() + 1);
   std::vector<int> v1(pattern.size() + 1, 0);
   std::iota(v0.begin(), v0.end(), 0);
   for (int i = 0; i < text.size(); ++i) {
      int delete_cost = 0;
      int sub_cost = 0;
      int insert_cost = 0;
      v1.front() = i + 1;
      for (int j = 0; j < pattern.size(); ++j) {
         delete_cost = v0[j + 1] + 1;
         insert_cost = v1[j] + 1;
         sub_cost = v0[j] + (int) (tolower(text[i]) != tolower(pattern[j]));
         v1[j + 1] = std::min({delete_cost, insert_cost, sub_cost});
      }
      v0.swap(v1);
   }
   return v0.back();
}

double lcs_length(std::string_view s1, std::string_view s2) {
   std::vector<int> top(s1.size() + 1, 0);
   std::vector<int> bot(s1.size() + 1);
   for (int i = 1; i <= s2.size(); ++i) {
      bot[0] = 0;
      for (int j = 1; j <= s1.size(); ++j) {
         if (tolower(s1[j - 1]) == tolower(s2[i - 1])) {
            bot[j] = top[j - 1] + 1;
         } else {
            bot[j] = std::max(top[j], bot[j - 1]);
         }
      }
      top.swap(bot);
   }
   return top.back();
}

} // unnamed

double edit_similarity::operator()(const std::string &pattern, const std::string &text) const {
   return 1 - (edit_distance(pattern, text) / std::max(pattern.size(), text.size()));
}

double lcs_similarity::operator()(const std::string &pattern, const std::string &text) const {
   double num_matched = 2 * lcs_length(pattern, text);
   return num_matched / (pattern.size() + text.size());
}

} // search

} // enigma