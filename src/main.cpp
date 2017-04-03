#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

string getFileName();
vector<vector<char>> getMaze(string fileName);

int main() {
  string filename = getFileName();
  vector<vector<char>> dimensions = getMaze(filename);
  
}

string getFileName() {
  string filename;
  cout << "Please enter the maze you would like to solve: ";
  cin >> filename;
  return filename;
}

vector<vector<char>> getMaze(string fileName) {
  ifstream mazeFile;
  mazeFile.open(fileName);
  string line;
  vector<vector<char>> mazeVec;
  if(mazeFile.is_open()) {
    while(getline(mazeFile, line)) {
      vector<char> tempVec;
      for(unsigned i = 0; i < line.length(); i++) {
        tempVec.push_back(line.at(i));
      }
      mazeVec.push_back(tempVec);
    }
  }
  mazeFile.close();
  return mazeVec;
}
