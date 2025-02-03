#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct HuffmanNode {
    char data;
    int frequency;
    struct HuffmanNode* left;
    struct HuffmanNode* right;
};

struct MinHeap {
    int size;
    int capacity;
    struct HuffmanNode** array;
};

void buildHuffmanCodes(struct HuffmanNode* root, char* currentCode, char** huffmanCodes);

struct HuffmanNode* createNode(char data, int frequency) 
{
   //Type your code
   struct HuffmanNode* temp= (struct HuffmanNode*)malloc(sizeof(struct HuffmanNode));
   temp->data=data;
   temp->frequency=frequency;
   temp->left=temp->right=NULL;
   return temp;
}

struct HuffmanNode* createMinHeapNode(char data, int frequency) {
    return createNode(data, frequency);
}

struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct HuffmanNode**)malloc(capacity * sizeof(struct HuffmanNode*));
    return minHeap;
}

void swapMinHeapNodes(struct HuffmanNode** a, struct HuffmanNode** b) {
    struct HuffmanNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isSizeOne(struct MinHeap* minHeap) {
    return minHeap->size == 1;
}

struct HuffmanNode* extractMin(struct MinHeap* minHeap) {
    struct HuffmanNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct HuffmanNode* node) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && node->frequency < minHeap->array[(i - 1) / 2]->frequency) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

struct HuffmanNode* buildHuffmanTree(char data[], int frequency[], int size) 
{
   //Type your code
   struct HuffmanNode *left,*right,*top;
   struct MinHeap *minHeap=createMinHeap(size);
   for(int i=0;i<size;i++)
   {
       struct HuffmanNode* temp=createMinHeapNode(data[i],frequency[i]);
       insertMinHeap(minHeap,temp);
   }
   while(!isSizeOne(minHeap))
   {
       left=extractMin(minHeap);
       right=extractMin(minHeap);
       top=createNode('$',left->frequency+right->frequency);
       top->left=left;
       top->right=right;
       insertMinHeap(minHeap,top);
   }
   return extractMin(minHeap);
}

void printHuffmanCodes(struct HuffmanNode* root, char* currentCode, char** huffmanCodes) {
    if (root->left) {
        strcat(currentCode, "0");
        printHuffmanCodes(root->left, currentCode, huffmanCodes);
        currentCode[strlen(currentCode) - 1] = '\0'; 
    }
    if (root->right) {
        strcat(currentCode, "1");
        printHuffmanCodes(root->right, currentCode, huffmanCodes);
        currentCode[strlen(currentCode) - 1] = '\0';
    }
    if (!root->left && !root->right) {
        printf("%c: %s\n", root->data, currentCode);
        huffmanCodes[root->data] = strdup(currentCode);
    }
}

void decodeMessage(char encodedMessage[], struct HuffmanNode* root, char decodedMessage[]) 
{
    int index = 0;
    struct HuffmanNode* currentNode = root;
    char* output = decodedMessage;

    for (int i = 0; encodedMessage[i] != '\0'; i++) 
    {
        if (encodedMessage[i] == '0') {
            currentNode = currentNode->left;
        } else if (encodedMessage[i] == '1') {
            currentNode = currentNode->right;
        }

        // If a leaf node is reached
        if (!currentNode->left && !currentNode->right) {
            *output = currentNode->data; // Decode character
            output++;
            currentNode = root; // Reset to root for the next character
        }
    }
    *output = '\0'; // Null-terminate the decoded string
}


int main(void) 
{
    int numCharacters;
    
    scanf("%d", &numCharacters);
    
    char data[numCharacters];
    int frequency[numCharacters];
    
    for (int i = 0; i < numCharacters; ++i) 
    {
        scanf(" %c", &data[i]);
        scanf("%d", &frequency[i]);
    }

    struct HuffmanNode* root = buildHuffmanTree(data, frequency, numCharacters);

    char* huffmanCodes[256] = {0};
    char currentCode[256] = {0};
    printHuffmanCodes(root, currentCode, huffmanCodes);

    char message[256];
    scanf(" %[^\n]", message);
    
    char decodedMessage[256] = {0};
    decodeMessage(message, root, decodedMessage);
    printf("Decoded: %s\n", decodedMessage);

    for (int i = 0; i < 256; i++) {
        if (huffmanCodes[i]) free(huffmanCodes[i]);
    }

    return 0;
}
