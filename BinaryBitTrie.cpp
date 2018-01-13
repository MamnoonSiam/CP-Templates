// From github.com/RezwanArefin01/CodeTemplate/blob/master/Mex%20using%20Trie%20O(log%20Max).cpp
// Implement erase() function using another variable occ in node structure

struct node{
	node *ch[2]; int cnt; 
	node() {ch[0] = ch[1] = NULL, cnt = 0; } 
}root;

void insert(int x) {
	node *curr = &root; 
	for(int i = 20; i >= 0; i--) {
		int bit = (x >> i) & 1;
		if(curr -> ch[bit] == NULL) 
			curr -> ch[bit] = new node(); 
		curr -> ch[bit] -> cnt++;
		curr = curr -> ch[bit]; 
	}
}

int max(int x) {
	int ret = 0;
	node *curr = &root;
	for(int i = 20; i >= 0; i--) {
		int bit = (x >> i) & 1;
		if(curr -> ch[bit^1] != NULL) {
			ret |= (1<<i);
			curr = curr -> ch[bit^1];
		}
		else curr = curr -> ch[bit];
	} return ret;
}

int mex() {
	int ret = 0;
	node *curr = &root;
	for(int i = 20; i >= 0; i--) { 
		if(curr == NULL || curr -> ch[0] == NULL) return ret; 
		if(curr -> ch[0] -> cnt >= (1 << i)) {
			curr = curr -> ch[1];
			ret |= (1 << i); 
		} else curr = curr -> ch[0]; 
	} return ret; 
}
