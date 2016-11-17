//
//  main.cpp
//  Homework 1
//
//  Created by Jack Noren on 2/20/14.
//  Copyright (c) 2014 Jack Noren. All rights reserved.
//


#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

//*This makes it easy to count.
struct Word
{
    string word;
    int amount;
};
//*
//need this function for the sort method of the algorithms class to work.
// this is why we use the book and a.amount with b.amount
bool compareByAmount (const Word &a, const Word &b)

{
    return a.amount > b.amount;
};
// *
// These are my Void functions that I use at the bottom. I must state them
// before using them in my main.
void countDistincts(string& word, vector<Word>& distinctWords);

void holyCleanse(string& word);


int main()
{
    //*
    int totalCountOfWords=0;
    vector <Word> distinct_words;
    string currentWord;
    
    
    ifstream infile;
    
    //add your text file here. Go to file, and look up information for Mac. (right click)
    infile.open("/Users/Jack/Dev/HolyCleanse/TestFile.txt");
    
   
    if(infile.fail())
    {
        cout<<"File could not be found. Choose enter to quit program";
        exit(33);
    }
    
    cout << "One moment. I am counting..." << "\n\n";
    
    
    while(infile.good())
    {
        infile>> currentWord;
        holyCleanse(currentWord);
        
        //sarah said to type string with .empty so that you dont count " - " in the text
        if(!currentWord.empty())
        {
            Word varName;
            varName.word = currentWord;
            varName.amount = 1;
            countDistincts(currentWord, distinct_words);
            totalCountOfWords++;
        }
        
    }
    // These are just my normal cout statements in the beginning
    cout << "Total Word Count: " << totalCountOfWords << "\n";
    cout << "Distinct words: " << distinct_words.size() << "\n\n";
    
    
    cout << "Enter the number of most frequent words to view: ";
    
    int wordsToDisplay;
    cin >> wordsToDisplay;
    
    
    
    cout << "Sorting words by frequency occured... please wait" << "\n\n";
    
    //using the sort method in the alogirthms library which we included above the method will sort
    //the entire vector by greatest number of occurances to least number of occurances
    
    sort(distinct_words.begin(), distinct_words.end(), compareByAmount);
    
    //we took in a variable above wordsToDisplay so while we iterate through the list of distinct words
    //we only need to print out the number that was inputted by the user
    for(int i = 0; i < wordsToDisplay; i++)
        
    {
        
        cout << distinct_words.at(i).word << ": "<< distinct_words.at(i).amount << "\n";
        
    }
    
    cout <<endl<< "Enter the number of most frequent words to view: ";
    //again taking in a variable of wordsToDisplay
    cin >> wordsToDisplay;
    
    
    
    cout << "Enter the minimum number of letters in the words: ";
    //now we need a minimum number of letters in the word to display
    int lengthToDisplay;
    
    cin >> lengthToDisplay;
    
    
    
    int count = 0;
    //counter is used to only display the number of words that we want to display
    for(int i = 0; i < distinct_words.size(); i++)
        //iterate through the entire list
    {
        
        if(distinct_words.at(i).word.size() >= lengthToDisplay)
            //if the words lenght we come across is greater than the inputted min length from the user we display it
        {
            
            cout << distinct_words.at(i).word << ": " << distinct_words.at(i).amount << "\n";
            //increase the count so once we get to the requested number of words we can stop
            count++;
        }
        //if the count gets to the requested nubmer of words to display then we can break out of this for loop
        //if we dont do this it will iterate through the entire list and not stop once we get the requested number
        if(count == wordsToDisplay)
            
        {
            //I need to put this break because when I tried to run it before
            //it was printing out all the words, and not stopping where I stated
            //the number of most frequent words amount. Easy fix with a break
            break;
            
        }
        
    }
    
    printf("\nEnter a frequency to find every occurrence of that frequency: ");
    int frequency;
    cin >> frequency;
    //same logic as above but instead of checking to see if the lenght is a minimum number of characters
    //we just check to see if it occurs a certain number of times
    //probably a better way of doing this, but this is will work.
    for(int i = 0; i < distinct_words.size(); i++)
    {
        
        if(distinct_words.at(i).amount == frequency)
            
        {
            
            cout << distinct_words.at(i).word << "\n";
            
        }
        
    }
    
    // Seems dumb but I'm actually not sure how to send this program.
    // I put return 0, and thought thats how I end this program.
    // I know I'm missing some small key part to this code for this
    printf("\nPress any key you would like to end this program\n");
    
    return 0;
    
}



//---------------------------------------
//Functions
//---------------------------------------



void countDistincts(string& word, vector<Word>& distinctWords)
{   //if this vector is empty then we are going to just add the first word/ this is pretty much automatic
    bool retVal = false;
    
    if(distinctWords.size() == 0)
    {   //this is just going to create the struct
        Word tempWord;
        tempWord.amount = 1;
        tempWord.word = word;
        //here we are just going to add to the vector
        distinctWords.push_back(tempWord);
    }
    //we are otherwise going to just iterate through this entire list and check to see if
    //the word is already inside it. If it is than we can just increment the amount.
    for(int i = 0; i < distinctWords.size(); i++)
    {
        if(word == distinctWords.at(i).word)
        {
            distinctWords.at(i).amount++;
            retVal = true;
            break;
        }
    }
    //otherwise this retVal is still false and we need to add it to the vector
    if(retVal == false)
    {
        
        Word tempWord;
        tempWord.amount = 1;
        tempWord.word = word;
        
        distinctWords.push_back(tempWord);
    }
    
}

//this is just my function that goes through and basically strips the bad characters we dont need or want
//or can't use away. We can use a for loop
void holyCleanse(string& input)
{
    for(int i=0; i<input.length(); i++)
    {
        //If capital letter, make lowercase
        if(input[i] >= 'A'   &&   input[i] <='Z')
            input[i]=input[i]+32;
        // Once you have set A-Z above you need to use the isalnum
        // learned about this in S.I.
        if(!isalnum(input[i]))
        {   // I tried doing the loop that the professor showed us in class
 
            // Would like to go back and rework this part.
            input.erase(i,1);
            i=i-1;
        }
        
    }
    
}
