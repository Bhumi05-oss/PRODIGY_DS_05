#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
using namespace std;

// Count frequencies in maps
unordered_map<string, int> timeCounts;
unordered_map<string, int> weatherCounts;
unordered_map<string, int> roadCounts;

void readCSV(const string& filename) {
    ifstream file(filename);
    string line;

    // Skip header
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string time, weather, road;

        getline(ss, time, ',');
        getline(ss, weather, ',');
        getline(ss, road, ',');

        timeCounts[time]++;
        weatherCounts[weather]++;
        roadCounts[road]++;
    }
}

void printSummary() {
    cout << "=== Accident Summary ===\n\n";

    cout << "Accidents by Time of Day:\n";
    for (auto& pair : timeCounts)
        cout << pair.first << ": " << pair.second << "\n";

    cout << "\nAccidents by Weather Condition:\n";
    for (auto& pair : weatherCounts)
        cout << pair.first << ": " << pair.second << "\n";

    cout << "\nAccidents by Road Condition:\n";
    for (auto& pair : roadCounts)
        cout << pair.first << ": " << pair.second << "\n";
}

// Optional: export to CSV for visualization
void exportSummary(const string& outFile) {
    ofstream out(outFile);

    out << "Category,Type,Count\n";
    for (auto& p : timeCounts)
        out << "Time of Day," << p.first << "," << p.second << "\n";
    for (auto& p : weatherCounts)
        out << "Weather," << p.first << "," << p.second << "\n";
    for (auto& p : roadCounts)
        out << "Road Condition," << p.first << "," << p.second << "\n";

    out.close();
    cout << "\nData exported to: " << outFile << endl;
}

int main() {
    string filename = "accidents.csv";
    readCSV(filename);

    printSummary();

    exportSummary("accident_summary.csv");

    return 0;
}