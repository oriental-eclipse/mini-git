#include "../include/hasher.hpp"

uint64_t hashingLogic(const std::string &originalString){
    uint64_t hash = 6942067;     //funny number

    for(unsigned char c : originalString){
        hash = (hash * 67) + (uint64_t)c;
    }
    
    return hash;
}

uint64_t fileHasher(std::string fileName){
    std::ifstream fin;
    std::string line, content = "";
    uint64_t hashedBlob = 0;

    fin.open("../data/" + fileName + ".txt");

    while(std::getline(fin, line)){
        content.append(line);
    }

    std::string blobHeader = "blob" + std::to_string(content.size()) + "\0";
    std::string blob = blobHeader + content;

    fin.close();

    hashedBlob = hashingLogic(blob);

    return hashedBlob;
}

void fileCopy(uint64_t hashedBlob, std::string fileName){
    std::ifstream fin;
    std::ofstream fout;

    fin.open("../data/" + fileName + ".txt");
    
    if(!fin.is_open()){
        std::cerr << "\nFatal Error : File doesn't exist/Could not be opened!";
        exit(1);
    }
    else{
        std::cout << "\nInput File Opened Successfully";
    }

    std::string hashedBlobFileName = std::to_string(hashedBlob);
    std::string directory = "";
    directory.append(hashedBlobFileName.substr(0,2));
    hashedBlobFileName.erase(0, 2);
    
    std::string objPath("../objects/" + directory);

    if(std::filesystem::exists(objPath) && std::filesystem::is_directory(objPath)){
        if(std::filesystem::exists(objPath.append("/" + hashedBlobFileName + ".txt"))){
            std::cout << "\nNo Changes Recorded!";
            fin.close();
            return;
        }
        else{
            objPath.append("/" + hashedBlobFileName + ".txt");
            std::ofstream newFile(objPath);
            fout.open(objPath);
            std::cout << "\nNew object created!";
        }
    }
    else{
        std::filesystem::create_directory(objPath);
        objPath.append("/" + hashedBlobFileName + ".txt");
        std::ofstream newFile(objPath);
        fout.open(objPath);
        std::cout << "\nNew directory and object created!";
    }

    std::string line;
    while(std::getline(fin, line)){
        fout << line << '\n'; 
    }

    if(fin.bad() || fout.bad()){
        std::cerr << "\nFatal Error : Unrecoverable I/O error occured during reading/writing file!";
        std::filesystem::remove(objPath);
    }

    std::cout << "\nChanges Recorded Succesfully!";

    fin.close();
    fout.close();
}