// This is identical to detecting cycles in a graph.
// For an undirected graph, we can use DFS (T: O(V+E), S: O(V+E)), BFS (T: O(V+E), S: O(V+E)) or the union-find algorithm (T: O(ElogV), S: O(max(V,E))).
// For a directed graph, we can utilize DFS (T: O(V+E), S: O(V+E)) or a topological sorting algorithm.
// The topological sorting algorithm can be realized through DFS or Kanh's
// algorithm (using a queue to store nodes with current in-degrees of 0, similart to BFS (T: O(V+E), S: O(V+E))).

// DFS is usually faster at detecting cycles due to the pruning strategy that involve recording the visit status.
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> answer;

        // Builds the graph.
        vector<vector<int>> g(numCourses);
        for (const auto& prerequisite: prerequisites) {
            g[prerequisite[1]].push_back(prerequisite[0]);
        }

        // `visit_status`: 0 means unvisited, 1 means visiting, and 2 means visited.
        vector<int> visit_status(numCourses);
        for (int i = 0; i < numCourses; ++i) {
            if (_dfs(i, g, visit_status, answer)) return vector<int>();
        }

        // The courses that need to be learned first are added last.
        std::reverse(answer.begin(), answer.end());
        return answer;
    }

private:
    // Returns true if a cycle is detected.
    bool _dfs(const int& i, const vector<vector<int>>& g, vector<int>& visit_status, vector<int>& answer) {
        if (visit_status[i] == 2) return false;
        if (visit_status[i] == 1) return true;

        visit_status[i] = 1;
        for (const int& neighbour: g[i]) {
            if (_dfs(neighbour, g, visit_status, answer)) return true;
        }
        visit_status[i] = 2;
        answer.push_back(i);
        return false;
    }
};

// Topological sorting (kahn's algorithm)
class Solution2 {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> answer;

        // Builds the graph and calculates the in-degrees.
        vector<vector<int>> g(numCourses);
        vector<int> indegrees(numCourses);
        for (const auto& prerequisite: prerequisites) {
            g[prerequisite[1]].push_back(prerequisite[0]);
            ++indegrees[prerequisite[0]];

        }

        // Uses a queue to continuously record the zero-degree nodes to implement the Kahn's algorithm.
        queue<int> zero_degrees_queue;
        for (int i = 0; i < numCourses; ++i) {
            if (indegrees[i] == 0) zero_degrees_queue.push(i);
        }

        // Starting from zero-degree nodes, each visited node results in decreasing its children's
        // in-degrees by 1. If when zero_degrees_queue becomes empty before all nodes are visited, 
        // there is at least one cycle present.
        vector<int> visited;
        // T: O(V+E)
        while (!zero_degrees_queue.empty()) {
            int course = zero_degrees_queue.front();
            zero_degrees_queue.pop();

            for (const int& next_course: g[course]) {
                if (--indegrees[next_course] == 0) zero_degrees_queue.push(next_course);
            }
            visited.push_back(course);
        }

        // Or checks if the in-degree of any node is not 0.
        if (visited.size() < numCourses) return {};
        return visited;
    }
};