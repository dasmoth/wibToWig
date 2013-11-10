#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>

using namespace std;


int main(int argc, char** argv) {
    if (argc != 3) {
        cerr << "Usage: wibToWig table.txt table.wib" << endl;
        return 1;
    }

    ifstream meta(argv[1]);
    if (meta.fail()) {
        cerr << "Couldn't open " << argv[1] << endl;
        return 1;
    }

    ifstream wib(argv[2]);
    if (wib.fail()) {
        cerr << "Couldn't open " << argv[2] << endl;
        return 1;
    }

    int bin;
    string chr;
    int minPos, maxPos;
    string name;
    int width;
    int count;
    uint64_t offset;
    string wibName;
    double lowerLimit;
    double dataRange;
    int validCount;
    double sumData;
    double sumSquares;

    unsigned char buffer[10000];

    while (true) {
        meta>>bin>>chr>>minPos>>maxPos>>name>>width>>count>>offset>>wibName>>lowerLimit>>dataRange>>validCount>>sumData>>sumSquares;
        if (meta.eof())
            break;

        wib.seekg(offset);
        wib.read((char *) &buffer, count);

        cout << "fixedStep chrom=" << chr << " start=" << minPos << " step=" << width << endl;
        for (int i = 0; i < count; ++i) {
            if (buffer[i] < 128) {
                double value = lowerLimit+(dataRange*((double)buffer[i]/127.0));
                cout << value << '\n';
            }
        }
    }

    cout.flush();
}
