import csv
import numpy as np
from numpy.linalg import matrix_power


Jack = np.loadtxt(open("matrix.csv"), delimiter=";")


JFriends = matrix_power(Jack,2)
PFriends = matrix_power(Policemen,2)


JIso = np.empty((195,195))
JNeighbors = np.empty((195,1))
                       
def printPairs(n):
    if n == 195:
        for i in range(0,195):
            JNeighbors[i]  <-  np.sum(Jack[i])
        for i in range(0,195):
            for j in range(0,195):
                r=0
                if JFriends[i][j] != 0:
                    if Jack[i][j] == 1:
                        for k in range(0,195):
                            if k != i:
                                if k!= j:
                                    if str(Jack[i][k]) == str(Jack[j][k]):
                                        r=r+1
                        if r==193:
                            JIso[i][j] = 1
                        else:
                            JIso[i][j] = 0
                                
                if JFriends[i][j] == 0:
                    JIso[i][j]=0
                if i < j:
                    if JIso[i][j]==1:
                        s1 = " and "
                        s2 = " are isomorphic!"
                        print(str(i+1)+ s1 + str(j+1)+s2)

 

