#########################################################################################
# Here you need to write some basic tests to make sure your Queue implementation runs correctly
# You can run them by running 'python QueueTests.py' from the command line
#########################################################################################

from Queue import Queue

queue = Queue()

print "Checking basic variable initializations..."

assert(queue.size() == 0)
assert(queue.is_empty() == True)

queue.print_queue()
print "done\n"

###################################

print "Checking is_empty and size..."

queue.addBack(8)
assert(queue.size() == 1)
assert(queue.is_empty() == False)

queue.addBack(6)
queue.addBack(7)

assert(queue.size() == 3)

queue.print_queue()
print "done\n"

###################################

print "Checking front, removeFront..."

assert(queue.front() == 8)
queue.removeFront()
assert(queue.size() == 2)

assert(queue.front() == 6)
queue.removeFront()
assert(queue.size() == 1)
assert(queue.is_empty() == False)

assert(queue.front() == 7)
queue.removeFront()
assert(queue.size() == 0)
assert(queue.is_empty() == True)

queue.print_queue()
print "done\n"

###################################

print "Checking back, addBack..."

queue.addBack(5)
assert(queue.back() == 5)
assert(queue.size() == 1)

queue.addBack(3)
assert(queue.back() == 3)

queue.addBack(0)
assert(queue.back() == 0)

queue.addBack(9)
assert(queue.back() == 9)

assert(queue.size() == 4)
assert(queue.is_empty() == False)

queue.print_queue()
print "done\n"

###################################

queue.print_queue()
print "All checks passed"