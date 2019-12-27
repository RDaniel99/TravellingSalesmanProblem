from Representation import *
from Evaluator import *
class Population:
    def __init__(self,evaluator  ,pMax=100,mRate=0.05,cRate=0.01,ePercent=0.1):
        self.Evaluator=evaluator
        self.ElitismPercentage=ePercent*100
        self.PopMax=pMax
        self.Members=[ Representation(len(evaluator.Graph)) for _ in range(self.PopMax) ]
        self.mRate=mRate
        self.cRate=cRate


    def sortPop(self):
        val=[self.Evaluator.eval(b.decode()) for b in self.Members]
        for i in range(len(val)):
            for j in range(i,len(val)):
                if(val[i]>val[j]):
                    val[i],val[j]=val[j],val[i]
                    self.Members[i],self.Members[j]=self.Members[j],self.Members[i]

    def getFortuneWheelResults(self,n):
        toAdd=[]
        eval=[]
        p=[]
        nElements=len(self.Members)
        q=[0 for _ in range(nElements)]
        sum=0

        self.sortPop()

        for b in self.Members:
            eval=eval+[self.Evaluator.eval(b.decode())]        
        
        minn=eval[0]
        for i in range(nElements):
            eval[i]=eval[i]-minn+0.1
        

        sup=np.sum(eval)

        for i in range(nElements):
            p=p+[eval[i]/sup]
        for i in range(nElements-1):
            q[i+1]=q[i]+p[i]

        for i in range(n-1):
            r=random.uniform(0,1)
            for j in range(nElements-1):
                if q[j]<r<=q[j+1]:
                    toAdd=toAdd+[self.Members[j]]
        
        return toAdd
            

    def sortedBatch(self,batch):
        val=[self.Evaluator.eval(b.decode()) for b in batch]
        for i in range(len(val)):
            for j in range(i,len(val)):
                if(val[i]>val[j]):
                    val[i],val[j]=val[j],val[i]
                    batch[i],batch[j]=batch[j],batch[i]
        return batch

    def select(self):
        toAdd=[]
        toAdd=toAdd+self.sortedBatch(self.Members)[:int(self.PopMax/self.ElitismPercentage)]
        
        toAdd=toAdd+self.getFortuneWheelResults(self.PopMax-len(toAdd))
        self.Members=toAdd
    
    def mutate(self):
        toAdd=[]
        for m in self.Members:
            toAdd=toAdd+[deepcopy(m)]
            m.mutate(self.mRate)
        self.Members=self.Members+toAdd

    def crossover(self):
        toAdd=[]
        self.sortPop()
        for idx in range(int(self.PopMax/2)):
            toAdd=toAdd+[self.Members[idx].cross(self.Members[idx+1])]
            idx+=1
        self.Members=self.Members+toAdd
    
    def meanFit(self):
        return np.mean([self.Evaluator.eval(m.decode()) for m in self.Members])
    
    def bestFit(self):
        return np.min([self.Evaluator.eval(m.decode()) for m in self.Members])

    def printPopulation(self):
        #for m in self.Members: 
            #print (m.decode(), end=' ')
        print()
        print("mean : ",end=' ')
        print(self.meanFit())
        print("best : ",end=' ')
        print(self.bestFit())
        print()
    