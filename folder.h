
int make_directory() {
    char* dirname = "DATA";

    // Check if directory exists
    struct stat st;
    if (stat(dirname, &st) == -1) {
        // Directory does not exist, create it
        if (mkdir(dirname) != 0) {
            fprintf(stderr, "Error: Could not create directory %s\n", dirname);
            exit(EXIT_FAILURE);
        }
        printf("Directory %s created successfully\n", dirname);
    }

    return 0;
}

