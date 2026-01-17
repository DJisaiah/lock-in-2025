def solution(nums):
    if not nums: return []
    size = len(nums)
    for i in range(size):
        min_index = i
        for j in range(i + 1, size):
            if nums[j] < nums[min_index]: min_index = j
        temp = nums[i]
        nums[i] = nums[min_index]
        nums[min_index] = temp
    return nums
# decided to use selection sort
