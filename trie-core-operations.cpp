#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    
    // Constructor
    TrieNode() {
        isEndOfWord = false;
    }
};

// Insert a word into the trie
void insert(TrieNode* root, const string& word) {
    TrieNode* current = root;
    
    for (char c : word) {
        // If character doesn't exist, create new node
        if (current->children.find(c) == current->children.end()) {
            current->children[c] = new TrieNode();
        }
        // Move to the next node
        current = current->children[c];
    }
    
    // Mark the end of the word
    current->isEndOfWord = true;
}

// Search for a word in the trie
bool search(TrieNode* root, const string& word) {
    TrieNode* current = root;
    
    for (char c : word) {
        // If character doesn't exist, word is not in trie
        if (current->children.find(c) == current->children.end()) {
            return false;
        }
        // Move to the next node
        current = current->children[c];
    }
    
    // Return true only if we reached the end of a word
    return current->isEndOfWord;
}

// Helper function for deletion (recursive)
bool deleteHelper(TrieNode* current, const string& word, int index) {
    if (index == word.length()) {
        // If we're at the end of the word
        if (!current->isEndOfWord) {
            return false; // Word doesn't exist
        }
        current->isEndOfWord = false;
        
        // If node has no children, it can be deleted
        return current->children.empty();
    }
    
    char c = word[index];
    // If character doesn't exist, word is not in trie
    if (current->children.find(c) == current->children.end()) {
        return false;
    }
    
    TrieNode* nextNode = current->children[c];
    bool shouldDeleteChild = deleteHelper(nextNode, word, index + 1);
    
    if (shouldDeleteChild) {
        // Delete the child node
        delete nextNode;
        current->children.erase(c);
        
        // If current node has no other children and is not end of another word
        return current->children.empty() && !current->isEndOfWord;
    }
    
    return false;
}

// Delete a word from the trie
bool deleteWord(TrieNode* root, const string& word) {
    return deleteHelper(root, word, 0);
}