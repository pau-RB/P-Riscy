#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "interpreter.h"

using namespace std;

int main(int argc, char *argv[]) {

  	uint32_t word;

  	while(cin >> std::hex >> word) {
        cout << interpreter(word)<< endl;
  	}

  	return 0;
}