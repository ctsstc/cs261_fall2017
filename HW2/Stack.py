from DynamicArray import DynamicArray

# The Stack Class
# Python has all kinds of powerful stuff that does what your Stack needs to do
# No, you CAN'T use any of that
# You need to use your Dynamic Array implementation instead
class Stack(object):

    # The __init__ function is run when you instantiate an instance of this object
    def __init__(self):
        self._size = 0
        self._dynamic_array = DynamicArray()

    #################################
    ## DO YOUR WORK BELOW THIS LINE #
    #################################

    # Return whether or not the stack is empty
    def is_empty(self):
        return self.size() == 0

    # Return the size on the stack
    def size(self):
        return self._size

    # look at the top of the stack (but don't remove)
    def top(self):
        return self._dynamic_array.get(self.size() - 1)

    # Push a value on to the top of the stack
    def push(self, value):
        self._dynamic_array.add(value)
        self._size += 1

    # take the top value off of the stack and return it to the user
    def pop(self):
        self._size -= 1
        return self._dynamic_array.remove(self.size())

    # DO NOT MODIFY THIS PRINT
    def print_stack(self):
        print '====\n' + '\n----\n'.join([str(v) for v in self._dynamic_array._data[:self._size]]) + '\n^^^^'
