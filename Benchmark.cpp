#include "BST.h"
#include "SearchArray.h"
#include <time.h>

SearchArray<UPC>* full_list = new SearchArray<UPC>();
SearchArray<UPC>* array = new SearchArray<UPC>();
BST<UPC>* bst = new BST<UPC>();
void load_data(std::string&);
void load_partial(std::string&, int, int);


int main() {
  std::string file_name = "upc_corpus.txt";
  std::clock_t avg_array;
  std::clock_t avg_bst;

  std::clock_t array_time;
  std::clock_t bst_time;

  load_data(file_name);
  int prev = 0; //number of elements previously in the list
  std::ofstream file;
  file.open("benchmark.txt");

  /*
   * Incrementally add items to both the array and BST
   * data structures 1000 items at a time, and each time
   * perform a search for a random item in each data structure,
   * and store the benchmark results (i.e. time taken using each
   * type of data structure) in a new .txt file
   */
  for(int i = 0; i < full_list -> getCount(); i += 1000) {
    // load UPC's into array/BST up to the i'th line
    load_partial(file_name, i-prev, prev);

    // reset average array/bst clock times
    avg_array = 0;
    avg_bst = 0;

    // perform timing test for each of Array and BST 10 times and
    // store the average results in the "benchmark.txt" file
    for(int j = 0; j < 10; j++) {
      // store randomly-selected UPC from the master list
      UPC* upc = new UPC(full_list->get(rand() % (i+1)));

      // execute array search test
      array_time = clock();
      try {
        array->search(*upc);
      } catch (std::exception e) {
        std::cout << "not found\n";
      }
      array_time = clock() - array_time;
      avg_array += array_time;

      // execute BST search test
      bst_time = clock();
      try {
        bst->search(*upc);
      } catch (std::exception e) {
        std::cout << "not found\n";
      }
      bst_time = clock() - bst_time;
      avg_bst += bst_time;
    }
    file << i << "," << avg_array/10 << "," << avg_bst/10 << "," << "\n";
    prev = i;

  }

}

void load_data(std::string& file_name) {

		std::string cur_line, cur_token, upc, data;	// strings to hold linewise data as file is read
		std::ifstream file;	// input file stream to read file data
		int lines = 0;	// number of lines that have been loaded

		file.open(file_name);

		/*
		 * read each line of the file and convert the
		 * upc/data from each line to a UPC object and
		 * store them in the @param upc_codes SearchArray
		 */
		while (std::getline(file, cur_line)) {

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
        full_list -> add(*cur_upc);

			} catch (std::exception e) {
				std::cout << "Discarded malformed UPC: " << upc << " : "
									<< data << std::endl;
			}

		}
}

void load_partial(std::string& file_name, int num_lines, int start_index) {
		/*
		 * read each line of the file and convert the
		 * upc/data from each line to a UPC object and
		 * store them in the @param upc_codes SearchArray
		 */
		for(int i = 0; i < num_lines; i++) {
      UPC* upc = new UPC(full_list->get(start_index+i));
      array -> add(*upc);
      bst -> insert(*upc);
		}
}
