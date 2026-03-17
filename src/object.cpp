#include "../include/object.hpp"

objectPath filePathCreation(const Blob &hashedBlob){
    std::string hashedBlobFileName = hashedBlob.hash;
    std::string directory = hashedBlobFileName.substr(0, 2);
    std::string fileNamePart = hashedBlobFileName.substr(2);

    objectPath objPath;
    objPath.dirPath = "../objects/" + directory;
    objPath.filePath = objPath.dirPath + "/" + fileNamePart + ".txt";

    return objPath;
}

void fileCopy(const objectPath &objPath, const std::string &content){
    std::ofstream fout;

    std::filesystem::create_directories(objPath.dirPath);

    if(std::filesystem::exists(objPath.filePath)){
        std::cout << "\nNo Changes Recorded!";
        return;
    }

    fout.open(objPath.filePath, std::ios::binary);
    
    if(!fout){
        std::cerr << "\nFatal Error: Could not create object file!";
        return;
    }

    fout.write(content.data(), content.size());

    if(fout.bad()){
        std::cerr << "\nFatal Error : Unrecoverable I/O error occured during reading/writing file!";
        std::filesystem::remove(objPath.filePath);
        return;
    }

    std::cout << "\nObject Stored Succesfully!";

    fout.close();
}