#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#define CacheLineWords 16
#define WMBAddr 12

using namespace std;

int main(int argc, char *argv[]) {

  	string current_exec_name = argv[0];
  	vector<string> all_args;

  	if (argc > 1) {
  	  all_args.assign(argv + 1, argv + argc);
  	}

  	string path = "./vmh/" + all_args[0] + ".riscv.vmh";
	cout << path << endl;

	ifstream srcfile;
  	srcfile.open(path);

  	ofstream dstfile;
  	dstfile.open("mem.vmh");
  	
  	string word; int i = 0;

  	srcfile >> word;
  	dstfile << word << "\n";

  	for (int i = 0; i < (1<<WMBAddr); ++i) {
  		for (int j = 0; j < CacheLineWords; ++j) {
  			srcfile >> word;
  			dstfile << word;
  		}
  		dstfile << "\n";
  	}

  	return 0;
}