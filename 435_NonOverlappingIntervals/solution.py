#Overall Approach:
# This is essentially a meeting problem where have one room and want to schedule the maximum number of meetings. So we can sort by end time and then keep those that are not in conflict

class Solution:
    def eraseOverlapIntervals(self, intervals: List[List[int]]) -> int:
        # Sort by end
        def sort_by_end(list: List[int]):
            return list[1]

        intervals.sort(key=sort_by_end)

        # Determine how many to keep by those which end after the previous
        intervals_len = len(intervals)
        keep_idx = 0
        keep_cnt = 1

        for i in range(1, intervals_len):
            if intervals[i][0] >= intervals[keep_idx][1]:
                keep_cnt += 1
                keep_idx = i

        # Amount to remove is the length minus the count we want to keep
        return intervals_len - keep_cnt
