class TrieNode {
	public:
	unordered_map<char, TrieNode*> child;
	int val;
	bool isEnd;
	TrieNode() {
		val = 0;
		isEnd=false;
	}
};
class Trie {
	public:
	TrieNode* root;
	Trie() {
		root = new TrieNode();
	}
	void insert(string word){
	    // To hold the value of root
	    TrieNode* current = root;
	
	    // To hold letters of the word
	    char s;
	
	    // Traverse through strings in list
	    for (int i = 0; i < word.length(); i++) {
	        s = word[i];
	        // If s is not present in the character field of current node
	        if (current->child.find(s) == current->child.end()) {
	            // Get new node
	            TrieNode* newNode = new TrieNode();
	            // Insert s in character field of current node with reference to node p
	            (current->child)[s] = newNode;
	        }
	
	        // Go to next node
	        current = (current->child)[s];
	    }
	    current->isEnd = true;
	}
	
	// Function to count the number of words in trie with given prefix
	int query(string prefix){
	
	    TrieNode* current = root;
	    char s;
	
	    // Initialize the ans = 0
	    int ans = 1;
	
	    for (int i = 0; i < prefix.size(); i++) {
	        s = prefix[i];
	
	        // If the complete prefix isnot present in the trie
	        if (current->child.find(s) == current->child.end()) {
	
	            // Make ans 0 and break out of loop
	            ans = 0;
	            break;
	        }
	
	        // Go to next node
	        current = (current->child)[s];
	    }
		if(current->isEnd == false)
			ans=0;
	    return ans;
	}	
};
