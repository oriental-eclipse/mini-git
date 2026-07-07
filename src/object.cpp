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

bool createDirectory(const char *path){
    char tempPath[strlen(path) + 1];
    strcpy(tempPath, path);
    size_t len = strlen(tempPath);

    for(size_t i = 0; i < len; i++){
        if(tempPath[i] == '/'){
            tempPath[i] = '\0';

            if(mkdir(tempPath, 0755) == -1 && errno != EEXIST){
                perror("Directory Creation Error");
                return false;
            }

            tempPath[i] = '/';
        }
    }
    
    if(mkdir(path, 0755) == -1 && errno != EEXIST){
        perror("Directory Creation Error");
        return false;
    }

    return true;
}

bool fileExists(const char *path){
    return access(path, F_OK) == 0;
}

void fileCopy(const objectPath &objPath, const char *content, size_t size){
    if(!createDirectory(objPath.dirPath.c_str())){
        return;
    }

    if(fileExists(objPath.filePath.c_str())){
        std::cout << "No changes recorded!\n";
        return;
    }

    int fDesc = open(objPath.filePath.c_str(), O_WRONLY | O_CREAT, 0644);

    if(fDesc < 0){
        perror("Fatal Error : Could not create file!\n");
        return;
    }

    size_t writtenBytes = 0;

    while(writtenBytes < size){
        ssize_t written = write(fDesc, content + writtenBytes, size - writtenBytes);

        if(written < 0){
            perror("Fatal Error : Write Failed!\n");
            close(fDesc);
            unlink(objPath.filePath.c_str());
            return;
        }

        writtenBytes += written;
    }

    std::cout << "Object Stored Succesfully!\n";

    close(fDesc);
}