#include <iostream>
#include <vector>
using namespace std;

int missingNumber(const vector<int>& nums) {
    int n = nums.size();
    int expectedSum = n * (n + 1) / 2;
    int actualSum = 0;

    for (int num : nums) {
        actualSum += num;
    }

    return expectedSum - actualSum; 
}

int main() {
    setlocale( LC_ALL, "Rus");
    vector<int> nums = { 3, 0, 1, 4,5,6 }; 
    cout << "Пропущенное число: " << missingNumber(nums) << endl;  
    return 0;
}
