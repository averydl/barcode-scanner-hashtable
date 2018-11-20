#include "UPC.h"
#include "SearchArray.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

// Author: Derek Avery
// Version: 1
// Date: 11/16/2018

void load_data(std::string&, int, SearchArray<UPC>&);
bool running = true;
/*
 * This main method will read the contents of a comma-delimited
 * file where each line contains a UPC code (12-digits) and an
 * item description, separated by a comma. Each line is tokenized
 * and then used to create a new UPC object, which is then stored
 * in an array (vector) for later search operations
 */
int main(int argc, char* argv[]) {
	SearchArray<UPC>* codes = new SearchArray<UPC>();
	std::string file_name;

	// use command line argument for file name; if
	// none is provided, use the default 'upc_corpus.txt' name
	if(argc > 1)
		file_name = argv[1];
	else
		file_name = "upc_corpus.txt";
	load_data(file_name, 2000000000, *codes);

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
				result = new UPC(codes->search(*upc));
				std::cout << "UPC Code: " << upc_code << "\n"
									<< result->getData() << "\n";

			} catch(std::exception e) {
				std::cout << "INVALID INPUT\n";
			}
		}
	}

}

/*
 * This function loads data from the @param file_name text file
 * into the SearchArray line by line, discarding any UPC's in
 * the file which are not 12 digits long
 */
void load_data(std::string& file_name, int num_lines, SearchArray<UPC>& array) {

		std::string cur_line, cur_token, upc, data;	// strings to hold linewise data as file is read
		std::ifstream file;	// input file stream to read file data
		int lines = 0;	// number of lines that have been loaded

		file.open(file_name);

		/*
		 * read each line of the file and convert the
		 * upc/data from each line to a UPC object and
		 * store them in the @param upc_codes SearchArray
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
				array.add(*cur_upc);
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
