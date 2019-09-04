//
// Created by marcel on 6/13/19.
//
#include "catch.hpp"
#include <funcomp.h>
#include <iostream>
#include <sstream>
namespace csv2xls
{
namespace funcompTest
{
    using cppfuncomp::operator|;
    using cppfuncomp::repeatUntil;

    struct Tracer{
        Tracer(){std::cout << "Tracer()\n";}
        Tracer(Tracer const& ){std::cout << "Tracer(Tracer const&)\n";}
        Tracer(Tracer&& ){std::cout << "Tracer(Tracer&&)\n";}
        Tracer operator=(Tracer const&){std::cout << "operator=(Tracer const&)\n";return *this;}
        Tracer operator=(Tracer const&&){std::cout << "operator=(Tracer const&&)\n";return *this;}
        ~Tracer(){std::cout << "~Tracer()\n";}
    };

}
}
