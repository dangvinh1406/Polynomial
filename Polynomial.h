#define ERROR 0.001
#include <iomanip>
#include <math.h>
#include <sstream>
#include <iostream>
using namespace std;
string exi="exit";
string clear="clear";
string delet="delete";
string help="help";
string about="about";
string none="";
string gcdf="gcd";
string eapf="eap";
string tepf="tep";
string htpf="htp";
string NA="N/A";

class Polynomial{
private:
	float *p;
	int deg;
	char var;
	string name;
public:
	Polynomial(){
		p=NULL;deg=0;var='x';name="";
	};
	Polynomial(const Polynomial &q){
		p=NULL;deg=0;var='x';name="";
		*this=q;
	};
	Polynomial(char v,int d){
		deg=d;
		var=v;
		if(deg>=0)
			p=new float[deg+1];
		for(int i=0;i<=deg;i++)
			p[i]=0;
	};
	~Polynomial(){
		if(p!=NULL)
			delete []p;
	};
	void set(string s){
		name="";
		deg=0;
		int n=s.length();
		var=s[1];
		string temp="";
		for(int i=3;i<n;i++)
			temp=temp+s[i];
		s=temp;
		n=s.length();
		string num="";
		int d=0;
		for(int i=0;i<n;i++){
			if(s[i]==var){
				if(i<n-2){
					if(s[i+1]!='^')
						if(deg<1)
							deg=1;
				}
				else{
					if(deg<1)
						deg=1;
				}
			}
			if(s[i]=='^'){
				int j=i+1;
				while(j<n){
					if(s[j]>='0'&&s[j]<='9'){
						num=num+s[j];
						stringstream(num)>>d;
						j++;
					}
					else
						break;
				}
				num="";
				if(d>deg)
					deg=d;
			}
		}
		if(p==NULL)
			p=new float[deg+1];
		else{
			float *del=p;
			p=new float[deg+1];
			delete del;
		}
		for(int i=0;i<=deg;i++)
			p[i]=0;
		d=1;
		num="";
		string num2="";
		string free="";
		float d2=1;
		float d3=0;
		for(int i=0;i<n;i++){
			if(s[i]==var){
				int k=i+1;
				int l=i-1;
				while(k<n){
					if(s[k]=='^')
						k++;
					if(s[k]>='0'&&s[k]<='9'){
						num=num+s[k];
						stringstream(num)>>d;
						k++;
					}
					else
						break;
				}
				while(l>=0){				
					if(s[l]=='*')
						l--;
					if((s[l]>='0'&&s[l]<='9')||s[l]=='.'){
						num2=s[l]+num2;
						stringstream(num2)>>d2;
						l--;
					}
					else{
						if(s[l]=='-')
							d2=d2*(-1);			
						break;
					}
				}		
				d2=d2+p[d];
				p[d]=d2;
				num="";
				num2="";
				d=1;
				d2=1;
			}		
			if(s[i]=='+'||s[i]=='-'||i==0){
				int j=i;
				float fr=0;
				bool flag=true;
				string free="";
				if(s[i]=='+'||s[i]=='-')
					j=i+1;
				while(j<n){
					if((s[j]>='0'&&s[j]<='9')||s[j]=='.')
						free=free+s[j];
					if(s[j]=='^'||s[j]=='*'||s[j]==var){
						free="";
						flag=false;
						break;
					}
					if(s[j]=='+'||s[j]=='-')
						break;
					j++;
				}
				if(flag){
					stringstream(free)>>fr;
					if(s[i]=='-')
						fr=fr*(-1);
					fr=fr+p[0];
					p[0]=fr;
				}
			}
		}
	};
	void setName(string na){
		name=na;
	};
	void capsVar(){
		if(var>=97)
			var=var-32;
		else
			var=var+32;
	};
	int getDeg(){
		return deg;
	};
	char getVar(){
		return var;
	};
	string getName(){
		return name;
	};
	bool isZero(){
		if(p==NULL)
			return false;
		if(deg!=0)
			return false;
		else{
			if(p[0]!=0)
				return false;
			else
				return true;
		}
	};
	const Polynomial &operator=(const Polynomial &q){
		name=q.name;
		deg=q.deg;
		var=q.var;
		if(q.p==NULL)
			p=NULL;
		else{
			if(p==NULL)
				p = new float[deg+1];
			else{
				float *del=p;
				p = new float[deg+1];
				delete []del;
			}
			for(int i=0;i<=deg;i++)
				p[i]=q.p[i];
		}
		return q;
	};
	Polynomial operator+(Polynomial &q){
		bool flag=true;
		int max=deg;
		int min=q.deg;
		if(deg<q.deg){
			max=q.deg;
			min=deg;
			flag=false;
		}
		Polynomial r(var,max);
		for(int i=0;i<=min;i++)
			r.p[i]=p[i]+q.p[i];
		if(max!=min){
			if(flag){
				for(int i=min+1;i<=max;i++)
					r.p[i]=p[i];
			}
			else{
				for(int i=min+1;i<=max;i++)
					r.p[i]=q.p[i];
			}
		}
		max=0;
		for(int i=r.deg;i>=0;i--){
			if(abs(r.p[i])>=ERROR){
				max=i;
				break;
			}
		}
		if(max==r.deg)
			return r;
		Polynomial result(var,max);
		for(int i=0;i<=max;i++)
			result.p[i]=r.p[i];
		return result;
	};
	Polynomial operator-(Polynomial q){
		for(int i=0;i<=q.deg;i++)
			q.p[i]=0-q.p[i];
		return *this+q;
	};
	Polynomial operator*(Polynomial &q){
		int max=deg+q.deg;
		Polynomial r(var,max);
		for(int i=0;i<=deg;i++){
			for(int j=0;j<=q.deg;j++){
				int k=i+j;
				r.p[k]=r.p[k]+p[i]*q.p[j];
			}
		}
		max=0;
		for(int i=r.deg;i>=0;i--){
			if(abs(r.p[i])>=ERROR){
				max=i;
				break;
			}
		}
		if(max==r.deg)
			return r;
		Polynomial result(var,max);
		for(int i=0;i<=max;i++)
			result.p[i]=r.p[i];
		return result;
	};
	Polynomial operator*(float k){
		Polynomial res=*this;
		for(int i=0;i<=deg;i++)
			res.p[i]=k*res.p[i];
		return res;
	};
	Polynomial operator/(Polynomial &q){
		if(q.isZero())
			return q;
		if(deg<q.deg){
			Polynomial r(var,0);
			return r;
		}
		int rmax=deg-q.deg;
		int amax=deg;
		Polynomial result(var,rmax);
		Polynomial r(var,rmax);
		Polynomial a=*this;
		Polynomial u;	
		while(amax>=q.deg){
			r.p[rmax]=a.p[amax]/q.p[q.deg];
			result=result+r;
			u=r*q;
			a=a-u;
			amax=a.deg;
			r.p[rmax]=0;
			rmax=a.deg-q.deg;
			if(a.isZero())
				break;
		}
		return result;
	};
	Polynomial operator%(Polynomial &q){
		if(q.isZero())
			return q;
		if(deg<q.deg)
			return *this;
		int rmax=deg-q.deg;
		int amax=deg;
		Polynomial r(var,rmax);
		Polynomial a=*this;
		Polynomial u;	
		while(amax>=q.deg){
			r.p[rmax]=a.p[amax]/q.p[q.deg];
			u=r*q;
			a=a-u;
			amax=a.deg;
			r.p[rmax]=0;
			rmax=a.deg-q.deg;
			if(a.isZero())
				break;
		}
		return a;
	};
	friend Polynomial gcd(Polynomial a,Polynomial b){
		Polynomial r,res;
		while(!(r.isZero())){
			res=r;
			if(a.deg>b.deg){
				r=a%b;
				a=r;
			}
			else{
				r=b%a;	
				b=r;
			}
		}
		if(res.p==NULL)
			res=b;
		else
			res=res*(float(1)/(res.p[res.deg]));
		return res;
	};
	friend Polynomial *eap(Polynomial a,Polynomial b){
		Polynomial r,res; 
		int n=a.deg;
		int i=0;
		if(a.deg<b.deg)
			n=b.deg;
		Polynomial *result=new Polynomial[n];
		while(!(r.isZero())){
			res=r;
			if(a.deg>b.deg){
				r=a%b;
				a=r;
			}
			else{
				r=b%a;	
				b=r;
			}
			result[i]=r;
			i++;
		}
		if(res.p==NULL)
			res=b;
		else res=res*(float(1)/(res.p[res.deg]));
		result[i]=res;
		return result;
	};
	friend Polynomial tep(Polynomial q,float x){
		int n=0;
		while(n<=q.deg){
			for(int i=q.deg-1;i>=n;i--){
				q.p[i]=q.p[i+1]*x+q.p[i];
			}
			n++;
		}
		return q;
	};
	friend float **htp(Polynomial q,const float &x){
		int n=0;
		float **p=new float*[q.deg+2];
		for(int i=0;i<=q.deg+1;i++)
			p[i]=new float[q.deg+2];
		for(int i=0;i<=q.deg+1;i++){
			for(int j=0;j<=q.deg+1;j++)
				p[i][j]=0;
		}
		for(int i=0;i<=q.deg+1;i++)
			p[i][0]=x;
		for(int i=1;i<=q.deg+1;i++)
			p[0][i]=q.p[q.deg-i+1];
		while(n<=q.deg){
			for(int i=q.deg-1;i>=n;i--){
				q.p[i]=q.p[i+1]*x+q.p[i];
			}
			for(int i=1;i<=q.deg+1;i++)
				p[n+1][i]=q.p[q.deg-i+1];
			n++;
		}
		return p;
	};
	/*------------------------*/
	void show(){
		if(p!=NULL){
			int flag=0;
			cout<<'\t';
			for(int i=deg;i>=1;i--){
				if(p[i]==0)
					flag++;
				if(i>1){
					if(p[i]>0){
						if(p[i]!=1)
							cout<<'+'<<p[i]<<'*'<<var<<"^("<<i<<") ";
						else
							cout<<'+'<<var<<"^("<<i<<") ";
					}
					if(p[i]<0){
						if(p[i]!=-1)
							cout<<p[i]<<'*'<<var<<"^("<<i<<") ";
						else
							cout<<'-'<<var<<"^("<<i<<") ";
					}
				}
				else{
					if(p[1]>0){
						if(p[1]!=1)
							cout<<'+'<<p[1]<<'*'<<var<<' ';
						else
							cout<<'+'<<var<<' ';
					}
					if(p[1]<0){
						if(p[1]!=-1)
							cout<<p[1]<<'*'<<var<<' ';
						else
							cout<<'-'<<var<<' ';
					}
				}
			}
			if(p[0]<0)
				cout<<p[0];
			if(p[0]>0)
				cout<<'+'<<p[0];
			if(p[0]==0&&flag==deg)
				cout<<'0';
			cout<<endl;
		}
		else
			cout<<"NULL"<<endl;
	}
};
                             
class PList{
private:
	Polynomial *pl;
	int n;
	bool full;
public:
	PList(){
		n=0;
		pl=new Polynomial[50];
		full=false;
	};
	~PList(){
		if(pl!=NULL){
			delete []pl;
		}
	};
	void set(Polynomial &a){
		int k=-1;
		k=search(a.getName());
		if(k==-1){
			if(n<50){
				pl[n]=a;
				n++;
			}
			else{
				full=true;
				n=0;
				pl[n]=a;
				n++;
			}
		}
		else
			pl[k]=a;
	};
	int search(string &na){
		if(na.compare(none)==0)
			return -1;
		string temp;
		int m=n;
		if(full)
			m=50;
		for(int i=0;i<m;i++){
			temp=pl[i].getName();
			if(na.compare(temp)==0)
				return i;
		}
		return -1;
	}; 
	friend int operators(const char &c){
		if(c=='(')
			return -2;
		if(c==')')
			return -3;
		if(c=='+')
			return -4;
		if(c=='-')
			return -5;
		if(c=='*')
			return -6;
		if(c=='/')
			return -7;
		if(c=='%')
			return -8;
		return -1;
	};
	friend bool compareOpe(const int &ope1,const int &ope2){
		int h1=0,h2=0;
		if(ope1==-6||ope1==-7||ope1==-8)
			h1=2;
		if(ope1==-4||ope1==-5)
			h1=1;
		if(ope2==-6||ope2==-7||ope2==-8)
			h2=2;
		if(ope2==-4||ope2==-5)
			h2=1;
		if(h2>h1)
			return true;//ope2 higher ope1
		else
			return false;//ope2 lower or equal ope1
	};
	friend bool transOpeNum(Polynomial &left,Polynomial &right,const int &ope){
		if(ope==-4)
			left=left+right;
		if(ope==-5)
			left=left-right;
		if(ope==-6)
			left=left*right;
		if(ope==-7){
			if(right.isZero())
				return false;
			left=left/right;
		}
		if(ope==-8){
			if(right.isZero())
				return false;
			left=left%right;
		}
		return true;
	};
	int testGcd(string &la,Polynomial &ans){
		int n=la.length();
		if(n<8)
			return 0;//function syntax error
		if(la[3]!='('||la[n-1]!=')')
			return 0;//function syntax error
		string arg1="";
		int k=-1;
		for(int i=4;i<n-1;i++){
			if(la[i]==','){
				k=i;
				break;
			}
			arg1=arg1+la[i];
		}
		if(k==-1||k==n-2)
			return 0;//function syntax error
		string arg2="";
		for(int i=k+1;i<n-1;i++)
			arg2=arg2+la[i];
		int a1=-1,a2=-1;
		a1=search(arg1);
		a2=search(arg2);
		if(a1==-1)
			return -1;//unknown first argument 
		if(a2==-1)
			return -2;//unknown second argument 
		ans=gcd(pl[a1],pl[a2]);
		if((ans.getName()).compare(NA)==0)
			return -3;//N/A
		return 1;
	};
	int testEap(string &la,Polynomial &ans,Polynomial *&re,int &m){
		int n=la.length();
		if(n<8)
			return 0;//function syntax error
		if(la[3]!='('||la[n-1]!=')')
			return 0;//function syntax error
		string arg1="";
		int k=-1;
		for(int i=4;i<n-1;i++){
			if(la[i]==','){
				k=i;
				break;
			}
			arg1=arg1+la[i];
		}
		if(k==-1||k==n-2)
			return 0;//function syntax error
		string arg2="";
		for(int i=k+1;i<n-1;i++)
			arg2=arg2+la[i];
		int a1=-1,a2=-1;
		a1=search(arg1);
		a2=search(arg2);
		if(a1==-1)
			return -1;//unknown first argument 
		if(a2==-1)
			return -2;//unknown second argument 
		m=pl[a1].getDeg();
		ans=gcd(pl[a1],pl[a2]);
		if((ans.getName()).compare(NA)==0)
			return -3;//N/A
		else
			re=eap(pl[a1],pl[a2]);
		return 1;
	};
	int testTep(string &la,Polynomial &ans,float &x){
		int n=la.length();
		if(n<8)
			return 0;//function syntax error
		if(la[3]!='('||la[n-1]!=')')
			return 0;//function syntax error
		string arg1="";
		int k=-1;
		for(int i=4;i<n-1;i++){
			if(la[i]==','){
				k=i;
				break;
			}
			arg1=arg1+la[i];
		}
		if(k==-1||k==n-2)
			return 0;//function syntax error
		string arg2="";
		for(int i=k+1;i<n-1;i++){
			if((!(la[i]>='0'&&la[i]<='9'))&&la[i]!='.'&&la[i]!='-')
				return -2;//unknown second argument 
			if(la[i]=='.')
				if(!(la[i]>='0'&&la[i]<='9'))
					return -2;//unknown second argument 
			if(la[i]=='-')
				if(!(la[i]>='0'&&la[i]<='9'))
					return -2;//unknown second argument 
			arg2=arg2+la[i];
		}
		int a1=-1;
		float a2;
		stringstream(arg2)>>a2;
		a1=search(arg1);
		if(a1==-1)
			return -1;//unknown first argument 
		ans=tep(pl[a1],a2);
		x=a2;
		return 1;
	};
	int testHtp(string &la,Polynomial &ans,float &x,float **&mat,int &m){
		int n=la.length();
		if(n<8)
			return 0;//function syntax error
		if(la[3]!='('||la[n-1]!=')')
			return 0;//function syntax error
		string arg1="";
		int k=-1;
		for(int i=4;i<n-1;i++){
			if(la[i]==','){
				k=i;
				break;
			}
			arg1=arg1+la[i];
		}
		if(k==-1||k==n-2)
			return 0;//function syntax error
		string arg2="";
		for(int i=k+1;i<n-1;i++){
			if((!(la[i]>='0'&&la[i]<='9'))&&la[i]!='.'&&la[i]!='-')
				return -2;//unknown second argument 
			if(la[i]=='.')
				if(!(la[i]>='0'&&la[i]<='9'))
					return -2;//unknown second argument 
			if(la[i]=='-')
				if(!(la[i]>='0'&&la[i]<='9'))
					return -2;//unknown second argument 
			arg2=arg2+la[i];
		}
		int a1=-1;
		float a2;
		stringstream(arg2)>>a2;
		a1=search(arg1);
		if(a1==-1)
			return -1;//unknown first argument 
		mat=htp(pl[a1],a2);
		x=a2;
		m=pl[a1].getDeg()+2;
		return 1;
	};
	int testExpression(string &la,string &wrongs,Polynomial &ans){
		int m=la.length();
		int flag=0;
		for(int i=0;i<m;i++){
			if(la[i]=='(')
				flag++;
			else if(la[i]==')')
				flag--;
		}
		if(flag!=0)
			return 0;//syntax error
		int *exp=new int [m];
		for(int i=0;i<m;i++)
			exp[i]=-1;
		int k=0,j=0;
		string pol="";
		for(int i=0;i<m;i++){
			if((la[i]>='a'&&la[i]<='z')||(la[i]>='0'&&la[i]<='9')){
				pol=pol+la[i];
				if(i==m-1){
					k=search(pol);
					if(k==-1){
						wrongs=pol;
						return -1;//Unknown Object 'wrongs'
					}
					else{
						exp[j]=k;
						j=j+1;
						pol="";
					}
				}
			}
			else if(la[i]=='+'||la[i]=='-'||la[i]=='*'||la[i]=='/'||la[i]=='%'||la[i]==')'||la[i]=='('){
				if(pol.compare(none)!=0){
					k=search(pol);
					if(k==-1){
						wrongs=pol;
						return -1;//Unknown Object 'wrongs'
					}
					else{
						exp[j]=k;
						exp[j+1]=operators(la[i]);
						j=j+2;
						pol="";
					}
				}
				else{
					exp[j]=operators(la[i]);
					j++;
				}
			}
			else 
				return 0;//syntax error
		}
		int *stkA=new int[j];
		int *stkB=new int[j];
		for(int i=0;i<j;i++){
			stkA[i]=stkB[i]=-1;
		}
		int a=0,b=0;
		for(int i=0;i<j;i++){
			if(exp[i]==-2){
				stkA[a]=exp[i];
				a++;
			}
			else if(exp[i]==-3){
				while(stkA[a-1]!=-2){
					a--;
					stkB[b]=stkA[a];
					b++;
					if(a==0)
						break;
				}
			}
			else if(exp[i]==-4||exp[i]==-5||exp[i]==-6||exp[i]==-7||exp[i]==-8){
				if(a<=0){
					stkA[a]=exp[i];
					a++;
				}
				else{
					while(!compareOpe(stkA[a-1],exp[i])){
						a--;
						if(stkA[a]!=-2){	
							stkB[b]=stkA[a];
							b++;
						}
						if(a==0)
							break;
					}
					if(compareOpe(stkA[a-1],exp[i])){
						stkA[a]=exp[i];
						a++;
					}
				}
			}
			else{ 
				stkB[b]=exp[i];
				b++;
			}
		}
		while(a>0){
			a--;
			if(stkA[a]!=-2){	
				stkB[b]=stkA[a];
				b++;
			}
		}
		Polynomial *stkP=new Polynomial[b];
		int p=0;
		for(int i=0;i<b;i++){
			if(stkB[i]>=0){
				stkP[p]=pl[stkB[i]];
				p++;
			}
			else{
				if(!transOpeNum(stkP[p-2],stkP[p-1],stkB[i]))
					return 2;//can not divide to 0;
				p--;
			}
		}
		ans=stkP[0];
		delete []exp;
		delete []stkA;
		delete []stkB;
		delete []stkP;
		return 1;
	};
};

void showHornerTable(float **p,const int &n){
	if(p!=NULL){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++)
				cout<<setw(6)<<p[i][j];
			cout<<endl;
		}
	}
};

void reduceSpace(string &s){
	string re="";
	int m=s.length();
	for(int i=0;i<m;i++)
		if(s[i]!=32)
			re=re+s[i];
	s=re;
}

int divideString(string &s,string &fi,string &la){
	string r="";
	int flag1=0;
	int m=s.length();
	if(m==0)
		return 2;//empty string
	if(m==1){
		if(s[0]=='+')
			return 6;//operator '+'
		if(s[0]=='-')
			return 7;//operator '-'
		if(s[0]=='*')
			return 8;//operator '*'
		if(s[0]=='/')
			return 9;//operator '/'
		if(s[0]=='%')
			return 10;//operator '%'
		if(!(s[0]>='a'&&s[0]<='z'))
			return -6;//wrong operator
	}
	if(s[m-1]==';'){
		flag1++;
		for(int i=0;i<m-1;i++)
			r=r+s[i];
		s=r;
	}
	if(s.compare(exi)==0)
		return -1;
	if(s.compare(clear)==0)
		return -2;
	if(s.compare(delet)==0)
		return -3;
	if(s.compare(help)==0)
		return -4;
	if(s.compare(about)==0)
		return -5;
	
	reduceSpace(s);
	m=s.length();
	fi="";
	la="";
	int j=-1;
	
	for(int i=0;i<m;i++){
		if(s[i]==';')
			flag1++;
		else{
			if(s[i]!='+'&&s[i]!='-'&&s[i]!='*'&&s[i]!='='&&s[i]!='/'&&s[i]!='%'&&s[i]!='^'&&s[i]!='('&&s[i]!=')'&&s[i]!=']'&&s[i]!='['&&s[i]!=','){
				if(!(s[i]>='0'&&s[i]<='9')){
					if(!(s[i]>='a'&&s[i]<='z')){
						return 5;//string contains wrong character
					}
				}
			}
		}
	}
	for(int i=m-1;i>=0;i--){
		if(s[i]!='=')
			la=s[i]+la;
		else{
			j=i-1;
			break;
		}
	}
	for(int i=j;i>=0;i--){
		if(s[i]!='=')
			fi=s[i]+fi;
		else
			return 3;//string contains more than 1 '='
	}
	if(flag1>1)
		return 4;//string contains more than 1 ';'
	else{
		if(flag1==1)
			return 1;//string finishes at ';'
		else
			return 0;//string finishes without ';'
	}
};

int classifyStringLast(string &la){
	int m=la.length();
	string temp="";
	if(m>=3){
		for(int i=0;i<3;i++)
			temp=temp+la[i];
		if(temp.compare(gcdf)==0)
			return 2;//function gcd
		if(temp.compare(eapf)==0)
			return 3;//function eap
		if(temp.compare(tepf)==0)
			return 4;//function tep
		if(temp.compare(htpf)==0)
			return 5;//fuction htp
		if(temp[0]=='['&&temp[2]==']'){
			if(temp[1]>='a'&&temp[1]<='z'){
				char var=temp[1];
				for(int i=3;i<m-1;i++){
					if(la[i]==var){
						if(la[i+1]!='+'&&la[i+1]!='-'&&la[i+1]!='^')
							return -2;//polynomial: syntax error
					}
					if(la[i]=='^'){
						if(!(la[i+1]>='0'&&la[i+1]<='9')){
							if(la[i+1]=='-')
								return -3;//the degree of polynomial must not be smaller than 0
							else
								return -2;//polynomial: syntax error
						}
					}
					if(la[i]>='a'&&la[i]<='z'&&la[i]!=var)
						return -1;//polynomial has wrong variable 
				}
				if(la[m-1]>='a'&&la[m-1]<='z'&&la[m-1]!=var)
						return -1;//polynomial has wrong variable 
				return 1;//is polynomial
			}
			else return -1;//polynomial has wrong variable 
		}
		else{
			if(temp[0]=='['||temp[2]==']')
				return -2;//polynomial: syntax error
			else return 0;//statement
		}
	}
	return 0;//statement
}

bool calculate(Polynomial &ans,Polynomial &tem,int &ope){
	if(ope==6)
		ans=ans+tem;
	if(ope==7)
		ans=ans-tem;
	if(ope==8)
		ans=ans*tem;
	if(ope==9){
		if(tem.isZero())
			return false;
		else
			ans=ans/tem;
	}
	if(ope==10){
		if(tem.isZero())
			return false;
		else
			ans=ans%tem;
	}
	return true;
}
