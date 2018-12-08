#include<string>
#include<fstream>
#include<algorithm>
#include<vector>

using namespace std;

vector <string> TOKENS;
vector <string> LEXEMES;

string current, lexeme;
int curr = 0, spaces = 0;

ofstream cout("Parse Tree.txt");

void POPULATE();
void printSpaces();
void ERROR();
string nextToken();
void match(string token);
void B();
void T1();
void T2();
void A1();
void A2();
void FD();
void NI();
void D();
void VAL();
void AV();
void M();
void VD();
void OP();
void AO();
void VAO();
void W();
void E();
void F();
void S();
void P();
void R();
void I();
void P1();
void P2();
void FC();
void BD();

int main() {

	POPULATE();

	current = TOKENS.at(curr); lexeme = LEXEMES.at(curr);
	S();


	//cout<<"\nOutput File has been Created\n\n";

	system("pause");
	return 0;
}

string nextToken() {

	if (++curr<TOKENS.size()) {
		lexeme = LEXEMES.at(curr);
		return TOKENS.at(curr);
	}
	else
		return "FINISH";
	//goto FINISH;
}

void match(string token) {


	if (token == current) {
		printSpaces();
		spaces--;
		cout << token;
		if (lexeme != "NULL")
			cout << " ( " << lexeme << " )";

		current = nextToken();
	}
	else
		ERROR();
}
void POPULATE() {


	string input;
	ifstream fin("Lex Output.txt");
	while (!fin.eof()) {

		getline(fin, input);
		//fin>>input;
		if (input.find(",", 0) != string::npos) {

			TOKENS.push_back(input.substr(1, input.find(",", 2) - 1));
			int i = input.length() - 2;
			LEXEMES.push_back(input.substr(input.find(",", 2) + 1, input.length() - input.find(",", 2) - 2));
		}
	}
}

//void printSpaces(){
//
//	char c=-77,c1=-60;
//
//	cout<<"\n";
//	
//	for(int i=0;i<spaces-1;i++)
//		cout<<c<<"   ";
//
//	if(spaces!=0)
//		cout<<c<<c1<<c1<<c1;
//
//	spaces++;
//}

void printSpaces() {

	cout << "\n";

	for (int i = 0; i<spaces - 1; i++)
		cout << "|   ";

	if (spaces != 0)
		cout << "|---";

	spaces++;
}

void ERROR() {

	cout << "Invalid String\n";
}

void B() {
	printSpaces();
	cout << "B";

	if (current == "[") {
		match("[");
		match("]");
	}
	else
		;									//NULL


	spaces--;


}

void T1() {
	printSpaces();
	cout << "T1";


	if (current == "int")
		match("int");

	else if (current == "char")
		match("char");
	else
		ERROR();


	spaces--;

}

void T2() {
	printSpaces();
	cout << "T2";

	if (current == "int" || current == "char")
		T1();
	else if (current == "void")
		match("void");
	else
		ERROR();


	spaces--;

}

void A2() {
	printSpaces();
	cout << "A2";

	if (current == ",") {
		match(",");
		T1();
		B();
		match("ID");
		A2();
	}
	else
		;						//NULL


	spaces--;

}

void A1() {
	printSpaces();
	cout << "A1";

	if (current != ")") {
		T1();
		B();
		match("ID");
		A2();
	}
	else
		;						//NULL


	spaces--;
}

void FD() {
	printSpaces();
	cout << "FD";

	match("def");
	match("ID");
	match("(");
	A1();
	match(")");
	//match("returns");
	//T2();
	match("{");
	BD();
	match("}");

	spaces--;
}

void NI() {
	printSpaces();
	cout << "NI";


	if (current == "NUM")
		match("NUM");
	else if (current == "ID")
		match("ID");
	else
		ERROR();


	spaces--;
}

void D() {
	printSpaces();
	cout << "D";


	if (current == "[") {
		match("[");
		NI();
		match("]");
	}
	else
		;								//NULL


	spaces--;
}

void VAL() {
	printSpaces();
	cout << "VAL";


	if (current == "ID") {
		match("ID");
		D();
	}
	else if (current == "NUM")
		match("NUM");
	else if (current == "CHAR")
		match("CHAR");
	else
		ERROR();


	spaces--;
}

void AV() {
	printSpaces();
	cout << "AV";


	if (current == "[") {
		match("[");
		match("NUM");
		match("]");
	}
	else if (current == "EQ") {
		match("EQ");
		VAL();
	}
	else
		;						//NULL


	spaces--;
}

void M() {
	printSpaces();
	cout << "M";


	if (current == ",") {
		match(",");
		match("ID");
		AV();
		M();
	}
	else
		;						//NULL


	spaces--;
}

void VD() {
	printSpaces();
	cout << "VD";


	T1();
	match("ID");
	AV();
	M();
	match(";");


	spaces--;
}

void OP() {

	printSpaces();
	cout << "OP";


	if (current == "+")
		match("+");
	else if (current == "-")
		match("-");
	else if (current == "*")
		match("*");
	else if (current == "/")
		match("/");
	else
		ERROR();


	spaces--;
}

void AO() {
	printSpaces();
	cout << "AO";

	if (current == "+" || current == "-" || current == "*" || current == "/") {
		OP();
		VAL();
	}
	else
		;						//NULL



	spaces--;
}

void VAO() {
	printSpaces();
	cout << "VAO";

	//match("ID");
	D();
	match("EQ");
	VAL();
	AO();
	match(";");


	spaces--;
}

void W() {
	printSpaces();
	cout << "W";


	match("while");
	VAL();
	match("RO");
	VAL();
	match("{");
	BD();
	match("}");


	spaces--;
}

void F() {
	printSpaces();
	cout << "F";


	match("if");
	VAL();
	match("RO");
	VAL();
	match("{");
	BD();
	match("}");
	E();


	spaces--;
}

void E() {
	printSpaces();
	cout << "E";


	match("else");
	if (current == "{") {
		match("{");
		BD();
		match("}");
	}
	else if (current == "if") {
		F();
	}
	else
		;									//NULL


	spaces--;
}

void R() {
	printSpaces();
	cout << "R";


	match("return");
	VAL();
	match(";");


	spaces--;
}

void P() {
	printSpaces();
	cout << "P";


	match("print");
	match("ID");
	match(";");


	spaces--;
}

void I() {
	printSpaces();
	cout << "I";


	match("input");
	match("ID");
	match(";");


	spaces--;
}

void P2() {
	printSpaces();
	cout << "P2";

	if (current == ",") {
		match(",");

		if (current == "ID") {
			match("ID");
			P2();
		}
		else if (current == "NUM") {
			match("NUM");
			P2();
		}
		else if (current == "CHAR") {
			match("CHAR");
			P2();
		}
		else
			ERROR();
	}
	else
		;


	spaces--;
}

void P1() {
	printSpaces();
	cout << "P1";

	if (current == "ID") {
		match("ID");
		P2();
	}
	else if (current == "NUM") {
		match("NUM");
		P2();
	}
	else if (current == "CHAR") {
		match("CHAR");
		P2();
	}
	else
		;


	spaces--;
}

void FC() {
	printSpaces();
	cout << "FC";

	//match("ID");
	match("(");
	P1();
	match(")");
	match(";");

	spaces--;
}

void BD() {
	printSpaces();
	cout << "BD";


	if (current == "while") {
		W();
		BD();
	}
	else if (current == "if") {
		F();
		BD();
	}
	else if (current == "print") {
		P();
		BD();
	}
	else if (current == "input") {
		I();
		BD();
	}
	else if (current == "return") {
		R();
	}
	else if (current == "char" || current == "int") {
		VD();
		BD();
	}
	else if (current == "ID") {
		match("ID");

		if (current == "(") {
			FC();
			BD();
		}
		else {
			VAO();
			BD();
		}
		//else
		//ERROR();
	}

	else
		;							//NULL


	spaces--;

}

void S() {

	printSpaces();
	cout << "S";

	if (current == "def") {
		FD();

		if (current != "FINISH")
			S();
	}
	else if (current == "int" || current == "char") {
		VD();
		if (current != "FINISH")
			S();
	}
	else if (current == "FINISH")
		;
	else
		ERROR();

	spaces--;
}