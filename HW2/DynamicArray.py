# The Dynamic Array Class
# Python has all kinds of powerful stuff that does what your dynamic array needs to do
# No, you CAN'T use any of that
class DynamicArray(object):

    INIT_CAPACITY = 2^4
    RESIZE_MULTIPLIER = 2

    # The __init__ function is run when you instantiate an instance of this object
    def __init__(self):

        # variables beginning with the underscore can denote internal or self referential data
        # That isn't strictly enforced, but merely a nice convention for readability
        self._size = 0
        self._capacity = DynamicArray.INIT_CAPACITY
        self._data = [None] * self._capacity

    #################################
    ## DO YOUR WORK BELOW THIS LINE #
    #################################

    # Return the size of the dynamic array
    def size(self):
        return self._size

    # Return the capacity of the dynamic array
    def capacity(self):
        return self._capacity


    # Add an element to the end of the dynamic array
    def add(self, value):
        if (self._size >= self._capacity):
            self._resize()
        self.put(self._size, value)
        self._size += 1


    # Get the value at the position passed in as a parameter
    def get(self, pos):
        return self._data[pos]

    # Put a value into the dynamic array at the specified position, overwriting what was there
    def put(self, pos, value):
        self._data[pos] = value

    # Swap 2 specified values in the dynamic array
    def swap(self, pos1, pos2):
        hold1 = self.get(pos1)
        hold2 = self.get(pos2)
        self.put(pos1, hold2)
        self.put(pos2, hold1)

    # Returns a slice from the start of the array to the given amount
    # Guess these are No-Nos
    # DEPRECATED
    def left(self, amount):
        return self._data[:amount]

    # Returns a slice starting from the startPos to the end of the array
    # Guess these are No-Nos
    # DEPRECATED
    def right(self, startPos):
        return self._data[startPos:]

    # Remove a value from the dynamic array (and return it)
    def remove(self, pos):
        goodbye = self.get(pos)
        # Shift Values Left
        while self._data[pos] != None and pos < self._size - 1:
            self._data[pos] = self._data[pos + 1]
            pos += 1
        # None'atize the last value
        self.put(pos, None)
        self._size -= 1
        return goodbye
        # Can't use this RIP, I would hope this is a single operation O(3) and faster than 1x1 shifting O(n)
        # Take the left and shift the right over one then add a new None at the end
        # left = self.left(pos - 1)
        # right = self.right(pos)
        # self._data = left + right + [None]

    # Resize the underlying array to make room
    def _resize(self):
        new_size = self._capacity * DynamicArray.RESIZE_MULTIPLIER
        additional_size = new_size - self._capacity
        self._capacity = new_size
        self._data += ([None] * additional_size)

    # DO NOT MODIFY THIS PRINT
    # Print the data in a useful way
    def print_data(self):
        print "[ %s ]" % ' | '.join([str(v) for v in self._data])
