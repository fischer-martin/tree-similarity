// The MIT License (MIT)
// Copyright (c) 2017 Mateusz Pawlik.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

/// \file join/naive_join_impl.h
///
/// \details
/// Contains the implementation of a naive tree similarity join.

#ifndef TREE_SIMILARITY_JOIN_NAIVE_JOIN_IMPL_H
#define TREE_SIMILARITY_JOIN_NAIVE_JOIN_IMPL_H

template <typename Label, typename CostModel, typename VerificationAlgorithm>
NaiveJoin<Label, CostModel, VerificationAlgorithm>::NaiveJoin() {}

template <typename Label, typename CostModel, typename VerificationAlgorithm>
std::vector<join::JoinResultElement> NaiveJoin<Label, CostModel, VerificationAlgorithm>::execute_join(
    std::vector<node::Node<Label>>& trees_collection, 
    const double distance_threshold) {

  std::vector<join::JoinResultElement> result_set;

  VerificationAlgorithm ted_algorithm;

  double ted_value = std::numeric_limits<double>::infinity();
  int i = 0;
  int j = 0;
  for (auto it_i = trees_collection.begin(); it_i != trees_collection.end(); ++it_i) {
    ++i;
    j = i;
    // Start the inner loop with the tree just iafter it_i.
    for (auto it_j = it_i+1; it_j != trees_collection.end(); ++it_j) {
      ++j;
      ted_value = ted_algorithm.verify(*it_i, *it_j, distance_threshold);
      if (ted_value != std::numeric_limits<double>::infinity()) {
        result_set.emplace_back(i, j, ted_value);
      }

      // Sum up all number of subproblems
      sum_subproblem_counter_ += ted_algorithm.get_subproblem_count();
    }
  }

  return result_set;
}

template <typename Label, typename CostModel, typename VerificationAlgorithm>
const unsigned long long int NaiveJoin<Label, CostModel, VerificationAlgorithm>::get_subproblem_count() const {
  return sum_subproblem_counter_;
}


#endif // TREE_SIMILARITY_JOIN_NAIVE_JOIN_IMPL_H
