#ifndef __HUFFMAN_CODING_H__
#define __HUFFMAN_CODING_H__

#include <string.h>
#include <stdlib.h>

#define MAX_TREE_HT 1000

typedef struct MinHeapNode {
    char data;
    int freq;
    struct MinHeapNode *left, *right;
} MinHeapNode;

typedef struct {
    int size;     // current size of min heap
    int capacity; // capacity of min heap
    MinHeapNode **array;
} MinHeap;

MinHeapNode *createMinHeapNode(char data, int freq) {
    MinHeapNode *ret = (MinHeapNode *)malloc(sizeof(MinHeapNode));
    ret->data = data;
    ret->freq = freq;
    ret->left = ret->right = NULL;
    return ret;
}

MinHeap *createMinHeap(int capacity) {
    MinHeap *ret = (MinHeap *)malloc(sizeof(MinHeap));
    MinHeapNode **array = (MinHeapNode **)malloc(capacity * sizeof(MinHeapNode *));

    ret->size = 0;
    ret->capacity = capacity;
    ret->array = array;

    return ret;
}

void swapMinHeapNode(MinHeapNode **a, MinHeapNode **b) { 
    MinHeapNode* t = *a; 
    *a = *b; 
    *b = t; 
    return;
} 

void minHeapify(MinHeap *minHeap, int idx) {
    int smallest = idx; 
    int left = 2 * idx + 1; 
    int right = 2 * idx + 2; 
  
    if (
        left < minHeap->size && 
        minHeap->array[left]->freq < minHeap->array[smallest]->freq
    ) smallest = left; 
  
    if (
        right < minHeap->size && 
        minHeap->array[right]->freq < minHeap->array[smallest]->freq
    ) smallest = right; 
  
    if (smallest != idx) { 
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]); 
        minHeapify(minHeap, smallest); 
    } 
}

MinHeapNode* extractMin(MinHeap *minHeap) { 
  
    MinHeapNode* temp = minHeap->array[0]; 
    minHeap->array[0] = minHeap->array[minHeap->size - 1]; 
  
    --minHeap->size; 
    minHeapify(minHeap, 0); 
  
    return temp; 
} 

void insertMinHeap(MinHeap *minHeap, MinHeapNode *minHeapNode) { 
  
    ++minHeap->size; 
    int i = minHeap->size - 1; 
  
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) { 
  
        minHeap->array[i] = minHeap->array[(i - 1) / 2]; 
        i = (i - 1) / 2; 
    } 
  
    minHeap->array[i] = minHeapNode; 
    
    return;
}

void buildMinHeap(MinHeap* minHeap) { 
    int n = minHeap->size - 1; 
    int i; 
    
    for (i = (n - 1) / 2; i >= 0; --i) {
        minHeapify(minHeap, i);
    }

    return; 
} 

MinHeap *createAndBuildMinHeap(char data[], int freq[], int size) {
    MinHeap *ret = createMinHeap(size);
    
    for (int i = 0; i < size; i++) {
        ret->array[i] = createMinHeapNode(data[i], freq[i]);
    }
    ret->size = size;
    buildMinHeap(ret);

    return ret;
}

MinHeapNode *buildHuffmanTree(char data[], int freq[], int size) {
    MinHeapNode *left, *right, *top;
    MinHeap *heap = createAndBuildMinHeap(data, freq, size);

    while (heap->size != 1) {
        left = extractMin(heap);
        right = extractMin(heap);

        top = createMinHeapNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(heap, top);
    }

    return extractMin(heap);
}

int isLeaf(MinHeapNode *root) { 
    return !(root->left) && !(root->right); 
} 

void printArray(int array[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", array[i]);
    }
    printf("\n");
    return;
}

void printCodes(MinHeapNode *root, int array[], int top) {
    if (root->left) {
        array[top] = 0;
        printCodes(root->left, array, top + 1);
    }

    if (root->right) {
        array[top] = 1;
        printCodes(root->right, array, top + 1);
    }

    if (isLeaf(root)) {
        printf("%c: ", root->data);
        printArray(array, top);
    }

    return;
}

void printHuffmanCodes(char data[], int freq[], int size) {
    MinHeapNode *root = buildHuffmanTree(data, freq, size);
    
    int array[MAX_TREE_HT];
    int top = 0;
    printCodes(root, array, top);
    
    return;
}


typedef struct {
    int size;
    int bits[20];
} Coding;

Coding huffmanTable[256];

void copyArray(int *source, int *destination, int n) {
    for (int i = 0; i < n; i++) {
        destination[i] = source[i];
    }
    return;
}

void createHuffmanEndcoding(MinHeapNode *root, int array[], int top) {
    
    if (root->left) {
        array[top] = 0;
        createHuffmanEndcoding(root->left, array, top + 1);
    }

    if (root->right) {
        array[top] = 1;
        createHuffmanEndcoding(root->right, array, top + 1);
    }

    if (isLeaf(root)) {
        char endCodeChar = root->data;
        huffmanTable[endCodeChar].size = top;

        int *bitArray = huffmanTable[endCodeChar].bits;
        copyArray(array, bitArray, top);
    }
    
    return;
}

MinHeapNode *createHuffmanTable(char data[], int freq[], int size) {
    MinHeapNode *root = buildHuffmanTree(data, freq, size);

    int array[MAX_TREE_HT];
    int top = 0;
    createHuffmanEndcoding(root, array, top);

    return root;
}

void printHuffmanEndCoding(Coding huffmanCode) {
    for (int i = 0; i < huffmanCode.size; i++) {
        printf("%d", huffmanCode.bits[i]);
    }
    return;
}



long countCharInFile(FILE *fp) {
    long nchars;
    fseek(fp, 0, SEEK_END);
    nchars = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return nchars;
}

FILE *openFileWithCatchException(char *fn) {
    FILE *fp = fopen(fn, "rb");
    if (fp == NULL) {
        printf("Can not open file!");
        exit(0);
    }
    return fp;
}

void generateDataForHuffmanAlgo(char *buffer, long nchars, char data[], int freq[], int *size) {
    
    char countOf[127] = { 0 };
    for (int i = 0; i < nchars; i++) {
        char ch = buffer[i];
        countOf[ch]++;
    }

    int _size = 0;
    for (char i = 0; i < 127; i++) {
        if (countOf[i] > 0) {
            freq[_size] = countOf[i];
            data[_size] = i;
            _size++; 
        }
    }
    *size = _size;
    return; 
}

void createHuffmanEndCodedFile(char *bufferIn, long nchars, char *fnOut) {
    FILE *fp = fopen(fnOut, "w");
    fprintf(fp, "HM ");
    for (long i = 0; i < nchars; i++) {
        char ch = bufferIn[i];
        int size = huffmanTable[ch].size;
        int *bits = huffmanTable[ch].bits;
        for (int j = 0; j < size; j++) {
            fprintf(fp, "%d", bits[j]);
        }
    }
    fclose(fp);
    return;
}

void huffmanEndCodingToFile(char *fnIn, char *fnOut) {
    FILE *fp = openFileWithCatchException(fnIn);
    long nchars = countCharInFile(fp);
    
    char *bufferIn = malloc(nchars + 1);
    if (bufferIn) {
        fread(bufferIn, 1, nchars, fp);
    }
    
    char data[127];
    int freq[127];
    int size;
    generateDataForHuffmanAlgo(bufferIn, nchars, data, freq, &size);

    createHuffmanTable(data, freq, size);
    createHuffmanEndCodedFile(bufferIn, nchars, fnOut);
    printHuffmanCodes(data, freq, size);
    
    fclose(fp);
    return;
}

MinHeapNode *createHuffmanTreeFromFile(char *fn) {
    FILE *fp = openFileWithCatchException(fn);
    long nchars = countCharInFile(fp);
    
    char *bufferIn = malloc(nchars + 1);
    if (bufferIn) {
        fread(bufferIn, 1, nchars, fp);
    }
    
    char data[127];
    int freq[127];
    int size;
    generateDataForHuffmanAlgo(bufferIn, nchars, data, freq, &size);
    MinHeapNode *huffmanTreeRoot = createHuffmanTable(data, freq, size);
    
    fclose(fp);
    return huffmanTreeRoot;
}

typedef MinHeapNode HuffmanTree;

int isHuffmanEndcodingFile(char *fn) {
    FILE *fp = fopen(fn, "r");
    if (fp == NULL) {
        printf("Can not open file");
    }
    char str[10];
    fscanf(fp, "%s ", str);
    fclose(fp);

    return strcmp(str, "HM") == 0;    
}

long countCharWithoutPrefixInFile(FILE *fp) {
    long nchars;
    fseek(fp, -3, SEEK_END);
    nchars = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return nchars;
}

char *readEndcodedString(FILE *fp, long nbits) {
    char *buffer = (char *)malloc(nbits);
    fscanf(fp, "%s ", buffer);
    fread(buffer, 1, nbits, fp);
    fclose(fp);
    return buffer;
}

char *decodingString(char *bufferIn, long nbits, HuffmanTree *root) {
    char *decodedStr = (char *)malloc(nbits);
    HuffmanTree *current = root;
    long index = 0;
    for (long i = 0; i < nbits; i++) {
        if (bufferIn[i] == '0')
            current = current->left;
        else 
            current = current->right;

        if (current->left == NULL && current->right == NULL) {
            decodedStr[index] = current->data;
            index++;
            current = root;
        } 
    }
    decodedStr[index] = '\0';
    return decodedStr;
}

char *huffmanDecodingToString(char *fn, HuffmanTree *root) {
    if (!isHuffmanEndcodingFile(fn)) return NULL;

    FILE *fp = openFileWithCatchException(fn);
    long nbits = countCharWithoutPrefixInFile(fp);
    char *bufferIn = readEndcodedString(fp, nbits);
    printf("\n %s", bufferIn);
    char *decodedString = decodingString(bufferIn, nbits, root);
    fclose(fp);
    return decodedString;
}

void printStringToFile(char *fn, char *decodedString) {
    FILE *fp = fopen(fn, "w+");
    if (fp == NULL) {
        printf("Can not open file\n");
        return;
    }
    fprintf(fp, "%s", decodedString);
    fclose(fp);
    return;
}

#endif