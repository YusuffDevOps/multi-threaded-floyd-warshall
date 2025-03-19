import random
import subprocess
from time import time
import numpy as np
import matplotlib.pyplot as plt

array = [ 10, 100, 1000, 10000]
numNodes = np.array(array)
singleFW = []
multiFW = []
speedup = []


# Function to random graph input with n nodes
def generate_edge_matrix(n):
    edges = set()
    max_order =int( n*(n-1)/2)
    num_edges = random.randint(n, max_order)
    with open('graph.txt', 'w') as file:
        file.write(f"{n} {num_edges}\n")
        while len(edges) < num_edges:
            u = random.randint(1,n)
            v = random.randint(1,n)
            w = random.randint(1, 20)
            if u!=v:
                edge = (min(u,v), max(u,v))
                if edge not in edges:
                    edges.add(edge)
                    file.write(f"{u} {v} {w}\n")

def get_runtime():
    start = time()
    tmp = subprocess.call("./a.out")
    print(tmp)
    end = time()
    runtime= (end - start) * 1000
    return runtime

generate_edge_matrix(10)