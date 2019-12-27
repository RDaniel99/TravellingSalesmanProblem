from Representation import *

class Evaluator:
    def __init__(self,graph,distFunction):
        self.Graph=graph
        self.Distance=distFunction

    def eval(self,decodedRepresentation):
        evaluation=0
        for i in range(len(decodedRepresentation)-1):
            evaluation=evaluation+self.Distance(self.Graph[decodedRepresentation[i]],self.Graph[decodedRepresentation[i+1]])
        return evaluation