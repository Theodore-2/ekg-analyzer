#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class EKG {
private:
    string name;
    vector<double> times;
    vector<double> voltages;
    vector<double> peakTimes;
    vector<double> peakVoltages;
    vector<double> normal_T, bradycardia_T, tachycardia_T;
    vector<double> normal_V, bradycardia_V, tachycardia_V;

public:

    void analyze(string fileName) {
        name = fileName;
        readDataFromFile();
        calculatePeaks();
        classify();
        writeToFiles();
    }

    void readDataFromFile() {
        ifstream file(name + ".txt");
        if (!file.is_open()) {
            cout << "File could not be opened!" << endl;
            return;
        }

        string line;
        getline(file, line); // skip header
        double time, voltage;

        while (file >> time >> voltage) {
            times.push_back(time);
            voltages.push_back(voltage);
        }

        file.close();
    }

    void calculatePeaks() {
        peakTimes.push_back(0);
        peakVoltages.push_back(0);

        for (size_t i = 1; i < voltages.size() - 1; ++i) {
            if (voltages[i] >= 0.06 && voltages[i] > voltages[i - 1] && voltages[i] > voltages[i + 1]) {
                bool isPeak = true;
                for (int j = 1; j <= 500; j++) {
                    if (voltages[i] < voltages[i + j]) {
                        isPeak = false;
                        break;
                    }
                }
                if (isPeak) {
                    peakTimes.push_back(times[i]);
                    peakVoltages.push_back(voltages[i]);
                    i += 500;
                }
            }
        }
    }

    void classify() {
        double timeDiff = 0, voltageDiff = 0;

        for (size_t i = 1; i < peakTimes.size(); ++i) {
            voltageDiff = abs(peakVoltages[i] - peakVoltages[i - 1]);
            if (voltageDiff > 0.0033) {
                timeDiff = abs(peakTimes[i] - peakTimes[i + 1]);
                if (timeDiff <= 0.6) {
                    tachycardia_T.push_back(peakTimes[i]);
                    tachycardia_V.push_back(peakVoltages[i]);
                } else if (timeDiff > 1) {
                    bradycardia_T.push_back(peakTimes[i]);
                    bradycardia_V.push_back(peakVoltages[i]);
                } else {
                    normal_T.push_back(peakTimes[i]);
                    normal_V.push_back(peakVoltages[i]);
                }
            } else {
                timeDiff = abs(peakTimes[i] - peakTimes[i - 1]);
                if (timeDiff <= 0.6) {
                    tachycardia_T.push_back(peakTimes[i]);
                    tachycardia_V.push_back(peakVoltages[i]);
                } else if (timeDiff > 1) {
                    bradycardia_T.push_back(peakTimes[i]);
                    bradycardia_V.push_back(peakVoltages[i]);
                } else {
                    normal_T.push_back(peakTimes[i]);
                    normal_V.push_back(peakVoltages[i]);
                }
            }
        }
    }

    void writeToFiles() {
        ofstream normalOut(name + "-normal.txt");
        ofstream bradycardiaOut(name + "-bradycardia.txt");
        ofstream tachycardiaOut(name + "-tachycardia.txt");

        normalOut << left << setw(15) << "TIME" << "VOLTAGE" << endl;
        normalOut << string(30, '-') << endl;
        for (size_t i = 0; i < normal_T.size(); ++i) {
            normalOut << left << setw(15) << fixed << setprecision(4) << normal_T[i]
                      << fixed << setprecision(4) << normal_V[i] << endl;
        }

        bradycardiaOut << left << setw(15) << "TIME" << "VOLTAGE" << endl;
        bradycardiaOut << string(30, '-') << endl;
        for (size_t i = 0; i < bradycardia_T.size(); ++i) {
            bradycardiaOut << left << setw(15) << fixed << setprecision(4) << bradycardia_T[i]
                           << fixed << setprecision(4) << bradycardia_V[i] << endl;
        }

        tachycardiaOut << left << setw(15) << "TIME" << "VOLTAGE" << endl;
        tachycardiaOut << string(30, '-') << endl;
        for (size_t i = 0; i < tachycardia_T.size(); ++i) {
            tachycardiaOut << left << setw(15) << fixed << setprecision(4) << tachycardia_T[i]
                           << fixed << setprecision(4) << tachycardia_V[i] << endl;
        }
    }
};

void mergeFiles(const string& input1, const string& input2, const string& input3, const string& output) {
    ifstream in1(input1), in2(input2), in3(input3);
    ofstream out(output);

    if (!in1 || !in2 || !in3 || !out) {
        cout << "One or more files could not be opened!" << endl;
        return;
    }

    out << left << setw(15) << "TIME" << "VOLTAGE" << endl;
    out << string(30, '-') << endl;

    string line;
    int count = 0;

    auto copyBody = [&](ifstream& file) {
        count = 0;
        while (getline(file, line)) {
            if (count++ < 2) continue;
            out << line << endl;
        }
        out << "***************************" << endl;
    };

    copyBody(in1);
    copyBody(in2);
    copyBody(in3);

    out.close();
    cout << "File operations completed!" << endl;
}

int main() {
    EKG p1, p2, p3;

    p1.analyze("person1");
    p2.analyze("person2");
    p3.analyze("person3");

    mergeFiles("person1-normal.txt", "person2-normal.txt", "person3-normal.txt", "normal-person-1-2-3.txt");
    mergeFiles("person1-bradycardia.txt", "person2-bradycardia.txt", "person3-bradycardia.txt", "bradycardia-person-1-2-3.txt");
    mergeFiles("person1-tachycardia.txt", "person2-tachycardia.txt", "person3-tachycardia.txt", "tachycardia-person-1-2-3.txt");

    return 0;
}