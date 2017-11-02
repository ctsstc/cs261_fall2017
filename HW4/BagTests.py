#########################################################################################
# Here are some basic tests to make sure your Bag implementation runs correctly
# You can run them by running 'python BagTests.py' from the command line
#########################################################################################

# Creativity borrowed from BstTests.py

from Bag import *

bag = Bag()

print "Checking basic variable initializations..."

assert bag.size() == 0
assert bag.is_empty() == 1

bag.print_bag()
print "done\n"

###################################

print "Checking add, contains, functions..."

bag.add(100)
assert bag.size() == 1
assert bag.is_empty() == 0
assert bag.contains(100)

bag.add(50)
bag.add(40)
bag.add(60)

bag.add(150)
bag.add(160)
bag.add(140)
assert bag.contains(140)
bag.add(140)
assert bag.contains(140)
assert bag.size() == 7

bag.print_bag()
print "done\n"

###################################

print "Checking remove, function(s)..."

bag.remove(50)
bag.remove(150)
assert bag.size() == 5

assert bag.contains(150) == False
assert bag.contains(50) == False
assert bag.contains(40)
assert bag.contains(140)

bag.print_bag()
print "done\n"

###################################

print "Checking that all of the above didn't break things"

bag.add(120)
bag.add(130)
bag.add(150)

assert bag.size() == 8

assert bag.contains(120)
assert bag.contains(130)
assert bag.contains(150)

bag.print_bag()
print "All checks passed"