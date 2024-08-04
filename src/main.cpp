#include <SFML/Graphics.hpp>
#include "Graph.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <windows.h>
#pragma comment(lib, "urlmon.lib")
// Reference for urlmon API: https://www.youtube.com/watch?v=HSUKNHVda_I
#include <urlmon.h>

constexpr unsigned int WINDOW_WIDTH = 1600;
constexpr unsigned int WINDOW_HEIGHT = 900;

bool loadItemImage(Item myItem) {
    //This is for loading the ImageLink of a specific object into our "THEIMAGE.jpg" so we can display it on SFML
    std::string url = myItem.getImageLink();
    std::cout << myItem.getName() << std::endl;
    std::cout << url << std::endl;
    const char* dst = "Image/THEIMAGE.jpg";
    if(S_OK == URLDownloadToFile(NULL, url.c_str(), dst, 0, NULL)){
        return true;
    }
    else {
        return false;
    }
}

// TODO IMPORTANT NOTE: DO NOT USE NAMESPACE STD because we have both sf and std libraries

// int main() {
// //     // Work with this one first to test out graph functionalities
//     Graph graph;
// // //     // Creating the Graph DataStructure and adding main categories
// //      // For Testing
// //      std::string temp;
// //      graph.addCategory("Video Games");
// //      graph.addCategory("Guitar");
// //      graph.addCategory("Accessories");
// //      graph.printCategories();
// //      // Adding a Sub Category to a Main category
// //  //    graph.getRoot().getMainCategories()["Video Games"].add(tempSub);
// //      graph.addSubcategory("Video Games", "FPS");
// //      graph.addSubcategory("Video Games", "Platformers");
// //      graph.addSubcategory("Video Games", "StoryMode");
// //      graph.addSubcategory("Video Games", "Moba");
// //
// //
// //  //    auto& subCategories = graph.getRoot().getMainCategories()["Video Games"].getSubCategory();
// //      auto subCategories = graph.accessSubcategory("Video Games");
// //      std::cout << "Sub Categories for Video Games: " << std::endl;
// //      for(auto iter = subCategories.begin(); iter != subCategories.end(); ++iter) {
// //          std::cout << iter->second.getName() << std::endl;
// //      }
//
//     std::ifstream myFile("AmazonData/AMAZONDSAFINAL.csv");
//     if(!myFile.is_open()) throw std::runtime_error("Could not open file");
//
//     std::string line;
//     std::string data;
//     std::getline(myFile, line);
//
//     // Create a stringstream from line
//     std::stringstream ss(line);
//
//
//
//     // Extract each column
//     for(int i = 0; i < 8; i++) {
//         std::getline(ss, data, ',');
//         std::cout << data << std::endl;
//     }
//     std::string name, main_category, sub_category, image, link, ratings, no_of_ratings, price;
//     //Begin timer
//     auto a = std::chrono::high_resolution_clock::now();
//
//     for(int i = 0; i < 100000; i++) {
//         // Gets each data column value
//         std::getline(myFile, line);
//         std::stringstream s(line);
//             getline(s, name, ',');
//             getline(s, main_category, ',');
//             getline(s, sub_category, ',');
//             getline(s, image, ',');
//             getline(s,  link, ',');
//             getline(s, ratings, ',');
//             getline(s, no_of_ratings, ',');
//             getline(s, price, ',');
//
//         // TODO: NOW WORK ON PLACING THAT DATA INTO GRAPH
//         graph.addCategory(main_category);
//         graph.addSubcategory(main_category, sub_category);
// //        std::cout << main_category << ", " << sub_category << std::endl;
//         graph.addItemToSubcategory(main_category, sub_category, name, image,
//                                    link, ratings, no_of_ratings, price);
//     }
//
// //    // This is for Timing the BFS and DFS
// //    auto c = std::chrono::high_resolution_clock::now();
// //    graph.BFS();
// //    auto d = std::chrono::high_resolution_clock::now();
// //
// //    auto e = std::chrono::high_resolution_clock::now();
// //    graph.DFS();
// //    auto f = std::chrono::high_resolution_clock::now();
// //
// //    std::cout << "BFS took " << std::chrono::duration_cast<std::chrono::milliseconds>(d - c).count() << " milliseconds" << std::endl;
// //    std::cout << "DFS took " << std::chrono::duration_cast<std::chrono::milliseconds>(f - e).count() << " milliseconds" << std::endl;
//
// //    //Printing out Items ordered by Rating Score
//     // for(auto& i : graph.orderByRatingScore("grocery & gourmet foods", "All Grocery & Gourmet Foods")) {
//     //     std::cout << "Rating Score: " << i.getRatingScore() << std::endl;
//     //     std::cout << "Stars: " << i.getRating() << std::endl;
//     //     std::cout << "Number of Reviews: " << i.getNumRatings() << std::endl;
//     //     std::cout << std::endl;
//     // }
//
//     Item myItem;
//     //Printing out Items from Lowest Prices to highest
//     for(auto& i : graph.orderByPrice("grocery & gourmet foods", "All Grocery & Gourmet Foods")) {
// //        std::cout << "Name of Product: " << i.getName() << std::endl;
// //        std::cout << "Price: " << i.getPrice() << std::endl;
// //        std::cout << i.getImageLink() << std::endl;
// //        std::cout << std::endl;
//         myItem = i;
//         break;
//
//     }
//
//     //Calls function that loads the Image of one Item
//     loadItemImage(myItem);
//
//     //Below is for testing if the image can be displayed properly
//     sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML works!");
//     sf::CircleShape shape(100.f);
//     shape.setFillColor(sf::Color::Green);
//
//     sf::Texture texture;
//     if (!texture.loadFromFile("Image/THEIMAGE.jpg")) {
//         perror("Couldn't load texture.");
//         return 0;
//     }
//     sf::Sprite sprite;
//     sprite.setTexture(texture);
//
//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }
//
//         window.clear();
//         sprite.setPosition(400,500);
//         window.draw(sprite);
//         window.draw(shape);
//         window.display();
//     }
//
//
//     return 0;
// }

int main() {
    // Graph Backend
    Graph graph;

    std::ifstream myFile("AmazonData/AMAZONDSAFINAL.csv");
    if(!myFile.is_open()) throw std::runtime_error("Could not open file");

    std::string line;
    std::string data;
    std::getline(myFile, line);

    // Create a stringstream from line
    std::stringstream ss(line);

    // Extract each column
    for(int i = 0; i < 8; i++) {
        std::getline(ss, data, ',');
        std::cout << data << std::endl;
    }
    std::string name, main_category, sub_category, image, link, ratings, no_of_ratings, price;

    for(int i = 0; i < 100000; i++) {
        // Gets each data column value
        std::getline(myFile, line);
        std::stringstream s(line);
            getline(s, name, ',');
            getline(s, main_category, ',');
            getline(s, sub_category, ',');
            getline(s, image, ',');
            getline(s,  link, ',');
            getline(s, ratings, ',');
            getline(s, no_of_ratings, ',');
            getline(s, price, ',');

        graph.addCategory(main_category);
        graph.addSubcategory(main_category, sub_category);
        graph.addItemToSubcategory(main_category, sub_category, name, image,
                                   link, ratings, no_of_ratings, price);
    }


    // Final GUI main function (Work on last)
    auto window = sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "Amazon Offline", sf::Style::Close);
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("Font/arial.ttf")) {
        std::cerr << "Error loading font";
        return -1;
    }

    sf::Text TitleText;
    TitleText.setFont(font);
    TitleText.setString("Amazon Offline");
    TitleText.setCharacterSize(80);
    TitleText.setFillColor(sf::Color::Black);

    sf::Text QuestionItem;
    QuestionItem.setFont(font);
    QuestionItem.setString("What Item Would You Like?");
    QuestionItem.setCharacterSize(50);
    QuestionItem.setFillColor(sf::Color::Black);

    sf::Text MainCategory;
    MainCategory.setFont(font);
    MainCategory.setString("MAIN CATEGORY");
    MainCategory.setCharacterSize(40);
    MainCategory.setFillColor(sf::Color::Black);
    MainCategory.setStyle(sf::Text::Bold | sf::Text::Underlined);

    sf::Text SubCategory;
    SubCategory.setFont(font);
    SubCategory.setString("SUB CATEGORY");
    SubCategory.setCharacterSize(40);
    SubCategory.setFillColor(sf::Color::Black);
    SubCategory.setStyle(sf::Text::Bold | sf::Text::Underlined);

    sf::Text BFS_DFS_Text;
    BFS_DFS_Text.setFont(font);
    BFS_DFS_Text.setString("BFS vs. DFS");
    BFS_DFS_Text.setCharacterSize(40);
    BFS_DFS_Text.setFillColor(sf::Color::Black);

    sf::FloatRect BFS_DFS_Rect = BFS_DFS_Text.getLocalBounds();
    BFS_DFS_Text.setOrigin(BFS_DFS_Rect.left + BFS_DFS_Rect.width / 2.0f, BFS_DFS_Rect.top);
    BFS_DFS_Text.setPosition(sf::Vector2f(window.getSize().x / 6.0f, 150.0f));

    sf::Text START;
    START.setFont(font);
    START.setString("START");
    START.setCharacterSize(40);
    START.setFillColor(sf::Color::Black);

    sf::FloatRect STARTRect = START.getLocalBounds();
    START.setOrigin(STARTRect.left + STARTRect.width / 2.0f, STARTRect.top);
    START.setPosition(sf::Vector2f(window.getSize().x / 1.2f, 150.0f));

    sf::FloatRect TitleRect = TitleText.getLocalBounds();
    TitleText.setOrigin(TitleRect.left + TitleRect.width / 2.0f, TitleRect.top);
    TitleText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, 10.f));

    sf::FloatRect QuestionRect = QuestionItem.getLocalBounds();
    QuestionItem.setOrigin(QuestionRect.left + QuestionRect.width / 2.0f, QuestionRect.top);
    QuestionItem.setPosition(sf::Vector2f(window.getSize().x / 2.0f, TitleText.getPosition().y + TitleRect.height + 100.f));

    sf::FloatRect  MainCatRect = MainCategory.getLocalBounds();
    MainCategory.setOrigin(MainCatRect.left + MainCatRect.width / 2.0f, MainCatRect.top);
    MainCategory.setPosition(sf::Vector2f(window.getSize().x / 4.0f, 265.f));

    sf::FloatRect  SubCatRect = SubCategory.getLocalBounds();
    SubCategory.setOrigin(SubCatRect.left + SubCatRect.width / 2.0f, SubCatRect.top);
    SubCategory.setPosition(sf::Vector2f(window.getSize().x / 4.0f * 3.0f, 265.f));

    std::vector<sf::RectangleShape*> mainBoxes {};
    // Main Column Left Column
    for (int i = 0; i < 8; i++) {
        sf::RectangleShape* tempBoxMainCat = new sf::RectangleShape(sf::Vector2f(350, 50));
        tempBoxMainCat->setOutlineColor(sf::Color(135, 206, 235));
        tempBoxMainCat->setOutlineThickness(5);
        tempBoxMainCat->setPosition(sf::Vector2f((window.getSize().x / 2.0f) / 10.0f, 340.0f + 70.0f * i));
        tempBoxMainCat->setFillColor(sf::Color(211,211,211));
        mainBoxes.push_back(tempBoxMainCat);
    }
    // Main Column Right Column
    for (int i = 0; i < 8; i++) {
        sf::RectangleShape* tempBoxMainCat = new sf::RectangleShape(sf::Vector2f(310, 50));
        tempBoxMainCat->setOutlineColor(sf::Color(135, 206, 235));
        tempBoxMainCat->setOutlineThickness(5);
        tempBoxMainCat->setPosition(sf::Vector2f((window.getSize().x / 2.0f) / 1.8f + 32.0f, 340.0f + 70.0f * i));
        tempBoxMainCat->setFillColor(sf::Color(211,211,211));
        mainBoxes.push_back(tempBoxMainCat);
    }

    std::vector<sf::RectangleShape*> subBoxes {};
    // Sub Left Column
    for (int i = 0; i < 13; i++) {
        sf::RectangleShape* tempBoxSubCat = new sf::RectangleShape(sf::Vector2f(310, 30));
        tempBoxSubCat->setOutlineColor(sf::Color(135, 206, 235));
        tempBoxSubCat->setOutlineThickness(5);
        tempBoxSubCat->setPosition(sf::Vector2f((window.getSize().x / 2.0f) * 1.06f + 32.0f,
            (window.getSize().y / 3.0f) + 44.0f*i + 30.0f));
        tempBoxSubCat->setFillColor(sf::Color(211,211,211));
        subBoxes.push_back(tempBoxSubCat);
    }
    // Sub Right Column
    for (int i = 0; i < 13; i++) {
        sf::RectangleShape* tempBoxSubCat = new sf::RectangleShape(sf::Vector2f(310, 30));
        tempBoxSubCat->setOutlineColor(sf::Color(135, 206, 235));
        tempBoxSubCat->setOutlineThickness(5);
        tempBoxSubCat->setPosition(sf::Vector2f((window.getSize().x / 2.0f) * 1.60f - 28.0f,
            (window.getSize().y / 3.0f) + 44.0f*i + 30.0f));
        tempBoxSubCat->setFillColor(sf::Color(211,211,211));
        subBoxes.push_back(tempBoxSubCat);
    }
    // BFS_DFS_RECT
    sf::RectangleShape BFS_DFS_Rectangle(sf::Vector2f(310, 90));
    BFS_DFS_Rectangle.setOutlineColor(sf::Color(35,47,62));
    BFS_DFS_Rectangle.setOutlineThickness(10);
    BFS_DFS_Rectangle.setPosition(sf::Vector2f(window.getSize().x / 6.0f - 4.85f*32.0f, 120.0f));
    BFS_DFS_Rectangle.setFillColor(sf::Color(211,211,211));

    sf::RectangleShape START_Rectangle(sf::Vector2f(310, 90));
    START_Rectangle.setOutlineColor(sf::Color(35,47,62));
    START_Rectangle.setOutlineThickness(10);
    START_Rectangle.setPosition(sf::Vector2f(window.getSize().x / 1.2 - 4.85f*32.0f, 120.0f));
    START_Rectangle.setFillColor(sf::Color(211,211,211));


    // Mapping main cats to sub cats
    std::unordered_map<sf::RectangleShape*, std::vector<sf::RectangleShape*>> mainToSubMap {};

    // Get Sorted Main Category vector as strings
    auto& mainCatFromGraph = graph.getRoot().getMainCategories();
    std::vector<std::string> mainCats {};
    for (auto iter = mainCatFromGraph.begin(); iter != mainCatFromGraph.end(); ++iter) {
        mainCats.push_back(iter->first);
    }
    auto compareFunction = [] (std::string a, std::string b) -> bool {return a<b;};
    std::sort(mainCats.begin(),mainCats.end(), compareFunction);

    auto getIndex = [](std::vector<std::string> v, std::string s) -> int {
        auto iter = find(v.begin(), v.end(), s);
        if (iter != v.end()) {
            int index = iter - v.begin();
            return index;
        }
        return -1;
    };

    auto allSubCats = graph.getAllSubcategories();
    std::sort(allSubCats.begin(),allSubCats.end(), compareFunction);

    for (int i = 0; i < 16; i++) {
        std::vector<std::string> subCats{};
        std::vector<int> subCatIndexes{};

        auto subVect = graph.accessSubcategory(mainCats[i]);
        for (auto iter = subVect.begin(); iter != subVect.end(); ++iter) {
            subCats.push_back(iter->first);
        }
        for (auto& j : subCats) {
            subCatIndexes.push_back(getIndex(allSubCats, j));
        }
        for (auto& j : subCatIndexes) {
            mainToSubMap[mainBoxes[i]].push_back(subBoxes[j]);
        }
    }

    // Draw Text in rectangles
    std::vector<sf::Text*> MainCatTextLeft {};
    for (int i = 0; i < 8; i++) {
        auto tempMainCatLeft = new sf::Text;
        tempMainCatLeft->setFont(font);
        tempMainCatLeft->setString(mainCats[i]);
        tempMainCatLeft->setCharacterSize(30);
        tempMainCatLeft->setFillColor(sf::Color::Black);

        tempMainCatLeft->setPosition(sf::Vector2f((window.getSize().x / 2.0f) / 10.0f, 340.0f + 70.0f * i));
        MainCatTextLeft.push_back(tempMainCatLeft);
    }
    std::vector<sf::Text*> MainCatTextRight {};
    for (int i = 8; i < 16; i++) {
        auto tempMainCatRight = new sf::Text;
        tempMainCatRight->setFont(font);
        tempMainCatRight->setString(mainCats[i]);
        tempMainCatRight->setCharacterSize(30);
        tempMainCatRight->setFillColor(sf::Color::Black);

        tempMainCatRight->setPosition(sf::Vector2f((window.getSize().x / 2.0f) / 8.0f * 4.8f, 340.0f + 70.0f * (i-8.0f)));
        MainCatTextRight.push_back(tempMainCatRight);
    }
    std::vector<sf::Text*> SubCatTextLeft {};
    for (int i = 0; i < 13; i++) {
        auto tempSubCatLeft = new sf::Text;
        tempSubCatLeft->setFont(font);
        tempSubCatLeft->setString(allSubCats[i]);
        tempSubCatLeft->setCharacterSize(20);
        tempSubCatLeft->setFillColor(sf::Color::Black);

        tempSubCatLeft->setPosition(sf::Vector2f((window.getSize().x / 2.0f) * 1.06f + 32.0f,
            (window.getSize().y / 3.0f) + 44.0f*i + 30.0f));
        SubCatTextLeft.push_back(tempSubCatLeft);
    }
    std::vector<sf::Text*> SubCatTextRight {};
    for (int i = 0; i < 13; i++) {
        auto tempSubCatRight = new sf::Text;
        tempSubCatRight->setFont(font);
        tempSubCatRight->setString(allSubCats[i + 13]);
        tempSubCatRight->setCharacterSize(20);
        tempSubCatRight->setFillColor(sf::Color::Black);

        tempSubCatRight->setPosition(sf::Vector2f((window.getSize().x / 2.0f) * 1.60f - 28.0f,
            (window.getSize().y / 3.0f) + 44.0f*i + 30.0f));
        SubCatTextRight.push_back(tempSubCatRight);
    }

    // Pointers to check which ones to color
    sf::RectangleShape* selectedBox = nullptr;
    sf::RectangleShape* selectedSubbox = nullptr;
    std::vector<sf::RectangleShape*> availableSubBoxes {};

    // Other Window Logic
    bool BFS_DFS_ButtonClicked = false;
    bool START_ButtonClicked = false;

    // Strings for Main Category and Sub Category Selected
    std::string selectedMain = "";
    std::string selectedSub = "";

    while (window.isOpen()) {
        sf::Event event {};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                    for (auto& i : mainBoxes) {
                        if (i->getGlobalBounds().contains(mousePos)) {
                            if (selectedBox) {
                                selectedBox->setOutlineColor(sf::Color(135, 206, 235));
                            }
                            if (!availableSubBoxes.empty()) {
                                for (auto& j : availableSubBoxes) {
                                    j->setOutlineColor(sf::Color(135, 206, 235));
                                }
                            }
                            i->setOutlineColor(sf::Color::Red);
                            auto subCatsOfI = mainToSubMap[i];
                            for (auto& j : subCatsOfI) {
                                j->setOutlineColor(sf::Color::Yellow);
                            }
                            selectedBox = i;
                            availableSubBoxes.clear();
                            for (auto& j : subCatsOfI) {
                                availableSubBoxes.push_back(j);
                            }
                        }
                    }
                    for (auto& i : subBoxes) {
                        if (i->getGlobalBounds().contains(mousePos)) {
                            if (selectedSubbox) {
                                if (selectedSubbox->getOutlineColor() == sf::Color::Red) {
                                    selectedSubbox->setOutlineColor(sf::Color::Yellow);
                                }
                                else {
                                    selectedSubbox->setOutlineColor(sf::Color(135, 206, 235));
                                }
                            }
                            if (i->getOutlineColor() == sf::Color::Yellow) {
                                i->setOutlineColor(sf::Color::Red);
                            }
                            selectedSubbox = i;
                        }
                    }
                    if (BFS_DFS_Rectangle.getGlobalBounds().contains(mousePos)) {
                        BFS_DFS_ButtonClicked = true;
                        window.close();
                    }
                    if (START_Rectangle.getGlobalBounds().contains(mousePos)) {
                        START_ButtonClicked = true;
                        // Lambda for getting index for RectangleBox vectors
                        auto getIndexRect = [](std::vector<sf::RectangleShape*> v, sf::RectangleShape* s) -> int {
                            auto iter = find(v.begin(), v.end(), s);
                            if (iter != v.end()) {
                                int index = iter - v.begin();
                                return index;
                            }
                            return -1;
                        };
                        // Get Main and Sub Category
                        for (auto& i : mainBoxes) {
                            if (i->getOutlineColor() == sf::Color::Red) {
                                int mainIndex = getIndexRect(mainBoxes, i);
                                selectedMain = mainCats[mainIndex];
                            }
                        }
                        for (auto& i : subBoxes) {
                            if (i->getOutlineColor() == sf::Color::Red) {
                                int subIndex = getIndexRect(subBoxes, i);
                                selectedSub = allSubCats[subIndex];
                            }
                        }
                        if (selectedMain != "" && selectedSub != "") {
                            window.close();
                        }
                        else {
                            START_ButtonClicked = false;
                        }
                    }
                }
            }
        }

        window.clear(sf::Color(211, 211, 211));
        window.draw(TitleText);
        window.draw(QuestionItem);
        window.draw(MainCategory);
        window.draw(SubCategory);
        window.draw(BFS_DFS_Rectangle);
        window.draw(START_Rectangle);
        window.draw(BFS_DFS_Text);
        window.draw(START);
        for (auto& i : mainBoxes) {
            window.draw(*i);
        }
        for (auto& i : subBoxes) {
            window.draw(*i);
        }
        for (auto& i : MainCatTextLeft) {
            window.draw(*i);
        }
        for (auto& i : MainCatTextRight) {
            window.draw(*i);
        }
        for (auto& i : SubCatTextLeft) {
            window.draw(*i);
        }
        for (auto& i : SubCatTextRight) {
            window.draw(*i);
        }

        window.display();
    }
    if (BFS_DFS_ButtonClicked) {
        auto bfsDfsWindow = sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "BFS&DFSTESTING");
        bfsDfsWindow.setFramerateLimit(60);

        sf::Text loadingText;
        loadingText.setFont(font);
        loadingText.setString("Loading...");
        loadingText.setCharacterSize(60);
        loadingText.setFillColor(sf::Color::Black);
        loadingText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
        auto loadingTextRect = loadingText.getLocalBounds();
        loadingText.setOrigin(sf::Vector2f(loadingTextRect.left + loadingTextRect.width / 2.0f, loadingTextRect.top));
        bfsDfsWindow.clear(sf::Color::White);
        bfsDfsWindow.draw(loadingText);
        bfsDfsWindow.display();

        auto c = std::chrono::high_resolution_clock::now();
        graph.BFS();
        auto d = std::chrono::high_resolution_clock::now();

        auto e = std::chrono::high_resolution_clock::now();
        graph.DFS();
        auto f = std::chrono::high_resolution_clock::now();

        std::cout << "BFS took " << std::chrono::duration_cast<std::chrono::milliseconds>(d - c).count() << " milliseconds" << std::endl;
        std::cout << "DFS took " << std::chrono::duration_cast<std::chrono::milliseconds>(f - e).count() << " milliseconds" << std::endl;

        sf::Text BFSTime;
        BFSTime.setFont(font);
        std::string BFSString = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(d - c).count());
        BFSTime.setString(BFSString);
        BFSTime.setCharacterSize(30);
        BFSTime.setFillColor(sf::Color::Black);
        BFSTime.setPosition(sf::Vector2f(WINDOW_WIDTH / 4 - WINDOW_WIDTH / 12, WINDOW_HEIGHT / 2));

        sf::Text BFSmilli;
        BFSmilli.setFont(font);
        BFSmilli.setString("milliseconds");
        BFSmilli.setCharacterSize(20);
        BFSmilli.setFillColor(sf::Color::Black);
        BFSmilli.setPosition(sf::Vector2f(WINDOW_WIDTH / 4 - WINDOW_WIDTH / 12, WINDOW_HEIGHT / 2 + WINDOW_HEIGHT / 10));

        sf::Text BFSTag;
        BFSTag.setFont(font);
        BFSTag.setString("BFS (Breadth First Search):");
        BFSTag.setCharacterSize(35);
        BFSTag.setFillColor(sf::Color::Black);
        BFSTag.setPosition(sf::Vector2f(WINDOW_WIDTH / 4 - WINDOW_WIDTH / 7, WINDOW_HEIGHT / 2 - WINDOW_HEIGHT / 10));
        BFSTag.setStyle(sf::Text::Bold);

        sf::Text DFSTime;
        DFSTime.setFont(font);
        std::string DFSString = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(f - e).count());
        DFSTime.setString(DFSString);
        DFSTime.setCharacterSize(30);
        DFSTime.setFillColor(sf::Color::Black);
        DFSTime.setPosition(sf::Vector2f(3 * WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2));

        sf::Text DFSmilli;
        DFSmilli.setFont(font);
        DFSmilli.setString("milliseconds");
        DFSmilli.setCharacterSize(20);
        DFSmilli.setFillColor(sf::Color::Black);
        DFSmilli.setPosition(sf::Vector2f(4*WINDOW_WIDTH / 5 - WINDOW_WIDTH / 20, WINDOW_HEIGHT / 2 + WINDOW_HEIGHT / 10));

        sf::Text DFSTag;
        DFSTag.setFont(font);
        DFSTag.setString("DFS (Depth First Search):");
        DFSTag.setCharacterSize(35);
        DFSTag.setFillColor(sf::Color::Black);
        DFSTag.setPosition(sf::Vector2f(3 * WINDOW_WIDTH / 4 - WINDOW_WIDTH / 8, WINDOW_HEIGHT / 2 - WINDOW_HEIGHT / 10));
        DFSTag.setStyle(sf::Text::Bold);

        while (bfsDfsWindow.isOpen()) {
            sf::Event event {};
            while (bfsDfsWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    bfsDfsWindow.close();
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        bfsDfsWindow.close();
                    }
                }
            }
            bfsDfsWindow.clear(sf::Color::White);
            // Draw elements for BFS/DFS window here
            bfsDfsWindow.draw(BFSTime);
            bfsDfsWindow.draw(DFSTime);
            bfsDfsWindow.draw(BFSmilli);
            bfsDfsWindow.draw(DFSmilli);
            bfsDfsWindow.draw(BFSTag);
            bfsDfsWindow.draw(DFSTag);
            bfsDfsWindow.display();
        }
    }
    if (START_ButtonClicked) {
        auto itemWindow = sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "items", sf::Style::Close);
        std::vector<Item> myItems = graph.orderByRatingScore(selectedMain, selectedSub);
        Item currentItem = myItems[0];

        sf::Text objectName;
        objectName.setFont(font);
        objectName.setString(currentItem.getName());
        objectName.setCharacterSize(24);
        objectName.setFillColor(sf::Color::Black);
        objectName.setStyle(sf::Text::Bold | sf::Text::Underlined);
        objectName.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 10));
        auto objectNameRect = objectName.getLocalBounds();
        objectName.setOrigin(objectNameRect.left + objectNameRect.width / 2, objectNameRect.top);

        sf::Text objectRating;
        objectRating.setFont(font);
        objectRating.setString("Rating: " + std::to_string(currentItem.getRating()).substr(0,3) + " stars");
        objectRating.setCharacterSize(15);
        objectRating.setFillColor(sf::Color::Black);
        objectRating.setStyle(sf::Text::Bold);
        objectRating.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, 2 * WINDOW_HEIGHT / 10));
        auto objectRatingRect = objectRating.getLocalBounds();
        objectRating.setOrigin(objectRatingRect.left + objectRatingRect.width / 2, objectRatingRect.top);

        sf::Text objectPrice;
        objectPrice.setFont(font);
        objectPrice.setString(currentItem.getPrice());
        objectPrice.setCharacterSize(15);
        objectPrice.setFillColor(sf::Color::Black);
        objectPrice.setStyle(sf::Text::Bold);
        objectPrice.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, 3 *  WINDOW_HEIGHT / 10));
        auto objectPriceRect = objectPrice.getLocalBounds();
        objectPrice.setOrigin(objectPriceRect.left + objectPriceRect.width / 2, objectPriceRect.top);

        sf::Texture objectImageTexture;
        if (loadItemImage(currentItem)) {
            std::cout << "Image loaded Successfully" << std::endl;
            if (!objectImageTexture.loadFromFile("Image/THEIMAGE.jpg")) {
                perror("Couldn't load texture.");
            }
        }
        else {
            std::string failedURL = "https://cdn.vectorstock.com/i/500p/36/49/no-image-symbol-missing-available-icon-gallery-vector-43193649.jpg";
            const char* dst = "Image/imageFailed.jpg";
            URLDownloadToFile(NULL, failedURL.c_str(), dst, 0, NULL);
            if (!objectImageTexture.loadFromFile("Image/imageFailed.jpg")) {
                perror("Couldn't load texture.");
            }
        }
        sf::Sprite objectImage;
        objectImage.setTexture(objectImageTexture);
        objectImage.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, 4 * WINDOW_HEIGHT / 10));
        auto objectImageRect = objectImage.getLocalBounds();
        objectImage.setOrigin(sf::Vector2f(objectImageRect.left + objectImageRect.width/2, objectImageRect.top));

        while (itemWindow.isOpen()) {
            sf::Event event {};
            while(itemWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    itemWindow.close();
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        itemWindow.close();
                    }
                }
            }
            itemWindow.clear(sf::Color::White);
            itemWindow.draw(objectName);
            itemWindow.draw(objectPrice);
            itemWindow.draw(objectImage);
            itemWindow.draw(objectRating);
            itemWindow.display();
        }
    }

    return 0;
}