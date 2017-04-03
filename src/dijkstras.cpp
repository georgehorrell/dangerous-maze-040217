#include <vector>
#include <iostream>
#include <queue>
#include <set>

using namespace std;

struct location {
    int x;
    int y;
    char ch;
    bool visited;

    bool operator ==(const location& other) {
        return x == other.x && y == other.y;
    }
};

struct path {
    vector<location> locations;
    int cost;

    bool operator<(const path& other) {
        return cost < other.cost;
    }
};

using grid = vector<vector<location>>;

vector<location> get_neighbors(grid g, location loc);

int main() {
    cout << "Hello world" << endl;
}

bool operator<(const path& one, const path& two) {
    return one.cost < two.cost;
}

path dijkstras(grid g, location start, location end) {
    priority_queue<path> paths;
    path first_path = {{start}, 0};
    paths.push(first_path);
    start.visited = true;

    while (!paths.empty()) {
        path curr_path = paths.top();
        paths.pop();
        location end_of_curr = curr_path.locations[curr_path.locations.size() - 1];
        end_of_curr.visited = true;

        if (end_of_curr == end) {
            cout << "Path found" << endl;
        }

        vector<location> neighbors = get_neighbors(g, end_of_curr);
        for (location neighbor : neighbors) {
            if (!neighbor.visited && neighbor.ch != '#') {
                char neighbor_ch = neighbor.ch;
                int cost = 1;
                if (neighbor_ch == 'm') cost += 10;
                path copy = curr_path;
                copy.locations.push_back(neighbor);
                copy.cost += cost;
                paths.push(copy);
            }
        }
    }
    cout << "No path found" << endl;
    return {};
}

vector<location> get_neighbors(grid g, location loc) {
    vector<location> neighbors;
    if (loc.x != 0) neighbors.push_back(g[loc.y][loc.x - 1]);
    if (loc.x != g[0].size() - 1) neighbors.push_back(g[loc.y][loc.x + 1]);
    if (loc.y != 0) neighbors.push_back(g[loc.y - 1][loc.x]);
    if (loc.y != g.size() - 1) neighbors.push_back(g[loc.y + 1][loc.x]);
    return neighbors;
}
