#include "string.h"
#include <stdio.h>

int main(int argc, char **argv) {
  { //string test
    std::string test = "hello world!\n";
    test = "world hello!\n";
    test += "test\n";
    test.at(0) = 'b';
    test[6] = 'b';
    test.resize(13);
    test.append("append test\n");
  
    printf("%s %i\n", test.c_str(), test.find("append") == std::string::npos);
  }
}
