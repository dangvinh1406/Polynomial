#include "Polynomial.h"
#include <sstream>
#include <iostream>
#include <stdlib.h>
using namespace std;
string answer="ans";

int main(){
	cout<<endl;
	cout<<" ****** ****** **  **     * ***    ** ****** ***     ** **    **    **    "<<endl;
	cout<<" **  ** **  ** **   **   *  ****   ** **  ** ****   *** **   ****   **    "<<endl;
	cout<<" **  ** **  ** **    ** *   **  ** ** **  ** ** **** ** **  **  **  **    "<<endl;
	cout<<" ****** **  ** **     **    **   **** **  ** **  **  ** ** ******** **    "<<endl;
	cout<<" **     **  ** **     **    **     ** **  ** **      ** ** **    ** **    "<<endl;
	cout<<" **     **  ** **     **    **     ** **  ** **      ** ** **    ** **    "<<endl;
	cout<<" **     ****** ****** **    **     ** ****** **      ** ** **    ** ******"<<endl;
	cout<<endl;
	cout<<"        *****  ***   ***  *     ****   ***  *   *"<<endl;
	cout<<"          *   *   * *   * *     * **  *   *  * * "<<endl;
	cout<<"          *   *   * *   * *     *   * *   *  * * "<<endl;
	cout<<"          *    ***   ***  ***** ****   ***  *   *"<<endl;
	cout<<endl;
	cout<<" Version 1.0 Beta                                    Author: Dang Vinh\n";
	cout<<" =====================================================================\n";
	cout<<" Type 'help' for more informations.\n";

	string inp="";
	string la,fi;
	int con=0;//conditional variable
	int kind=0;//kind of input string variable
	Polynomial ans,tem;
	int flag=0;
	int ope=0;
	PList *l=new PList();
	while(con!=-1){
		cout<<">> ";
		getline(cin,inp);
		con=divideString(inp,fi,la);
		switch(con){
		case -1:
			break;
		case -2:
			system("clear");
			break;
		case -3:{
			PList *del=l;
			l=new PList();
			delete del;
				}
			break;
		case -4:
			cout<<"1.Correct form of polynomials:\n";
			cout<<"  You can type a correct Polynomial if you follow this rule: The variable of polynomial is alphabet character in lowercase. And you must write this character in to '[' and ']'. The degree of the polynomial is before '^' character and it can not be smaller than 0. Example: [x]2x^2-3x+1 or [y]2*y^2-3*y+1\n"; 
			cout<<"  Note: If you want to type a number, you must follow the rule of polynomial (Example: [x]42 is number fourty two) because all objects are also polynomial.\n"; 
			cout<<endl;
			cout<<"2.Operators of polynomials:\n";
			cout<<"  There are 5 operators: you can use '+' character to plus 2 polynomials, and use '-' to minus, '*' to multiplicate. If you want to divide and get an result, use '/'. Or you can use '%' for modulo division. Note: The division of polynomial also comply with the rule of real numbers, such as it can't divide to 0,...\n";  
			cout<<endl;
			cout<<"3.Functions of polynomials:\n";
			cout<<"  gcd(polynomial a,polynomial b): find the greatest common division of a and b.\n";
			cout<<"  eap(polynomial a,polynomial b): display steps of Euclide's algorithm for polynomial to find the greatest common division of a and b.\n";
			cout<<"  tep(polynomial a,value x): find the Taylor expansion polynomial of a at x value.\n";
			cout<<"  htp(polynomial a,value x): display the Horner table to find the Taylor expansion polynomial of a at x value.\n";
			cout<<"4.Command to program:\n";
			cout<<"  Type 'clear' to clear all the screen.\n";
			cout<<"  Type 'delete' to delete all polynomial objects in memory.\n";
			cout<<"  Type 'about' to read more informations about the developer.\n";
			cout<<"  Type 'exit' to leave the program.\n";
 			break;
		case -5:
			cout<<" This is the program helps you to calculate about polynomial. \n";
			cout<<" Developer: Dang Vinh             Email: dangvinh14061994@gmail.com\n";
			break;
		case 2:
			break;
		case 3:
			cout<<"Error: Unknown '=' character(s)."<<endl;break;
		case 4:
			cout<<"Error: Unknown ';' character(s)."<<endl;break;
		case 5:
			cout<<"Error: Unknown character(s)."<<endl;break;
		case 6:
			if(flag==1){ ope=6;flag++;}
			else cout<<"Error: No polynomial can be plus."<<endl;break;
		case 7:
			if(flag==1){ ope=7;flag++;}
			else cout<<"Error: No polynomial can be minus."<<endl;break;
		case 8:
			if(flag==1){ ope=8;flag++;}
			else cout<<"Error: No polynomial can be multiplicate."<<endl;break;
		case 9:
			if(flag==1){ ope=9;flag++;}
			else cout<<"Error: No polynomial can be divide."<<endl;break;
		case 10:
			if(flag==1){ ope=10;flag++;}
			else cout<<"Error: No polynomial can be get modulo."<<endl;break;
		case -6:
			cout<<"Error: Wrong operator."<<endl;break;
		default:
			kind=classifyStringLast(la);
			if(fi.compare(none)!=0){
				if(!(fi[0]>='a'&&fi[0]<='z')){
					cout<<"Error: '"<<fi<<"' The name of the objects must be begun with alphabet character.\n";break;
				}
				if(fi.compare(answer)==0){
					cout<<"Error: The name of the objects can not be 'ans'.\n";break;
				}
				if(fi.compare(exi)==0){
					cout<<"Error: The name of the objects can not be 'exit'.\n";break;
				}
				if(fi.compare(clear)==0){
					cout<<"Error: The name of the objects can not be 'clear'.\n";break;
				}
				if(fi.compare(delet)==0){
					cout<<"Error: The name of the objects can not be 'delete'.\n";break;
				}
				if(fi.compare(help)==0){
					cout<<"Error: The name of the objects can not be 'help'.\n";break;
				}
				if(fi.compare(about)==0){
					cout<<"Error: The name of the objects can not be 'about'.\n";break;
				}
				if(fi.compare(gcdf)==0){
					cout<<"Error: The name of the objects can not be 'gcd'.\n";break;
				}
				if(fi.compare(eapf)==0){
					cout<<"Error: The name of the objects can not be 'eap'.\n";break;
				}
				if(fi.compare(tepf)==0){
					cout<<"Error: The name of the objects can not be 'tep'.\n";break;
				}
				if(fi.compare(htpf)==0){
					cout<<"Error: The name of the objects can not be 'htp'.\n";break;
				}
			}
			//con=0:show; =1:don't show 
			switch (kind){
			case -1:
				cout<<"Error: The polynomial has wrong variable(s)."<<endl;break;
			case -2:
				cout<<"Error: Polynomial - syntax error."<<endl;break;
			case -3:
				cout<<"Error: The degree of polynomial must not be smaller than 0."<<endl;break;
			case 0:{
				string wrongs="";
				int te=l->testExpression(la,wrongs,ans);
				switch (te){
				case 0:
					cout<<"Error: Expression - syntax error."<<endl;break;
				case -1:
					cout<<"Error: Unknown object '"<<wrongs<<"' ."<<endl;wrongs="";break;
				case 2:
					cout<<"Error: Can not divide to Zero polynomial."<<endl;flag=0;break;
				case 1:
					flag=1;
					if(fi.compare(none)!=0){
						ans.setName(fi);
						l->set(ans);
						ans.setName(none);
						if(con==0){
							cout<<endl<<fi<<" ="<<endl;
							ans.show();
						}
					}
					else if(con==0){
						cout<<endl<<"ans ="<<endl;
						ans.show();
					}
				}
				   }
				break;
			case 1:
				tem.set(la);
				if(fi.compare(none)!=0){
					tem.setName(fi);
					l->set(tem);
					tem.setName(none);
				}
				if(flag==0){
					ans=tem;
					flag++;
				}
				else{
					if(flag==1)
						ans=tem;
					else{
						if(!calculate(ans,tem,ope)){
							cout<<"Error: Can not divide to Zero polynomial."<<endl;flag=0;break;
						}
						flag=1;
					}
				}
				if(con==0){
					if(fi.compare(none)==0)
						cout<<endl<<"ans ="<<endl;
					else
						cout<<endl<<fi<<" ="<<endl;
					ans.show();
				}
				break;
			case 2:{
				int tgcd=l->testGcd(la,ans);
				if(tgcd==1)
					flag=1;
				else if(tgcd==0){
					cout<<"Error: Function 'gcd' - syntax error."<<endl;break;
				}
				else if(tgcd==-1){
					cout<<"Error: Unknown first argument of function 'gcd'."<<endl;break;
				}
				else if(tgcd==-2){
					cout<<"Error: Unknown second argument of function 'gcd'."<<endl;break;
				}
				else if(tgcd==-3){
					cout<<endl<<"ans ="<<endl<<"\t N/A"<<endl;break;
				}
				   }
				if(fi.compare(none)!=0){
					ans.setName(fi);
					l->set(ans);
					ans.setName(none);
					if(con==0){
						cout<<"Greatest common division: \n";
						cout<<endl<<fi<<" ="<<endl;
						ans.show();
					}
				}
				else if(con==0){
					cout<<"Greatest common division: \n";
					cout<<endl<<"ans ="<<endl;
					ans.show();
				}
				break;
			case 3:{
				Polynomial *re;
				int m=0;
				int tgcd=l->testEap(la,ans,re,m);
				if(tgcd==1)
					flag=1;
				else if(tgcd==0){
					cout<<"Error: Function 'eap' - syntax error."<<endl;break;
				}
				else if(tgcd==-1){
					cout<<"Error: Unknown first argument of function 'eap'."<<endl;break;
				}
				else if(tgcd==-2){
					cout<<"Error: Unknown second argument of function 'eap'."<<endl;break;
				}
				else if(tgcd==-3){
					cout<<endl<<"ans ="<<endl<<"\t N/A"<<endl;break;
				}
				if(fi.compare(none)!=0){
					ans.setName(fi);
					l->set(ans);
					ans.setName(none);
					if(con==0){
						cout<<"Euclide Algorithm: \n";
						for(int i=0;i<m;i++){
							cout<<"Step "<<i+1;
							re[i].show();
						}
					}
				}
				else{
					if(con==0){
						cout<<"Euclide Algorithm: \n";
						for(int i=0;i<m;i++){
							cout<<"Step "<<i+1;
							re[i].show();
						}
					}
				}
				   }
				break;
			case 4:{
				float xvalue=0;
				int ttep=l->testTep(la,ans,xvalue);
				if(ttep==1)
					flag=1;
				else if(ttep==0){
					cout<<"Error: Function 'tep' - syntax error."<<endl;break;
				}
				else if(ttep==-1){
					cout<<"Error: Unknown first argument of function 'tep'."<<endl;break;
				}
				else if(ttep==-2){
					cout<<"Error: Unknown second argument of function 'tep'."<<endl;break;
				}
				if(fi.compare(none)!=0){
					ans.setName(fi);
					l->set(ans);
					ans.setName(none);
					if(con==0){
						cout<<"Taylor expansion: \n";
						cout<<endl<<fi<<" ="<<endl;
						ans.capsVar();
						ans.show();
						cout<<"   Note: "<<ans.getVar()<<" = ";
						ans.capsVar();
						cout<<ans.getVar()<<" - ("<<xvalue<<')'<<endl;
					}
				}
				else{
					if(con==0){
						cout<<"Taylor expansion: \n";
						cout<<endl<<"ans = "<<endl;
						ans.capsVar();
						ans.show();
						cout<<"   Note: "<<ans.getVar()<<" = ";
						ans.capsVar();
						cout<<ans.getVar()<<" - ("<<xvalue<<')'<<endl;
					}
				}
				   }
				break;
			case 5:{
				float xvalue=0;
				float **mat;
				int m=0;
				int ttep=l->testHtp(la,ans,xvalue,mat,m);
				if(ttep==1)
					flag=1;
				else if(ttep==0){
					cout<<"Error: Function 'htp' - syntax error."<<endl;break;
				}
				else if(ttep==-1){
					cout<<"Error: Unknown first argument of function 'htp'."<<endl;break;
				}
				else if(ttep==-2){
					cout<<"Error: Unknown second argument of function 'htp'."<<endl;break;
				}
				if(fi.compare(none)!=0){
					ans.setName(fi);
					l->set(ans);
					ans.setName(none);
				}
				if(con==0){
					cout<<"Horner table: "<<endl;
					showHornerTable(mat,m);
				}
				   }
				break;
			}
		}
	}
	return 0;
}