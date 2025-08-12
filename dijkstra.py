import heapq

file_name = "graph1.txt"

# (dictionary) Maps letters -> integer indices (numbers), simpler & faster internally
node_map = {
    'A': 0, 'B': 1, 'C': 2, 'D': 3, 'E': 4,
    'F': 5, 'G': 6, 'H': 7, 'I': 8, 'J': 9
}
# Reverse mapping (number → letter).
reverse_map = {v: k for k, v in node_map.items()}

# Returns the dictionary length.
n = len(node_map)

# creates an adjacency list of n empty lists. Uses _ as a throwaway loop variable
graph = [[] for _ in range(n)]

try:
    with open(file_name, 'r') as file:
        m = int(file.readline().strip())
        for _ in range(m):
            u, v, w = file.readline().split()
            u = node_map[u]
            v = node_map[v]
            w = int(w)
            graph[u].append((v, w))
            graph[v].append((u, w)) #undirected graph (edge both ways).

except FileNotFoundError:
    print(f"Error: {file_name} not found")
    exit(1)

except Exception as e:
    print(e)

INF = float('inf')
dist = [INF] * n
parent = [-1] * n  # To track the path

start = node_map['I']
goal = node_map['G']
dist[start] = 0

pq = [(0, start)]  # priority queue (min-heap)

while pq:
    current_cost, u = heapq.heappop(pq)

    if current_cost > dist[u]:
        continue

    for v, weight in graph[u]:
        if dist[u] + weight < dist[v]:
            dist[v] = dist[u] + weight
            parent[v] = u
            heapq.heappush(pq, (dist[v], v))

# Step 3: Output
# if dist[goal] != INF:
#     print(f"Minimum cost from I to G = {dist[goal]}")
# else:
#     print("No path found from I to G")

if dist[goal] != INF:
    print(f"Minimum cost from I to G = {dist[goal]}")

    # Rebuilded path
    path = []
    current = goal
    while current != -1:
        path.append(reverse_map[current])
        current = parent[current]
    path.reverse()
    print("Path:", " -> ".join(path))
else:
    print(f"No path found from {reverse_map[start]} to {reverse_map[goal]}")
