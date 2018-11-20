#include "BST.h"
#include "UPC.h"
#include <iostream>
#include <fstream>
#include <sstream>

void load_data(std::string&, int);
void add_array(UPC&);
void upsize();

BST<UPC>* UPCTree = new BST<UPC>();
bool running = true;

int main(int argc, char* argv[]) {
	std::string file_name;

	// use command line argument for file name; if
	// none is provided, use the default 'upc_corpus.txt' name
	if(argc > 1)
		file_name = argv[1];
	else
		file_name = "upc_corpus.txt";

	load_data(file_name, 2000000000);

	/*
	 * Prompt for user-input and search for UPC code
	 * data until the user enters "Q" to quit.
 	 */
 std::string input;
	while(running == true) {
		std::cout << "Enter a UPC code, or 'Q' to quit: \n";
		std::getline(std::cin, input);
		if(input == "Q" || input == "q") {
			running = false;
		} else {
			UPC* upc = new UPC();
			UPC* result;
			try {
				long long upc_code = std::stoll(input);
				upc -> setUPC(upc_code);
				result = new UPC(UPCTree->search(*upc));
				std::cout << "UPC Code: " << upc_code << "\n"
									<< result->getData() << "\n";

			} catch(std::exception e) {
				std::cout << "INVALID INPUT\n";
			}
		}
	}
}

void load_data(std::string& file_name, int num_lines) {

		std::string cur_line, cur_token, upc, data;	// strings to hold linewise data as file is read
		std::ifstream file;	// input file stream to read file data

		file.open(file_name);
		int lines = 0;

		/*
		 * read each line of the file and convert the
		 * upc/data from each line to a UPC object and
		 * store them in the @param codes array
		 */
		while (std::getline(file, cur_line) && lines < num_lines) {

			std::istringstream tokens(cur_line);
			std::getline(tokens, upc, ',');
			std::getline(tokens, data, ',');

			long long upc_code;

			/* Discard any UPC code which does not
			 * conform to the normal specification
			 * (12-digit number)
			 */
			try {
				upc_code = std::stoll(upc);
				UPC * cur_upc = new UPC(upc_code, data);
				UPCTree -> insert(*cur_upc);
				lines++;

			} catch (std::exception e) {
				std::cout << "Discarded malformed UPC: " << upc << " : "
									<< data << std::endl;
			}

		}
}

/*
 * Overrides the insertion operator to
 * add UPC fields to an outputstream for
 * the purposes of printing each UPC object
 */
std::ostream& operator<<(std::ostream& os, UPC& upc) {
  os << "UPC code: " << upc.getUPC()
		 << "\n" << upc.getData();
  return os;
}
