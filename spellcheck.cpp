#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "trie-core-operations.cpp"  // include existing trie core operations
using namespace std;

// Load dictionary into Trie
void loadDictionary(TrieNode* root, const string& filename) {
    ifstream file(filename);
    string word;
    while (file >> word) {
        // Convert to lowercase
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        insert(root, word); // use function from trie-core-operations.cpp
    }
}

// Generate words 1 edit distance away
vector<string> edits1(const string& word) {
    vector<string> results;
    string letters = "abcdefghijklmnopqrstuvwxyz";

    // Deletion
    for (size_t i = 0; i < word.size(); i++) {
        string s = word;
        s.erase(i, 1);
        results.push_back(s);
    }

    // Insertion
    for (size_t i = 0; i <= word.size(); i++) {
        for (char c : letters) {
            string s = word;
            s.insert(i, 1, c);
            results.push_back(s);
        }
    }

    // Replacement
    for (size_t i = 0; i < word.size(); i++) {
        for (char c : letters) {
            string s = word;
            s[i] = c;
            results.push_back(s);
        }
    }

    // Transposition
    for (size_t i = 0; i < word.size() - 1; i++) {
        string s = word;
        swap(s[i], s[i + 1]);
        results.push_back(s);
    }

    return results;
}

// Spell check
vector<string> spellCheck(TrieNode* root, const string& word) {
    vector<string> suggestions;
    if (search(root, word)) { // from trie-core-operations.cpp
        suggestions.push_back(word);
        return suggestions;
    }

    vector<string> candidates = edits1(word);
    for (const string& w : candidates)
        if (search(root, w))
            suggestions.push_back(w);

    return suggestions;
}

int main() {
    TrieNode* root = new TrieNode();

    loadDictionary(root, "word.txt");
    cout << "Dictionary loaded." << endl;

    while (true) {
        string input;
        cout << "\nEnter a word (or 'exit' to quit): ";
        cin >> input;
        if (input == "exit") break;

        // Convert input to lowercase
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        vector<string> suggestions = spellCheck(root, input);
        if (suggestions.empty())
            cout << "No suggestions found." << endl;
        else {
            cout << "Did you mean: ";
            for (const auto& w : suggestions) cout << w << " ";
            cout << endl;
        }
    }

    return 0;
}