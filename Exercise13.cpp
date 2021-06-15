#include <iostream>

using namespace std;

class Point{

    private:
        float x;
        float y;

    public:
        // Mutator and Constructor 
        Point(){
            x = 0; 
            y = 0;
        }

        Point(int tempX, int tempY){
            this->x = tempX;
            this->y = tempY;
        }

        // Accessor (since the x and y data members are private)
        int getXCoordinate(){
            return this->x;
        }

        int getYCoordinate(){
            return this->y;
        }

};

class Rectangle{
        private:
        Point topLeft;
        Point bottomRight;

        public:
            Rectangle(Point one, Point two){
                this->topLeft = one;
                this->bottomRight = two;
            }

            void display(){
                // Initialize X and Y coordinates
                int topLeft[2] = {this->topLeft.getXCoordinate(),this->topLeft.getYCoordinate()};
                int botRight[2] = {this->bottomRight.getXCoordinate(),this->bottomRight.getYCoordinate()};

        
                for (int i = 0; i <= botRight[1]; i++){
                    for (int j = 0; j <= botRight[0]; j++){
                        if ((j == topLeft[0] || j == botRight[0]) && i >= topLeft[1])
                            cout << "# ";
                        else if((i == topLeft[1] || i == botRight[1]) && j >= topLeft[0])
                            cout << "# ";
                        else 
                            cout << "  ";
                    }
                cout << endl;
                }
            
            }

            int area(){
                // Area of rectangle = (bottomRight.X - topLeft.X) * (bottomRight.Y - topLeft.Y)
                int answer = (this->bottomRight.getXCoordinate() - this->topLeft.getXCoordinate()) *
                (this->bottomRight.getYCoordinate() - this->topLeft.getYCoordinate());
                return answer;
            }

            int perimeter(){
                // Perimeter of rectangle = 2(bottomRight.X - topLeft.X) + 2(bottomRight.Y - topLeft.Y)
                int answer = (2 * (this->bottomRight.getXCoordinate() - this->topLeft.getXCoordinate())) +
                (2 * (this->bottomRight.getYCoordinate() - this->topLeft.getYCoordinate()));
                return answer;
            }

            void centerPoint(){
                // Midpoint Formula
                float x[2] = {this->topLeft.getXCoordinate(),this->bottomRight.getXCoordinate()};
                float y[2] = {this->topLeft.getYCoordinate(),this->bottomRight.getYCoordinate()};

                float xAnswer = (x[0] + x[1]) / 2;
                float yAnswer = (y[0] + y[1]) / 2;

                printf("(%.2f, %.2f) ",xAnswer,yAnswer);
            }

            bool checkSquare(){

                if (this->bottomRight.getXCoordinate() - this->topLeft.getXCoordinate() 
                 == this->bottomRight.getYCoordinate() - this->topLeft.getYCoordinate())
                    return true;
                else
                    return false;
            }
 


};

int main()
{
    int input1,input2,input3,input4;

    // Coordinate inputs
    cin >> input1;
    cin >> input2;
    Point oneInput(input1,input2);

    cin >> input3;
    cin >> input4;
    Point twoInput(input3,input4);

    // The first input must be less than and not equal to the second input
    if(oneInput.getXCoordinate() >= twoInput.getXCoordinate() 
    || oneInput.getYCoordinate() >= twoInput.getYCoordinate()){
        printf("Invalid coordinates. Please try again.\n");
        return 0;
    }

    Rectangle rect(oneInput,twoInput);

    cout << "\nArea: " << rect.area() << endl; // Prints the Area
    cout << "Perimeter: " << rect.perimeter() << endl; // Prints the Perimeter

    cout << "Center: "; 
    rect.centerPoint(); // Prints the Center
    cout << endl;

    bool isRectangle = rect.checkSquare();
    string booleanValue;

    if(isRectangle == 1)
        booleanValue = "Yes";
    else
        booleanValue = "No";

    cout << "Square: " << booleanValue << endl; // Prints the boolean value of the input being square

    cout << endl;
    
    rect.display(); // Prints the rectangle/square

    return 0;
}
