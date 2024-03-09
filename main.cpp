#include "string.h" // our std::string is in here
#include "vector.h" // our std::vector is in here

#include <stdio.h> //only using this for printf

#define STRING_TEST 0
#define VECTOR_TEST 1

int main(int argc, char **argv) {
  if (STRING_TEST) {                   // string test
    std::string test = "hello world!"; // initialize with a string
    printf("constructor: %s\n", test.c_str());

    test = "world hello!"; // assign a string
    printf("operator=: %s\n", test.c_str());

    test += " APPENDED!";             // append a string with a operator
    test.append(" APPENEDED AGAIN!"); // append a string with a method
    test.push_back('!');              // append a char with a method
    printf("operator+=: %s\n", test.c_str());

    test.at(0) = 'b'; // indexing and assigning char with a method
    test[6] = 'b';    // indexing and assigning char with an operator
    printf("indexed =: %s\n", test.c_str());

    test.resize(13); // resize the string
    printf("resized string: %s\n", test.c_str());

    auto find1 =
        test.find("hello"); // find hello (our string does not include hello)
    auto find2 =
        test.find("bello"); // find bello (our string does include bello)
    printf("find test: %i (found? %s) %i (found? %s)\n", (int)find1,
           find1 != std::string::npos ? "yes" : "no", (int)find2,
           find2 != std::string::npos ? "yes" : "no");

    // both of these methods do the same thing
    size_t len = test.length(); // get the length of the string
    size_t sz = test.size();    // get the size of the string
    printf("length & size (both do the same thing): %i %i\n", (int)len,
           (int)sz);

    test.erase(0, 5); // get rid of the first 5 characters (borld)
    printf("erase test: %s\n", test.c_str());

    test.insert(0, "world"); // insert world at the very beginning (it will say
                             // world bello)
    printf("insert test: %s\n", test.c_str());

    test.replace(0, 5, "hello"); // replace the first world with hello (it will
                                 // say hello bello)
    printf("replace test: %s\n", test.c_str());

    std::string test2 = "swapped";
    test.swap(test2); // swap the contents of test and test2
    printf("swap test: %s %s\n", test.c_str(), test2.c_str());

    test.pop_back(); // remove the last character
    printf("pop back test: %s\n", test.c_str());

    std::string substr_test = test.substr(2, 4);
    printf("substr test: %s\n", substr_test.c_str());

    test.clear(); // clear the string
    printf("clear test: %s\n", test.c_str());

    test = "hello world!";
    auto compare1 = test.compare("hello world!");
    auto compare2 = test.compare("world hello!");

    printf("compare test: %i (equals? %s) %i (equals? %s)\n", (int)compare1,
           compare1 == 0 ? "yes" : "no", (int)compare2,
           compare2 == 0 ? "yes" : "no");

    bool equal_operator1 = test == "hello world!";
    bool equal_operator2 = test == "world hello!";
    printf("equal operator: %i %i\n", (int)equal_operator1,
           (int)equal_operator2);
  }

  if (VECTOR_TEST) {
    std::vector<int> test = {5, 4, 3, 2, 1, 0}; // initialize with a list
    std::vector<int> test2 = {0, 1, 2, 3, 4, 5}; // initialize with a list

    int index_operator = test[2]; // indexing with an operator
    int index_at = test.at(1);    // indexing with a method
    printf("index test %i %i\n", index_operator, index_at);

    printf("Loop test: { ");
    for (auto& a : test) {
    	printf("%i, ", a); // loop through the vector
    }
    printf(" }\n");

    test.push_back(-1); // append a value
    int back = test.back(); // get the last value
    printf("push back & back test: %i\n", back);

    test.pop_back(); // remove the last value
    printf("pop back test & back test: %i\n", test.back());

    test.assign(4, 100); // assign 4 values of 100
    printf("Assign test: { ");
    for (auto& a : test) {
    	printf("%i, ", a); // loop through the vector
    } printf(" }\n");

    test.insert(test.begin() + 3, 200); // insert 200 at the 3rd index
    printf("Insert test: { ");
    for (auto& a : test) {
    	printf("%i, ", a); // loop through the vector
    } printf(" }\n");

    bool equal1 = test == test2;
    bool equal2 = test == test;
    printf("equal test: %i (equals %s) %i (equals %s)\n",equal1, equal1 ? "yes" : "no", equal2, equal2 ? "yes" : "no" );
  }
}
