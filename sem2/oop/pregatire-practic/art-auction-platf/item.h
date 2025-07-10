#pragma once  
#include <string>  
#include <vector>  
#include <tuple>

using std::vector;  
using std::string;  
using std::tuple;  
using std::istream;  
using std::ostream;  

class Item {  
private:  
   string name;  
   string category;  
   int price;  
   vector<tuple<int, string, int>> offersList;  

public:  
   Item() {};  
   Item(string name, string category, int price, vector<tuple<int, string, int>> offersList) :  
       name{ name }, category{ name }, price{ price }, offersList{ offersList } {  
   };  
   ~Item() {};  
   string getName() { return this->name; };  
   string getCategory() { return this->category; };  
   int getPrice() { return this->price; };  
   void setPrice(int newPrice) {  
       this->price = newPrice;  
   }  
   void addOffer(tuple<int, string, int> offer) {
       this->offersList.push_back(offer);  
   }  
   vector<tuple<int, string, int>> getOffersList() { return this->offersList; };  
   friend istream& operator>>(istream& is, Item& item);  
   friend ostream& operator<<(ostream& os, Item item);  
};