#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
    std::ifstream file("./testfile.th");
    if (file.bad()) perror("failed to open file");
    string line("");
    for (int i = 0;file.peek() != EOF;){
        line.push_back((char) file.get());
        line.push_back(file.get());
        cout << line << endl;
        line.clear();
    }
}