#include <iostream>
#include <string>
using namespace std;

int main(){
    
    // define variables
    int odoStart, odoEnd, rentalDays, month, amtMiles;
    double totalCharge = 0.0;
    string name, carType;
    cout << "Odometer at start: ";
    cin >> odoStart;
    cout << "Odometer at end: ";
    cin >> odoEnd;
    cout << "Rental days: ";
    cin >> rentalDays;
    cin.ignore(10000, '\n');
    cout << "Customer name: ";
    getline(cin, name);
    cout << "Luxury car? (y/n): ";
    getline(cin, carType);
    cout << "Month (1=Jan, 2=Feb, etc.): ";
    cin >> month;
    // define prices
    
    const int BASE_NONLUXURY = 33;
    const int BASE_LUXURY = 61;
    const double FIRST_INTERVAL = 0.27;
    const double SECOND_INTERVAL_WINTER = 0.27;
    const double SECOND_INTERVAL_NOWINTER = 0.21;
    const double THIRD_INTERVAL = 0.19;
    
    // check errors
    // error types: 1 = negative starting odometer, 2 = ending odometer less than starting odometer
    // 3 = the number of rental days is not positive, 4 = empty customer name
    // 5 = luxury status is not y or n, 6 = meaningless number of month
    
    int wrongType = 0;
    
    if (month > 12 || month < 1)
        wrongType = 6;
    if (carType != "y" && carType != "n")
        wrongType = 5;
    if (name == "")
        wrongType = 4;
    if (rentalDays <= 0)
        wrongType = 3;
    if (odoEnd < odoStart)
        wrongType = 2;
    if (odoStart < 0)
        wrongType = 1;
    
    
    // calculate rental charge
    
    if (wrongType == 1){
        cout << "---" << endl << "The starting odometer reading must be nonnegative." << endl;
    }
    else if (wrongType == 2){
        cout << "---" << endl << "The final odometer reading must be at least as large as the starting reading." << endl;
    }
    else if (wrongType == 3){
        cout << "---" << endl << "The number of rental days must be positive." << endl;
    }
    else if (wrongType == 4){
        cout << "---" << endl << "You must enter a customer name." << endl;
    }
    else if (wrongType == 5){
        cout << "---" << endl << "You must enter y or n." << endl;
    }
    else if (wrongType == 6){
        cout << "---" << endl << "The month number must be in the range 1 through 12." << endl;
    }
    else{
        amtMiles = odoEnd - odoStart;
        if(carType == "y")
            totalCharge = rentalDays * BASE_LUXURY;
        else
            totalCharge = rentalDays * BASE_NONLUXURY;
        if(amtMiles <= 100){
            totalCharge += FIRST_INTERVAL * amtMiles; // no more than 100 miles
        }
        else{
            double currentPrice = 0.0;
            if(month == 12 || month < 4)
                currentPrice = SECOND_INTERVAL_WINTER;
            else
                currentPrice = SECOND_INTERVAL_NOWINTER;
            
            if(amtMiles <= 400)
                totalCharge = totalCharge + FIRST_INTERVAL * 100 + currentPrice * (amtMiles - 100);
            else
                totalCharge = totalCharge + FIRST_INTERVAL * 100 + currentPrice * 300 + THIRD_INTERVAL * (amtMiles-400);
        }
        cout.setf(ios::fixed);
        cout.precision(2);
        cout << "---" << endl << "The rental charge for " << name << " is $" << totalCharge << endl;
    }
    
}
