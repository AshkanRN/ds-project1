#ifndef UTILS_H
#define UTILS_H

#include <iostream>

inline std::string toLowerCase(std::string &str) {
    for (int i = 0 ; i < str.length() ; i++)
        str[i] = (str[i] >= static_cast<int>('A') && str[i] <= 'Z') ? (str[i] + 32) : str[i];
    return str;
}

#endif
