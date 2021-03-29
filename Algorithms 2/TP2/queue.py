from collections import deque

# making a simple queue
# this will be used in finding the best solution
class Queue(object):
    def __init__(self):
        self.queue = deque()

    def push(self, value):
        self.queue.appendleft(value)

    def pop(self):
        return self.queue.pop()

    def __len__(self):
        return len(self.queue)
