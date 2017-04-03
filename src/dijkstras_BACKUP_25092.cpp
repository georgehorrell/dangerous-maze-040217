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
};

<<<<<<< HEAD
using path = vector<location>;
=======
struct path {
    vector<location> locations;
    int cost;

    bool operator<(const path& other) {
        return cost < other.cost;
    }
};

using grid = vector<vector<location>>;

int main() {
    cout << "Hello world" << endl;
}


path dijkstras(grid g, location start, location end) {
    priority_queue<path> paths;
    path first_path = {{start}, 0};
    paths.push(first_path);
    start.visited = true;

    while (!paths.empty()) {
        path curr_path = paths.top();
        paths.pop();
        location end_of_curr = curr_path.locations[curr_path.size() - 1];
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
                path copy = curr_path + neighbor;
                copy.cost += cost;
                paths.push(copy);
            }
        }
    }
}

vector<location> get_neighbors(grid g, location loc) {
    vector<location> neighbors;
    if (loc.x != 0) neighbors.push_back(g[loc.y][loc.x - 1]);
    if (loc.x != grid[0].length - 1) neighbors.push_back(g[loc.y][loc.x + 1]);
    if (loc.y != 0) neighbors.push_back(g[loc.y - 1][loc.x]);
    if (loc.y != grid.length - 1) neighbors.push_back(g[loc.y + 1][loc.x]);
    return neighbors;
}
>>>>>>> 35dfcb224d416ac8ca7ce0b26185b00f1d80b9d8
