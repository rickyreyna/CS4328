/* Ricardo Reyna - rjr110
 * Due Date: 04/27/2020 - Assignment 4
 * Operating Systems - M/W 5:00 pm
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>

// Optimal looks into the future. Replace only the page that will not be used for the longest period of time in the future
// LRU. Looks into the past. Replace only the page that has not been used for the longest period of time in the past.

using namespace std;

void printFrame(int reference[], int dArray[], int indexCurrentRef, int frames);
void ranGenerateReferenceString(int reference[]);

int main(){
    int size = 20; // Size of String Reference
    int reference[size];
    int frames;
    int indexCurrentRef = 0;
    int indexLongestFrame = 0;
    int indexLongestRef = 0;
    bool flag = false;
    int optimalNumFaults = 0;
    int lruNumFaults = 0;
    int index = 0;
    queue<int> qFrames;

    cout << "The program will randomly generate the 20 reference strings. Type in the number of frames: " << endl;
    cin >> frames;

    int *dArray = new int[frames]{0}; // Initialize a dynamic array and sets all values to zero
    bool *dFlag = new bool[frames]{false}; // Flags for each page
    int *refArray = new int[frames]{0};

    ranGenerateReferenceString(reference);

    cout << endl << "The following numbers are all the randomly generated reference strings: ";
    for (int i = 0; i < 20; i++){
        cout << " " << reference[i] << " ";
    }
    cout<<endl<<endl;

    // AFTER THIS, THE OPTIMAL ALGORITHM BEGINS
    cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl
         << "The Optimal Algorithm begins after this." << endl
         << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    printFrame(reference, dArray, indexCurrentRef, frames);
    while((indexCurrentRef < size) && (reference[indexCurrentRef] !=  0)  ){
        // Checks if current frame has string reference in
        index = 0;
        while(index < frames && (reference[indexCurrentRef] !=  0)){
            // If the frame already has the string reference. No Page fault
            if(dArray[index] == reference[indexCurrentRef]){
                cout << "The current reference string to be placed is \"" << reference[indexCurrentRef] << "\"." << endl;
                cout << "Reference string is in the frame. No page-fault." << endl;
                printFrame(reference, dArray, indexCurrentRef, frames);
                ++indexCurrentRef;
                index = 0;
                continue;
            }
            // If frame is empty, add string reference. Page fault
            else if(dArray[index] == 0){
                dArray[index] = reference[indexCurrentRef];
                cout << "The current reference string to be placed is \"" << reference[indexCurrentRef] << "\"." << endl;
                cout << "The frame is not full. Therefore there is a page-fault." << endl;
                printFrame(reference, dArray, indexCurrentRef, frames);
                ++indexCurrentRef;
                ++optimalNumFaults;
                index = 0;
                continue;
            }
            ++index;
        }

        // Sets variables to search for page that wont be used in the longest period of time based on the future.
        flag = false;
        // Searches for page that wont be used in the longest period of time based on the future.
        for(int i = 0; i < frames; i++){
            if (flag == true) {
                break;
            }
            for (int j = indexCurrentRef; j <= size; j++){
                if (dArray[i] == reference[j] && dFlag[i] == false && (reference[indexCurrentRef] !=  0)){
                    refArray[i] = j;
                    dFlag[i]= true;
                    break;
                }
                else if(j == size && dFlag[i] == false && (reference[indexCurrentRef] !=  0)){
                    cout << "The current reference string to be placed is \"" << reference[indexCurrentRef] << "\"." << endl;
                    cout << "The frame #\"" << i << "\" that holds the reference string \"" << dArray[i] << "\" is not being used in the future, so it will be replaced. This creates a page-fault." << endl;
                    dArray[i] = reference[indexCurrentRef];
                    printFrame(reference, dArray, indexCurrentRef, frames);
                    ++indexCurrentRef;
                    ++optimalNumFaults;
                    flag = true;
                    break;
                }

            }

        }

        if(flag == false) {
            indexLongestRef = refArray[0];
            for(int i = 0; i < frames; i++){
                if(indexLongestRef <= refArray[i]){
                    indexLongestFrame = i;
                    indexLongestRef = refArray[i];
                }
                dFlag[i] = false; // Resets all flags
                refArray[i] = 0; // Resets tempArray
            }
            cout << "The current reference string to be placed is \"" << reference[indexCurrentRef] << "\"." << endl;
            cout << "The reference string " << "\"" << dArray[indexLongestFrame] << "\" which is on the frame #" << indexLongestFrame
                 << ", is currently the least used page. It will be replaced for the new reference string "
                 << "\"" << reference[indexCurrentRef] << "\". This means that there is a page-fault." << endl;
            dArray[indexLongestFrame] = reference[indexCurrentRef];
            printFrame(reference, dArray, indexCurrentRef, frames);
            ++indexCurrentRef;
            ++optimalNumFaults;
        }

    }

    // Resets everything
    indexCurrentRef = 0;
    indexLongestFrame = 0;
    indexLongestRef = 0;
    flag = false;
    for(int i = 0; i < frames; i++){
        dArray[i] = 0;
        refArray[i] = 0;
        dFlag[i] = false;
    }

    cout << endl << "The following numbers are all the randomly generated reference strings: ";
    for (int i = 0; i < 20; i++){
        cout << " " << reference[i] << " ";
    }
    cout<<endl<<endl;

    // AFTER THIS THE LRU ALGORITHM BEGINS
    cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl
         << "The LRU Algorithm begins after this." << endl
         << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    printFrame(reference, dArray, indexCurrentRef, frames);
    while((indexCurrentRef < size) && (reference[indexCurrentRef] !=  0)  ) {
        // Checks if current frame has string reference in
        index = 0;
        while (index < frames && (reference[indexCurrentRef] != 0)) {
            // If the frame already has the string reference. No Page fault
            if (dArray[index] == reference[indexCurrentRef] && (reference[indexCurrentRef] != 0)) {
                cout << "The current reference string to be placed is \"" << reference[indexCurrentRef] << "\"."
                     << endl;
                cout << "Reference string is in the frame. No page-fault." << endl;
                printFrame(reference, dArray, indexCurrentRef, frames);
                ++indexCurrentRef;
                indexLongestFrame = index;
                qFrames.pop();
                qFrames.push(indexLongestFrame);
                index = 0;
                continue;
            }
            // If frame is empty, add string reference. Page fault
            else if (dArray[index] == 0 && (reference[indexCurrentRef] != 0)) {
                cout << "The current reference string to be placed is \"" << reference[indexCurrentRef] << "\"."
                     << endl;
                cout << "The frame is not full. Therefore there is a page-fault." << endl;
                dArray[index] = reference[indexCurrentRef];
                printFrame(reference, dArray, indexCurrentRef, frames);
                ++indexCurrentRef;
                indexLongestFrame = index;
                qFrames.push(indexLongestFrame);
                ++lruNumFaults;
                index = 0;
                continue;
            }
            ++index;
        }

        if(indexCurrentRef >= size){
            break;
        }
        indexLongestFrame = qFrames.front();
        cout << "The current reference string to be placed is \"" << reference[indexCurrentRef] << "\"." << endl
             << "The frame that has not been used in the longest is #" << indexLongestFrame << " that holds the reference string \"" << dArray[indexLongestFrame]
             << "\". Since it has not being used in the longest time it will be replaced. This creates a page-fault." << endl;
        qFrames.pop();
        dArray[indexLongestFrame] = reference[indexCurrentRef];
        printFrame(reference, dArray, indexCurrentRef, frames);
        qFrames.push(indexLongestFrame);
        ++indexCurrentRef;
        ++lruNumFaults;
    }

    cout << endl << "The Optimal Algorithm has a total number of page faults of " << optimalNumFaults << endl
         << "The LRU Algorithm has a total number of page faults of " << lruNumFaults << endl << endl;

    delete [] dArray;
    delete [] dFlag;
    delete [] refArray;
    return 0;
}

// Prints out the state of current frame
void printFrame(int reference[], int dArray[], int indexCurrentRef, int frames){


    cout << "The frame currently looks like this: " << endl;
    for(int i = 0; i < frames; i++)
    {
       cout << "           -----\n"
               << "Frame #" << i <<"  |  " << dArray[i] << "  |\n";
    }
    cout << "           -----" << endl;

}

// Randomly Generates the Numbers of Reference String
void ranGenerateReferenceString(int reference[]){
    srand((unsigned) time(0));
    for (int i = 0; i < 20; i++) {
        reference[i] = (rand() % 5) + 1;
    }
}