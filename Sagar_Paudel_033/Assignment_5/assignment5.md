**1.Capture an ip packet on Wireshark , what is the value of each of the header fields? Explain why the value is what it is ?**
This was done as a group

1. Version (4 bits)
   - Value: 4
   - Explanation: This value indicates that the IP version is 4, i.e., IPv4.

2. Header Length (IHL) (4 bits)
   - Value: 5
   - Explanation: This value indicates the number of 32-bit words in the header. 5 means the header is 20 bytes long (5 * 4 bytes).

3. Differentiated Services Field (DSCP) (6 bits)
   - Value: 0x2B
   - Explanation: The value 0x2B indicates a DSCP value corresponding to 43 in decimal, which is associated with a certain type of QoS behavior, specifically AF11 (Assured Forwarding).

4. ECN (2 bits)
   - Value: 00
   - Explanation: This value indicates that the packet is not using ECN. It is not ECN-capable, and any network devices should not set or interpret ECN-related bits for this packet.

5. Total Length (16 bits)
   - Value: 102
   - Explanation: This value indicates that the entire packet, including the header and data, is 102 bytes long.

6. Identification (16 bits)
   - Value: 0x510d (20749)
   - Explanation: This value indicates the identification value of the packet, which is used to uniquely identify fragments of an original IP datagram.

7. Flags (3 bits)
   - Value: 0x02 (Don't Fragment)
   - Explanation: The value 0x02 identifies the "Don't Fragment" flag, indicating that the packet should not be fragmented.

8. Fragment Offset (13 bits)
   - Value: 0
   - Explanation: Indicates where in the datagram this fragment belongs. 0 means the packet is not fragmented.

9. Time to Live (TTL) (8 bits)
   - Value: 57
   - Explanation: This value indicates that the packet can pass through 57 more routers before being discarded. The initial TTL is typically 64, meaning it has already passed through 7 routers (64 - 57).

10. Protocol (8 bits)
   - Value: TCP (6)
   - Explanation: This value indicates that the data portion of this IP packet contains a TCP segment, as indicated by the protocol number 6.

11. Header Checksum (16 bits)
   - Value: 0x0487
   - Explanation: This checksum is used for error-checking the header. A correct checksum ensures the integrity of the header data.

12. Source Address (32 bits)
   - Value: 162.159.134.234
   - Explanation: This value indicates the IP address of the sender.

13. Destination Address (32 bits)
   - Value: 192.168.1.164
   - Explanation: This value indicates the IP address of the receiver.

14. Transmission Control Protocol (TCP)
   - Source Port: 443
   - Destination Port: 52631
   - Sequence Number: 106
   - Acknowledgment Number: 1
   - Header Length: 62 bytes


   **2.On leetcode find a problem that can be solved with Dijkstra's algorithm and solve it ?**
   https://leetcode.com/problems/network-delay-time/
   You are given a network of `n` nodes, labeled from `1` to `n`. You are also given `times`, a list of travel times as directed edges `times[i] = (ui, vi, wi)`, where `ui` is the source node, `vi` is the target node, and `wi` is the time it takes for a signal to travel from source to target.

We send a signal from a given node `k`. How long will it take for all nodes to receive the signal? If it is impossible for all the `n` nodes to receive the signal, return `-1`.

Solution using Dijkstra's Algorithm:
#include <iostream> // For input and output
#include <vector>   // For using vectors
#include <queue>    // For using priority queue

using namespace std;

// Function to find the network delay time
int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    const int INF = 1e9; // A large number to represent infinity
    vector<vector<pair<int, int>>> graph(n + 1); // Adjacency list to store the graph

    // Build the graph from the given times
    for (const auto& time : times) {
        int u = time[0], v = time[1], w = time[2];
        graph[u].push_back({v, w});
    }

    // Distance vector initialized to infinity
    vector<int> dist(n + 1, INF);
    dist[k] = 0; // Distance to the source node is 0

    // Priority queue to process nodes, sorted by distance
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, k}); // Push the source node with distance 0

    // Process the nodes in the priority queue
    while (!pq.empty()) {
        int d = pq.top().first; // Current distance
        int u = pq.top().second; // Current node
        pq.pop(); // Remove the top element

        // Skip processing if the current distance is not optimal
        if (d > dist[u]) continue;

        // Check all neighbors of the current node
        for (const auto& edge : graph[u]) {
            int v = edge.first; // Neighbor node
            int w = edge.second; // Edge weight
            if (dist[u] + w < dist[v]) { // If a shorter path is found
                dist[v] = dist[u] + w; // Update the distance
                pq.push({dist[v], v}); // Push the neighbor to the queue
            }
        }
    }

    // Find the maximum distance to any node
    int maxDist = 0;
    for (int i = 1; i <= n; ++i) {
        if (dist[i] == INF) return -1; // If any node is unreachable
        maxDist = max(maxDist, dist[i]);
    }

    return maxDist; // Return the maximum distance
}

// Main function to test the algorithm
int main() {
    int n = 4; // Number of nodes
    int k = 2; // Source node
    vector<vector<int>> times = { {2, 1, 1}, {2, 3, 1}, {3, 4, 1} }; // Times

    int result = networkDelayTime(times, n, k); // Get the result
    cout << "Network delay time: " << result << endl; // Print the result

    return 0;
}


**2. On leetcode find a problem that can be solved with Bellman-Ford algorithm and solve it. For each of your solution build a flowchart and a table that shows all the updates to all your varaiables**
https://leetcode.com/problems/cheapest-flights-within-k-stops/
![alt text](image.png)
There are `n` cities connected by some number of flights. You are given an array `flights` where `flights[i] = [from_i, to_i, price_i]` indicates that there is a flight from city `from_i` to city `to_i` with cost `price_i`.

You are also given three integers `src`, `dst`, and `k`, return the cheapest price from `src` to `dst` with at most `k` stops. If there is no such route, return `-1`.

#include <iostream> // For standard input and output operations
#include <vector>   // For using vectors
#include <algorithm> // For using the min function

using namespace std;

int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    const int INF = 1e9; // Infinity constant for initial distances
    vector<int> dist(n, INF); // Distance vector initialized to infinity
    dist[src] = 0; // Distance to the source node is 0

    // Bellman-Ford algorithm
    for (int i = 0; i <= k; ++i) {
        vector<int> temp = dist; // Temporary distance vector for the current iteration
        for (const auto& flight : flights) {
            int u = flight[0], v = flight[1], w = flight[2];
            if (dist[u] != INF) {
                temp[v] = min(temp[v], dist[u] + w);
            }
        }
        dist = temp; // Update the distance vector
    }

    return dist[dst] == INF ? -1 : dist[dst]; // Return the result
}

int main() {
    int n = 3; // Number of cities
    int src = 0; // Source city
    int dst = 2; // Destination city
    int k = 1; // Maximum number of stops
    vector<vector<int>> flights = { {0, 1, 100}, {1, 2, 100}, {0, 2, 500} }; // Flights

    int result = findCheapestPrice(n, flights, src, dst, k); // Get the result
    cout << "Cheapest price: " << result << endl; // Print the result

    return 0;
}
Iteration   	Distance Vector (dist)	      Updates Applied
0	             [0, INF, INF]	               Initial distances
1	             [0, 100, INF]	               Update dist[1] to 100 from flight [0, 1, 100]
	             [0, 100, 200]	               Update dist[2] to 200 from flight [1, 2, 100]
2	             [0, 100, 200]	               No further updates since max stops (k) is 1

