#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "string_label.h"
#include "node.h"
#include "bracket_notation_parser.h"

/// Convert vector of int values to is string representation.
///
/// TODO: Move this method to some util.
///
/// \param v Vector of int values.
/// \return String representation of v.
const std::string vector_to_string(const std::vector<std::string>& v) {
  std::string s("{");
  for (auto e : v) {
    s += e + ",";
  }
  s.pop_back(); // Delete the last coma.s
  s += "}";
  return s;
}

int main() {

  using Label = label::StringLabel;

  // Parse test cases from file.
  // TODO: Do something that we don't have to give a relative path to the input file.
  std::ifstream test_cases_file("../../../test/parser/labels_test_data.txt");
  for (std::string line; std::getline( test_cases_file, line);) {
    if (line[0] == '#') {
      std::getline(test_cases_file, line);
      std::string input_tree = line;
      std::getline(test_cases_file, line);
      std::string correct_result = line;

      // Parse test tree.
      parser::BracketNotationParser bnp;
      node::Node<Label> t1 = bnp.parse_string(input_tree);

      std::string computed_results = vector_to_string(t1.get_all_labels());

      if (correct_result != computed_results) {
        // TODO: Print test case input.
        std::cerr << "Incorrect labels: " << computed_results << " instead of " << correct_result << std::endl;
        return -1;
      }
    }
  }

  return 0;
}
