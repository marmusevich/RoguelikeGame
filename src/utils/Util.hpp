#ifndef UTIL_H
#define UTIL_H

#include <string>
//#include <cstdarg>
//#include <cstdio>

/**
 * Make formated string like printf(pattern, ...).
 * \param pattern - formated string see printf function
 * \param ... variable list of param
 * \return return formated string or emty string if error occured
 */
std::string ToStringFormated(const char* pattern, ...);

#endif