
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <fstream>
using std::ofstream;

#include <ios>
using std::ios_base;

/*

    General logic

    Arguments at [1] onwards will have the necessary data to generate a .cmd file

    The first 3 arguments given by console [1] ... [3] will correspond to:
    [1] - fileName to save to
    [2] - name for VDD
    [3] - name for VSS
    
    Arguments at [4] onwards are inputs and outputs

    input arguments come first, then separated by '.' next comes outputs

    ex: irsimCmdCreationTool fileName VDD VSS input1 input2 input3 . out1 out2 out3




*/

void genericMsg(bool Power)
{
    if (Power)
    {
        cout << "Arguments at [1] onwards will have the necessary data to generate a .cmd file" << endl;
        cout << "The first 3 arguments given by console [1] ... [3] will correspond to:" << endl;
        cout << "[1] - fileName to save to" << endl;
        cout << "[2] - name for VDD" << endl;
        cout << "[3] - name for VSS" << endl;
    
        cout << "Arguments at [4] onwards are inputs and outputs" << endl;
    
        cout << "input arguments come first, then separated by '.' next comes outputs" << endl;
    
        cout << "ex: irsimCmdCreationTool fileName VDD VSS input1 input2 input3 . out1 out2 out3" << endl;
    }
    else
    {
        cout << "Arguments at [1] onwards will have the necessary data to generate a .cmd file" << endl;
        cout << "[1] - fileName to save to" << endl;
    
        cout << "Arguments at [2] onwards are inputs and outputs" << endl;
    
        cout << "input arguments come first, then separated by '.' next comes outputs" << endl;
    
        cout << "ex: irsimCmdCreationTool fileName input1 input2 input3 . out1 out2 out3" << endl;
    }


}


int main(int argc, char* argv[])
{
    bool Pwr = false;
    int argAmt = 4; //minimum argument amount

    cout << "Do you have a VDD name and VSS name? type 'yes' if so." << endl;
    string userInput;

    cin >> userInput;

    for (int i = 0; i < userInput.size(); i++)
    {
        userInput[i] = tolower(userInput[i]);
    }

    if (userInput == "yes")
    {
        Pwr = true;
        argAmt = 5;
    }


    if (argc > argAmt)
    {
        vector <string> inputs;
        vector <string> outputs;
        string VDD_name = "";
        string VSS_name = "";

        string fileName = argv[1];

        if (Pwr)
        {
            VDD_name = argv[2];
            VSS_name = argv[3];
        }

        
        string temp = "";
        bool dotFound = false;
        bool outPutFound = false;
        bool quitTime = false;

        string validStr = "";

        if (fileName == ".")
        {
            quitTime = true;
        }

        if (Pwr)
        {
            
            if (VDD_name == "." || VSS_name == "." )
            {
                quitTime = true;
            }

            temp = argv[4];

            if (temp == ".")
            {
                quitTime = true;
            }

        }
        else
        {
            temp = argv[2];
        }

        if (temp == "." || temp == "")
        {
            quitTime = true;
        }

        int startPoint = 0;

        if (Pwr)
        {
            startPoint = 4;
        }
        else
        {
            startPoint = 2;
        }


        if ( quitTime )
        {
            cout << "Invalid data found '.'" << endl;
            genericMsg(Pwr);
        }   
        else
        {
            string value = "";
            for (int i = startPoint; i < argc && !quitTime; i++)
            {
                value = argv[i];

                if(dotFound) //time to store outputs
                {
                    if (value == ".")
                    {
                        cout << "ERROR: Two '.' detected" << endl;
                        genericMsg(Pwr);
                        quitTime = true;
                    }
                    else
                    {
                        outPutFound = true;
                        outputs.push_back(argv[i]);
                    }
                }
                else
                {
                    if (value == ".") //detected '.'
                    {   
                        dotFound = true;
                    }
                    else //store inputs
                    {
                        inputs.push_back(argv[i]);
                    }
                }
                
                
            }

            if (outPutFound) //there were outputs
            {

                cout << "The input was this: " << endl;

                cout << "filename: " << fileName << ".cmd" << endl;

                if (Pwr)
                {
                    cout << "VDD name: " << VDD_name << endl;
                    cout << "VSS name: " << VSS_name << endl;
                }

                if (inputs.size() + outputs.size() < 10)
                {
                    cout << "Inputs: " << endl;

                    for (vector<string>::iterator in_iter = inputs.begin(); in_iter != inputs.end(); ++in_iter)
                    {
                        cout << *in_iter << endl; 
                    }

                    cout << "Outputs: " << endl;

                    for (vector<string>::iterator out_iter = outputs.begin(); out_iter != outputs.end(); ++out_iter)
                    {
                        cout << *out_iter << endl; 
                    }



                }
                else
                {
                    cout << "number of inputs + outputs is 10 or greater, will not display them" << endl;
                }




                cout << "" << endl;
                cout << "Is this what you want? type 'yes' if this correct " << endl;

                
                userInput = "";

                cin >> userInput;

                for (int i = 0; i < userInput.size(); i++)
                {
                    userInput[i] = tolower(userInput[i]);
                }

                if (userInput == "yes") //time to do the file writing 
                {

                    ofstream outfile;

                    outfile.open(fileName + ".cmd", ios_base::out);

                    if (Pwr)
                    {
                        outfile << "analyzer " << VDD_name << " " << VSS_name;
                    }
                    else
                    {
                        outfile << "analyzer";
                    }

		

                    for (vector<string>::iterator in_iter = inputs.begin(); in_iter != inputs.end(); ++in_iter) //write the inputs to file
                    {
                        outfile << " " << *in_iter;
                    }

                    for (vector<string>::iterator out_iter = outputs.begin(); out_iter != outputs.end(); ++out_iter)
                    {
                        outfile << " " << *out_iter;
                    }

                    outfile << "\n";
                    
                    if (Pwr)
                    {
                        outfile << "h " << VDD_name << "\n";
                        outfile << "l " << VSS_name << "\n";
                    }


                    for (int i = 0; i < ( 1 << inputs.size() ); i++) //row amount
                    {
                        int copy = i;

                        for (vector<string>::iterator in_iter = inputs.begin(); in_iter != inputs.end(); ++in_iter) //write the inputs to file
                        {
                            if (copy & 1)
                            {
                                outfile << "h " << *in_iter;
                            }
                            else
                            {
                                outfile << "l " << *in_iter;
                            }

                            outfile << "\n";

                            copy = copy >> 1;
                        } //single row outputs

                        outfile << "s\n";
                        
                    }

                    outfile << "\n";

                    outfile.close();

                }
                else
                {
                    cout << "you did not type 'yes' goodbye." << endl;
                }


            }
            else
            {
                cout << "ERROR: No outputs found" << endl;
                genericMsg(Pwr);
                
            }

            
            
            /*
            for (vector<string>::iterator in_iter = inputs.begin(); in_iter != inputs.end(); ++in_iter)
            {
                cout << "input: " << *in_iter << endl; 
            }

            for (vector<string>::iterator out_iter = outputs.begin(); out_iter != outputs.end(); ++out_iter)
            {
                cout << "output: " << *out_iter << endl; 
            }

            */


            


        }



    }
    else
    {
        cout << "ERROR: Too few arguments passed in" << endl;
        genericMsg(Pwr);
    }
    

}
