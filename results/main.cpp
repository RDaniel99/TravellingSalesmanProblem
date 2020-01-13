#include <cstdio>
#include <random>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstring>
#include <string>
#include <iostream>
#include <chrono>

using namespace std;

#define MAX_RUNS 10000

typedef pair<double, double> city;

vector <city> points;
vector <int> permutare;
vector <double> distances;

double ComputeDistance(city a, city b)
{
    return sqrt((a.first - b.first) * (a.first - b.first) +
                (a.second - b.second) * (a.second - b.second));
}

int main()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);

    ifstream fin("fisiere.txt");

    string fisier;
    while(fin >> fisier)
    {
        cout << "Running on: " << fisier << '\n';
        ifstream in(fisier.c_str());
        double tip;
        in >> tip;

        points.clear();
        int tmp;
        double x, y;
        while(in >> x >> y)
        {
            if(tip == 3)
            {
                in >> tmp;
                x = y;
                y = tmp;
            }

            city toAdd;
            toAdd.first = x;
            toAdd.second = y;

            points.push_back(toAdd);
        }

        permutare.clear();
        for(int i = 0; i < points.size(); i++)
            permutare.push_back(i);


        double bstDistance;
        distances.clear();

        auto rng = std::default_random_engine {};

        for(int run = 1; run <= MAX_RUNS; run++)
        {
            std::shuffle(std::begin(permutare), std::end(permutare), e);

            double sumDist = 0;
            for(int i = 0; i < points.size() - 1; i++)
            {
                int nxtPoint = i + 1;
                sumDist += ComputeDistance(points[permutare[i]], points[permutare[nxtPoint]]);
            }

            if(run == 1 || bstDistance > sumDist)
                bstDistance = sumDist;

            distances.push_back(sumDist);
        }

        cout << "Printing the results...\n";

        string output = "OUTPUT_" + fisier;

        ofstream fout(output.c_str());

        fout << "Best Distance = " << bstDistance << '\n';

        fout << "[";
        for(int i = 0; i < distances.size(); i++)
        {
            fout << distances[i];
            if(i != distances.size() - 1)
                fout << ", ";
        }

        fout << "]";
        in.close();
        fout.close();

        cout << "Done! Next...\n";
    }

    cout << "Done all!\n";

    return 0;
}
