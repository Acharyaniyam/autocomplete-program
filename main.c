#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 256

typedef struct item{
  char *word;
  int weight;
}Item;

void swap(Item *a, Item *b) {
    //swapping the elements in a and b using t as a temporary variable
    Item t = *a;
    *a = *b;
    *b = t;
}

int partitionByWord(Item *items, int start, int stop) {
    int pivotindex = (rand() % (stop - start)) + start;
    swap (&items[pivotindex], &items[stop]);

    char *pivot = items[stop].word;
    int i = (start - 1);

    for (int j = start; j < stop; j++) {
        if (strcmp(items[j].word, pivot) < 0) {
            i++;
            swap(&items[i], &items[j]);
        }
    }
    swap(&items[i + 1], &items[stop]);
    return (i + 1);
}

void quickSORTByWord(Item *items, int start, int stop) {

    if (start < stop) {
        int p = partitionByWord(items, start, stop);

        quickSORTByWord(items, start, p-1);
        quickSORTByWord(items, p + 1, stop);
    }
}

int partitionByWeight(Item * items, int start, int stop){
    //randomize the pivot
    int pivotindex = (rand() % (stop - start)) + start;
    swap (&items[pivotindex], &items[stop]);

    int pivot = items[stop].weight;
    int i = (start - 1);

    for (int j = start; j < stop; j++){
        if (items[j].weight > pivot){
            i++;
            swap(&items[i], &items[j]);
        }
    }
    swap(&items[i + 1], &items[stop]);
    return (i+1);
}

void quickSORTByWeight(Item *items, int start, int stop) {
    if (start < stop) {
        int p = partitionByWeight(items, start, stop);

        quickSORTByWeight(items, start, p - 1);
        quickSORTByWeight(items, p + 1, stop);
    }
}


void sortItems(Item *items, int itemCount) {
    //Using the above quick sort to sort the knowledge base in order
    quickSORTByWord(items, 0, itemCount - 1);
}

void sortByWeight(Item *items, int itemCount) {
    // The sortByWeight function now uses quicksort with a randomized pivot to sort items by their weights in descending order.
    quickSORTByWeight(items, 0, itemCount - 1);
}

int binarySearch(Item *items, int itemCount, const char *query) {
    int left = 0, right = itemCount - 1; // inititalize the left and right pointers  forr the BinarySearch
    //
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strncmp(items[mid].word, query, strlen(query));
        if (cmp == 0) {
            // Move left to find the first occurrence
            while (mid > 0 && strncmp(items[mid - 1].word, query, strlen(query)) == 0) {
                mid--;
            }
            return mid;
        }
        if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

void searchSuggest(Item *items, int itemCount, char **searchQueries, int searchCount) {
    //This loop iterates over each query substring in the searchQueries array
    for (int i = 0; i < searchCount; i++) {
        printf("Query word:%s\n", searchQueries[i]);
        //This initializes a flag to track if any suggestions are found for the current query.
        int found = 0;
        Item *suggestions = NULL;
        int suggestionCount = 0;
        //calls the 'binarySearch' function to find the starting index of items that match the current query substring
        int start = binarySearch(items, itemCount, searchQueries[i]);
        if (start != -1) {
            // Collect all matches starting from the index given by the binary search
            for (int j = start; j < itemCount && strncmp(items[j].word, searchQueries[i], strlen(searchQueries[i])) == 0; j++) {
                suggestionCount++;
                //resizes the suggestions array to accommodate the new suggestion
                suggestions = realloc(suggestions, suggestionCount * sizeof(Item));
                //adds the current item to the suggestions array
                suggestions[suggestionCount - 1] = items[j];
            }

            //  in descending order
            sortByWeight(suggestions, suggestionCount);
            for (int k = 0; k < suggestionCount && k < 10; k++) {
                printf("%s %d\n", suggestions[k].word, suggestions[k].weight);
            }
            found = 1;
        }

        if (!found) {
            printf("No suggestion!\n");
        }
        //frees the memory allocated to suggestions
        free(suggestions);
    }
}

int main(int argc, char **argv) {
    char *dictionaryFilePath = argv[1]; //this keeps the path to dictionary file
    char *queryFilePath = argv[2]; //this keeps the path to the file that keeps a list of query wrods, 1 query per line
    int wordCount=0; //this variable will keep a count of words in the dictionary, telling us how much memory to allocate
    int queryCount=0; //this variable will keep a count of queries in the query file, telling us how much memory to allocate for the query words
    
    ////////////////////////////////////////////////////////////////////////
    ///////////////////////// read dictionary file /////////////////////////
    ////////////////////////////////////////////////////////////////////////

    FILE *fp = fopen(dictionaryFilePath, "r");
    char *line = NULL; //variable to be used for line counting
    size_t lineBuffSize = 0; //variable to be used for line counting
    ssize_t lineSize; //variable to be used for line counting
    
    //check if the file is accessible, just to make sure...
    if(fp == NULL){
        fprintf(stderr, "Error opening file:%s\n",dictionaryFilePath);
        return -1;
    }

    //First, let's count number of lines. This will help us know how much memory to allocate
    while((lineSize = getline(&line,&lineBuffSize,fp)) !=-1)
    {
        wordCount++;
    }

    //Printing wordCount for debugging purposes. You can remove this part from your submission.
    //printf("%d\n",wordCount);
    
    /////////////////PAY ATTENTION HERE/////////////////
    //This might be a good place to allocate memory for your data structure, by the size of "wordCount"
    ////////////////////////////////////////////////////
    Item *items = malloc(wordCount * sizeof(Item));
    if (items == NULL) {
        printf("Error allocating memory for items\n");
        return -1;
    }
    //Read the file once more, this time to fill in the data into memory
    fseek(fp, 0, SEEK_SET);// rewind to the beginning of the file, before reading it line by line.
    char word[BUFSIZE]; //to be used for reading lines in the loop below
    int weight;
    for(int i = 0; i < wordCount; i++)
    {
        fscanf(fp, "%s %d\n",word,&weight);
        //Let's print them to the screen to make sure we can read input, for debugging purposes. You can remove this part from your submission.
        //printf("%s %d\n",word,weight);

        /////////////////PAY ATTENTION HERE/////////////////
        //This might be a good place to store the dictionary words into your data structure
        ////////////////////////////////////////////////////
        items[i].word = strdup(word);
        items[i].weight = weight;
    }
    //close the input file
    fclose(fp);

    ////////////////////////////////////////////////////////////////////////
    ///////////////////////// read query list file /////////////////////////
    ////////////////////////////////////////////////////////////////////////
    fp = fopen(queryFilePath, "r");
        
    //check if the file is accessible, just to make sure...
    if(fp == NULL){
        fprintf(stderr, "Error opening file:%s\n",queryFilePath);
        return -1;
    }

    //First, let's count number of queries. This will help us know how much memory to allocate
    while((lineSize = getline(&line,&lineBuffSize,fp)) !=-1)
    {
        queryCount++;
    }
    free(line); //getline internally allocates memory, so we need to free it here so as not to leak memory!!

    //Printing line count for debugging purposes. You can remove this part from your submission.
    //printf("%d\n",queryCount);

    /////////////////PAY ATTENTION HERE/////////////////
    //This might be a good place to allocate memory for storing query words, by the size of "queryCount"
    ////////////////////////////////////////////////////
    char **queries = malloc(queryCount * sizeof(char *));
    if (queries == NULL) {
        printf("Error allocating memory for queries\n");
        return -1;
    }
    fseek(fp, 0, SEEK_SET);// rewind to the beginning of the file, before reading it line by line.
    for(int i = 0; i < queryCount; i++)
    {
        fscanf(fp, "%s\n",word);
        //Let's print them to the screen to make sure we can read input, for debugging purposes. You can remove this part from your submission.
        //printf("%s\n",word);
        queries[i] = strdup(word);
        /////////////////PAY ATTENTION HERE/////////////////
        //This might be a good place to store the query words in a list like data structure
        ////////////////////////////////////////////////////   
    }
    //close the input file
    fclose(fp);

    ////////////////////////////////////////////////////////////////////////
    ///////////////////////// reading input is done ////////////////////////
    ////////////////////////////////////////////////////////////////////////
    
    //Now it is your turn to do the magic!!!
    //do search/sort/print, whatever you think you need to do to satisfy the requirements of the assignment!
    //loop through the query words and list suggestions for each query word if there are any
    //don't forget to free the memory before you quit the program!
    sortItems(items, wordCount);
    searchSuggest(items, wordCount, queries, queryCount);
    // Free allocated memory
    for (int i = 0; i < wordCount; i++) {
        free(items[i].word);
    }
    free(items);
    for (int i = 0; i < queryCount; i++) {
        free(queries[i]);
    }
    free(queries);
    //OUTPUT SPECS:
    // use the following if no word to suggest: printf("No suggestion!\n");
    // use the following to print a single line of outputs (assuming that the word and weight are stored in variables named word and weight, respectively): 
    //printf("%s %d\n",word,weight);
    // if there are more than 10 outputs to print, you should print the top 10 weighted outputs.
    
    return 0;
}