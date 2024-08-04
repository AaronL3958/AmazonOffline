#include "Graph.h"

#include <stack>


Item::Item(std::string name, std::string imageLink, std::string amazonLink, std::string ratings,
           std::string no_of_ratings, std::string price) {
    this->name = name;
    this->imageLink = imageLink;
    this->amazonLink = amazonLink;
    double ratingScore = std::stod(ratings) * std::stoi(no_of_ratings);
    this->ratingScore = ratingScore;
    this->price = price;
    this->rating = std::stof(ratings);
    this->no_of_ratings = std::stoi(no_of_ratings);
}

void Graph::SubCategory::addItemToSubCategory(Item item) {
    items.push_back(item);
}

void Graph::SubCategory::printItems() {
    std::cout << "number of items in this subcategory:" << items.size() << std::endl;
    for (auto& i : items) {
        std::cout << i.getPrice() << std::endl;
    }
}

void Graph::addCategory(std::string category) {
    root.add(category);
}

void Graph::printCategories() {
    root.printCategories();
}

Graph::Root &Graph::getRoot() {
    return root;
}

void Graph::addSubcategory(std::string mainCategory, std::string subCategory) {
    root.getMainCategories()[mainCategory].add(subCategory);
}

std::vector<std::string> Graph::getAllSubcategories() {
    std::vector<std::string> sub_categories {};
    for (auto& i : root.getMainCategories()) {
        for (auto& j : i.second.getSubCategory()) {
            sub_categories.push_back(j.first);
        }
    }
    return sub_categories;
}

std::unordered_map<std::string, Graph::SubCategory>& Graph::accessSubcategory(std::string mainCategory) {
    return root.getMainCategories()[mainCategory].getSubCategory();
}

std::unordered_map<std::string, Graph::MainCategory>& Graph::Root::getMainCategories() {
    return mainCategories;
}

std::unordered_map<std::string, Graph::SubCategory> & Graph::MainCategory::getSubCategory() {
    return subCategories;
}

void Graph::addItemToSubcategory(std::string mainCategory,std::string subCategory, std::string name,
                                 std::string imageLink, std::string amazonLink, std::string ratings, std::string no_of_ratings, std::string price) {

    std::vector<Item>& items = this->accessSubcategory(mainCategory)[subCategory].getItems();
    Item temp(name, imageLink, amazonLink, ratings, no_of_ratings, price);
    this->accessSubcategory(mainCategory)[subCategory].getItems().push_back(temp);
}

void Graph::BFS() {
    std::queue<Node*> toVisit;
    std::unordered_set<Node*> visited;

    // Iterate through all main categories to start BFS from each one
    for (auto& mainCategoryPair : root.getMainCategories()) {
        toVisit.emplace(&mainCategoryPair.second);
        visited.emplace(&mainCategoryPair.second);
    }
    while(!toVisit.empty()) {
        MainCategory* mainCat = dynamic_cast<MainCategory*>(toVisit.front());
        if (mainCat) {
            toVisit.pop();
            std::cout << "Visited: " << mainCat->getName() << std::endl;
            for (auto& i : mainCat->getSubCategory()) {
                toVisit.emplace(&i.second);
            }
        }
        SubCategory* subCat = dynamic_cast<SubCategory*>(toVisit.front());
        if (subCat) {
            break;
        }
    }

    std::vector<SubCategory*> subCategories {};

    while(!toVisit.empty()) {
        SubCategory* subCat = dynamic_cast<SubCategory*>(toVisit.front());
        if (subCat) {
            toVisit.pop();
            std::cout << "Visited: " << subCat->getName() << std::endl;
            subCategories.push_back(subCat);
        }
    }

    int index = 0;
    while (!subCategories.empty()) {
        for (auto i : subCategories) {
            if (index >= i->getItems().size()) {
                // Remove from Array
                int indexToRemove = 0;
                for (int j = 0; j < subCategories.size(); j++) {
                    if (subCategories[j] == i) {
                        indexToRemove = j;
                    }
                }
                subCategories.erase(subCategories.begin() + indexToRemove);
            }
            std::cout << "Visited: " << i->getItems()[index].getName() << std::endl;
        }
        index++;
    }
}

void Graph::DFS() {
    std::stack<Node*> toVisit;
    std::unordered_set<Node*> visited;

    // Iterate through all main categories to start DFS from each one
    for (auto& mainCategoryPair : root.getMainCategories()) {
        toVisit.emplace(&mainCategoryPair.second);
        visited.emplace(&mainCategoryPair.second);
    }
    while(!toVisit.empty()) {
        MainCategory* mainCat = dynamic_cast<MainCategory*>(toVisit.top());
        if (mainCat) {
            toVisit.pop();
            std::cout << "Visited: " << mainCat->getName() << std::endl;
            for (auto& i : mainCat->getSubCategory()) {
                toVisit.emplace(&i.second);
            }
        }
        SubCategory* subCat = dynamic_cast<SubCategory*>(toVisit.top());
        if (subCat) {
            std::cout << "Visited: " << subCat->getName() << std::endl;
            toVisit.pop();
            for(auto& i : subCat->getItems()) {
                std::cout << "Visited: " << i.getName() << std::endl;
            }
        }
    }
}

std::vector<Item> Graph::orderByRatingScore(std::string mainCategory, std::string subCategory) {
    std::vector<double> orderedByRating;
    std::vector<Item> orderedItems;
    for(auto& i : this->accessSubcategory(mainCategory)[subCategory].getItems()) {
        orderedByRating.push_back(i.getRatingScore());
    }
    sort(orderedByRating.begin(), orderedByRating.end(), std::greater<int>());
    for(auto& i : orderedByRating) {
        for(auto& j : this->accessSubcategory(mainCategory)[subCategory].getItems()) {
            if(j.getRatingScore() == i) {
                orderedItems.push_back(j);
            }
        }
    }
    return orderedItems;
}

std::vector<Item> Graph::orderByPrice(std::string mainCategory, std::string subCategory) {

    std::vector<float> orderedByPrice;
    std::vector<Item> orderedItems;
    for(auto& i : this->accessSubcategory(mainCategory)[subCategory].getItems()) {
        std::string priceFloat = i.getPrice().substr(1);
        orderedByPrice.push_back(std::stof(priceFloat));
    }
    sort(orderedByPrice.begin(), orderedByPrice.end());
    for(auto& i : orderedByPrice) {
        for(auto& j : this->accessSubcategory(mainCategory)[subCategory].getItems()) {
            float priceCompare = std::stof(j.getPrice().substr(1));
            if(priceCompare == i) {
                orderedItems.push_back(j);
            }
        }
    }
    return orderedItems;
}
