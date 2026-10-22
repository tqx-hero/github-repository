//
// Created by Administrator on 2026/7/5.
//

#include <vector>

#include "Animals.h"

// int main(int argc, const char * argv[]) {
//     string line;
//     getline(cin, line);
//     Utils::trimAll(line);
//     vector<string> data = Utils::splitWithOuterComma(line);
//     vector<vector<string> > animals = Utils::parseAnimals(data);
//
//     for (const auto &animal : animals) {
//         if (animal.size() > 2) {
//             cout << "Error input!" << endl;
//             break;
//         }
//
//         try {
//             Animals a(animal[0], stoi(animal[1]));
//             a.printInfo();
//         } catch (const exception& e) {
//             cout << "Cannot convert to int => " << animal[1] << endl;
//             break;
//         }
//     }
//
//     cout << "Total animals: " << Animals::total << endl;
//
//     return 0;
// }
