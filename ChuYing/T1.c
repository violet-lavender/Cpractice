#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LEN 101
#define MAX_CHILD 256
#define MAX_DEPTH 100
#define MAX_LIST_RESULT 1024

typedef enum
{
    FILE_NODE,
    DIR_NODE
} NodeType;

typedef struct Node
{
    char name[MAX_NAME_LEN];
    NodeType type;
    struct Node *parent;
    struct Node *children[MAX_CHILD];
    int childCount;
} Node;

typedef struct
{
    Node *root;
    Node *current;
} FileSystem;

static Node *createNode(const char *name, NodeType type, Node *parent)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node)
        return NULL;
    strncpy(node->name, name, MAX_NAME_LEN);
    node->type = type;
    node->parent = parent;
    node->childCount = 0;
    return node;
}

static Node *findChild(Node *dir, const char *name)
{
    for (int i = 0; i < dir->childCount; ++i)
    {
        if (strcmp(dir->children[i]->name, name) == 0)
            return dir->children[i];
    }
    return NULL;
}

FileSystem *FileSystemCreate()
{
    FileSystem *fs = (FileSystem *)malloc(sizeof(FileSystem));
    if (!fs)
        return NULL;
    fs->root = createNode("/", DIR_NODE, NULL);
    fs->current = fs->root;
    return fs;
}

static bool FileSystemMakeDir(FileSystem *fs, const char *dirName)
{
    if (findChild(fs->current, dirName))
        return false;
    if (fs->current->childCount >= MAX_CHILD)
        return false;
    Node *newDir = createNode(dirName, DIR_NODE, fs->current);
    fs->current->children[fs->current->childCount++] = newDir;
    return true;
}

static bool FileSystemCreateFile(FileSystem *fs, const char *fileName)
{
    if (findChild(fs->current, fileName))
        return false;
    if (fs->current->childCount >= MAX_CHILD)
        return false;
    Node *newFile = createNode(fileName, FILE_NODE, fs->current);
    fs->current->children[fs->current->childCount++] = newFile;
    return true;
}

static void freeNodeRecursive(Node *node)
{
    for (int i = 0; i < node->childCount; ++i)
    {
        freeNodeRecursive(node->children[i]);
    }
    free(node);
}

static bool FileSystemRemove(FileSystem *fs, const char *name)
{
    for (int i = 0; i < fs->current->childCount; ++i)
    {
        if (strcmp(fs->current->children[i]->name, name) == 0)
        {
            freeNodeRecursive(fs->current->children[i]);
            // shift left
            for (int j = i; j < fs->current->childCount - 1; ++j)
                fs->current->children[j] = fs->current->children[j + 1];
            fs->current->childCount--;
            return true;
        }
    }
    return false;
}

static int cmpName(const void *a, const void *b)
{
    const Node *na = *(const Node **)a;
    const Node *nb = *(const Node **)b;
    return strcmp(na->name, nb->name);
}

static char **FileSystemListDir(FileSystem *fs, size_t *returnValSize)
{
    Node *list[MAX_CHILD];
    int count = 0;

    for (int i = 0; i < fs->current->childCount; ++i)
    {
        list[count++] = fs->current->children[i];
    }

    // split into dirs and files, sort separately
    Node *dirs[MAX_CHILD], *files[MAX_CHILD];
    int dCount = 0, fCount = 0;
    for (int i = 0; i < count; ++i)
    {
        if (list[i]->type == DIR_NODE)
            dirs[dCount++] = list[i];
        else
            files[fCount++] = list[i];
    }

    qsort(dirs, dCount, sizeof(Node *), cmpName);
    qsort(files, fCount, sizeof(Node *), cmpName);

    *returnValSize = dCount + fCount;
    char **res = (char **)malloc((*returnValSize) * sizeof(char *));
    int idx = 0;
    for (int i = 0; i < dCount; ++i)
    {
        size_t len = strlen(dirs[i]->name) + 1;
        res[idx] = (char *)malloc(len);
        strcpy(res[idx++], dirs[i]->name);
    }
    for (int i = 0; i < fCount; ++i)
    {
        size_t len = strlen(files[i]->name) + 1;
        res[idx] = (char *)malloc(len);
        strcpy(res[idx++], files[i]->name);
    }
    return res;
}

static Node *navigatePath(FileSystem *fs, const char *path)
{
    if (strlen(path) == 0)
        return fs->current;
    char temp[1024];
    strncpy(temp, path, sizeof(temp));
    if (temp[strlen(temp) - 1] == '/')
        temp[strlen(temp) - 1] = '\0';

    Node *cur = (path[0] == '/') ? fs->root : fs->current;
    char *token = strtok(temp, "/");
    while (token != NULL)
    {
        Node *child = findChild(cur, token);
        if (!child || child->type != DIR_NODE)
            return NULL;
        cur = child;
        token = strtok(NULL, "/");
    }
    return cur;
}

static bool FileSystemChangeDir(FileSystem *fs, const char *pathName)
{
    Node *target = navigatePath(fs, pathName);
    if (!target)
        return false;
    fs->current = target;
    return true;
}

static void FileSystemFree(FileSystem *fs)
{
    freeNodeRecursive(fs->root);
    free(fs);
}