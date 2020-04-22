#ifndef MACROS_HPP
#define MACROS_HPP

#define foreach(a, b, c) for (int i = 0; i < c.size(); i++) { a *b = &c[i];
#define npforeach(a, b, c) for (int i = 0; i < c.size(); i++) { a b = c[i];
#define cforeach(a, b, c) for (int i = 0; i < sizeof(c) / sizeof(c[0]); i++) { a *b = &c[i];
#define mapforeach(a, b, c) for (std::map<a,b>::iterator it=c.begin(); it!=c.end(); ++it)

#endif