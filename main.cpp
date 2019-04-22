#include <iostream>
#include <string>
#include "library_sources.cpp"

int main(int argc, char const *argv[]) {
    echo(std::string("linked: ") + argv[0]);
    std::cout << "fnv \"check\" hash: " << fnvhash("check") << '\n';
    return 0;
}
