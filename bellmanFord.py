# 6 20
# A B -2
# B A -2
# A C 5
# C A 5
# A E 3
# E A 3
# B D 5
# D B 5
# B E 1
# E B 1
# C D -3
# D C -3
# C E -4
# E C -4
# C F 5
# F C 5
# D E -2
# E D -2
# D F 10
# F D 10

file_name = 'graph.txt'

# 🎯 Map letters to numbers: A=0, B=1, ..., F=5
node_map = {'A': 0, 'B': 1, 'C': 2, 'D': 3,'E': 4, 'F': 5}

# 🧱 Step 1: Read the input file and build the edge list
edges = []
try:
    with open(file_name, 'r') as file:
        n, m = map(int, file.readline().split()) # number of nodes, number of edges

        for _ in range(m):
            u, v, w = file.readline().split()
            u = node_map[u]
            v = node_map[v]
            w = int(w)
            edges.append((u,v,w))

# Exception Handling
except FileNotFoundError:
    print(f"Error: {file_name} not found")
except Exception as e:
    print(f"Error reading file: {e}")

# print("----ALL EDGES--------")
# for(u,v,w) in edges:
#     print(f"{u}->{v}: {w}")

# 🧠 Step 2: Initialization/ Bellman-Ford to detect negative cycle
INF = float('inf')
dist = [INF] * n
dist[0] = 0  #Start from node 0 (A)

# Step 3: Relaxation/Relax all edges n-1 times
for i in range(n-1):
    for u,v,w in  edges:
        if dist[u] != INF and dist[u] + w < dist[v]:
            dist[v] = dist[u] + w

# 🔍 Step 4: Checking for negative weight cycle
has_negative_cycles = False
for u,v,w in edges:
    if dist[u] != INF and dist[u] + w < dist[v]:
        has_negative_cycles = True
        break

# 🖨️ Output/Result
if has_negative_cycles:
    print(f"{file_name} contains a negative cycle")
else:
    print(f"{file_name} doesn't contains a negative cycle")
