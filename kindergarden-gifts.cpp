#include <iostream>
#include <limits>
#include <string>
#include <memory>
#include <list>
#include <optional>
#include <sstream>
#include <vector>


using namespace std;

enum class RecommendedFor{
    boys,
    girls
};

enum class Flavor{
    sweet,
    salty
};

string to_string(RecommendedFor recommended_for) {
    switch (recommended_for) {
        case RecommendedFor::boys: return "Boys";
        case RecommendedFor::girls: return "Girls";
        default: return "Unknown";
    }
}

string to_string(Flavor flavor) {
    switch (flavor) {
        case Flavor::sweet: return "Sweet";
        case Flavor::salty: return "Salty";
        default: return "Unknown";
    }
}

optional<Flavor> intToFlavor(int value) {
    switch (value) {
        case 0: return Flavor::sweet;
        case 1: return Flavor::salty;
        default: return nullopt;
    }
}

optional<RecommendedFor> intToRecommendedFor(int value) {
    switch (value) {
        case 0: return RecommendedFor::boys;
        case 1: return RecommendedFor::girls;
        default: return nullopt;
    }
}

class Gift {

    private:

        string name;
        string recipient_name;

    public:

        string get_name() const { return name; }

        string get_recipient_name() const { return recipient_name; }

        int set_name(const string& item_name){

            if(item_name.length() > 50){
                cout<<"Name length exceeds maximum number of allowed characters (50)"<<endl;
                return 1;
            }
            name = item_name;
            return 0;
        }

        int set_recipient_name(const string& name){

            if(name.length() > 50){
                cout<<"Name length exceeds maximum number of allowed characters (50)"<<endl;
                return 1;
            }

            recipient_name = name;
            return 0;

        }
    
        virtual void display() const = 0;

        virtual ~Gift() = default;
};

class Article : public Gift {

    private:

        int quantity;
        Flavor flavor;
    
    public:

        void display() const override {
            cout << "==================== Article ====================" << endl;
            cout << "Name:           " << get_name() << endl;
            cout << "Quantity:       " << quantity << endl;
            cout << "Flavor:         " << to_string(flavor) << endl;
            cout << "Recipient Name: " << get_recipient_name() << endl;
            cout << "=================================================" << endl;
        }

        int get_quantity() const { return quantity; }

        Flavor get_flavor() const { return flavor; }

        int set_quantity(int article_quantity){

            if(article_quantity <= 0){
                cout<<"Quantity has to be at least 1"<<endl;
                return 1;
            }
         
            quantity = article_quantity;
            return 0;
        }

        int set_flavor(Flavor article_flavor){
            flavor = article_flavor;
            return 0;
        }
};

class Toy : public Gift {

    private:

        string color;
        RecommendedFor recommended_for;

    public:

        void display() const override {
            cout << "===================== Toy ======================" << endl;
            cout << "Name:           " << get_name() << endl;
            cout << "Recommended For:" << to_string(recommended_for) << endl;
            cout << "Color:          " << color << endl;
            cout << "Recipient Name: " << get_recipient_name() << endl;
            cout << "=================================================" << endl;
        }

        string get_color() const { return color; }

        RecommendedFor get_recommended_for() const { return recommended_for; }

        int set_color(const string& chosen_color){
            if(chosen_color.length() > 20){
                cout<<"Color exceeds maximum allowed characters (20)"<<endl;
                return 1;
            }
            color = chosen_color;
            return 0;
        }

        int set_recommended_for(RecommendedFor recommended_group){
            recommended_for = recommended_group;
            return 0;
        }
};

class Program{

    private: 

        list<unique_ptr<Gift>> gifts;
        
    public:

        void displayMenu() {
            int menu_choice;

            cout << "Main Menu: Please select the operation you wish to perform!" << endl;
            cout << "1. Display gifts" << endl;
            cout << "2. Create gift" << endl;
            cout << "3. Update gift" << endl;
            cout << "4. Delete gift" << endl;
            cout << "5. Search gifts" << endl;
            cout << "6. Exit" << endl;

            cout << "Option: ";

            getUserOption(menu_choice, 1, 6);

            switch (menu_choice) {
                case 1:
                    displayGifts();
                    break;
                case 2:
                    createGift();
                    break;
                case 3:
                    updateGift();
                    break;
                case 4:
                    deleteGift();
                    break;
                case 5:
                    searchGifts();
                    break;
                case 6:
                    cout << "Goodbye" << endl;
                    return;
                default:
                    cout << "Invalid option. Program will quit." << endl;
                    return; 
            }
        }

        void displayGifts() {

            if (gifts.empty()) {

                cout << "No gifts to display." << endl;

            } else {

                for (const auto& gift : gifts) {
                    gift->display();
                }
            }

            displayMenu();
        }

        void createGift(){
            
            int gift_choice;

            cout << "What gift would you like to add? (1. Article, 2. Toy, 3. Go Back)" << endl;

            getUserOption(gift_choice, 1, 3);

            if(gift_choice == 1){

                auto article = make_unique<Article>();
                setCommon(*article);
                setArticleProperties(*article);
                gifts.push_back(move(article));

            }
            else if(gift_choice == 2){

                auto toy = make_unique<Toy>();
                setCommon(*toy);
                setToyProperties(*toy);
                gifts.push_back(move(toy));

            }
            else if(gift_choice == 3){

                cout << "Sending you back to main menu" << endl;

            }
            displayMenu();
        }

        void searchGifts() {

            int search_choice;

            cout << "What would you like to search by?" << endl;
            cout << "1. Gift name" << endl;
            cout << "2. Gift recipient name" << endl;
            cout << "3. Flavor" << endl;
            cout << "4. Recommended for" << endl;
            cout << "5. Color" << endl;
            cout << "6. Go Back" << endl;

            getUserOption(search_choice, 1, 6);

            if (search_choice == 6) {
                displayMenu();
                return;
            }

            list<Gift*> matchingGifts;

            switch (search_choice) {
                case 1:
                    matchingGifts = searchByName();
                    break;
                case 2:
                    matchingGifts = searchByRecipientName();
                    break;
                case 3:
                    matchingGifts = searchByFlavor();
                    break;
                case 4:
                    matchingGifts = searchByRecommendedFor();
                    break;
                case 5:
                    matchingGifts = searchByColor();
                    break;
                default:
                    cout << "Invalid option." << endl;
                    return;
            }

            if (matchingGifts.empty()) {
                cout << "No matching gifts found." << endl;
            } else {
                for (const auto& gift : matchingGifts) {
                    gift->display();
                }
            }

            displayMenu();
        }


        void updateGift() {

            int update_choice;
            cout << "What attribute would you like to update?" << endl;
            cout << "1. Name" << endl;
            cout << "2. Recipient Name" << endl;
            cout << "3. Flavor (Articles)" << endl;
            cout << "4. Quantity (Articles)" << endl;
            cout << "5. Color (Toys)" << endl;
            cout << "6. Recommended For (Toys)" << endl;
            cout << "7. Go Back" << endl;

            getUserOption(update_choice, 1, 7);

            if (update_choice == 7) {
                displayMenu();
                return;
            }

            list<Gift*> matchingGifts = getMatchingGifts();
            if (matchingGifts.empty()) {
                cout << "No matching gifts found." << endl;
                displayMenu();
                return;
            }

            int index = 1;
            vector<Gift*> matchingGiftsVector;
            for (const auto& gift : matchingGifts) {
                cout << index << ". ";
                gift->display();
                matchingGiftsVector.push_back(gift);
                ++index;
            }

            cout << "Enter the numbers of the gifts you want to update, separated by spaces (or 'all' to update all): ";
            string input;
            getline(cin, input);

            vector<int> indicesToUpdate;
            if (input == "all") {
                for (int i = 1; i < index; ++i) {
                    indicesToUpdate.push_back(i);
                }
            } else {
                istringstream iss(input);
                int num;
                while (iss >> num) {
                    if (num >= 1 && num < index) {
                        indicesToUpdate.push_back(num);
                    } else {
                        cout << "Invalid index: " << num << endl;
                    }
                }
            }

            if (indicesToUpdate.empty()) {
                cout << "No valid indices selected." << endl;
                displayMenu();
                return;
            }

            for (int idx : indicesToUpdate) {
                Gift* gift = matchingGiftsVector[idx - 1];

                switch (update_choice) {
                    case 1:
                        updateName(*gift);
                        break;
                    case 2:
                        updateRecipientName(*gift);
                        break;
                    case 3:
                        if (Article* article = dynamic_cast<Article*>(gift)) {
                            updateFlavor(*article);
                        } else {
                            cout << "Gift at index " << idx << " is not an Article. Cannot update Flavor." << endl;
                        }
                        break;
                    case 4:
                        if (Article* article = dynamic_cast<Article*>(gift)) {
                            updateQuantity(*article);
                        } else {
                            cout << "Gift at index " << idx << " is not an Article. Cannot update Quantity." << endl;
                        }
                        break;
                    case 5:
                        if (Toy* toy = dynamic_cast<Toy*>(gift)) {
                            updateColor(*toy);
                        } else {
                            cout << "Gift at index " << idx << " is not a Toy. Cannot update Color." << endl;
                        }
                        break;
                    case 6:
                        if (Toy* toy = dynamic_cast<Toy*>(gift)) {
                            updateRecommendedFor(*toy);
                        } else {
                            cout << "Gift at index " << idx << " is not a Toy. Cannot update Recommended For." << endl;
                        }
                        break;
                    default:
                        cout << "Invalid attribute choice." << endl;
                        break;
                }
            }

            displayMenu();
        }

        void deleteGift() {
            list<Gift*> matchingGifts = getMatchingGifts();

            if (matchingGifts.empty()) {
                cout << "No matching gifts found." << endl;
                displayMenu();
                return;
            }

        
            int index = 1;
            vector<Gift*> matchingGiftsVector;
            for (const auto& gift : matchingGifts) {
                cout << index << ". ";
                gift->display();
                matchingGiftsVector.push_back(gift);
                ++index;
            }

            cout << "Enter the numbers of the gifts you want to delete, separated by spaces (or 'all' to delete all): ";
            string input;
            getline(cin, input);

            vector<int> indicesToDelete;
            if (input == "all") {
                for (int i = 1; i < index; ++i) {
                    indicesToDelete.push_back(i);
                }
            } else {
                istringstream iss(input);
                int num;
                while (iss >> num) {
                    if (num >= 1 && num < index) {
                        indicesToDelete.push_back(num);
                    } else {
                        cout << "Invalid index: " << num << endl;
                    }
                }
            }

            if (indicesToDelete.empty()) {
                cout << "No valid indices selected." << endl;
                displayMenu();
                return;
            }

            for (int idx : indicesToDelete) {
                Gift* giftToDelete = matchingGiftsVector[idx - 1];

                auto it = gifts.begin();
                while (it != gifts.end()) {
                    if (it->get() == giftToDelete) {
                        it = gifts.erase(it);
                        cout << "Gift deleted successfully." << endl;
                        break;
                    } else {
                        ++it;
                    }
                }
            }
            displayMenu();
        }
    private:

        list<Gift*> searchByName() {

            string name;
            cout << "Insert the name: ";
            getline(cin, name); 

            list<Gift*> matchingGifts;

            for (const auto& giftPtr : gifts) {
                if (giftPtr->get_name() == name) {
                    matchingGifts.push_back(giftPtr.get());
                }
            }

            return matchingGifts;
        }

        list<Gift*> searchByRecipientName() {

            string recipientName;
            cout << "Insert the recipient's name: ";
            getline(cin, recipientName);

            list<Gift*> matchingGifts;

            for (const auto& giftPtr : gifts) {
                if (giftPtr->get_recipient_name() == recipientName) {
                    matchingGifts.push_back(giftPtr.get());
                }
            }

            return matchingGifts;
        }

        list<Gift*> searchByFlavor() {
            int flavorChoice;
            cout << "Choose a flavor to search for (0. Sweet, 1. Salty): ";
            getUserOption(flavorChoice, 0, 1);

            auto flavorOpt = intToFlavor(flavorChoice);
            if (!flavorOpt.has_value()) {
                cout << "Invalid flavor choice." << endl;
                return {};
            }

            Flavor flavor = flavorOpt.value();
            list<Gift*> matchingGifts;

            for (const auto& giftPtr : gifts) {
                Article* article = dynamic_cast<Article*>(giftPtr.get());
                if (article && article->get_flavor() == flavor) {
                    matchingGifts.push_back(giftPtr.get());
                }
            }
            return matchingGifts;
        }

        list<Gift*> searchByRecommendedFor() {
            int recommendedForChoice;
            cout << "Who is it recommended for? (0. Boys, 1. Girls): ";
            getUserOption(recommendedForChoice, 0, 1);

            auto recommendedForOpt = intToRecommendedFor(recommendedForChoice);
            if (!recommendedForOpt.has_value()) {
                cout << "Invalid choice." << endl;
                return {};
            }

            RecommendedFor recommendedFor = recommendedForOpt.value();
            list<Gift*> matchingGifts;

            for (const auto& giftPtr : gifts) {
                Toy* toy = dynamic_cast<Toy*>(giftPtr.get());
                if (toy && toy->get_recommended_for() == recommendedFor) {
                    matchingGifts.push_back(giftPtr.get());
                }
            }
            return matchingGifts;
        }

        list<Gift*> searchByColor() {
            string color;
            cout << "Insert the color to search for: ";
            getline(cin, color);
            list<Gift*> matchingGifts;

            for (const auto& giftPtr : gifts) {
                Toy* toy = dynamic_cast<Toy*>(giftPtr.get());
                if (toy && toy->get_color() == color) {
                    matchingGifts.push_back(giftPtr.get());
                }
            }
            return matchingGifts;

        }

        void updateName(Gift& gift) {
            string newName;
            cout << "Enter new name: ";
            getline(cin, newName);
            if (gift.set_name(newName) == 0) {
                cout << "Name updated successfully." << endl;
            } else {
                cout << "Failed to update name." << endl;
            }
        }

        void updateRecipientName(Gift& gift) {
            string newRecipientName;
            cout << "Enter new recipient name: ";
            getline(cin, newRecipientName);
            if (gift.set_recipient_name(newRecipientName) == 0) {
                cout << "Recipient name updated successfully." << endl;
            } else {
                cout << "Failed to update recipient name." << endl;
            }
        }

        void updateFlavor(Article& article) {
            while (true) {
                int flavorChoice;
                cout << "Choose new flavor: (0. Sweet, 1. Salty) ";
                cin >> flavorChoice;

                if (cin.fail()) {
                    cout << "Invalid input. Please enter 0 or 1." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                auto flavorOpt = intToFlavor(flavorChoice);
                if (flavorOpt.has_value()) {
                    article.set_flavor(flavorOpt.value());
                    cout << "Flavor updated successfully." << endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                } else {
                    cout << "Invalid flavor choice. Please enter 0 or 1." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
        }

        void updateQuantity(Article& article) {
            while (true) {
                int quantity;
                cout << "Enter new quantity: ";
                cin >> quantity;

                if (cin.fail() || article.set_quantity(quantity) != 0) {
                    cout << "Invalid quantity." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                } else {
                    cout << "Quantity updated successfully." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
            }
        }

        void updateColor(Toy& toy) {
            cin.ignore(); 
            string newColor;
            cout << "Enter new color: ";
            getline(cin, newColor);
            if (toy.set_color(newColor) == 0) {
                cout << "Color updated successfully." << endl;
            } else {
                cout << "Failed to update color." << endl;
            }
        }

        void updateRecommendedFor(Toy& toy) {
            while (true) {
                int recommendedForChoice;
                cout << "Choose new recommended for: (0. Boys, 1. Girls) ";
                cin >> recommendedForChoice;

                if (cin.fail()) {
                    cout << "Invalid input. Please enter 0 or 1." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                auto recommendedForOpt = intToRecommendedFor(recommendedForChoice);
                if (recommendedForOpt.has_value()) {
                    toy.set_recommended_for(recommendedForOpt.value());
                    cout << "Recommended for updated successfully." << endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                } else {
                    cout << "Invalid choice. Please enter 0 or 1." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
        }

        list<Gift*> getMatchingGifts() {
            int search_choice;

            cout << "Search gifts by:" << endl;
            cout << "1. Gift name" << endl;
            cout << "2. Gift recipient name" << endl;
            cout << "3. Flavor" << endl;
            cout << "4. Recommended for" << endl;
            cout << "5. Color" << endl;
            cout << "6. Go Back" << endl;

            getUserOption(search_choice, 1, 6);

            if (search_choice == 6) {
                return {};
            }

            list<Gift*> matchingGifts;

            switch (search_choice) {
                case 1:
                    matchingGifts = searchByName();
                    break;
                case 2:
                    matchingGifts = searchByRecipientName();
                    break;
                case 3:
                    matchingGifts = searchByFlavor();
                    break;
                case 4:
                    matchingGifts = searchByRecommendedFor();
                    break;
                case 5:
                    matchingGifts = searchByColor();
                    break;
                default:
                    cout << "Invalid option." << endl;
                    break;
            }

            return matchingGifts;
        }

        void getUserOption(int& choice, int min, int max){

            while(true){

                cin >> choice;

                if(cin.fail() || (choice < min || choice > max)){
                    cout << "Invalid selection. Try again." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                } else {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
            }
        }

        void setCommon(Gift& gift){

            while(true){

                string name;

                cout << "Insert the name of the gift: "; 
                getline(cin, name);

                if(gift.set_name(name) == 0){
                    cout << "Gift name set to: " << gift.get_name() << endl;
                    break;
                }
            }

            while(true){

                string name;

                cout << "Insert the name of the recipient: "; 
                getline(cin, name);

                if(gift.set_recipient_name(name) == 0){
                    cout << "Recipient name set to: " << gift.get_recipient_name() << endl;
                    break;
                }
            }
        }

        void setArticleProperties(Article& article){
            
            while(true){
                int quantity;

                cout << "Enter quantity: ";
                cin >> quantity;

                if(cin.fail() || article.set_quantity(quantity) != 0){
                    cout << "Quantity you entered is invalid." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else{
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
            }

            while (true) {
                int flavorChoice;
                cout << "Choose a flavor: (0. Sweet, 1. Salty) ";
                cin >> flavorChoice;

                if (cin.fail()) {
                    cout << "Invalid input. Please enter 0 or 1." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                auto flavorOpt = intToFlavor(flavorChoice);
                if (flavorOpt.has_value()) {
                    article.set_flavor(flavorOpt.value());
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                } else {
                    cout << "Invalid flavor choice. Please enter 0 or 1." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

        }

        void setToyProperties(Toy& toy){

            while(true){

                string color;

                cout << "Insert the color: ";
                getline(cin, color);

                if(toy.set_color(color) == 0){
                    cout << "Toy color set to: " << toy.get_color() << endl;
                    break;
                }
            }

            while (true) {
                int recommendedForChoice;
                cout << "Who is it recommended for? (0. Boys, 1. Girls) ";
                cin >> recommendedForChoice;

                if (cin.fail()) {
                    cout << "Invalid input. Please enter 0 or 1." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                auto recommendedForOpt = intToRecommendedFor(recommendedForChoice);
                if (recommendedForOpt.has_value()) {
                    toy.set_recommended_for(recommendedForOpt.value());
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                } else {
                    cout << "Invalid choice. Please enter 0 or 1." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

        }

};

int main(){

    Program program;
    program.displayMenu();

    return 0;
}
