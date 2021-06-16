#include "asmBuilder.h"
#include "emitcode.h"
#include "global.h"
#include <stdio.h>
#include <string>
FILE *fp = nullptr;
extern "C"
{
    TreeNode *parse(FILE *fileIn);
}

int main(int argc, char *argv[])
{
    //    QApplication a(argc, argv);
    //    MainWindow w;
    //    w.show();

    FILE *targetCodeFile = nullptr;
    FILE *sourceCodeFile = nullptr;
    FILE *treeFile = nullptr;
    std::string treeName;
    std::string sourceCodeName;
    std::string targetCodeName;
    for (int i = 1; i < argc; i++)
    {
        if (std::string(argv[i]) == "-o")
        {
            i++;
            targetCodeName = std::string(argv[i]);
            targetCodeFile = fopen(argv[i], "w");
        }
        else if (!sourceCodeFile)
        {
            sourceCodeName = std::string(argv[i]);
            sourceCodeFile = fopen(argv[i], "r");
        }
    }

    if (!sourceCodeFile)
    {
        sourceCodeFile = fopen("../test/loop.c", "r");
    }
    

    if (!targetCodeFile)
    {
        targetCodeName = "./output.asm";
        targetCodeFile = fopen("./output.asm", "w");
    }

    if (!treeFile)
    {
        treeName = "./AST.txt";
        treeFile = fopen("./AST.txt", "w");
    }
    
    TreeNode *myTree = parse(sourceCodeFile);
    fclose(sourceCodeFile);

    printSyntaxTree(treeFile, myTree, 0);
    fclose(treeFile);

    symbolTable aSymbolTable;

    fp = targetCodeFile;
    asmBuilder ab(myTree);
    ab.asmBuild();

    
    
    fclose(targetCodeFile);

    return 0;
}
