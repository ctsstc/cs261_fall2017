#########################################################################################
# Here are some basic tests to make sure your Bag implementation runs correctly
# You can run them by running 'python BagTests.py' from the command line
#########################################################################################

from Bag import *

bag = Bag()

print "Checking basic variable initializations..."

# TODO: check that your inits are ok

bag.print_bag()
print "done\n"

###################################

print "Checking add, contains, functions..."

#TODO: check that your add and contains operate as expected

bag.print_bag()
print "done\n"

###################################

print "Checking remove, function(s)..."

#TODO: check that your remove operates as expected

bag.print_bag()
print "done\n"

###################################

print "Checking that all of the above didn't break things"

#TODO: check that everything works and that the order in which you call your 
# functions doesn't break things

bag.print_bag()
print "All checks passed"