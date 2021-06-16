#include <iostream>
using namespace std;

class Package{

    private: 
        double weightKg;
        double costPerKilo;

    public:

        // Constructor
        Package(double weightInput, double costInput){
            this->weightKg = weightInput;
            this->costPerKilo = costInput;
        }
        
        // Accessors
        double getWeight(){
            return this->weightKg;
        }

        double getCost(){
            return this->costPerKilo;
        }

        double calculateCost(){
            double weight, cost;

            weight = getWeight();
            cost = getCost();

            return weight * cost;
        }

};

// Derived class 1
class TwoDayPackage : public Package{
    protected:
        double flatFee;

    public:

        // Constructor
        TwoDayPackage(double weight, double cost, double fee) : Package(weight,cost){
            this->flatFee = fee; 
        }

        // Accessor
        double getFee(){
            return this->flatFee;
        }

        double calculateCost(){
            return Package::calculateCost() + getFee();
        }
};

// Derived Class 2
class OvernightPackage : public Package{
    protected:
        double feePerKg;
    
    public:

        // Constructor
        OvernightPackage(double weight, double cost, double kilogramFee) : Package(weight,cost){
            this->feePerKg = kilogramFee;
        }

        // Accessor 
        double getFeePerKg(){
            return this->feePerKg;
        }

        double calculateCost(){
            return Package::calculateCost() + (Package::getWeight() * getFeePerKg());
        }
};

int main()
{
    double one,two,three,four;

    cin >> one;
    cin >> two;
    cin >> three;
    cin >> four;

    Package packageInit(one,two);
    TwoDayPackage twoDay(one,two,three);
    OvernightPackage overnight(one,two,four);

    //Printing the calculated using printf to have two decimal places in double data type
    printf("%.2lf ",packageInit.calculateCost());
    printf("%.2lf ",twoDay.calculateCost());
    printf("%.2lf\n",overnight.calculateCost());

    return 0;
}
