#include <string>
#include <limits>
#include <cmath>
#include "matrix.h"

namespace common {

/// Convert vector of values to its string representation.
/**
 * \param v Vector of values.
 * \return String representation of v.
 */
template <typename T>
const std::string vector_to_string(const std::vector<T>& v) {
  std::string s("{");
  for (auto e : v) {
    s += std::to_string(e) + ",";
  }
  s.pop_back();
  s += "}";
  return s;
};

/// Convert vector of double values to its string representation.
/**
 * Specialized vector_to_string.
 * \param v Vector of values.
 * \return String representation of v.
 */
const std::string vector_to_string(const std::vector<double>& v) {
  char int_part[2];
  // printf ("[%s] is a string %d chars long\n",buffer,n);
  std::string s("{");
  for (auto e : v) {
    sprintf(int_part, "%.0f", e);
    s += std::string(int_part) + ",";
  }
  s.pop_back();
  s += "}";
  return s;
};

/// Convert vector of vectors of values to its string representation.
/**
 * Specialized vector_to_string.
 * \param vv Vector of vectors of values.
 * \return String representation of vv.
 */
template <typename T>
const std::string vector_to_string(const std::vector<std::vector<T>>& vv) {
  std::string s("{");
  for (auto v : vv) {
    s += "{";
    for (auto e : v) {
      s += std::to_string(e) + ",";
    }
    if (v.size() > 0) {
      s.pop_back();
    }
    s += "},";
  }
  s.pop_back();
  s += "}";
  return s;
};

/// Convert a matrix of double values to its string representation.
/**
 * \param m Matrix of double values.
 * \return String representation of m.
 */
const std::string matrix_to_string(const data_structures::Matrix<double>& m) {
  std::string s("");
  for (unsigned int x = 0; x < m.get_rows(); ++x){
    for (unsigned int y = 0; y < m.get_columns(); ++y){
      double e = m.read_at(x, y);
      if (e == std::numeric_limits<double>::infinity()) {
        s += "@";
      } else {
        std::string e_string = std::to_string(e);
        std::string e_string_int = e_string.substr(0, e_string.find("."));
        s += e_string_int;
      }
    }
    s += "\n";
  }
  s.pop_back();
  return s;
};

/// Convert a matrix of double values to its string representation.
/**
 * \param m Matrix of double values.
 * \return String representation of m.
 */
const std::string format_matrix_to_string(const data_structures::Matrix<double>& m) {
  std::string s("");
  for (unsigned int x = 0; x < m.get_rows(); ++x){
    for (unsigned int y = 0; y < m.get_columns(); ++y){
      double e = m.read_at(x, y);
      if (e == std::numeric_limits<double>::infinity()) {
        s += "  @";
      } else if (std::isnan(e)) {
        s += "  -";
      } else {
        std::string e_string = std::to_string(e);
        std::string e_string_int = e_string.substr(0, e_string.find("."));
        if (e_string_int.length() == 1) {
          s += "  " + e_string_int;
        }
        else if (e_string_int.length() == 2) {
          s += " " + e_string_int;
        } else {
          s += e_string_int;
        }
      }
    }
    s += "\n";
  }
  s.pop_back();
  return s;
};

}
