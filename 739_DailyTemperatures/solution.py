#Overall approach:
# Using "day" as termonolgy for a temperature at an index
# Go through list once, remembering days we need to figure out in a sorted stack
# As we process new days, check if previous days can be solved

class Solution:
    # Define a class to store information about a day: it's index and temperature
    class day:
        def __init__(self, idx, temp):
            self.idx = idx
            self.temp = temp

    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        # Define list of previous days we haven't figured out yet, always to be sorted by temperature descending
        prev_days = []
        prev_days_len = 0

        # Process all days
        temp_len = len(temperatures)
        answer = [0] * temp_len

        for i in range(0, temp_len):
            # Go through previous days and as long as the current temp is greater, we have answers
            while prev_days_len > 0:
                if temperatures[i] > prev_days[0].temp:
                    answer[prev_days[0].idx] = (i - prev_days[0].idx)
                    prev_days.pop(0)
                    prev_days_len -= 1
                else:
                    break

            # Insert the current day into the previous days such that is sorted by temperature descending
            idx = 0
            while idx < prev_days_len:
                if( temperatures[i] > prev_days[idx].temp ):
                    idx += 1
                else:
                    break
            
            prev_days.insert(idx, self.day(i, temperatures[i]))
            prev_days_len += 1

        return answer