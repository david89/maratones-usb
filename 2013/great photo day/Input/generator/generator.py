#This will only generate the huge test cases
import random

limit = 100
for t in xrange(100):
    print limit,limit
    for i in xrange(limit):
        bound = 100+random.randrange(901)
        print " ".join([str(random.randrange(bound)) for j in xrange(limit)])
print 0,0
