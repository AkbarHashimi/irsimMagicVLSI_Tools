
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
using std::fstream;
using std::ofstream;

#include <ios>
using std::ios_base;

#include <memory>
using std::unique_ptr;


int main()
{
	//non generic program

	/*
	
	inputs: 
	selector s0 s8
	outputs:
	out0 and out1 pairs

	create vectors

	add watches

	set vdd and vss

	loop through selector and step

	90 max

	out0 out1 - 45 indices at a time

	0 to 44
	45 to 89
	90 to 134
	135 to 179
	180 to 224
	225 to 255


	*/

	/*
	ofstream outfile;

	outfile.open("test.txt");

	string value = "";

	value += "testNewline";
	value += "\n";
	value += "anotherLine";

	outfile << value;

	outfile.close();
	*/

	int value = 0;
	int max = (1 << 9);

	ofstream outfile;

	outfile.open("decoder512_test.cmd");

	string temp = "";

	temp = "stepsize 50\n";

	outfile << temp;
	outfile.flush();

	//create log file

	temp = "logfile decoder512_test.log\n";

	outfile << temp;
	outfile.flush();

	temp = "";

	//create watches

	temp = "w VDD VSS\n";

	outfile << temp;
	outfile.flush();

	temp = "";

	//create vectors

	temp = "vector sel s8 s7 s6 s5 s4 s3 s2 s1 s0\n";

	outfile << temp;
	outfile.flush();

	temp = "vector out0to44 ";

	outfile << temp;
	outfile.flush();

	

	for (int i = 44; i >= 0; --i)
	{
		temp = "";

		temp += "{tester512_1_0[";
		temp += to_string(i);
		temp += "]/out1} ";

		temp += "{tester512_1_0[";
		temp += to_string(i);
		temp += "]/out0} ";

		outfile << temp;
		outfile.flush();
	}

	temp = "";

	temp += "\n";
	outfile << temp;
	outfile.flush();


	temp = "vector out45to89 ";

	outfile << temp;
	outfile.flush();

	

	for (int i = 89; i >= 45; --i)
	{
		temp = "";

		temp += "{tester512_1_0[";
		temp += to_string(i);
		temp += "]/out1} ";

		temp += "{tester512_1_0[";
		temp += to_string(i);
		temp += "]/out0} ";



		outfile << temp;
		outfile.flush();
	}

	temp = "";
	temp += "\n";
	outfile << temp;
	outfile.flush();

	temp = "vector out90to134 ";

	outfile << temp;
	outfile.flush();
	

	for (int i = 134; i >= 90; --i)
	{
		temp = "";

		temp += "{tester512_1_0[";
		temp += to_string(i);
		temp += "]/out1} ";

		temp += "{tester512_1_0[";
		temp += to_string(i);
		temp += "]/out0} ";



		outfile << temp;
		outfile.flush();
	}

	temp = "";
	temp += "\n";
	outfile << temp;
	outfile.flush();

	temp = "vector out135to179 ";

	outfile << temp;
	outfile.flush();

	

	for (int i = 179; i >= 135; --i)
	{
		temp = "";

		temp += "{tester512_1_0[";
		temp += to_string(i);
		temp += "]/out1} ";

		temp += "{tester512_1_0[";
		temp += to_string(i);
		temp += "]/out0} ";

		outfile << temp;
		outfile.flush();
	}

	temp = "";
	temp += "\n";
	outfile << temp;
	outfile.flush();



	temp = "vector out180to224 ";

	outfile << temp;
	outfile.flush();

	

	for (int i = 224; i >= 180; --i)
	{
		temp = "";

		temp += "{tester512_1_0[";
		temp += to_string(i);
		temp += "]/out1} ";

		temp += "{tester512_1_0[";
		temp += to_string(i);
		temp += "]/out0} ";


		outfile << temp;
		outfile.flush();
	}

	temp = "";
	temp += "\n";
	outfile << temp;
	outfile.flush();

	temp = "vector out225to255 ";

	outfile << temp;
	outfile.flush();

	

	for (int i = 255; i >= 225; --i)
	{
		temp = "";

		temp += "{tester512_1_0[";
		temp += to_string(i);
		temp += "]/out1} ";

		temp += "{tester512_1_0[";
		temp += to_string(i);
		temp += "]/out0} ";



		outfile << temp;
		outfile.flush();
	}


	temp = "";
	temp += "\n";
	outfile << temp;
	outfile.flush();

	//set watches

	temp = "w sel out0to44 out45to89 out90to134 out135to179 out180to224 out225to255 \n";

	outfile << temp;
	outfile.flush();


	//set init values

	temp = "h VDD\nl VSS\n";
	outfile << temp;
	outfile.flush();

	for (;value < max; value++)
	{
		temp = "setvector sel 0d";
		temp += to_string(value);
		temp += "\n";
		temp += "s\n";

		outfile << temp;
		outfile.flush();
	}

	outfile << "logfile \n";

	//set values and loop





	outfile.close();



}