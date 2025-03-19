#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;

class AIChatbot {
private:
    map<string, vector<string>> knowledgeBase; // Stores predefined question-response pairs
    vector<string> conversationHistory;        // Stores user input history

    // Convert input to lowercase
    string toLowerCase(string str) {
        for (char &c : str) c = tolower(c);
        return str;
    }

    // Remove punctuation
    string cleanString(string str) {
        string result = "";
        for (char c : str) {
            if (isalpha(c) || c == ' ') {
                result += c;
            }
        }
        return result;
    }

    // Check if input contains a keyword
    bool containsKeyword(string input, string keyword) {
        return input.find(keyword) != string::npos;
    }

public:
    AIChatbot() {
        srand(time(0)); // Random seed

        // Predefined Knowledge Base
        knowledgeBase["hello"] = {"Hi there! How can I help you?", "Hello! Nice to meet you!"};
        knowledgeBase["how are you"] = {"I'm an AI, so I don't have feelings, but I'm ready to chat!", "I'm just a bot, but I'm functioning perfectly!"};
        knowledgeBase["who are you"] = {"I'm a simple AI chatbot created in C++!", "I am Chatbot, your virtual assistant!"};
        knowledgeBase["what is your name"] = {"You can call me Chatbot!", "I am just a C++ chatbot."};
        knowledgeBase["bye"] = {"Goodbye! Have a great day!", "See you later!", "Bye! Take care!"};
        knowledgeBase["tell me a joke"] = {
            "Why don't skeletons fight each other? Because they don't have the guts!",
            "What did one ocean say to the other ocean? Nothing, they just waved!"
        };
        knowledgeBase["what is c++"] = {"C++ is a powerful programming language used for system programming, game development, and more!"};
        knowledgeBase["what is ai"] = {"AI stands for Artificial Intelligence. It is used to make machines think and learn like humans!"};
        knowledgeBase["what time is it"] = {"I don't have a clock, but your system does!", "Check your phone or watch for the exact time!"};
    }

    // Store user input in history
    void learn(string input) {
        conversationHistory.push_back(input);
    }

    // Generate a response
    string getResponse(string input) {
        input = toLowerCase(cleanString(input));

        // Check if the input has a direct response in the knowledge base
        for (const auto &entry : knowledgeBase) {
            if (containsKeyword(input, entry.first)) {
                vector<string> responses = entry.second;
                return responses[rand() % responses.size()];
            }
        }

        // If no match found, use a random response
        if (!conversationHistory.empty()) {
            return "Hmm, I don't know much about that, but you mentioned: \"" + conversationHistory[rand() % conversationHistory.size()] + "\" earlier.";
        }

        return "I'm not sure how to respond to that. Can you ask something else?";
    }
};

int main() {
    AIChatbot chatbot;
    string userInput;

    cout << "AI Chatbot (Type 'exit' to quit)\n";

    while (true) {
        cout << "\nYou: ";
        getline(cin, userInput);

        if (userInput == "exit") {
            cout << "AI: Goodbye! Have a great day!\n";
            break;
        }

        chatbot.learn(userInput); // Store input
        cout << "AI: " << chatbot.getResponse(userInput) << endl;
    }

    return 0;
}
