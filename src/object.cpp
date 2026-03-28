#include "../include/object.hpp"

objectPath filePathCreation(const Blob &hashedBlob){
    std::string hashedBlobFileName = hashedBlob.hash;
    std::string directory = hashedBlobFileName.substr(0, 2);
    std::string fileNamePart = hashedBlobFileName.substr(2);

    objectPath objPath;
    objPath.dirPath = "../objects/" + directory;
    objPath.filePath = objPath.dirPath + "/" + fileNamePart;

    return objPath;
}

void createDirectory(const char *path){
    mkdir(path, 0755);
}

bool fileExists(const char *path){
    return access(path, F_OK) == 0;
}

void fileCopy(const objectPath &objPath, const char *content, size_t size){
    createDirectory(objPath.dirPath.c_str());

    if(fileExists(objPath.filePath.c_str())){
        std::cout << "No changes recorded!";
        return;
    }

    int fDesc = open(objPath.filePath.c_str(), O_WRONLY | O_CREAT, 0644);

    if(fDesc < 0){
        perror("Fatal Error : Could not create file!");
        return;
    }

    size_t writtenBytes = 0;

    while(writtenBytes < size){
        ssize_t written = write(fDesc, content + writtenBytes, size - writtenBytes);

        if(written < 0){
            perror("Fatal Error : Write Failed!");
            close(fDesc);
            unlink(objPath.filePath.c_str());
            return;
        }

        writtenBytes += written;
    }

    std::cout << "\nObject Stored Succesfully!";

    close(fDesc);
}