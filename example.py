# line 2 to line 44 are for importing the neural net library using ctypes
from ctypes import cdll

lib = cdll.LoadLibrary('libnet.so')

class neural_net(object):
    certainty = 0
    outl = lib.list_new()
    out = 0

    def __init__(self, collumns, rows, outputs, inputs):
        self.obj = lib.net_new(collumns, rows, outputs, inputs)
    
    def __del__(self):
        lib.net_delete(self)
    
    def calc_out(self, input):
        return lib.net_calc_out(self, input)
    
    def calc_cost(self, wanted):
        return lib.net_calc_cost(self, wanted)
    
    def improve(self, wanted, learning_rate):
        lib.net_improve(self, wanted, learning_rate)
    
    def update(self):
        self.certainty = lib.net_certainty(self)
        self.out = lib.net_out(self)
        self.outl = lib.net_outl(self)

def list2clist(list):
    clist = lib.list_new()
    index = 0
    for element in list:
        lib.changeIndex(clist, index, element)
        index += 1
    return clist

def clist2list(clist):
    list = []
    for index in range(lib.length(clist)):
        list.append(lib.index(clist, index))
    return list

# defining both the python and the c/cpp input and wanted output lists
input = []
wanted = []
cinput = lib.list_new()
cwanted = lib.list_new()

# defines the test cases with known input and output values, here the net should return {1,0} if the input is -1 and it should return {0,1}
def testcases(case):
    input.clear()
    wanted.clear()
    if (case == 0):
        input.extend([-1])
        wanted.extend([1, 0])
    elif (case == 1):
        input.extend([1])
        wanted.extend([0, 1])


# defines a new neural net
neurnet0 = neural_net(1, 1, 2, 1) # The first number is the number of collumns of neurons in the net, excluding input and output neurons. The second number is the number of rows of neurons in the net, excluding input and output neurons. The third number is the number of input neurons and the last number is the number of output neurons.

# defines the testcase and converts the lists to the clists which the net can use
testcases(0)
cinput = list2clist(input)
cwanted = list2clist(wanted)

# prints the output of the net (the index of the highest output neuron activation), so if the output list is [0.035, 0.894] then the output is 1 since that's the index of the highest number
print(f"output: {neurnet0.calc_out(cinput)}")

# The calc_out method also stores the output list in neurnet0.outl and the certainty in neurnet0.certainty. To view them, first run the neurnet0.update function
neurnet0.update()
print(f"certainty: {neurnet0.certainty} %")
outl = clist2list(neurnet0.outl) # converts the clist to a normal python list
print("output list:")
print(outl)

# calculates how bad the net is doing, the higher the output, the worse the net is doing (this only works when the calc_out has already been run)
print(f"cost before: {neurnet0.calc_cost(cwanted)}")

# to improve the net's performance and have it give us the correct output, we use the improve() method (this only works when the calc_out has already been run)
neurnet0.improve(cwanted, 1) # the last number is the learning rate, the longer you train the net the lower it should become, this allows the net to progressively refine details

neurnet0.calc_out(cinput) # to see what the new outputs are, the calc_out method has to be run again
print(f"cost after (should be lower): {neurnet0.calc_cost}")

# example for training the neural net
# learningrate = 1
# for i in range(0, 100):
#     # oscillates between the testcases
#     testcases(i % 2)
#     cinput = list2clist(input)
#     cwanted = list2clist(wanted)

#     neurnet0.calc_out(cinput)
#     neurnet0.improve(cwanted, learningrate)
#     learningrate -= .1 # reducing the learning rate

# after training we can input other inputs than just the testcase inputs

del neurnet0
lib.remove(cinput) # deleting the pointers to prevent memory leaks (the function is called remove to prevent conflicts)
lib.remove(cwanted)
