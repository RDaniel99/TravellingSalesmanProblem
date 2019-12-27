import numpy as np
def de_jong(args:[...,float]) -> float:
    n=len(args)
    return np.sum([x*x for x in args])

def schwefel(args:[...,float]) -> float:
    n=len(args)
    return (np.sum([-x*np.sin(np.sqrt(abs(x))) for x in args]))

def rastrigin(args:[...,float]) -> float:
    n=len(args)
    return (10*n+np.sum([x**2-10*np.cos(2*np.pi*x) for x in args]))

def sum_dif(args:[...,float]) -> float:
    n=len(args)
    return np.sum([abs(x)**(idx+1) for idx,x in enumerate(args)])

def michalewicz(args:[...,float]) -> float:
    n=len(args)
    m=10
    return (-sum([np.sin(x)*(np.sin((i*(x**2))/np.pi))**(2*m) for i,x in enumerate(args)]))
