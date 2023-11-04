#include <vector>
#include <iostream>
using namespace std;
int quickselect(vector<int> &nums, int begin, int end, int k)
{
    if (begin == end)
        return nums[k];
    int pivot = nums[begin];
    bool pit_on_left = true;
    int left = begin, right = end;
    while (left < right)
    {
        while (nums[left] < pivot)
            left++;
        while (nums[right] > pivot)
            right--;
        if (left < right)
        {
            swap(nums[left], nums[right]);
            pit_on_left = !pit_on_left;
            if (pit_on_left)
                right--;
            else
                left++;
        }
    }
    if (k == left)
        return nums[left];
    else if (left > k)
        return quickselect(nums, begin, left - 1, k);
    else
        return quickselect(nums, left, end, k);
}
int findKthLargest(vector<int> &nums, int k)
{
    return quickselect(nums, 0, nums.size() - 1, nums.size() - k);
}

void main()
{
    vector<int> tmp{1,2,3,0,4,5};
    findKthLargest(tmp, 3);
    for(auto ele:tmp)
    {
        cout<< ele <<",";
    }
}