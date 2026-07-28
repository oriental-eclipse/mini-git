#include "../include/commands.hpp"

Command commands[] = {
    {"add", addCommand},
    {"init", initCommand}
};

const size_t COMMAND_COUNT = sizeof(commands) / sizeof(commands[0]);

const char* headContent = "ref: refs/heads/main\n";

int dispatcher(const int argc, char* argv[]){
    if(argc < 2){
        std::cerr << "Error: Too few arguments!";
        return -1;
    }

    for(size_t i = 0; i < COMMAND_COUNT; i++){
        if(strcmp(argv[1], commands[i].name) == 0){
            return commands[i].handler(argc, argv);
        }
    }

    std::cerr << "Error: Command doesn't exist!";
    return -1;
}

int delete_callback(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf){
    int status = remove(fpath);

    if(status == 0){
        printf("Deleted: %s\n", fpath);
    }
    else{
        perror(fpath);
    }

    return status;
}

int addCommand(const int argc, char* argv[]){
    if(argc < 3){
        std::cerr << "Expecting: ./ksks add <filename>\n";
        return -1;
    }
    if(argc > 3){
        std::cerr << "Error: Too many arguments!\n";
        return -1;
    }

    std::string fileName(argv[2]);

    Blob blob = fileHasher(fileName);
    
    fileCopy(filePathCreation(blob), blob.content.c_str(), blob.content.size());

    stageFile(fileName, blob.hash);

    return 0;
}

int initCommand(const int argc, char* argv[]){
    if (argc != 2){
        std::cerr << "Error: Too many arguments!\n";
        return -1;
    }

    if(access(".ksks", F_OK) == 0){
        printf("Repository already initialized!\n");
        return 0;
    }

    printf("Repository initializing...\n");

    bool dirDescMain = createDirectory(".ksks");
    bool dirDescObj = createDirectory(".ksks/objects");
    bool dirDescRefs = createDirectory(".ksks/refs");
    bool dirDescHeads = createDirectory(".ksks/refs/heads");

    int fDescHEAD = open(".ksks/HEAD", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int fDescConfig = open(".ksks/config", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int fDescIndex = open(".ksks/index", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int fDescMain = open(".ksks/refs/heads/main", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    ssize_t bytesWritten = write(fDescConfig, headContent, strlen(headContent));

    if(bytesWritten != (ssize_t)strlen(headContent)){
        perror("Error: HEAD write failure\n");
        close(fDescHEAD);
        goto cleanup;
    }

    if(fDescConfig == -1 || fDescHEAD == -1 || fDescIndex == -1 || fDescMain == -1 ||
       !dirDescMain || !dirDescObj || !dirDescRefs || !dirDescHeads){
    cleanup:
        perror("Fatal Error: Couldn't initialize .ksks directory!\n");

        if(dirDescMain){
            int delDesc = nftw(".ksks", delete_callback, 64, FTW_DEPTH | FTW_PHYS);

            if(delDesc == 0){
                printf("Removed residual .ksks directory\n");
                return -1;
            }
            else{
                perror("Error: Failed to remove residual .ksks directory!\n");
                return -2;
            }
        }
        return -1;
    }

    printf("Repository initialized!\n");

    
    close(fDescHEAD);
    close(fDescConfig);
    close(fDescIndex);
    close(fDescMain);

    return 0;
}