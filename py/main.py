from Evaluator import *
from Representation import *
import numpy as np
from copy import deepcopy
import random
import pandas as pd

from multiprocessing import Pool
from Population import *
from string import *
from scipy.spatial import distance

def evolve(pop,maxGen):
    
    meanResults=[]
    bestResults=[]

    nGenerations=maxGen+1
    start=time.time()
    for generation in range(nGenerations):
        pop.select()
        pop.mutate()
        if(random.uniform(0,1)<pop.cRate):
            pop.crossover()
        if(generation%200==0):
            #print(str(generation)+' '+str(pop.meanFit())+' '+str(pop.bestFit()))
            meanResults=meanResults+[pop.meanFit()]
            bestResults=bestResults+[pop.bestFit()]
    stop=time.time()
    return[meanResults,bestResults,stop-start]

def getData(pop,maxGen):
    res=[]
    with Pool(15) as p:
        res=p.starmap(evolve,[[deepcopy(pop),maxGen] for _ in range(15)])
    return(res)     
    
def toCsv(pop,iName,maxGen):
    data=getData(pop,maxGen)
    print("Got Data")
    mean=[aux[0] for aux in data]
    best=[aux[1] for aux in data]
    time=[aux[2] for aux in data]
    with open(iName+"mean","w") as f:
        f.write(str(mean))
    with open(iName+"best","w") as f:
        f.write(str(best))
        
    df=pd.DataFrame({'Generations':[i for i in range(len(mean[0]))], 'mean result': np.mean(mean,axis=0),'best result':np.mean(best,axis=0)})
    pd.DataFrame({'Instance':iName, 'Mean': np.mean(best,axis=0)[-1],'Min':np.min(best,axis=0)[-1],'Max':np.max(best,axis=0)[-1],'Std':np.std(best,axis=0)[-1],'Time': np.mean(time)},index=[0],columns=['Instance','Mean','Min','Max','Std','Time']).to_csv(iName+'.csv')

    """
    print(df['Generations'])
    print(df['mean result'])
    plt.plot( 'Generations', 'mean result', data=df,  color='blue', linewidth=2)
    plt.plot( 'Generations', 'best result', data=df,  color='red', linewidth=2)

    plt.xlabel('Generation')
    
    plt.ylabel("Evaluation")
    print('test1')

    plt.title(iName)

    plt.legend()
    
    print('test1')

    nDim=len(pop.constraits)
    plt.savefig(iName+'.png')
    plt.clf()
    """    

def EucDistance(x,y):
    return distance.euclidean(x,y)

def ReadGraph(path):
    points=[]
    with open(path,"r") as f:
        for line in f.readlines():
            x,y=line.strip().split()
            x=float(x)
            y=float(y)
            points=points+[[x,y]]

    return points

path="input.txt"
graph=ReadGraph(path)

print("Graf read")
evaluator=Evaluator(graph,EucDistance)

pop=Population(evaluator,pMax=20,mRate=0.05 ,cRate=0.01,ePercent=0.1)

toCsv(pop,"a4",maxGen=10000)