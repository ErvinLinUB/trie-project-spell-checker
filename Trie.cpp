#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    
    TrieNode() {
        isEndOfWord = false;
    }
};

class Trie {
private:
    TrieNode* root;
    
    bool deleteHelper(TrieNode* current, const string& word, int index) {
        if (index == word.length()) {
            if (!current->isEndOfWord) {
                return false;
            }
            current->isEndOfWord = false;
            return current->children.empty();
        }
        
        char ch = word[index];
        if (current->children.find(ch) == current->children.end()) {
            return false;
        }
        
        TrieNode* nextNode = current->children[ch];
        bool shouldDelete = deleteHelper(nextNode, word, index + 1);
        
        if (shouldDelete) {
            delete nextNode;
            current->children.erase(ch);
            return current->children.empty() && !current->isEndOfWord;
        }
        
        return false;
    }

public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(const string& word) {
        TrieNode* current = root;
        
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        
        current->isEndOfWord = true;
    }
    
    bool search(const string& word) {
        TrieNode* current = root;
        
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                return false;
            }
            current = current->children[ch];
        }
        
        return current->isEndOfWord;
    }
    
    bool startsWith(const string& prefix) {
        TrieNode* current = root;
        
        for (char ch : prefix) {
            if (current->children.find(ch) == current->children.end()) {
                return false;
            }
            current = current->children[ch];
        }
        
        return true;
    }
    
    bool remove(const string& word) {
        return deleteHelper(root, word, 0);
    }
    
    // Simple display function for testing
    void display() {
        cout << "Trie contents: ";
        displayHelper(root, "");
        cout << endl;
    }
    
private:
    void displayHelper(TrieNode* node, string currentWord) {
        if (node->isEndOfWord) {
            cout << currentWord << " ";
        }
        
        for (auto& pair : node->children) {
            displayHelper(pair.second, currentWord + pair.first);
        }
    }
};

// Test code in main
int main() {
    Trie trie;
    
    cout << "=== Testing Trie Operations ===" << endl;
    
    // Test insert
    cout << "\n1. Inserting words..." << endl;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("banana");
    trie.insert("bat");
    trie.insert("ball");
    trie.display();
    
    // Test search
    cout << "\n2. Testing search..." << endl;
    cout << "Search 'apple': " << (trie.search("apple") ? "Found" : "Not found") << endl;
    cout << "Search 'app': " << (trie.search("app") ? "Found" : "Not found") << endl;
    cout << "Search 'ap': " << (trie.search("ap") ? "Found" : "Not found") << endl;
    cout << "Search 'orange': " << (trie.search("orange") ? "Found" : "Not found") << endl;
    
    // Test prefix search
    cout << "\n3. Testing prefix search..." << endl;
    cout << "Starts with 'ap': " << (trie.startsWith("ap") ? "Yes" : "No") << endl;
    cout << "Starts with 'ba': " << (trie.startsWith("ba") ? "Yes" : "No") << endl;
    cout << "Starts with 'or': " << (trie.startsWith("or") ? "Yes" : "No") << endl;
    
    // Test delete
    cout << "\n4. Testing delete..." << endl;
    cout << "Delete 'app': " << (trie.remove("app") ? "Success" : "Failed") << endl;
    cout << "Search 'app' after delete: " << (trie.search("app") ? "Found" : "Not found") << endl;
    cout << "Search 'apple' after deleting 'app': " << (trie.search("apple") ? "Found" : "Not found") << endl;
    
    cout << "Delete 'banana': " << (trie.remove("banana") ? "Success" : "Failed") << endl;
    cout << "Search 'banana' after delete: " << (trie.search("banana") ? "Found" : "Not found") << endl;
    
    // Show final state
    cout << "\n5. Final trie contents:" << endl;
    trie.display();
    
    // Additional test cases
    cout << "\n6. Additional tests..." << endl;
    trie.insert("cat");
    trie.insert("car");
    trie.insert("card");
    cout << "After inserting cat, car, card:" << endl;
    trie.display();
    
    cout << "Search 'car': " << (trie.search("car") ? "Found" : "Not found") << endl;
    cout << "Search 'card': " << (trie.search("card") ? "Found" : "Not found") << endl;
    
    return 0;
}