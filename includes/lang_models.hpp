#ifndef __ENIGMA_LANGMODELHPP__
#define __ENIGMA_LANGMODELHPP__

#include <string>

namespace enigma {

namespace search {

struct lang_model {
   virtual ~lang_model() {}
   virtual double operator()(const std::string &text) const =0;
};

struct basic_model : public lang_model {
   virtual ~basic_model() {}
   virtual double operator()(const std::string &text) const final;
};
   
} // search

} // enigma

#endif