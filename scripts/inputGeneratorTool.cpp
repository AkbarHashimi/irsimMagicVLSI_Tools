#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <string>
using std::string;
using std::to_string;

#include <vector>
using std::vector;

#include <fstream>
using std::ofstream;

#include <ios>
using std::ios_base;

#include <istream>
using std::ws;

void isArrayF(vector<string> & in, string uInput);
void isInstArray(vector<string> & in, string uInput);
void Inst(vector<string> & in, string uInput);


int main()
{
    //prompts
    //is it an array of items you want?
    //is an instance array?

    vector<string> inputs;

    string userInput = "";
    bool isArray = false;
    bool isInst = false;


    bool again = true;

    while (again)
    {
        cout << "would you like to enter another value? type 'yes' to continue" << endl;

        cin >> userInput;

        for (int i = 0; i < userInput.size(); i++)
        {
            userInput[i] = tolower(userInput[i]);
        }

        if (userInput == "yes")
        {

            //here we start asking questions and writing to file

            cout << "please enter the name of the new item you wish to put into the list" << endl;
            string userStoredValue = "";
            cin >> userStoredValue;

            cout << "Is the item an array item? type 'yes' if that is the case" << endl;

            cin >> userInput;

            for (int i = 0; i < userInput.size(); i++)
            {
                userInput[i] = tolower(userInput[i]);
            }

            if (userInput == "yes")
            {   
                isArray = true;
            }

            cout << "Is the item an instance of a cell? type 'yes' if that is the case" << endl;

            cin >> userInput;

            for (int i = 0; i < userInput.size(); i++)
            {
                userInput[i] = tolower(userInput[i]);
            }

            if (userInput == "yes")
            {   
                isInst = true;
            }

            if (isArray && isInst) //both array and instance
            {
                isInstArray(inputs,userStoredValue);
            }
            else if (isInst) //just an instance
            {
                Inst(inputs,userStoredValue);
            }
            else if (isArray) //just an array of items
            {
                isArrayF(inputs, userStoredValue);
            }
            else //singular item
            {
                inputs.push_back(userStoredValue);
            }


            


            //reset flags
            isArray = false;
            isInst = false;

        }
        else
        {
            cout << "you have decided to quit entering values" << endl;
            again = false;
        }


    }

    cout << "would you like to write the values to a file?" << endl;

    cin >> userInput;

    for (int i = 0; i < userInput.size(); i++)
    {
        userInput[i] = tolower(userInput[i]);
    }

    if (userInput == "yes" && inputs.size() != 0) //write to file
    {
        ofstream outfile;
        vector<string>::iterator tracker = inputs.begin();

        outfile.open(*tracker + ".in", ios_base::out);

        

        for (; tracker != inputs.end(); tracker++)
        {
            outfile << *tracker + " ";
        }

        outfile.close();

    }
    else
    {
        cout << "you have decided to not write values to file. Quitting program" << endl;
    }

}

void isArrayF(vector<string> & in, string uInput)
{
    cout << "What is the beginning index you want?" << endl;
    int beginIndex = 0;
    int endIndex = 0;

    try
    {
        string temp = "";
        getline(cin >> ws, temp);

        beginIndex = stoi(temp);

        cout << "what is the ending index you want?" << endl;

        getline(cin >> ws,temp);

        endIndex = stoi(temp);

    }
    catch(const std::exception& e)
    {
        cout << "did not convert to a number properly" << endl;
        return;
    }
    
    if (beginIndex > endIndex || beginIndex < 0 || endIndex < 0)
    {
        cout << "invalid indices" << endl;
        return;
    }

    for (int index = beginIndex; index < (endIndex + 1); index++)
    {
        string output = uInput + to_string(index);

        in.push_back(output);
    }

}

void isInstArray(vector<string> & in, string uInput) //uInput is the net name on the innermost layer
{
    cout << "please enter the cell instance name" << endl;

    string cellInstanceName = "";

    cin >> cellInstanceName;

    cout << "please enter instance number" << endl;
    int instanceNum = 0;
    int beginIndex = 0;
    int endIndex = 0;

    try
    {
        string temp;
        getline(cin >> ws,temp);

        instanceNum = stoi(temp);

        cout << "please enter beginning index" << endl;
        
        getline(cin >> ws,temp);
        beginIndex = stoi(temp);

        cout << "please enter the ending index" << endl;

        getline(cin >> ws,temp);
        endIndex = stoi(temp);


    }
    catch(const std::exception& e)
    {
        cout << "invalid number entered" << endl;
        return;
    }

    if (beginIndex > endIndex | beginIndex < 0 | endIndex < 0)
    {
        cout << "invalid indices" << endl;
        return;
    }

    for (int index = beginIndex; index < (endIndex + 1); index++ )
    {
        string output = "{" + cellInstanceName + "_" + to_string(instanceNum) + "[" + to_string(index) + "]/" + uInput + "}";
        in.push_back(output);
    }

}

void Inst(vector<string> & in, string uInput)
{
    string output = "{";
    string cellInstance = "";
    int instanceNumber = 0;

    bool again = true;

    while (again)
    {
        cout << "Please enter the current level of cell instance" << endl;

         cin >> cellInstance;

        try
        {
            cout << "Please enter instance number" << endl;
            string temp = "";

            getline(cin >> ws,temp);

            instanceNumber = stoi(temp);

            output += cellInstance + "_" + to_string(instanceNumber) + "/";


            cout << "do you have more instances to type? type 'yes' if so" << endl;

            cin >> temp;

            for (int i = 0; i < temp.size(); i++)
            {
                temp[i] = tolower(temp[i]);
            }

            if (temp != "yes")
            {
                again = false;
            }

        }
        catch(const std::exception& e)
        {
            cout << "invalid value" << endl;
            return;
        
        }

    }

    output += uInput + "}";
    
    in.push_back(output);
    

}