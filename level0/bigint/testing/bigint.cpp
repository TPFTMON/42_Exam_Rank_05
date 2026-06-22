#include "bigint.hpp"
#include <sstream>

void    bigint::_trim(){
    size_t i = 0;
    while (i + 1 < _val.length() && _val[i] == '0'){
        i++;
    }
    _val = _val.substr(i);
}

bigint::bigint() : _val("0") {};

bigint::bigint(unsigned int n){

    std::stringstream ss;
    ss << n;
    _val = ss.str();
}

bigint::bigint(std::string str) : _val(str){

    _trim();
}


