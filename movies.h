// Alberto Huang He 
#include <iostream>
using namespace std;

class Movies{
private:
    struct Node{
        string movie_name;
        double rating;
        int depth;
        Node *left, *right, *parent;
        Node(string m_n, double r = 0.0, int d = 0) : left(0), right(0), parent(0) {
            movie_name = m_n;
            rating = r;
            depth = d;
        }
    };

    Node* root;

public:
    Movies();
    ~Movies();
    void clear(Node* n); // destructor helper

    void setName(string name){
        root->movie_name = name;
    }
    void setRating(double rating){
        root->rating = rating;
    }
    void setDepth(int depth){
        root->depth = depth;
    }

    string getName() const{ return root->movie_name; }
    double getRating() const{ return root->rating; }
    int getDepth() const{ return root->depth; }
    Node* getRoot() const{ return root; }


    void printPreOrder();
    void printPreOrder(Node* n); // helper

    bool insert(string name, double rating);
    bool insert(Node* n, string name, double rating, int depth);

    bool insertByRating(string name, double rating);
    bool insertByRating(Node* n, string name, double rating, int depth);

    void copyByPrefix(Node* n, string prefix);
    bool copyByRating(Node* n);
    Node* searchByPrefix(Node* n, string prefix);

    Node* searchByName(string name);
    Node* searchByName(Node* n, string name); // helper

    Node* nodeWithMaxRating();
    void printHighestRating();

    double getMax();
    double findMax(Node* n); // helper

    Node* searchByMaxRating();
    Node* searchByMaxRating(Node* n, double max); // helper

    Node* searchByHighestRating(); 
    Node* searchByHighestRating(Node* n, double max); // helper

    Node* searchMaxByPrefix(string prefix);
    Node* searchMaxByPrefix(Node* n, string prefix); // helper
    void printHighestRating(string prefix);

    void traverseAndTime();
    void traverseAndTime(Node* n); // helper

    // add search functions (see piazza)

};

