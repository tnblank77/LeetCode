#Overall approach:
# We only need to keep track of requets in the last 3000ms, so just keep a list of these
# When a new ping happens, pop the old ones, add the new ones, and the list size will be the result

class RecentCounter:
    requests = []

    def __init__(self):
        self.requests = []

    def ping(self, t: int) -> int:
        # Remove requests older than 3000ms
        requests_len = len(self.requests)

        while(requests_len > 0):
            if self.requests[0] < (t - 3000):
                self.requests.pop(0)
                requests_len -= 1
            else:
                break
        
        # Add new request
        self.requests.append(t)

        # Return the number of requests
        return(len(self.requests))


# Your RecentCounter object will be instantiated and called as such:
# obj = RecentCounter()
# param_1 = obj.ping(t)