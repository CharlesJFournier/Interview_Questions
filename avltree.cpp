/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
	*_out << __func__ << endl; 

	if(t == NULL) return;
	
	Node *k = t;
	t = k->right;
	k->right = t->left;
	t->left = k;
	t->height = 1+max(heightOrNeg1(t->left), heightOrNeg1(t->right));
	k->height = 1+max(heightOrNeg1(k->left), heightOrNeg1(k->right));
	//height = t->height;
}

template <class K, class V>
int AVLTree<K, V>::heightFixer(Node* t)
{
	if ( t == NULL )
	{
		t->height = -1;
		return -1;
	}
	t->height = 1+ max(heightFixer(t->right), heightFixer(t->left));
	return t->height;
}


template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    *_out << __func__ << endl; 
	// Outputs the rotation name (don't remove this)
	Node * k = t;
	t = t->left;
	k->left = t->right;
	t->right = k;
	t->height = 1+max(heightOrNeg1(t->left), heightOrNeg1(t->right));
	k->height = 1+max(heightOrNeg1(k->left), heightOrNeg1(k->right));
	//height = t->height;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
	rotateRight(t->right);
	rotateLeft(t);
    // your code here
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
	if(subtree == NULL){
		return;
	}	
	int k = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
	if(k == 2){
		int r = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
		if(r==1){
			rotateLeft(subtree);
		}
		else{
			rotateRightLeft(subtree);
		}
	}
	else if(k == -2){
		int l = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
		if(l == -1){
			rotateRight(subtree);
		}
		else
			rotateLeftRight(subtree);
	}	
	subtree->height = 1 + max(heightOrNeg1(subtree->right), heightOrNeg1(subtree->left));
}


template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
	if(root == NULL)
		root = new Node(key, value); 
	else{
		insert(root, key, value);
	}
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
	if(key < subtree->key){
		if(subtree->left == NULL){
			subtree->left = new Node(key, value);
		}
		else{
			insert(subtree->left, key, value);
		}
	}
	else{
		if(subtree->right == NULL){
			subtree->right = new Node(key, value);
		}
		else{
			insert(subtree->right, key, value);
		}
	}
	rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);	
}

template <class K, class V>
typename AVLTree<K, V>::Node *& AVLTree<K, V>::iop(Node*& subtree){
	if(subtree->right == NULL){
		return subtree;
	}
	else{
		return iop(subtree->right);
	}
}


template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
			delete subtree;
			subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
			Node *& t = iop(subtree->left);
			swap(subtree, t);
			remove(t, t->key);	
        } else {
			if(subtree->left != NULL){
				Node *t = subtree;
				subtree = subtree->left;
				delete t;
				t = NULL;
			}
			else {
				Node *k = subtree;
				subtree = subtree->right;
				delete k;
			}
            /* one-child remove */
            // your co1de here
        	
		}
        // your code here
    }
	rebalance(subtree);
}
