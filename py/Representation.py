from random import choice
from random import uniform
from random import shuffle
from copy import deepcopy
import time
import numpy as np
import random


class Representation:
    def __init__(self, representationLength,chanceOfMutation=0.05):
        if not 0<= chanceOfMutation <= 1:
            print("chancheOfMutation should be in the [0,1] range")
            exit(-1)
        self.Representation = [choice([ch for ch in range(representationLength-idx)]) for idx in range(representationLength)]
        self.RepresentationLength=representationLength
        
    def mutate(self,mRate):
        for idx in range (self.RepresentationLength):
            if uniform(0,1)< mRate :
                self.Representation[idx]= random.choice([ch for ch in range(self.RepresentationLength-idx)])
                
    def decode(self):
        result=[]
        el=[i for i in range(self.RepresentationLength)]
        for d in self.Representation:
            result=result+[el[d]]
            aux=el[:d]
            el=el[d+1:]+aux
        return result

    def cross (self,other):
        i=random.choice([idx for idx in range(len(self.Representation))])
        j=random.choice([idx for idx in range(i,len(self.Representation))])
        res=deepcopy(other)
        for cdx in range(len(self.Representation)):
            if(cdx<i):
                res.Representation[cdx]=self.Representation[cdx]
            elif(cdx<j):
                res.Representation[cdx]=other.Representation[cdx]
            else:
                res.Representation[cdx]=self.Representation[cdx]
            
        return res