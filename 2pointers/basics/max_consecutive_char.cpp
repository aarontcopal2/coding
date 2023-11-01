#include <algorithm>
#include <iostream>
#include <vector>

#define ASSERT(left,operator,right) { if(!((left) operator (right))) {\
    std::cerr << "ASSERT FAILED at line " << __LINE__ \
        << ", " << #left << " " << #operator << " " <<  #right << "\n"\
        << "LHS" << " = " << (left) << "; " << "RHS" << " = " << (right) << "\n"; }\
}

using namespace std;

int count_consecutive_ones (const vector<int> &sequence) {
    int max_consec = INT_MIN, count = 0;
    for (int j=0; j<sequence.size(); j++) {   
        if (sequence[j] == 1) {
            count++;
        } else {
            max_consec = max(max_consec, count);
            count = 0;
        }
    }
    max_consec = max(max_consec, count);
    return max_consec;
}

int max_consecutive_chars_1 (vector<int> sequence, int flips, int i=0) {
    // This is a brute_force approach.
    // TC: O(2^n), SC: O(n*2^n)

    if (flips == 0) {
        return count_consecutive_ones(sequence);
    }

    vector<int> new_sequence;
    int branch_max = INT_MIN;
    for (int j=i; j<sequence.size(); j++) {
        
        if (sequence[j] == 0) {
            new_sequence = sequence;
            new_sequence[j] = 1;
            branch_max = max(branch_max, max_consecutive_chars_1 (new_sequence, flips-1, j+1));
        }
    }

    int curr_max = count_consecutive_ones(sequence);
    return max(curr_max, branch_max);
}

int max_consecutive_chars_2 (vector<int> sequence, int flips) {
    // This is a sliding window approach.
    if (flips == 0) {
        return count_consecutive_ones(sequence);
    }

    vector<int> zero_indices;
    zero_indices.push_back(-1);
    for (int i=0; i<sequence.size(); i++) {
        if (sequence[i] == 0) {
            zero_indices.push_back(i);
        }
    }
    zero_indices.push_back((int)sequence.size());

    int count;
    int curr_max = INT_MIN;
    int j = 0;
    for (int i=1; i<zero_indices.size(), j<zero_indices.size()-2; i++) {
        j = min(i+flips-1, (int) zero_indices.size()-2);
        count = zero_indices[j+1] - zero_indices[i-1] - 1;
        curr_max = max(count, curr_max);
    }

    return curr_max;
}


int main() {
    int result = max_consecutive_chars_2({1,1,1,0,0,0,1,1,1,1,0}, 2);
    ASSERT(result, ==, 6);

    result = max_consecutive_chars_2({0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1}, 3);
    ASSERT(result, ==, 10);
}