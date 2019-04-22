#include <iostream>
#include <dlfcn.h>
#include <string>


void error_message(const std::string& str) {
    std::cout << str << "\nbecause of: " << dlerror() << '\n';
}

void* load_function(void* library, const std::string& func) {
    void* func_ptr = dlsym(library, func.c_str());
    if (!func_ptr) {
        error_message("Failed to load " + func);
        exit(-1);
    }
    return func_ptr;
}

int main(int argc, char const *argv[]) {
    const std::string library = "libdynamic.so";

    const std::string func = "_Z4echoRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE";
    using func_type = void (*) (const std::string&);

    const std::string hashfunc = "_Z7fnvhashPKc";
    using hashfunc_type = int (*) (const char*);


    void* loaded_lib = dlopen(library.c_str(),  RTLD_LAZY | RTLD_GLOBAL);
    if (!loaded_lib) {
        error_message("Failed to open " + library);
        return -1;
    }

    func_type echo_ptr = reinterpret_cast<func_type>(load_function(loaded_lib, func));
    hashfunc_type fnvhash_ptr = reinterpret_cast<hashfunc_type>(load_function(loaded_lib, hashfunc));

    echo_ptr(std::string("linked: ") + argv[0]);
    std::cout << "fnv \"check\" hash: " << fnvhash_ptr("check") << '\n';
    return 0;
}
