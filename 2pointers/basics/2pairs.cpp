#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#define ASSERT(left,operator,right) { if(!((left) operator (right))) {\
    std::cerr << "ASSERT FAILED at line " << __LINE__ \
        << ", " << #left << " " << #operator << " " <<  #right << "\n"\
        << "LHS" << " = " << (left) << "; " << "RHS" << " = " << (right) << "\n"; }\
}

using namespace std;

unordered_set<string> pair_indices;

int get_pairs_2 (const int expected_sum, const vector<int> &arr) {
    // TC: O(N), SC: O(1)
    // Get the number of pairs that sum upto a particular number.
    // Repetitive pairs are possible.
    int i = 0;
    int j = arr.size() - 1;
    int sum;
    int pairs = 0;

    while (i < j) {
        sum = arr[i] + arr[j];
        if (sum > expected_sum) {
            j--;
        } else if (sum < expected_sum) {
            i++;
        } else {
            // Account for multiple occurences of the element.
            if (arr[i] == arr[j]) return pairs+j-i+1;

            int count_i = 1, count_j = 1;
            while (i+1 < j) {
                if (arr[i] == arr[i+1]) {
                    count_i++;
                    i++;
                } else if (arr[j] == arr[j-1]) {
                    count_j++;
                    j--;
                }
            }
            pairs += count_i* count_j;
            i++;
            j--;
        }
    }
    return pairs;
}

int get_pairs (const int expected_sum, const vector<int> &elements, int i=-1, int j=-1) {
    // TC: O(N), SC: O(N)
    // Get the number of pairs that sum upto a particular number.
    // Repetitive pairs are possible.
    if (i == -1) {
        i = 0;
        j = elements.size() - 1;
    }
    int sum;
    int pairs = 0;

    while (i < j) {
        sum = elements[i] + elements[j];
        if (sum > expected_sum) {
            j--;
        } else if (sum < expected_sum) {
            i++;
        } else {
            // While branching, its possible that we process the same indices
            // multiple times. Hence we add a hashing mechanism.
            string key = to_string(i) + "," + to_string(j);
            if (pair_indices.find(key) != pair_indices.end()) break;
            pair_indices.insert(key);
            pairs++;
            // create 2 branches, i++ and j-- and merge results
            pairs += get_pairs(expected_sum, elements, i+1, j)
                     + get_pairs(expected_sum, elements, i, j-1);
            break;
        }
    }
    return pairs;
}

int main() {
    int result = get_pairs(11, {1, 4, 4, 5, 5, 5, 6, 6, 11});
    ASSERT(result, ==, 6);

    result = get_pairs_2(11, {1, 4, 4, 5, 5, 5, 6, 6, 11});
    ASSERT(result, ==, 6);
}