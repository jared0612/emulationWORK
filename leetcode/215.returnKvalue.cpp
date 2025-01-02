#include <iostream>
#include <vector>
#include <queue>
#include <functional>

class Solution {
public:
    // Function to find the kth largest element using a priority queue (min-heap approach)
    int findKthLargest(std::vector<int>& nums, int k) {
        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

        // Push elements into the priority queue
        for (int e : nums) {
            pq.push(e);

            // If the size of the queue exceeds k, pop the smallest element (min-heap)
            if (pq.size() > k) {
                pq.pop();
            }
        }

        // The top element is the kth largest element
        return pq.top();
    }

    // Function to partition the array for quickselect algorithm (quickselect is partition-based)
    int quickselect(std::vector<int>& nums, int low, int high, int k) {
        int pivot = partition(nums, low, high);

        // k is the pivot index, return the element at pivot
        if (pivot == k) {
            return nums[pivot];
        }
        // Recursively find the kth element
        else if (pivot < k) {
            return quickselect(nums, pivot + 1, high, k);
        } else {
            return quickselect(nums, low, pivot - 1, k);
        }
    }

private:
    // Partition function used for quickselect
    int partition(std::vector<int>& nums, int low, int high) {
        int pivot = nums[high];
        int i = low - 1;

        // Rearrange the elements
        for (int j = low; j < high; j++) {
            if (nums[j] <= pivot) {
                i++;
                std::swap(nums[i], nums[j]);
            }
        }
        std::swap(nums[i + 1], nums[high]);
        return i + 1;
    }
};

int main() {
    Solution solution;

    // Test case 1
    std::vector<int> nums1 = {3, 2, 1, 5, 6, 4};
    int k1 = 2;
    std::cout << "The " << k1 << "th largest element is: " 
              << solution.findKthLargest(nums1, k1) << std::endl;

    // Test case 2: Using quickselect to find the kth largest element
    std::vector<int> nums2 = {3, 2, 1, 5, 6, 4};
    int k2 = 2;
    int k2_index = nums2.size() - k2;  // Convert kth largest to index
    std::cout << "The " << k2 << "th largest element using quickselect is: " 
              << solution.quickselect(nums2, 0, nums2.size() - 1, k2_index) << std::endl;

    return 0;
}
