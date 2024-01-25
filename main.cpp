#include "rapidcsv.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

bool DBUGMODE = true; // Debugging auto set to on
long int COLUMS = 3;
long int ROWS = 2;

// Map for the nums in the map
auto tile_Def(int tile){
    std::map<int, std::string> tileMap = {{1, " 🌲 "}, {2, " 🍀 "}, {3, " 🌊 "}, {4, " ⛰ "}, {5, " 🏠 "}};
    return tileMap[tile];
}

// Generate the map based on the numbers using the tile set. It does not read from the CSV though. No current ability to load from the CSV
void generate_Map(std::vector<int>* mapVectorData){
    // Debug prints out the statistics
    if(DBUGMODE){
        std::cout<<"****DEBUGGING MODE ON:****\nDB: Got the vector. Priniting Data: " << std::endl;
        for(int i = 0; i < mapVectorData->size(); i++){
        std::cout<< (*mapVectorData)[i];
        }
    }
    
    // Init vars.
    int mapVectorSize = mapVectorData->size(); // We'll be using it alot
    int mapVectorMod = mapVectorSize%COLUMS; // Modulo for the amount of COLUMS

    // Create map
    // Prints \n every time the amount of COLUMS have been reached
    for(int i = 0; i < mapVectorData->size(); i++){
        if(i%COLUMS == 0){
            std::cout<<"\n";
        }
        std::cout<< tile_Def((*mapVectorData)[i]);
    }
}

// Save the map data to the CSV. Save in ints as to conserve data space
void save_Map(std::vector<int>* mapDataVector){
    // To read a colum
    // rapidcsv::Document doc("map.csv");
    // std::vector<float> col = do c.GetColumn<float>("");
    // std::cout << "Read " << col.size() << " values." << std::endl;
    std::vector<int> mData = *mapDataVector;

    std::ofstream file;
    file.open("map.csv");
    for(int i = 0; i < mData.size(); i++){
        if(i%COLUMS == 0 && i != 0){
            file << "\n";
        }
        if(DBUGMODE){
            std::cout<< "DB: Saved: " << mData[i] << std::endl;
        }
        file << mData[i] << ",";
    }
    std::cout << "SAVED" << std::endl;
    generate_Map(mapDataVector); // Call the function
}

// Make a random set of ints from 1-5 based on the inputted variables to render the map
auto random_Map_Data(){
    // Initialise the map data vector
    std::vector<int> mapData;

    // Ask for amount of random number
    std::cout<<"How many rows and columns? \nRows must be 2 <= n <= 100. \nValues MUST be spaced.\nDefaults:\n Rows:2 Colums: 3" << std::endl;
    std::cin >> ROWS >> COLUMS; // Assign values to ROWS and COLUMS

    for(int i = 0; i < ROWS*COLUMS; i++){
        int randNum = std::rand() % 5 + 1;
        mapData.push_back(randNum);
    }

    if(DBUGMODE){
        for(int i= 0; i < mapData.size(); i++){
            std::cout << "" << mapData[i];
        }
        std::cout << std::endl << "DB: Length: " << mapData.size() << std::endl;
    }

    // Make Map data Pointer
    std::vector<int>* mapDataPointer = &mapData;
    save_Map(mapDataPointer);
}

// Insert map data
auto insert_Map_Data(){
    std::vector<int> mapData;
    int input;
    while(true){
    std::cout << "Enter map data, one at a time(enter any non-integer to stop): " << std::endl;;

    while(std::cin >> input) { // It will continue adding till the input is a non valid input eg string/char
        mapData.push_back(input);
    }
    for(int i= 0; i < mapData.size(); i++){
        std::cout << mapData[i] << std::endl;
    }
    if(mapData.size() % 3 == 0){
        break;
    }else{
        std::cout<<"Please have a map data the length of a multiple " << COLUMS << " You only gave: " << mapData.size() << std::endl;
    }
    }

    if(DBUGMODE){
        for(int i= 0; i < mapData.size(); i++){
            std::cout << "" << mapData[i];
        }
        std::cout << std::endl << "DB: Length: " << mapData.size() << std::endl;
    }
    // Make Map data Pointer
    std::vector<int>* mapDataPointer = &mapData;
    save_Map(mapDataPointer);
}


// Menu
int menu(){
    while(true){
        std::cout << "Options:\n-- 1: Insert own map data\n-- 2: Use random map data\n-- 3: Change debugging from: " << DBUGMODE << " to its resirpocal.\n-- 4: END" << std::endl;
        int menuOption; std::cin >> menuOption;
        if(menuOption > 4 || menuOption < 1)
            std::cout << "Option invalid. Please choose 1, 2 or 3." << std::endl;
        else
            switch(menuOption){
                case 1:
                    insert_Map_Data();
                    return 0;
                case 2:
                    random_Map_Data();
                    return 0;
                case 3:
                    DBUGMODE = !DBUGMODE; // Flips it
                    std::cout<< "DB: Debugging is switched from: " << !DBUGMODE << " To " << DBUGMODE << std::endl;
                    break;
                case 4:
                    return 0;
            }
    }
};

// Drive
int main(){
    menu();
    return 0;
}