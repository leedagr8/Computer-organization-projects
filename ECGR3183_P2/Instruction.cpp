#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <algorithm>

using namespace std;

string FPtoDec(string val);
string DectoBin(double num, int k_prec);
string BintoFP(string bin, double d);

int main()
{
	string instruction, opcode, immediate, unused;
	string Ri, Rj, Rk;
	string R[16];
	//int i = 0;

	string val1, val2;
	string dec1, dec2;


	ifstream input("tb.txt");
	if (!input)
	{
		cout << "couldn't open file" << endl;
		return -1;
	}

	if (input.is_open())
	{
		while (getline(input, instruction))
		{
			opcode = instruction.substr(0, 5);
			//set
			if (opcode == "00001")
			{
				Ri = instruction.substr(5, 4);
				unused = instruction.substr(9, 23);
				cout << instruction << endl;
				cout << opcode << " " << Ri << " " << unused << endl;
				//cout << "opcode: " << opcode << endl;
				//cout << "Ri: " << Ri << endl;
				//cout << "unused: " << unused << endl;
				
				getline(input, instruction);
				immediate = instruction;
				cout << "immediate: " << immediate << endl;
				int temp = stoi(Ri, nullptr, 2);
				//cout << "temp: " << temp << endl;
				R[temp] = immediate;
			
				cout << "R" << temp << " = " << R[temp] << endl;
			}
			cout << endl;
			//get
			if (opcode == "00010")
			{
				double ge;
				Ri = instruction.substr(5, 4);
				unused = instruction.substr(9, 23);
				cout << instruction << endl;
				cout << opcode << " " << Ri << " " << unused << endl;
				//cout << "opcode: " << opcode << endl;
				//cout << "Ri: " << Ri << endl;
				//cout << "unused: " << unused << endl;

				int temp1 = stoi(Ri, nullptr, 2);		//the temp gets the value from Ri
				//cout << "temp1: " << temp1 << endl;
														

				val1 = R[temp1];
				dec1 = FPtoDec(val1);

				double one;
				one = stod(dec1);
				ge = one;		//adds Rj and Rk
				cout << "get: " << ge << endl;

				string bin = DectoBin(ge, 25);
				//cout << bin << endl;
				R[temp1] = BintoFP(bin,ge);
				cout << "R" << temp1 << " = " << R[temp1] << endl;
				//cout << one << endl;
				//cout << two << endl;
				//cout << R[temp1] << endl;

			}

			//move
			if (opcode == "00011")
			{

				Ri = instruction.substr(5, 4);
				Rj = instruction.substr(9, 4);
				unused = instruction.substr(13, 19);
				cout << instruction << endl;
				cout << opcode << " " << Ri << " " << Rj << " " << unused << endl;
				//cout << "opcode: " << opcode << endl;
				//cout << "Ri: " << Ri << endl;
				//cout << "Rj: " << Rj << endl;
				//cout << "unused: " << unused << endl;
				int temp = stoi(Ri, nullptr, 2);
				//cout << "temp: " << temp << endl;

				int temp1 = stoi(Ri, nullptr, 2);		//the temp gets the value from Ri
				int temp2 = stoi(Rj, nullptr, 2);		//Rj
				
				//cout << "temp1: " << temp1 << endl;


				val1 = R[temp1];
				val2 = R[temp2];
				dec1 = FPtoDec(val1);
				dec2 = FPtoDec(val2);

				double one, two;
				one = stod(dec1);
				two = stod(dec2);


				string bin1 = DectoBin(one, 23);
				string bin2 = DectoBin(two, 23);
				//cout << "bin1: " << bin1 << endl;
				//cout << "bin2: " << bin2 << endl;

				R[temp1] = BintoFP(bin2, two);

				cout << "R" << temp1 << " = " << R[temp1] << endl;
				cout << "R" << temp2 << " = " << R[temp2] << endl;
				//cout << one << endl;
				//cout << two << endl;
				//cout << R[temp1] << endl;
			}

			//add
			if (opcode == "00100")
			{
				double add;
				Ri = instruction.substr(5, 4);
				Rj = instruction.substr(9, 4);
				Rk = instruction.substr(13, 4);
				unused = instruction.substr(17, 15);
				cout << instruction << endl;
				cout << opcode << " " << Ri << " " << Rj << " " << Rk << " " << unused << endl;
				//cout << "opcode: " << opcode << endl;
				//cout << "Ri: " << Ri << endl;
				//cout << "Rj: " << Rj << endl;
				//cout << "Rk: " << Rk << endl;
				//cout << "unused: " << unused << endl;

				int temp1 = stoi(Ri, nullptr, 2);		//the temp gets the value from Ri
				int temp2 = stoi(Rj, nullptr, 2);		//Rj
				int temp3 = stoi(Rk, nullptr, 2);		//Rk
				//cout << "temp1: " << temp1 << endl;
				//cout << "temp2: " << temp2 << endl;
				//cout << "temp3: " << temp3 << endl;

				val1 = R[temp2];
				val2 = R[temp3];
				dec1 = FPtoDec(val1);
				dec2 = FPtoDec(val2);

				double one, two;
				one = stod(dec1);
				two = stod(dec2);
				add = one + two;		//adds Rj and Rk
				double temp_add = add;
				//cout << "one: " << one << endl;
				//cout << "two: " << two << endl;
				cout << "adding: " << add << endl;
				if (add < 0)
					add = -1 * add;
				string bin = DectoBin(add, 23);
				//cout << bin << endl;

				string str;
				str = BintoFP(bin,temp_add);
				if (temp_add < 0)
				{
					str.erase(0, 1);
					str.insert(0, "1");
					R[temp1] = str;
				}
				else
					R[temp1] = str;

				cout << "R" << temp1 << " = " << R[temp1] << endl;
				cout << "R" << temp2 << " = " << R[temp2] << endl;
				cout << "R" << temp3 << " = " << R[temp3] << endl;
				//cout << one << endl;
				//cout << two << endl;
				//cout << R[temp1] << endl;
			}
	
			//subtract
			if (opcode == "00101")
			{
				double sub;
				Ri = instruction.substr(5, 4);
				Rj = instruction.substr(9, 4);
				Rk = instruction.substr(13, 4);
				unused = instruction.substr(17, 15);
				cout << instruction << endl;
				cout << opcode << " " << Ri << " " << Rj << " " << Rk << " " << unused << endl;
				//cout << "opcode: " << opcode << endl;
				//cout << "Ri: " << Ri << endl;
				//cout << "Rj: " << Rj << endl;
				//cout << "Rk: " << Rk << endl;
				//cout << "unused: " << unused << endl;

				int temp1 = stoi(Ri, nullptr, 2);		//the temp gets the value from Ri
				int temp2 = stoi(Rj, nullptr, 2);		//Rj
				int temp3 = stoi(Rk, nullptr, 2);		//Rk
														//cout << "temp1: " << temp1 << endl;
														//cout << "temp2: " << temp2 << endl;
														//cout << "temp3: " << temp3 << endl;

				val1 = R[temp2];
				val2 = R[temp3];
				dec1 = FPtoDec(val1);
				dec2 = FPtoDec(val2);

				double one, two;
				one = stod(dec1);
				two = stod(dec2);
				sub = one - two;		//subtracts Rj and Rk
				double temp_sub = sub;
				//cout << "one: " << one << endl;
				//cout << "two: " << two << endl;
				cout << "subtracting: " << sub << endl;

				if (sub < 0)
					sub = -1 * sub;

				string bin = DectoBin(sub, 23);
				//cout << bin << endl;

				string str;
				str = BintoFP(bin,temp_sub);
				if (temp_sub < 0)
				{
					str.erase(0, 1);
					str.insert(0, "1");
					R[temp1] = str;
				}
				else
					R[temp1] = str;
			
				cout << "R" << temp1 << " = " << R[temp1] << endl;
				cout << "R" << temp2 << " = " << R[temp2] << endl;
				cout << "R" << temp3 << " = " << R[temp3] << endl;
				//cout << one << endl;
				//cout << two << endl;
				//cout << R[temp1] << endl;

			}

			//Negate
			if (opcode == "00110")
			{
				double neg;
				Ri = instruction.substr(5, 4);
				Rj = instruction.substr(9, 4);
				unused = instruction.substr(13, 19);
				cout << instruction << endl;
				cout << opcode << " " << Ri << " " << Rj << " " << unused << endl;
				//cout << "opcode: " << opcode << endl;
				//cout << "Ri: " << Ri << endl;
				//cout << "Rj: " << Rj << endl;
				//cout << "unused: " << unused << endl;

				int temp1 = stoi(Ri, nullptr, 2);		//the temp gets the value from Ri
				int temp2 = stoi(Rj, nullptr, 2);		//Rj

														//cout << "temp1: " << temp1 << endl;
														//cout << "temp2: " << temp2 << endl;

				val1 = R[temp2];
				dec1 = FPtoDec(val1);

				double one;
				one = stod(dec1);

				neg = one;		//subtracts Rj and Rk
				cout << "negate: " << neg << endl;
				//cout << one << endl;
				if (neg < 0)
					neg = -1 * neg;

				string bin = DectoBin(neg, 23);

				//cout << bin << endl;
				string str;
				str = BintoFP(bin,neg);

				if (one < 0)
				{
					str.erase(0, 1);
					str.insert(0, "0");
					R[temp1] = str;
				}
				else
				{
					str.erase(0, 1);
					str.insert(0, "1");
					R[temp1] = str;
				}

				cout << "R" << temp1 << " = " << R[temp1] << endl;
				cout << "R" << temp2 << " = " << R[temp2] << endl;
			}

			//multiply
			if (opcode == "00111")
			{
				double mul;
				Ri = instruction.substr(5, 4);
				Rj = instruction.substr(9, 4);
				Rk = instruction.substr(13, 4);
				unused = instruction.substr(17, 15);
				cout << instruction << endl;
				cout << opcode << " " << Ri << " " << Rj << " " << Rk << " " << unused << endl;
				//cout << "opcode: " << opcode << endl;
				//cout << "Ri: " << Ri << endl;
				//cout << "Rj: " << Rj << endl;
				//cout << "Rk: " << Rk << endl;
				//cout << "unused: " << unused << endl;

				int temp1 = stoi(Ri, nullptr, 2);		//the temp gets the value from Ri
				int temp2 = stoi(Rj, nullptr, 2);		//Rj
				int temp3 = stoi(Rk, nullptr, 2);		//Rk
														//cout << "temp1: " << temp1 << endl;
													//cout << "temp2: " << temp2 << endl;
														//cout << "temp3: " << temp3 << endl;

				val1 = R[temp2];
				val2 = R[temp3];
				dec1 = FPtoDec(val1);
				dec2 = FPtoDec(val2);

				double one, two;
				one = stod(dec1);
				two = stod(dec2);
				mul = one * two;		//multiply Rj and Rk
				double temp_mul = mul;
				cout << "multiply: " << mul << endl;
				if (mul < 0)
					mul = -1 * mul;

				string bin = DectoBin(mul, 23);
				//cout << bin << endl;

				string str;
				str = BintoFP(bin,temp_mul);
				if (temp_mul < 0)
				{
					str.erase(0, 1);
					str.insert(0, "1");
					R[temp1] = str;
				}
				else
					R[temp1] = str;
				
				cout << "R" << temp1 << " = " << R[temp1] << endl;
				cout << "R" << temp2 << " = " << R[temp2] << endl;
				cout << "R" << temp3 << " = " << R[temp3] << endl;
				//cout << one << endl;
				//cout << two << endl;
				//cout << R[temp1] << endl;
			}

			//divide
			if (opcode == "01000")
			{
				double div;
				Ri = instruction.substr(5, 4);
				Rj = instruction.substr(9, 4);
				Rk = instruction.substr(13, 4);
				unused = instruction.substr(17, 15);
				cout << instruction << endl;
				cout << opcode << " " << Ri << " " << Rj << " " << Rk << " " << unused << endl;
				//cout << "opcode: " << opcode << endl;
				//cout << "Ri: " << Ri << endl;
				//cout << "Rj: " << Rj << endl;
				//cout << "Rk: " << Rk << endl;
				//cout << "unused: " << unused << endl;

				int temp1 = stoi(Ri, nullptr, 2);		//the temp gets the value from Ri
				int temp2 = stoi(Rj, nullptr, 2);		//Rj
				int temp3 = stoi(Rk, nullptr, 2);		//Rk
				//cout << "temp1: " << temp1 << endl;
				//cout << "temp2: " << temp2 << endl;
				//cout << "temp3: " << temp3 << endl;

				val1 = R[temp2];
				val2 = R[temp3];
				//cout << "val1: " << val1 << endl;
				//cout << "val2: " << val2 << endl;
				dec1 = FPtoDec(val1);
				dec2 = FPtoDec(val2);
				//cout << "dec1: " << dec1 << endl;
				//cout << "dec2: " << dec2 << endl;
				double one, two;
				one = stod(dec1);
				two = stod(dec2);
				div = one / two;		//divide Rj and Rk
				double temp_div = div;
				cout << "divide: " << div << endl;

				if (div < 0)
					div = -1 * div;

				string bin = DectoBin(div, 25);
				//cout << bin << endl;
				

				string str;
				str = BintoFP(bin,temp_div);
				//cout << "str: " << str << endl;
				if (temp_div < 0)
				{
					str.erase(0, 1);
					str.insert(0, "1");
					R[temp1] = str;
				}
				else
					R[temp1] = str;

				cout << "R" << temp1 << " = " << R[temp1] << endl;
				cout << "R" << temp2 << " = " << R[temp2] << endl;
				cout << "R" << temp3 << " = " << R[temp3] << endl;
				//cout << one << endl;
				//cout << two << endl;
				//cout << R[temp1] << endl;
			}

			//floor
			if (opcode == "01001") 
			{
				double flo;
				Ri = instruction.substr(5, 4);
				Rj = instruction.substr(9, 4);
				unused = instruction.substr(13, 19);
				cout << instruction << endl;
				cout << opcode << " " << Ri << " " << Rj << " "  << unused << endl;
				//cout << "opcode: " << opcode << endl;
				//cout << "Ri: " << Ri << endl;
				//cout << "Rj: " << Rj << endl;
				//cout << "unused: " << unused << endl;

				int temp1 = stoi(Ri, nullptr, 2);		//the temp gets the value from Ri
				int temp2 = stoi(Rj, nullptr, 2);		//Rj
				//cout << "temp1: " << temp1 << endl;
				//cout << "temp2: " << temp2 << endl;

				val1 = R[temp2];
				dec1 = FPtoDec(val1);

				double one;
				one = stod(dec1);
				//cout << "one: " << one << endl;
				flo = floor(one);		//subtracts Rj and Rk
				cout << "floor: " << flo << endl;
				

				string bin = DectoBin(flo, 23);

				//cout << bin << endl;

				R[temp1] = BintoFP(bin,flo);
				cout << "R" << temp1 << " = " << R[temp1] << endl;
				cout << "R" << temp2 << " = " << R[temp2] << endl;
			}
	
			//ceiling
			if (opcode == "01010") 
			{
				double cei;
				Ri = instruction.substr(5, 4);
				Rj = instruction.substr(9, 4);
				unused = instruction.substr(13, 19);
				cout << instruction << endl;
				cout << opcode << " " << Ri << " " << Rj << " " << unused << endl;
				//cout << "opcode: " << opcode << endl;
				//cout << "Ri: " << Ri << endl;
				//cout << "Rj: " << Rj << endl;
				//cout << "unused: " << unused << endl;

				int temp1 = stoi(Ri, nullptr, 2);		//the temp gets the value from Ri
				int temp2 = stoi(Rj, nullptr, 2);		//Rj
														//cout << "temp1: " << temp1 << endl;
														//cout << "temp2: " << temp2 << endl;

				val1 = R[temp2];
				dec1 = FPtoDec(val1);

				double one;
				one = stod(dec1);
				//cout << "one: " << one << endl;
				cei = ceil(one);		//subtracts Rj and Rk
				cout << "ceiling: " << cei << endl;


				string bin = DectoBin(cei, 23);

				//cout << bin << endl;

				R[temp1] = BintoFP(bin,cei);
				cout << "R" << temp1 << " = " << R[temp1] << endl;
				cout << "R" << temp2 << " = " << R[temp2] << endl;
			}

			//Round
			if (opcode == "01011")
			{
				double rou;
				Ri = instruction.substr(5, 4);
				Rj = instruction.substr(9, 4);
				unused = instruction.substr(13, 19);
				cout << instruction << endl;
				cout << opcode << " " << Ri << " " << Rj << " " << unused << endl;
				//cout << "opcode: " << opcode << endl;
				//cout << "Ri: " << Ri << endl;
				//cout << "Rj: " << Rj << endl;
				//cout << "unused: " << unused << endl;

				int temp1 = stoi(Ri, nullptr, 2);		//the temp gets the value from Ri
				int temp2 = stoi(Rj, nullptr, 2);		//Rj
														//cout << "temp1: " << temp1 << endl;
														//cout << "temp2: " << temp2 << endl;

				val1 = R[temp2];
				dec1 = FPtoDec(val1);

				double one;
				one = stod(dec1);
				//cout << "one: " << one << endl;
				rou = round(one);		//subtracts Rj and Rk
				cout << "round: " << rou << endl;


				string bin = DectoBin(rou, 23);

				//cout << bin << endl;

				R[temp1] = BintoFP(bin,rou);
				cout << "R" << temp1 << " = " << R[temp1] << endl;
				cout << "R" << temp2 << " = " << R[temp2] << endl; 
			}
			
			//absolute value
			if (opcode == "01100") {
				double ab;
				Ri = instruction.substr(5, 4);
				Rj = instruction.substr(9, 4);
				unused = instruction.substr(13, 19);
				cout << instruction << endl;
				cout << opcode << " " << Ri << " " << Rj << " " << unused << endl;
				//cout << "opcode: " << opcode << endl;
				//cout << "Ri: " << Ri << endl;
				//cout << "Rj: " << Rj << endl;
				//cout << "unused: " << unused << endl;

				int temp1 = stoi(Ri, nullptr, 2);		//the temp gets the value from Ri
				int temp2 = stoi(Rj, nullptr, 2);		//Rj
														//cout << "temp1: " << temp1 << endl;
														//cout << "temp2: " << temp2 << endl;

				val1 = R[temp2];
				dec1 = FPtoDec(val1);

				double one;
				one = stod(dec1);
				//cout << "one: " << one << endl;
				ab = abs(one);		//absolute of Rj
				cout << "absolute value: " << ab << endl;


				string bin = DectoBin(ab, 23);

				//cout << bin << endl;

				R[temp1] = BintoFP(bin,ab);
				cout << "R" << temp1 << " = " << R[temp1] << endl;
				cout << "R" << temp2 << " = " << R[temp2] << endl; 
			}

			//Inverse
			if (opcode == "01101") {
				double inv;
				Ri = instruction.substr(5, 4);
				Rj = instruction.substr(9, 4);
				unused = instruction.substr(13, 19);
				cout << instruction << endl;
				cout << opcode << " " << Ri << " " << Rj << " " << unused << endl;
				//cout << "opcode: " << opcode << endl;
				//cout << "Ri: " << Ri << endl;
				//cout << "Rj: " << Rj << endl;
				//cout << "unused: " << unused << endl;

				int temp1 = stoi(Ri, nullptr, 2);		//the temp gets the value from Ri
				int temp2 = stoi(Rj, nullptr, 2);		//Rj
				
														//cout << "temp1: " << temp1 << endl;
														//cout << "temp2: " << temp2 << endl;

				val1 = R[temp2];
				dec1 = FPtoDec(val1);

				double one;
				one = stod(dec1);
				
				if (one != 0)
				{
					inv = 1 / one;

					cout << "inverse: " << inv << endl;

					string bin = DectoBin(inv, 23);
					//cout << bin << endl;
					R[temp1] = BintoFP(bin, inv);
					cout << "R" << temp1 << " = " << R[temp1] << endl;
					cout << "R" << temp2 << " = " << R[temp2] << endl; 
					//cout << one << endl;
					//cout << two << endl;
					//cout << R[temp1] << endl;
				}
				else
					return -1;
			}
		
			//Minimum
			if (opcode == "01110") 
			{
				double mi;
				Ri = instruction.substr(5, 4);
				Rj = instruction.substr(9, 4);
				Rk = instruction.substr(13, 4);
				unused = instruction.substr(17, 15);
				cout << instruction << endl;
				cout << opcode << " " << Ri << " " << Rj << " " << Rk << " " << unused << endl;
				//cout << "opcode: " << opcode << endl;
				//cout << "Ri: " << Ri << endl;
				//cout << "Rj: " << Rj << endl;
				//cout << "Rk: " << Rk << endl;
				//cout << "unused: " << unused << endl;

				int temp1 = stoi(Ri, nullptr, 2);		//the temp gets the value from Ri
				int temp2 = stoi(Rj, nullptr, 2);		//Rj
				int temp3 = stoi(Rk, nullptr, 2);		//Rk
				//cout << "temp1: " << temp1 << endl;
				//cout << "temp2: " << temp2 << endl;
				//cout << "temp3: " << temp3 << endl;

				val1 = R[temp2];
				val2 = R[temp3];
				dec1 = FPtoDec(val1);
				dec2 = FPtoDec(val2);

				double one, two;
				one = stod(dec1);
				two = stod(dec2);
				mi = min(one, two);		//minimum Rj and Rk
				cout << "minimum: " << mi << endl;

				string bin = DectoBin(mi, 23);
				//cout << bin << endl;
				R[temp1] = BintoFP(bin,mi);
				cout << "R" << temp1 << " = " << R[temp1] << endl;
				cout << "R" << temp2 << " = " << R[temp2] << endl;
				cout << "R" << temp3 << " = " << R[temp3] << endl;
				//cout << one << endl;
				//cout << two << endl;
				//cout << R[temp1] << endl;
			}

			// maximum
			if (opcode == "01111") 
			{
				double ma;
				Ri = instruction.substr(5, 4);
				Rj = instruction.substr(9, 4);
				Rk = instruction.substr(13, 4);
				unused = instruction.substr(17, 15);
				cout << instruction << endl;
				cout << opcode << " " << Ri << " " << Rj << " " << Rk << " " << unused << endl;
				//cout << "opcode: " << opcode << endl;
				//cout << "Ri: " << Ri << endl;
				//cout << "Rj: " << Rj << endl;
				//cout << "Rk: " << Rk << endl;
				//cout << "unused: " << unused << endl;

				int temp1 = stoi(Ri, nullptr, 2);		//the temp gets the value from Ri
				int temp2 = stoi(Rj, nullptr, 2);		//Rj
				int temp3 = stoi(Rk, nullptr, 2);		//Rk
				//cout << "temp1: " << temp1 << endl;
				//cout << "temp2: " << temp2 << endl;
				//cout << "temp3: " << temp3 << endl;

				val1 = R[temp2];
				val2 = R[temp3];
				dec1 = FPtoDec(val1);
				dec2 = FPtoDec(val2);

				double one, two;
				one = stod(dec1);
				two = stod(dec2);
				ma = max(one, two);		//minimum Rj and Rk
				cout << "maximum: " << ma << endl;

				string bin = DectoBin(ma, 23);
				//cout << bin << endl;
				R[temp1] = BintoFP(bin,ma);
				cout << "R" << temp1 << " = " << R[temp1] << endl;
				cout << "R" << temp2 << " = " << R[temp2] << endl;
				cout << "R" << temp3 << " = " << R[temp3] << endl;
				//cout << one << endl;
				//cout << two << endl;
				//cout << R[temp1] << endl;
			}

			//Power
			if (opcode == "10000") 
			{
				double po;
				Ri = instruction.substr(5, 4);
				Rj = instruction.substr(9, 4);
				unused = instruction.substr(13, 19);
				cout << instruction << endl;
				cout << opcode << " " << Ri << " " << Rj << " " << Rk << unused << endl;
				//cout << "opcode: " << opcode << endl;
				//cout << "Ri: " << Ri << endl;
				//cout << "Rj: " << Rj << endl;
				//cout << "unused: " << unused << endl;
				getline(input, instruction);
				immediate = instruction;
				cout << "immediate: " << immediate << endl;

				int temp1 = stoi(Ri, nullptr, 2);		//the temp gets the value from Ri
				int temp2 = stoi(Rj, nullptr, 2);		//Rj

				//cout << "temp1: " << temp1 << endl;
				//cout << "temp2: " << temp2 << endl;

				val1 = R[temp2];
				dec1 = FPtoDec(val1);
				dec2 = FPtoDec(immediate);
				
				double one;
				int two;

				one = stod(dec1);
				two = stoi(dec2);
				//cout << "one: " << one << endl;
				//cout << "two: " << two << endl;

				po = pow(one, two);
				cout << "power: " << po << endl;

				string bin = DectoBin(po, 23);
				cout << bin << endl;
				R[temp1] = BintoFP(bin,po);
				cout << "R" << temp1 << " = " << R[temp1] << endl;
				cout << "R" << temp2 << " = " << R[temp2] << endl; 
				//cout << one << endl;
				//cout << two << endl;
				//cout << R[temp1] << endl;
			}

			//sine
			if (opcode == "10001") 
			{
				double si;
				Ri = instruction.substr(5, 4);
				Rj = instruction.substr(9, 4);
				unused = instruction.substr(13, 19);
				cout << instruction << endl;
				cout << opcode << " " << Ri << " " << Rj << " " << Rk << unused << endl;
				//cout << "opcode: " << opcode << endl;
				//cout << "Ri: " << Ri << endl;
				//cout << "Rj: " << Rj << endl;
				//cout << "unused: " << unused << endl;

				int temp1 = stoi(Ri, nullptr, 2);		//the temp gets the value from Ri
				int temp2 = stoi(Rj, nullptr, 2);		//Rj

														//cout << "temp1: " << temp1 << endl;
														//cout << "temp2: " << temp2 << endl;

				val1 = R[temp2];
				dec1 = FPtoDec(val1);

				double one;
				one = stod(dec1);

				si = sin(one);
				cout << "sine: " << si << endl;

				string bin = DectoBin(si, 23);
				cout << bin << endl;
				R[temp1] = BintoFP(bin, si);
				cout << "R" << temp1 << " = " << R[temp1] << endl;
				cout << "R" << temp2 << " = " << R[temp2] << endl; 
				//cout << one << endl;
				//cout << two << endl;
				//cout << R[temp1] << endl;
			}

			//Cosine
			if (opcode == "10010")
			{
				double co;
				Ri = instruction.substr(5, 4);
				Rj = instruction.substr(9, 4);
				unused = instruction.substr(13, 19);
				cout << instruction << endl;
				cout << opcode << " " << Ri << " " << Rj << " " << unused << endl;
				//cout << "opcode: " << opcode << endl;
				//cout << "Ri: " << Ri << endl;
				//cout << "Rj: " << Rj << endl;
				//cout << "unused: " << unused << endl;

				int temp1 = stoi(Ri, nullptr, 2);		//the temp gets the value from Ri
				int temp2 = stoi(Rj, nullptr, 2);		//Rj

														//cout << "temp1: " << temp1 << endl;
														//cout << "temp2: " << temp2 << endl;

				val1 = R[temp2];
				dec1 = FPtoDec(val1);

				double one;
				one = stod(dec1);

				co = cos(one);
				cout << "cosine: " << co << endl;

				string bin = DectoBin(co, 23);
				cout << bin << endl;
				R[temp1] = BintoFP(bin, co);
				cout << "R" << temp1 << " = " << R[temp1] << endl;
				cout << "R" << temp2 << " = " << R[temp2] << endl; 
				//cout << one << endl;
				//cout << two << endl;
				//cout << R[temp1] << endl;
			}

			//Tangent
			if (opcode == "10011") 
			{
				double ta;
				Ri = instruction.substr(5, 4);
				Rj = instruction.substr(9, 4);
				unused = instruction.substr(13, 19);
				cout << instruction << endl;
				cout << opcode << " " << Ri << " " << Rj << " " <<  unused << endl;
				//cout << "opcode: " << opcode << endl;
				//cout << "Ri: " << Ri << endl;
				//cout << "Rj: " << Rj << endl;
				//cout << "unused: " << unused << endl;

				int temp1 = stoi(Ri, nullptr, 2);		//the temp gets the value from Ri
				int temp2 = stoi(Rj, nullptr, 2);		//Rj

														//cout << "temp1: " << temp1 << endl;
														//cout << "temp2: " << temp2 << endl;

				val1 = R[temp2];
				dec1 = FPtoDec(val1);

				double one;
				one = stod(dec1);
				

				ta = tan(one);
				cout << "tangent: " << ta << endl;

				string bin = DectoBin(ta, 23);
				cout << bin << endl;
				R[temp1] = BintoFP(bin, ta);
				cout << "R" << temp1 << " = " << R[temp1] << endl;
				cout << "R" << temp2 << " = " << R[temp2] << endl; 
				//cout << one << endl;
				//cout << two << endl;
				//cout << R[temp1] << endl;
			}
			cout << endl;
			//Exponent
			if (opcode == "10100")
			{
				double ex;
				Ri = instruction.substr(5, 4);
				Rj = instruction.substr(9, 4);
				unused = instruction.substr(13, 19);
				cout << instruction << endl;
				cout << opcode << " " << Ri << " " << Rj << " " << unused << endl;
				//cout << "opcode: " << opcode << endl;
				//cout << "Ri: " << Ri << endl;
				//cout << "Rj: " << Rj << endl;
				//cout << "unused: " << unused << endl;

				int temp1 = stoi(Ri, nullptr, 2);		//the temp gets the value from Ri
				int temp2 = stoi(Rj, nullptr, 2);		//Rj

														//cout << "temp1: " << temp1 << endl;
														//cout << "temp2: " << temp2 << endl;

				val1 = R[temp2];
				dec1 = FPtoDec(val1);

				double one;
				one = stod(dec1);

				ex = exp(one);
				cout << "exponent: " << ex << endl;

				string bin = DectoBin(ex, 23);
				cout << bin << endl;
				R[temp1] = BintoFP(bin, ex);
				cout << "R" << temp1 << " = " << R[temp1] << endl;
				cout << "R" << temp2 << " = " << R[temp2] << endl; 
				//cout << one << endl;
				//cout << two << endl;
				//cout << R[temp1] << endl;
			}
			
			//Logarithm
			if (opcode == "10101") {
				double lo;
				Ri = instruction.substr(5, 4);
				Rj = instruction.substr(9, 4);
				unused = instruction.substr(13, 19);
				cout << instruction << endl;
				cout << opcode << " " << Ri << " " << Rj << " " << unused << endl;
				//cout << "opcode: " << opcode << endl;
				//cout << "Ri: " << Ri << endl;
				//cout << "Rj: " << Rj << endl;
				//cout << "unused: " << unused << endl;

				int temp1 = stoi(Ri, nullptr, 2);		//the temp gets the value from Ri
				int temp2 = stoi(Rj, nullptr, 2);		//Rj

														//cout << "temp1: " << temp1 << endl;
														//cout << "temp2: " << temp2 << endl;

				val1 = R[temp2];
				dec1 = FPtoDec(val1);

				double one;
				one = stod(dec1);

				lo = log(one);
				cout << "logarithm: " << lo << endl;

				string bin = DectoBin(lo, 23);
				cout << bin << endl;
				R[temp1] = BintoFP(bin, lo);
				cout << "R" << temp1 << " = " << R[temp1] << endl;
				cout << "R" << temp2 << " = " << R[temp2] << endl; 
				//cout << one << endl;
				//cout << two << endl;
				//cout << R[temp1] << endl;
			}
			
			//Square root
			if (opcode == "10110") 
			{
				double sq;
				Ri = instruction.substr(5, 4);
				Rj = instruction.substr(9, 4);
				unused = instruction.substr(13, 19);
				cout << instruction << endl;
				cout << opcode << " " << Ri << " " << Rj << " " << unused << endl;
				//cout << "opcode: " << opcode << endl;
				//cout << "Ri: " << Ri << endl;
				//cout << "Rj: " << Rj << endl;
				//cout << "unused: " << unused << endl;

				int temp1 = stoi(Ri, nullptr, 2);		//the temp gets the value from Ri
				int temp2 = stoi(Rj, nullptr, 2);		//Rj
														//cout << "temp1: " << temp1 << endl;
														//cout << "temp2: " << temp2 << endl;

				val1 = R[temp2];
				dec1 = FPtoDec(val1);

				double one;
				one = stod(dec1);
				//cout << "one: " << one << endl;
				sq = sqrt(one);		//square root of Rj
				cout << "square root: " << sq << endl;

				if (sq < 0)
					sq = -1 * sq;
				string bin = DectoBin(sq, 23);

				//cout << bin << endl;

				R[temp1] = BintoFP(bin,sq);
				cout << "R" << temp1 << " = " << R[temp1] << endl;
				cout << "R" << temp2 << " = " << R[temp2] << endl; 
			}
		}
	}

	input.close();

	system("PAUSE");
	return 0;
}


string FPtoDec(string val)
{
	string S, E;	//sign, fraction, exponent -- used for floting point 
	string F;
	int iS, iE;
	double iF;
	double dec;
	string result;
	stringstream convert;

	S = val.substr(0, 1);
	E = val.substr(1, 8);
	F = val.substr(9, 23);
	iS = stoi(S, nullptr, 2);
	iE = stoi(E, nullptr, 2) - 127;

	if (iS != 1)	//determines the sign
		iS = 1;
	else
		iS = -1;

	iF = 0;

	for (int i = 0; i < 23; i++)
	{
		if (F[i] == '1')
			iF = pow(2, (-1 * (i + 1))) + iF;
	}


	dec = static_cast<double>(iS*(1 + iF)*(pow(2, iE)));

	convert << dec;
	result = convert.str();

	return result;
}

string DectoBin(double num, int k_prec)
{
	string binary = "";

	// Fetch the integral part of decimal number
	int Integral = num;

	// Fetch the fractional part decimal number
	double fractional = num - Integral;

	// Conversion of integral part to
	// binary equivalent
	while (Integral)
	{
		int rem = Integral % 2;

		// Append 0 in binary
		binary.push_back(rem + '0');

		Integral /= 2;
	}

	// Reverse string to get original binary
	// equivalent
	reverse(binary.begin(), binary.end());

	// Append point before conversion of
	// fractional part
	binary.push_back('.');

	// Conversion of fractional part to
	// binary equivalent
	while (k_prec--)
	{
		// Find next bit in fraction
		fractional *= 2;
		int fract_bit = fractional;

		if (fract_bit == 1)
		{
			fractional -= fract_bit;
			binary.push_back(1 + '0');
		}
		else
			binary.push_back(0 + '0');
	}


	return binary;
}

string BintoFP(string bin, double d)
{
	string bi = bin;
	//cout << "bi: " << bi << endl;
	string FP;
	int ex, location;
	string S, E, F;
	//int dec = stoi(bin, nullptr, 2);	//converts the binary to a decimal

	if (d > 0)		//the decimal number is checked to see if the number is positive
		S = "0";
	else
		S = "1";


	//cout << "S: " << S << endl;

	
	size_t found = bi.find('.'); //locates the position of the . in the string
		//cout << "found: " << found << endl;
	location = found;
	bi.insert(1, 1, bi[found]); // the binary number gets a . in the second position
	bi.erase(found + 1, 1);		//the other . (not the one just inserted) gets erased from the string
			//cout << "bi: " << bi << endl;

	//cout << "bi.length: " << bi.length() << endl;

	bi.erase(25, bi.length() - 25);	//since bi has more than just the 1.Fraction needed, the rest are erased from the string
	//cout << "bi: " << bi << endl;///displays 1.fraction
	if (location == 0)
	{
		ex = 126;
		E = DectoBin(ex, 0);	//calls to the function so the int ex can be changed to a string binary
		E.insert(0, "0");
		E.erase(8, 1);
		//cout << "E: " << E << endl;
	}
	else
	{
		ex = 127 + (found - 1);	//determines the size of the exponent 
		E = DectoBin(ex, 0);	//calls to the function so the int ex can be changed to a string binary
		E.erase(8, 1);	
		//cout << "E: " << E << endl;
	}
	//cout << "ex: " << ex << endl;

		//since it returns 8 bits plus a . we need to erase the .
							//cout << "E: " << E << endl;
	F = bi;			//store the 1.Fraction in F
	F.erase(0, 2);	//since we dont need the 1. in the F we erase the 1.
	//cout << "F: " << F << endl;
	FP = F;			//store the fraction in the FP (Floating Point) which is 23 
	FP.insert(0, E);	//insert the 8 bits from E (Exponent) infront because it has to go infront of the Fraction
	FP.insert(0, S);	//since he sign determines whether it - or + we insert it as the first chaaracter of the string which is just 1 bit making the total 32 bits 
	//cout << "FP: " << FP << endl;

	return FP;
}