#########################################################################################
# Here you need to write some basic tests to make sure your Stack implementation runs correctly
# You can run them by running 'python StackTests.py' from the command line
#########################################################################################

from Stack import Stack

stack = Stack()

print "Checking basic variable initializations..."

assert stack.size() == stack._size

stack.print_stack()
print "done\n"

###################################

print "Checking is_empty and size..."

assert stack.is_empty() == True

stack.push("cat")
assert stack.is_empty() == False
assert stack.size() == 1

stack.push("doge")
assert stack.is_empty() == False
assert stack.size() == 2

stack.pop()
assert stack.is_empty() == False
assert stack.size() == 1

stack.pop()
assert stack.is_empty() == True
assert stack.size() == 0

stack.print_stack()
stack._dynamic_array.print_data()
print "done\n"

###################################

print "Checking push, top..."

stack.push("otter")
assert stack.top() == "otter"

stack.push("water ferret")
assert stack.top() == "water ferret"

stack.print_stack()
print "done\n"

###################################

print "Checking pop..."

first = stack.pop()
assert first == "water ferret"

assert stack.pop() == "otter"

stack.print_stack()
print "done\n"

###################################

stack.print_stack()
print "All checks passed"