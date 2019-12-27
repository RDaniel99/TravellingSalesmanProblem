from Representation import *

class Evaluator:
    def __init__(self,graph):
        self.Graph=graph

    def eval(self,decodedRepresentation):
        evaluation=0
        for i in range(len(decodedRepresentation)-1):
            evaluation=evaluation+self.Graph[decodedRepresentation[i]][decodedRepresentation[i+1]]
        return evaluation