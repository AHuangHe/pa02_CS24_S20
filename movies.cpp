// Alberto Huang He
#include "movies.h"
#include <string.h>
#include <iostream>
#include <chrono>
using namespace std::chrono;
using namespace std;

Movies::Movies() : root(0) {}


Movies::~Movies(){
    clear(root);
}

void Movies::clear(Node* n){
    if (n){
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

// insert by name
bool Movies::insert(string name, double rating){

    if (!root){
        root = new Node(name, rating, 0);
        return true;
    }

    return insert(root, name, rating, 1);
}

bool Movies::insert(Node* n, string name, double rating, int depth){
    if (name < n->movie_name){

        if (n->left){
            return insert(n->left, name, rating, depth + 1);
        } else {
            n->left = new Node(name, rating, depth);
            n->left->parent = n;
            return true;
        }

    } else {

        if (n->right){
            return insert(n->right, name, rating, depth + 1);
        } else {
            n->right = new Node(name, rating, depth);
            n->right->parent = n;
            return true;
        }

    }
}

// insert by rating
bool Movies::insertByRating(string name, double rating){
    // empty tree first
    if (!root){
        root = new Node(name, rating, 0);
        return true;
    }

    return insertByRating(root, name, rating, 1);
}

bool Movies::insertByRating(Node* n, string name, double rating, int depth){
    if (rating < n->rating){

        if (n->left){
            return insertByRating(n->left, name, rating, depth + 1);
        } else {
            n->left = new Node(name, rating, depth);
            n->left->parent = n;
            return true;
        }

    } else if(rating > n->rating){

        if (n->right){
            return insertByRating(n->right, name, rating, depth + 1);
        } else {
            n->right = new Node(name, rating, depth);
            n->right->parent = n;
            return true;
        }

    }
}

// print pre-order
void Movies::printPreOrder(){
    printPreOrder(root);
    cout << endl;
}

void Movies::printPreOrder(Node *n){
    if (n){
        cout << n->movie_name << ", " << n->rating << ", " << n->depth << endl;
        printPreOrder(n->left);
        printPreOrder(n->right);
    }
}

// search by name
Movies::Node* Movies::searchByName(string name){
    return searchByName(root, name);
}

Movies::Node* Movies::searchByName(Node* n, string name){
    if(!n) {return NULL;}
    if(name == n->movie_name){
        return n;
    }
    if(name < n->movie_name){
        return searchByName(n->left, name);
    }
    if(name > n->movie_name){
        return searchByName(n->right, name);
    }
}

// copy by prefix and sort by rating
void Movies::copyByPrefix(Node* n, string prefix){

    if(!n) {return;}
    if(n){
        if(n->movie_name.substr(0, prefix.length()) == prefix){
            this->insertByRating(n->movie_name, n->rating);
        }
        copyByPrefix(n->left, prefix);
        copyByPrefix(n->right, prefix);
        return;

    }
}

// copy by rating (not used)
bool Movies::copyByRating(Node* n){
    if(!n) {return false;}
    if(n){
        this->insertByRating(n->movie_name, n->rating);
        copyByRating(n->left);
        copyByRating(n->right);
        return true;
    }

}


// search by prefix (not used and incomplete)
Movies::Node* Movies::searchByPrefix(Node* n, string prefix){
    if(!n) {return NULL;}
    if(n->movie_name.substr(0, prefix.length()) == prefix){

    }
    if(n->movie_name.substr(0, prefix.length()) < prefix){
        return searchByPrefix(n->left, prefix);
    }
    if(n->movie_name.substr(0, prefix.length()) > prefix){
        return searchByPrefix(n->right, prefix);
    }

}

// node with max rating
Movies::Node* Movies::nodeWithMaxRating(){
    Node* n = root;
    Node* max;
    if(!n) {return NULL;}
    while(n && n->right){
        n = n->right;
    }
    return n;
}

// print highest rating
void Movies::printHighestRating(){
    Node* n = this->nodeWithMaxRating();
    cout << "Best movie is " << n->movie_name << " with rating " << n->rating;
}

// get maximum rating (not used for the project)
double Movies::getMax(){
    return findMax(root);
}

double Movies::findMax(Node* n){
    //Node* n = root;
    
    if(!n) {return 0.0;}
    double max = n->rating;
    double nLeft = findMax(root->left);
    double nRight = findMax(root->right);
    if(nLeft > max){
        max = nLeft;
    }
    if(nRight > max){
        max = nRight;
    }
    return max;
    
}

// search by max rating (was used, then I stopped using it)
Movies::Node* Movies::searchByMaxRating(){
    double max = this->getMax();
    return searchByMaxRating(root, max);
}

Movies::Node* Movies::searchByMaxRating(Node* n, double max){
    if(!n) {return NULL;}
    if(n){
        if(n->rating == max){
            return n;
        }
        searchByMaxRating(n->left, max);
        searchByMaxRating(n->right, max);
        return NULL;
    }
}

// search by highest rating (similar to max rating, implemented prior to max rating, not used)
Movies::Node* Movies::searchByHighestRating(){
    return searchByHighestRating(root, 0.0);
}

Movies::Node* Movies::searchByHighestRating(Node* n, double max){
    if(!n) {return NULL;}
    if(n->rating > max){
        searchByHighestRating(n->left, n->rating);
        searchByHighestRating(n->right, n->rating);
        //return n;
    } else {
        searchByHighestRating(n->left, max);
        searchByHighestRating(n->right, max);
    }
    return n;
}

// search by prefix combined with searching for the max value (did not work)
Movies::Node* Movies::searchMaxByPrefix(string prefix){
    return searchMaxByPrefix(root, prefix);
}

Movies::Node* Movies::searchMaxByPrefix(Node* n, string prefix){
    if(!n) {return NULL;}
    Node* p = n;
    double m = n->rating;
    Node* left = searchMaxByPrefix(n->left, prefix);
    Node* right = searchMaxByPrefix(n->right, prefix);
    if(n->movie_name.substr(0, prefix.length()) == prefix){
        if(left->rating > m){
            p = left;
        } 
        if(right->rating > m){
            p = right;
        }
        return p;
    }
}
// did not work
void Movies::printHighestRating(string prefix){
    Node* n = this->searchMaxByPrefix(prefix);
    cout << "Best movie is " << n->movie_name << " with rating " << n->rating;
}

// doesn't work
void Movies::traverseAndTime(){
    auto start = high_resolution_clock::now();
    traverseAndTime(root);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
}

void Movies::traverseAndTime(Node *n){
    
    if (n){
        traverseAndTime(n->left);
        traverseAndTime(n->right);
    }

}
