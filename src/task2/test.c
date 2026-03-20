#include "avl.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void testInsertAndFind(void)
{
    printf("[RUNNING] TEST Insert and Find\n");
    AVL* tree = createAVL();

    tree = avlInsert(tree, "SVO", "Sheremetyevo");
    tree = avlInsert(tree, "DME", "Domodedovo");

    assert(strcmp(find(tree, "SVO"), "Sheremetyevo") == 0);
    assert(strcmp(find(tree, "DME"), "Domodedovo") == 0);
    assert(find(tree, "ZZZ") == NULL);

    freeAVL(tree);
}

void testAVLBalance(void)
{
    printf("[RUNNING] TEST AVL Balance\n");
    AVL* tree = createAVL();

    tree = avlInsert(tree, "AAA", "Airport A");
    tree = avlInsert(tree, "BBB", "Airport B");
    tree = avlInsert(tree, "CCC", "Airport C");

    assert(tree->root != NULL);
    assert(strcmp(tree->root->code, "BBB") == 0);
    assert(strcmp(tree->root->left->code, "AAA") == 0);
    assert(strcmp(tree->root->right->code, "CCC") == 0);

    freeAVL(tree);
}

void testSimpleDeletion(void)
{
    printf("[RUNNING] TEST Simple Deletion\n");
    AVL* tree = createAVL();

    tree = avlInsert(tree, "SVO", "Sheremetyevo");
    tree = avlInsert(tree, "DME", "Domodedovo");
    tree = avlInsert(tree, "VKO", "Vnukovo");

    tree = avlDeleteNode(tree, "DME");
    assert(find(tree, "DME") == NULL);
    assert(find(tree, "SVO") != NULL);
    assert(find(tree, "VKO") != NULL);

    freeAVL(tree);
}

void testTwoChildDeletion(void)
{
    printf("[RUNNING] TEST Deletion of two child\n");
    AVL* tree = createAVL();

    tree = avlInsert(tree, "MMM", "Root");
    tree = avlInsert(tree, "AAA", "Left");
    tree = avlInsert(tree, "ZZZ", "Right");

    tree = avlDeleteNode(tree, "MMM");

    assert(find(tree, "MMM") == NULL);
    assert(find(tree, "AAA") != NULL);
    assert(find(tree, "ZZZ") != NULL);
    assert(strcmp(tree->root->code, "ZZZ") == 0);

    freeAVL(tree);
}

void testInterface(void)
{
    printf("[RUNNING] TEST Interface\n");
    char* testFile = "test_airports.txt";

    FILE* fp = fopen(testFile, "w");
    fprintf(fp, "LED:Pulkovo\n");
    fprintf(fp, "KGD:Khrabrovo\n");
    fclose(fp);

    AVL* tree = load(testFile);
    assert(tree != NULL);
    assert(strcmp(find(tree, "LED"), "Pulkovo") == 0);
    assert(strcmp(find(tree, "KGD"), "Khrabrovo") == 0);

    tree = add(tree, "AER:Sochi International");
    assert(strcmp(find(tree, "AER"), "Sochi International") == 0);

    char* outputFile = "test_airports_output.txt";
    save(tree, outputFile);
    freeAVL(tree);

    AVL* tree2 = load(outputFile);
    assert(tree2 != NULL);
    assert(find(tree2, "LED") != NULL);
    assert(find(tree2, "AER") != NULL);

    freeAVL(tree2);
    remove(testFile);
    remove(outputFile);
}

void runTests(void)
{
    printf("[START] Running test...\n");
    testInsertAndFind();
    testAVLBalance();
    testSimpleDeletion();
    testTwoChildDeletion();
    testInterface();
    printf("[SUCCESS] All checks passed!\n");
}
