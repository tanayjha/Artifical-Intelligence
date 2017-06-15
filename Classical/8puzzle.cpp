#include <bits/stdc++.h>
using namespace std;

class searchTree {
    private:
	    struct tree_node{
	     tree_node* link1;
	     tree_node* link2;
		   tree_node* link3;
		   tree_node* link4;
		   tree_node* parent;
	     vector<int> state;
		   int cost;
		   int index;
		   int distance;
	    };
			vector<int> initial, final;
			vector<tree_node*> stack;
	    tree_node* root;
			int heuristic;
			bool success;
    
    public:
      searchTree() {
         root = NULL;
      }
       
	    bool isEmpty() const { return root==NULL; }
	    void insert(tree_node*);
			void makeRoot(vector<int>);
			void build();
			void read();
			void makeMove(tree_node*, tree_node*, char);
			void print(tree_node*);
			void pv(tree_node*);
			void checkSuccess(tree_node*);
			int h1(tree_node*);
			void sort();
};

void searchTree::build() {
	read();
	makeRoot(initial);
	success = false;
	tree_node* curr;
	heuristic = 1;

	int count = 0;
	while (stack.size() > 0) {
		curr = stack.front();
		stack.erase(stack.begin());
		insert(curr);

		if (curr->distance > count) {
			count = curr->distance;
			// cout << "n = " << count << endl;
		}
	}
}
void searchTree::read() {
	cout<<"Enter the initial state: \n";
	int a;
	for(int i = 1; i <= 9; i++) {
		cin>>a;
		initial.push_back(a);
	}
	cout<<"Enter the final state: \n";
	for(int i = 1; i <= 9; i++) {
		cin>>a;
		final.push_back(a);
	}
}
void searchTree::makeRoot(vector<int> state) {
    tree_node* t1 = new tree_node;
	for (int i=0; i<(signed)state.size(); i++)
		t1->state.push_back(state[i]);
	t1->cost = h1(t1);
	t1->distance = 1;
    t1->link1 = NULL; t1->link2 = NULL; t1->link3 = NULL; t1->link4 = NULL;
	t1->parent = NULL;

	for (int i=0; i<(signed)state.size(); i++) {
		if (state[i] == 0) {
			t1->index = i;
		}
	}

	if(isEmpty()) {
		root = t1;
		stack.push_back(root);
	}
}
int searchTree::h1(tree_node* t) {
	int cost = 0;

	for (int i=0; i<(signed)t->state.size(); i++) {
		if (t->state[i] != final[i]) {
			cost++;
		}
	}

	return cost;
}
void searchTree::makeMove(tree_node* curr, tree_node* t, char direction) {
	int temp, index;
	bool badMove = false;

	for (int i=0; i<(signed)curr->state.size(); i++) {
		if (curr->state[i] == 0) {
			index = i;
		}
		t->state.push_back(curr->state[i]);
	}
	t->index = index;

	if (curr->distance > 2) {
		if (index == curr->parent->index) {
			badMove = true;
		}
	}

	switch (direction) {
		case 'u' :
			if ((index > 2) && (!badMove)) {
				temp = t->state[index];
				t->state[index] = t->state[index-3];
				t->state[index-3] = temp;
			}
			else
				t->state.erase(t->state.begin(), t->state.end());
			break;
		case 'r' :
			if ((index%3 != 2) && (!badMove)) {
				temp = t->state[index];
				t->state[index] = t->state[index+1];
				t->state[index+1] = temp;
			}
			else
				t->state.erase(t->state.begin(), t->state.end());
			break;
		case 'd' :
			if ((index < 6) && (!badMove)) {
				temp = t->state[index];
				t->state[index] = t->state[index+3];
				t->state[index+3] = temp;
			}
			else
				t->state.erase(t->state.begin(), t->state.end());
			break;
		case 'l' :
			if ((index%3 != 0) && (!badMove)) {
				temp = t->state[index];
				t->state[index] = t->state[index-1];
				t->state[index-1] = temp;
			}
			else
				t->state.erase(t->state.begin(), t->state.end());
			break;
	}
}
void searchTree::insert(tree_node* curr) {
    tree_node* t1 = new tree_node;
	makeMove(curr, t1, 'u');
	t1->distance = curr->distance + 1;
	t1->cost = h1(t1) + t1->distance;
    t1->link1 = NULL; t1->link2 = NULL; t1->link3 = NULL; t1->link4 = NULL;
	t1->parent = curr;

    tree_node* t2 = new tree_node;
	makeMove(curr, t2, 'r');
	t2->distance = curr->distance + 1;
	t2->cost = h1(t2) + t2->distance;
    t2->link1 = NULL; t2->link2 = NULL; t2->link3 = NULL; t2->link4 = NULL;
	t2->parent = curr;

    tree_node* t3 = new tree_node;
	makeMove(curr, t3, 'd');
	t3->distance = curr->distance + 1;
	t3->cost = h1(t3) + t3->distance;
    t3->link1 = NULL; t3->link2 = NULL; t3->link3 = NULL; t3->link4 = NULL;
	t3->parent = curr;

    tree_node* t4 = new tree_node;
	makeMove(curr, t4, 'l');
	t4->distance = curr->distance + 1;
	t4->cost = h1(t4) + t4->distance;
    t4->link1 = NULL; t4->link2 = NULL; t4->link3 = NULL; t4->link4 = NULL;
	t4->parent = curr;

	if ((curr->link1 == NULL) && (t1->state.size() > 0)) {
		curr->link1 = t1;
		if (!success) stack.push_back(curr->link1);
	} 
	else 
		delete t1;
	if ((curr->link2 == NULL) && (t2->state.size() > 0)) {
		curr->link2 = t2;
		if (!success) stack.push_back(curr->link2);
	} 
	else 
		delete t2;
	if ((curr->link3 == NULL) && (t3->state.size() > 0)) {
		curr->link3 = t3;
		if (!success) stack.push_back(curr->link3);
	} 
	else 
		delete t3;
	if ((curr->link4 == NULL) && (t4->state.size() > 0)) {
		curr->link4 = t4;
		if (!success) stack.push_back(curr->link4);
	} 
	else 
		delete t4;

	sort();
	checkSuccess(curr);
}
void searchTree::sort() {
	tree_node* temp;

	for (int i=0; i<(signed)stack.size()-1; i++) {
		for (int j=0; j<(signed)stack.size()-1; j++) {
			if (stack[j]->cost > stack[j+1]->cost) {
				temp = stack[j];
				stack[j] = stack[j+1];
				stack[j+1] = temp;
			}
		}
	}
}
void searchTree::checkSuccess(tree_node* curr) {
	bool	pass1 = true, 
			pass2 = true, 
			pass3 = true, 
			pass4 = true;

	for (int i=0; i<(signed)final.size(); i++) {
		if (curr->link1 != NULL){
			if (curr->link1->state[i] != final[i]) 
				pass1 = false;
		}
		else 
			pass1 = false;
		if (curr->link2 != NULL) {
			if (curr->link2->state[i] != final[i]) 
				pass2 = false;
		} 
		else 
			pass2 = false;
		if (curr->link3 != NULL) {
			if (curr->link3->state[i] != final[i]) 
				pass3 = false;
		} 
		else 
			pass3 = false;
		if (curr->link4 != NULL) {
			if (curr->link4->state[i] != final[i]) 
				pass4 = false;
		} 
		else 
			pass4 = false;
	}
	if (pass1) {
		success = true;
		print(curr->link1);
	}
	else if (pass2) {
		success = true;
		print(curr->link2);
	}
	else if (pass3) {
		success = true;
		print(curr->link3);
	}
	else if (pass4) {
		success = true;
		print(curr->link4);
	}

	if (success) {
		while (!stack.empty())
			stack.erase(stack.begin());
	}
}
void searchTree::pv(tree_node* t) {
	for (int i=0; i<(signed)t->state.size(); i++) {
		cout << t->state[i] << " ";
		if (i%3 == 2) cout << endl;
	}
	cout << t->cost << " " << t->distance << endl;
	cout << endl;
}
void searchTree::print(tree_node* t) {
	vector<tree_node*> v;
	while (t != NULL) {
		v.push_back(t);
		t = t->parent;
	}
	cout << "Initial State" << endl;
	for (int j=v.size()-1; j>=0; j--) {
		for (int i=0; i<(signed)v[j]->state.size(); i++) {
			if (v[j]->state[i] == 0)
				cout << "0 ";
			else
				cout << v[j]->state[i] << " ";
			if (i%3 == 2) cout << endl;
		}
		cout << endl;
	}
	cout << "Goal State" << endl;
}
int main() {
  searchTree b; 
	b.build();
}
