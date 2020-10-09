//Do NOT inline any functions
//Do NOT use const parameters
//Do NOT use const member functions
//Do NOT use static except where specifically noted
//Do NOT use pass-by-reference except where specifically noted

/*
 * Title: Project 1. Automat
 * Abstract: This program displays......
 * Author: Aryana Buelna
 * Email: abuelna@csumb.edu
 * Estimate: 15 hours
 * Date: 09/28/2001
*/

#include <iostream>
using namespace std;




class Food{ //store information about a food item
public://methods
    Food();
    Food(string name, int calories, double price);
    string getName();
    int getCalories();
    double getPrice();
    void SetName(string name);
    void setCalories(int calories);
    void setPrice(double price);
    void display();
private: //attributes
    string myName;
    int myCalories;
    double myPrice;
};

Food::Food() :Food("Let's Potato Chips", 500, 1.5)
{} //default constructor

Food::Food(string name, int calories, double price)
    : myName(name), myCalories(calories), myPrice(price)
{}

string Food::getName() {
    return myName;
}

int Food::getCalories() {
    return myCalories;
}

double Food::getPrice() {
    return myPrice;
}

void Food::SetName(string name) {
    myName = name;
}

void Food::setCalories(int calories) {
    myCalories = calories;
}

void Food::setPrice(double price) {
    myPrice = price;
}

void Food::display() {
    cout << myName << ": " << myCalories << " calories, $" << myPrice << endl;
}




class Drink{ //store information about a drink
public://methods
    Drink(); //default constructor
    Drink(string name, int ounces, double price);
    string getName();
    int getOunces();
    double getPrice();
    void setName(string name);
    void setOunces(int ounces);
    void setPrice(double price);
    void display();
private://attributes
    string myName;
    int myOunces;
    double myPrice;
};

Drink::Drink() :Drink("Coffee", 12, 1.5)
{} //default constructor

Drink::Drink(string name, int ounces, double price)
    : myName(name), myOunces(ounces), myPrice(price)
{}

string Drink::getName() {
    return myName;
}

int Drink::getOunces() {
    return myOunces;
}

double Drink::getPrice() {
    return myPrice;
}

void Drink::setName(string name) {
    myName = name;
}

void Drink::setOunces(int ounces) {
    myOunces = ounces;
}

void Drink::setPrice(double price) {
    myPrice = price;
}

void Drink::display() {
    cout << myName << ": " << myOunces << " ounces, $" << myPrice << endl;
}




const int AUTOMAT_MAX = 10; //maximum capacity of array //0,1,2,3,4,5,6,7,8,9 //control array bounds
typedef Food QueueFood;
typedef Drink QueueDrink;

class Automat{ //vending machine that holds two queues: 1 for foods, 1 for drinks
public: //methods
    Automat();
    bool emptyFood();
    bool emptyDrink();
    void enqueue(Food f);
    void enqueue(Drink d);
    void dequeueFood();
    void dequeueDrink();
    Food frontFood();
    Drink frontDrink();
    int foodCount();
    int drinkCount();
    int getTotalCalories();
    int getTotalOunces();
    double getTotalPrice();
    void display();
private: //attributes
    int myFoodFront;
    int myFoodBack;
    int myDrinkFront;
    int myDrinkBack;
    Food myFood[AUTOMAT_MAX]; //array of Food objects
    Drink myDrink[AUTOMAT_MAX]; //array of Drink objects
};

Automat::Automat() :myFoodFront(0), myFoodBack(0), myDrinkFront(0), myDrinkBack(0)
{} //default constructor

bool Automat::emptyFood() {//return true if there are no food items, false otherwise
    return myFoodFront == myFoodBack;
}

bool Automat::emptyDrink() {
    //return true if there are no drink items, false otherwise
    return myDrinkFront == myDrinkBack;
}

void Automat::enqueue(Food f) { //Add a Food item to the back of the Food queue
    int newBackFood = (myFoodBack + 1) % AUTOMAT_MAX;
    if(newBackFood != myFoodFront) { //queue isn't full
        myFood[myFoodBack] = f;
        myFoodBack = newBackFood;
        }else{
        cerr <<  "Automat food full; new food not added" << endl;
    }
}

void Automat::enqueue(Drink d) { //Add a Drink item to the back of the Drink queue
    int newBackDrink = (myDrinkBack + 1) % AUTOMAT_MAX;
    if(newBackDrink != myDrinkFront) { //queue isn't full
        myDrink[myDrinkBack] = d;
        myDrinkBack = newBackDrink;
    }else{
        cerr <<  "Automat drink full; new drink not added" << endl;
    }
}

void Automat::dequeueFood() { //Move myFoodFront forward to remove the frontmost Food
    if(!emptyFood()){
        myFoodFront = (myFoodFront + 1) % AUTOMAT_MAX;
    }else{
        cerr << "Automat food is empty. Can't remove food item." << endl;
    }
}

void Automat::dequeueDrink() { //Move myDrinkFront forward to remove the frontmost Drink
    if(!emptyDrink()){
        myDrinkFront = (myDrinkFront + 1) % AUTOMAT_MAX;
    }else{
        cerr << "Automat drink is empty. Can't remove drink item." << endl;
    }
}

Food Automat::frontFood() { //Get the frontmost Food item
    if(!emptyFood()){
        return (myFood[myFoodFront]);
    }else{
        cerr << "Queue empty, returning garbage value" << endl;
        QueueFood garbage;
        return garbage;
    }
}

Drink Automat::frontDrink() { //Get the frontmost Drink item
    if(!emptyDrink()){
        return (myDrink[myDrinkFront]);
    }else{
        cerr << "Queue empty, returning garbage value" << endl;
        QueueDrink garbage;
        return garbage;
    }
}

int Automat::foodCount() { //Get the count of Food items currently in the Automat
    int countF = 0;
    for(int i = myFoodFront; i != myFoodBack; i = (i+1) % AUTOMAT_MAX){
        countF++;
    }
    return countF;
}

int Automat::drinkCount() { //Get the count of Drink items currently in the Automat
    int countD = 0;
    for(int i = myDrinkFront; i != myDrinkBack; i = (i+1) % AUTOMAT_MAX){
        countD++;
    }
    return countD;
}

int Automat::getTotalCalories() { //Return the sum of the calories of all Food items stored
    int sumF = 0;
    for(int i = myFoodFront; i != myFoodBack; i = (i+1) % AUTOMAT_MAX){
        sumF += myFood[i].getCalories();
    }
    return sumF;
}

int Automat::getTotalOunces() { //Return the sum of the ounces of all Drink items stored
    double sumD = 0;
    for(int i = myDrinkFront; i != myDrinkBack; i = (i+1) % AUTOMAT_MAX){
        sumD += myDrink[i].getOunces();
    }
    return sumD;
}
double Automat::getTotalPrice() { //Return the sum of the prices of all Food and Drink items

    double sumF = 0;
    for(int i = myFoodFront; i != myFoodBack; i = (i+1) % AUTOMAT_MAX){
        sumF += myFood[i].getPrice();
    }

    double sumD = 0;
    for(int i = myDrinkFront; i != myDrinkBack; i= (i+1) % AUTOMAT_MAX){
        sumD += myDrink[i].getPrice();
    }

    double sumP = sumD + sumF;

    return sumP;
}

void Automat::display() { //Print out the full Automat state; see examples below
    cout << "Automat:" << endl;
    cout << "  Food:" << endl;
    if(myFoodBack > myFoodFront){
        for(int i = myFoodFront; i < myFoodBack; i++){
            cout << "      " << myFood[i].getName() << ": " << myFood[i].getCalories() << " calories, $" << myFood[i].getPrice() << endl;
        }
    }else{
        for(int i = myFoodFront; i < AUTOMAT_MAX + myFoodBack; i++){
            cout << "      " << myFood[i % AUTOMAT_MAX].getName() << ": " << myFood[i % AUTOMAT_MAX].getCalories() << " calories, $" << myFood[i % AUTOMAT_MAX].getPrice() << endl;
        }
    }

    cout << "      " << foodCount() << " food items - Total Calories: " << getTotalCalories() << endl;


    cout << "  Drinks:" << endl;

    if(myDrinkBack > myDrinkFront){
        for(int i = myDrinkFront; i < myDrinkBack; i++){
            cout << "      " << myDrink[i].getName() << ": " << myDrink[i].getOunces() << " ounces, $" << myDrink[i].getPrice() << endl;
        }
    }else{
        for(int i = myDrinkFront; i < AUTOMAT_MAX + myDrinkBack; i++){
            cout << "      " << myDrink[i].getName() << ": " << myDrink[i].getOunces() << " ounces, $" << myDrink[i].getPrice() << endl;
        }
    }

    cout << "      " << drinkCount() << " drinks - Total Ounces: " << getTotalOunces() << endl;
    cout << endl;
}

const int ORDER_MAX = 5; //control array bounds //0,1,2,3,4
typedef Food StackFood;
typedef Drink StackDrink;

class Order{ //This class allows a user to add Food and/or Drink items to each seperate stack
public:
    Order();
    bool emptyFood();
    bool emptyDrink();
    void push(Food f);
    void push(Drink d);
    void popFood();
    void popDrink();
    Food topFood();
    Drink topDrink();
    int foodCount();
    int drinkCount();
    double getTotalPrice();
    void display();
    void cancel(Automat & a);
    void purchase();
    static int getTotalOrders();
private:
    int myFoodTop;
    int myDrinkTop;
    Food myFood[ORDER_MAX];
    Drink myDrink[ORDER_MAX];
    int static myTotalOrders;
};

int Order::myTotalOrders = 0;

Order::Order() :myFoodTop(-1), myDrinkTop(-1)
{ //default constructor
    myTotalOrders+=1;
}

bool Order::emptyFood() { //Return true if there are no Food items, false otherwise
    return myFoodTop == -1;
}

bool Order::emptyDrink() { //Return true if there are no Drink items, false otherwise
    return myDrinkTop == -1;
}

void Order::push(Food f) { //Add a Food item to the top of the Food stack
    if(myFoodTop < ORDER_MAX - 1){
        ++myFoodTop;
        myFood[myFoodTop] = f;
    }else{
        cerr << "Stack full. Can not add new food item to stack." << endl;
        return;
    }
}

void Order::push(Drink d) { //Add a Drink item to the top of the Drink stack
    if(myDrinkTop < ORDER_MAX - 1){
        ++myDrinkTop;
        myDrink[myDrinkTop] = d;
    }else{
        cerr << "Stack full. Can not add new drink item to stack." << endl;
        return;
    }
}

void Order::popFood() { //Move myFoodTop down to remove the topmost Food
    if ( !emptyFood()) {
        myFoodTop--;
    } else {
        cerr << "Stack is empty. Can not remove food item." << endl;
    }
}

void Order::popDrink() { //Move myDrinkTop down to remove the topmost Drink
    if ( !emptyDrink()) {
        myDrinkTop--;
    } else {
        cerr << "Stack is empty. Can not remove drink item." << endl;
    }
}

Food Order::topFood() { //Get the topmost Food item
    if ( !emptyFood()) {
        return (myFood[myFoodTop]);
    } else {
        cerr << "Stack is empty. Returning garbage value." << endl;
        StackFood garbage;
        return garbage;
    }
}

Drink Order::topDrink() { //Get the topmost Drink item
    if ( !emptyDrink()) {
        return (myDrink[myDrinkTop]);
    } else {
        cerr << "Stack is empty. Returning garbage value." << endl;
        StackDrink garbage;
        return garbage;
    }
}

int Order::foodCount() { //Get the count of Food items currently in the Order
    return myFoodTop + 1;
}

int Order::drinkCount() { //Get the count of Drink items currently in the Order
    return myDrinkTop + 1;
}

double Order::getTotalPrice() { //Return the sum of the prices of all Food and Drink items
    double totalF = 0;
    for(int i = myFoodTop; i >= 0; i--){
        totalF = totalF + myFood[i].getPrice();
    }
    double totalD = 0;
    for(int i = myDrinkTop; i >= 0; i--){
        totalD = totalD + myDrink[i].getPrice();
    }
    double totalAll = totalF + totalD;

    return totalAll;
}

void Order::display() { //Print out the full Automat state; see examples below

    cout << "Order: " << endl;
    cout << "   Food (" << foodCount() << " items):" << endl;
    for(int i = myFoodTop; i >= 0; i--){
        cout << "       ";
        myFood[i].display();
    }

    cout << "   Drink (" << drinkCount() << " items):" << endl;
    for(int i = myDrinkTop; i >= 0; i--){
        cout << "       " ;
        myDrink[i].display();
    }

    cout << "   Oder total: $" << getTotalPrice() << endl;
    cout << endl;

}

void Order::cancel(Automat & a) { //pop each item from each stack, in order, and enqueue into the AUTOMAT_MAX
    while(!emptyFood()){
        a.enqueue(topFood());
        popFood();
    }

    while(!emptyDrink()){
        a.enqueue(topDrink());
        popDrink();
    }

}

void Order::purchase() { //Should reset each stack
    myFoodTop = -1;
    myDrinkTop = -1;
}
int Order::getTotalOrders() { //A STATIC method to return myTotalOrders
    return myTotalOrders;
}


int main() {
    Automat a;
    a.enqueue(Food("Let's Potato Chips", 300, 1.50));
    a.enqueue(Food("Mini Donuts", 500, 1));
    a.enqueue(Drink("Coffee", 6, 5.50));
    a.enqueue(Drink("Nacho Drink", 22, 2.50));
    cout << "Starting Automat\n";
    a.display();

    Order o;
    o.push(a.frontFood());
    a.dequeueFood();
    o.push(a.frontDrink());
    a.dequeueDrink();
    cout << "Ordered one food, one drink\n";
    o.display();
    a.display();
    cout << "Canceled order\n";
    o.cancel(a);
    o.display();
    a.display();
    cout << "Ordered one food, one drink, purchased\n";
    o.push(a.frontFood());
    a.dequeueFood();
    o.push(a.frontDrink());
    a.dequeueDrink();
    o.purchase();
    o.display();
    a.display();



    return 0;
}
