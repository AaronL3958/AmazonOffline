#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <bits/stdc++.h>

// Reasons to use unordered_map over map:
// https://stackoverflow.com/questions/2196995/is-there-any-advantage-of-using-map-over-unordered-map-in-case-of-trivial-keys

class Item {
    //Item class struct
    std::string name;
    std::string imageLink;
    std::string amazonLink;
    // rating score is ratings * no_or_ratings
    double ratingScore;
    std::string price;
    double rating;
    int no_of_ratings;
public:
    Item() = default;
    Item(std::string name, std::string imageLink, std::string amazonLink,
         std::string ratings, std::string no_of_ratings, std::string price);
    std::string getPrice() {return price;}
    std::string getName() {return name;}
    double getRatingScore() {return ratingScore;}
    std::string getImageLink() {return imageLink;}
    std::string getAmazonLink() {return amazonLink;}
    double getRating() {return rating;}
    int getNumRatings() {return no_of_ratings;}

};

class Graph {
    // TODO: Implement as Adjacency List as our graph will be sparse, so this will perform much better
    // Variables should be camelCase. Note {} styling too.
    // Order of Nodes: Root->Main_Category->Sub_Category->Ratings (and then ordered by actual price within rating)
    // Node templating for class inheritance for more advanced structures
    class Node {
        std::string name;
        Node* next;
        Node* prev;

    public:
        Node() = default;
        Node(std::string& name, Node* next = nullptr, Node* prev = nullptr) {
            this->name = name;
            this->next = next;
            this->prev = prev;
        }
        std::string getName() {
            return name;
        }
        void setNext(Node* nextNode) {
            this->next = nextNode;
        }
        void setPrev(Node* prevNode) {
            this->prev = prevNode;
        }
        Node* getNext() {
            return this->next;
        }
        Node* getPrev() {
            return this->prev;
        }
        virtual ~Node() {} // Virtual destructor
    };

    // Sub Category Struct
    struct SubCategory : public Node {
        std::vector<Item> items;
        void addItemToSubCategory(Item item);
    public:
        SubCategory() : Node(){}
        SubCategory(std::string name) : Node(name, nullptr, nullptr) {}
        void add(Item item) {
            addItemToSubCategory(item);
        }
        std::vector<Item>& getItems() {return items;}
        void printItems();
    };

    // Main Category Struct
    class MainCategory : public Node {
    private:
        std::unordered_map<std::string, SubCategory> subCategories {};
        void addToSubCategories(std::string& subcategory) {
            if (subCategories.find(subcategory) == subCategories.end()) {
                SubCategory temp(subcategory);
                // Sets pointer of new category to the root's location
                temp.setPrev(this);
                subCategories[subcategory] = temp;
            }
        }
    public:
        MainCategory() : Node() {}
        MainCategory(std::string name) : Node(name, nullptr, nullptr) {}
        void add(std::string& subcategory) {
            addToSubCategories(subcategory);
        }
        std::unordered_map<std::string, SubCategory>& getSubCategory();
    };
    /*
    IDEA:
    Graph class strucutre: Root contains mapping to each main category.
    */
    class Root {
        MainCategory myRoot;
        std::unordered_map<std::string, MainCategory> mainCategories{};
        void addToMainCategories(std::string& category) {
            if (mainCategories.find(category) == mainCategories.end()) {
                MainCategory temp(category);
                // Sets pointer of new category to the root's location
                temp.setPrev(&myRoot);
                mainCategories[category] = temp;
            }
        }
    public:
        Root() = default;
        void add(std::string& category) {
            addToMainCategories(category);
        }
        std::unordered_map<std::string, MainCategory>& getMainCategories();
        void printCategories() {
            // Traversal Reference: https://www.geeksforgeeks.org/traversing-a-map-or-unordered_map-in-cpp-stl/
            auto iter = mainCategories.begin();
            for (; iter != mainCategories.end(); ++iter) {
                std::cout << iter->second.getName() << std::endl;
            }
        }
    };
    Root root;
public:
    Graph() = default;
    void addCategory(std::string category);
    void printCategories();
    Root& getRoot();
    void addSubcategory(std::string mainCategory, std::string subCategory);
    std::vector<std::string> getAllSubcategories();
    std::unordered_map<std::string, SubCategory>& accessSubcategory(std::string mainCategory);
    void addItemToSubcategory(std::string mainCategory,std::string subCategory, std::string name, std::string imageLink,
                              std::string amazonLink, std::string ratings, std::string no_of_ratings, std::string price);
    // void printAllItems();
    void BFS();
    void DFS();
    std::vector<Item> orderByRatingScore(std::string mainCategory, std::string subCategory);
    std::vector<Item> orderByPrice(std::string mainCategory, std::string subCategory);

};
