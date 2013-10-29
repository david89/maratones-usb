import random
import sys

def make_rounds(N) :
	for i in range(N) :
		D = random.randint(1, 2000)
		T = random.randint(1, 20)
		print D, T
		for j in range (D) :
			val = str(random.randint(1, 30))
			sys.stdout.write(val + " ")
		sys.stdout.write("\n")

Q = 98
print Q
for i in range(Q) :
      N = random.randint(1, 100)
      M = random.randint(1, 100)
      J = random.randint(1, 20)
      C = random.randint(1, 20)
      
      print N, M, J, C
      make_rounds(N)
      make_rounds(M)	

