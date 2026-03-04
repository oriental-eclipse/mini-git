#include "../include/hasher.hpp"

uint64_t hashingLogic(const std::string &originalString){
    uint64_t hash = 6942067;     //funny number

    for(unsigned char c : originalString){
        hash = (hash * 67) + (uint64_t)c;
    }
    
    return hash;
}

Blob fileHasher(const std::string &fileName){
    std::ifstream fin;
    std::string fileContent;
    Blob blob;

    fin.open("../data/" + fileName + ".txt", std::ios::binary);

    if(!fin.is_open()){
        std::cerr << "\nFatal Error : File doesn't exist/Could not be opened!";
        exit(1);
    }

    std::ostringstream ss;
    ss << fin.rdbuf();
    fileContent = ss.str();

    std::string blobHeader = "blob " + std::to_string(fileContent.size());
    blobHeader.push_back('\0');
    blob.content = blobHeader + fileContent;
    std::stringstream hexer;
    hexer << std::hex << std::setw(16) << std::setfill('0') << hashingLogic(blob.content);;
    blob.hash = hexer.str();

    fin.close();

    return blob;
}

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