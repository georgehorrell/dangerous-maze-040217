#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>

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
};

using grid = vector<vector<location>>;
vector<location> get_neighbors(grid& g, location& loc);
string getFileName();
grid getMaze(string fileName, location &start, location &end);
path dijkstras(grid g, location start, location end);
void printSolution(grid maze, path& soln);
void printGrid(const grid& maze);

bool operator<(const path& one, const path& two) {
        return one.cost > two.cost;
}

ostream& operator <<(ostream& o, const location& l) {
                o << l.x << ", " << l.y;
                                    return o;
}

int main() {
  string filename = getFileName();
  location start, end;
  grid maze = getMaze(filename, start, end);
  path soln = dijkstras(maze, start, end);
  printSolution(maze, soln);
  cout << "Solution cost: " << soln.cost << endl;
}

void printSolution(grid maze, path& soln) {
    if (soln.locations.empty()) return;
    for (int i = 1; i < soln.locations.size() - 1; i++) {
        location temp = soln.locations[i];
        temp.ch = '*';
        maze[temp.y][temp.x] = temp;
    }
    printGrid(maze);
}

void printGrid(const grid& maze) {
    for (int r = 0; r < maze.size(); r++) {
        for (int c = 0; c < maze[r].size(); c++) {
            cout << maze[r][c].ch;
        }
        cout << endl;
    }
}

string getFileName() {
  string filename;
  cout << "Please enter the maze you would like to solve: ";
  cin >> filename;
  return filename;
}

grid getMaze(string fileName, location &start, location &end) {
  ifstream mazeFile;
  mazeFile.open(fileName);
  string line;
  grid mazeVec;
  int row = 0;
  if(mazeFile.is_open()) {
    while(getline(mazeFile, line)) {
      vector<location> tempVec;
      for(unsigned col = 0; col < line.length(); col++) {
        location current;
        current.x = col;
        current.y = row;
        current.ch = line.at(col);
        current.visited = current.ch == 'S' ? true : false;
        tempVec.push_back(current);
        if(current.ch == 'S') start = current;
        if(current.ch == 'G') end = current;
      }
      mazeVec.push_back(tempVec);
      row++;
    }
  }
  mazeFile.close();
  return mazeVec;
}

void clearScreen() {
    cout << string(100, '\n');
}

int heuristic(location current, location end) {
    return abs(end.x - current.x) + abs(end.y - current.y);   
}

path dijkstras(grid g, location start, location end) {
    cout << "Start: " << start << endl;
    cout << "End: " << end << endl;
    priority_queue<path> paths;
    path first_path = {{start}, heuristic(start, end)};
    paths.push(first_path);
    start.visited = true;

    while (!paths.empty()) {
        path curr_path = paths.top();
        paths.pop();
        location end_of_curr = curr_path.locations[curr_path.locations.size() - 1];
        curr_path.cost -= heuristic(end_of_curr, end);
        end_of_curr.visited = true;
        g[end_of_curr.y][end_of_curr.x] = end_of_curr;
        clearScreen();
        printSolution(g, curr_path);
        usleep(10000);
//        cout << "Exploring location: " << end_of_curr.x << ", " << end_of_curr.y << endl;

        if (end_of_curr == end) {
            cout << "Path found" << endl;
            return curr_path;
        }

        vector<location> neighbors = get_neighbors(g, end_of_curr);
        for (location& neighbor : neighbors) {
            if (!neighbor.visited && neighbor.ch != '#') {
                char neighbor_ch = neighbor.ch;
                int cost = 1 + heuristic(neighbor, end);
                if (neighbor_ch == 'm') cost += 10;
                path copy = curr_path;
                copy.locations.push_back(neighbor);
                copy.cost += cost;
                paths.push(copy);
//                cout << "Enqueued " << neighbor << " with cost " << copy.cost << endl;
            }
        }
    }
    cout << "No path found" << endl;
    return {};
}

vector<location> get_neighbors(grid& g, location& loc) {
    vector<location> neighbors;
    if (loc.x != 0) neighbors.push_back(g[loc.y][loc.x - 1]);
    if (loc.x != g[0].size() - 1) neighbors.push_back(g[loc.y][loc.x + 1]);
    if (loc.y != 0) neighbors.push_back(g[loc.y - 1][loc.x]);
    if (loc.y != g.size() - 1) neighbors.push_back(g[loc.y + 1][loc.x]);
    return neighbors;
}
