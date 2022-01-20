// основная часть кода была взята вот отсюда 
// https://www.cyberforum.ru/cpp-beginners/thread289149.html
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <cstring>
#include <iostream>
#include <cstdlib>
// <цифра> ::= '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
// <число> ::= <цифра> { <цифра> } [ '.' <цифра> { <цифра> } ]
// 
// <выражение> ::= <слагаемое> [ ( '+' | '-' ) <слагаемое> ]
// <слагаемое> ::= <множитель> [ ( '*' | '/' ) <множитель> ]
// <множитель> ::= ( <число> | '(' <выражение> ')' ) [ '^' <множитель> ]
//void assert(0);
 	
 	
double eval(char *str);
double number(char *, unsigned *);//
double expr(char *, unsigned *);//
double term(char *, unsigned *);//
double factor(char *, unsigned *);//
void pars(char *);
int check(char *);//


void Ueval(){
	char str[1024];
	std::string s="1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)";
    strcpy(str, s.c_str());
    
    pars(str);
    assert(eval(str)==11.00);
}



void Ucheck(){
	
	char str[1024];
	std::string s="1234+1234/(12)";
    strcpy(str, s.c_str());
	assert(check(str)==0);
	
}
void Unumber(){
	char str123[5]={'1','2','3','\0'};
	unsigned i = 0;
	assert(number(str123,&i)==123);
	
	char str_123[5]={'-','1','2','3','\0'};
	i = 0;
	assert(number(str_123,&i)==-123);
}

void Uexpr(){
	unsigned i = 0;
    
	char str[1024];
	std::string s="1234+1234/1";
    strcpy(str, s.c_str());
	assert(expr(str, &i)==2468);
}

void Ufactor(){
	unsigned i = 0;
  
	char str[1024];
	std::string s="(1234+1)/wdfwfwe323";//ok
    strcpy(str, s.c_str());
	assert(factor(str, &i)==1235);
	
}

void Uterm(){
	unsigned i = 0;
  
	char str[1024];
	std::string s="1+2*3";
    strcpy(str, s.c_str());
    
    //std::cout<<term(str, &i);
	
	assert(term(str, &i)==1);
	
	
	i=0;
	s="2*2*3";
	strcpy(str, s.c_str());
    assert(term(str, &i)==12);
	
	
}

int main(){	
	
	Ucheck();
	
	Unumber();
	
	Uexpr();
	
	Ufactor();
	
	Uterm();
	
	Ueval();
	
    return 0;
}

int check(char *str){
	int t=1, i=0;
	int br=0;
	while(str[i]!='\0'){
		if(str[i]==')'){
			br--;
		}
		if(str[i]=='('){
			br++;
		}
		if(br<0){
			t=0;
		}
		i++;
	}
	if(t==0 || br!=0){
		printf("Brackets unbalanced!\n");
		return(-1);
	}
	else{
		i=0;
		while(str[i]!='\0'){
			if(str[i]==',' || str[i]=='.' || str[i]=='(' || str[i]==')' || (str[i]>='0' && str[i]<='9') || str[i]=='-' || str[i]=='+' || str[i]=='*' || str[i]=='/' || str[i]=='^'){
				i++;
			}
			else{
				printf("некорректный ввод, строка содержит недопустимое выражение ");
				while(str[i]!='\0' && !(str[i]==',' || str[i]=='.' ||  str[i]=='(' || str[i]==')' || (str[i]>='0' && str[i]<='9') || str[i]=='-' || str[i]=='+' || str[i]=='*' || str[i]=='/' || str[i]=='^')){
					printf("%c",str[i]);
					i++;
				}
				return(-1);
			}
		}
	}
	return(0);
}


void pars(char *str){
	int j = 0, i = 0;
	char c;
	while (str[j]!='\0'){
		if(str[j]!=' '){
			c = str[j];
			str[i]=c;
			i++;
			j++;
		}
		else{
			j++;
		}
	}
	str[i]='\0';
} 
/////////////////////////////
double eval(char *str)
{
    unsigned i = 0;
 
    return expr(str, &i);
}
 
double number(char *str, unsigned *idx)
{
    double result = 0.0;
    double div = 10.0;
    int sign = 1;
 
    if (str[*idx] == '-')
    {
        sign = -1;
        ++*idx;
    }
 
    while (str[*idx] >= '0' && str[*idx] <= '9')
    {
        result = result * 10.0 + (str[*idx] - '0');
        
        ++*idx;
    }
 
    if (str[*idx] == '.' || str[*idx] == ',')
    {
        ++*idx;
 
        while (str[*idx] >= '0' && str[*idx] <= '9')
        {
            result = result + (str[*idx] - '0') / div;
            div *= 10.0;
 
            ++*idx;
        }
    }
 
    return sign * result;
}
 
double expr(char *str, unsigned *idx)
{
    double result = term(str, idx);

    while (str[*idx] == '+' || str[*idx] == '-')
    {
        switch (str[*idx])
        {
        case '+':
            ++*idx;
 
            result += term(str, idx);
            
            break;
        case '-':
            ++*idx;
 
            result -= term(str, idx);
 
            break;
        }
    }
 
    return result;
}
 
double term(char *str, unsigned *idx)
{
    double result = factor(str, idx);
    double div;
 
    while (str[*idx] == '*' || str[*idx] == '/')
    {
        switch (str[*idx])
        {
        case '*':
            ++*idx;
 
            result *= factor(str, idx);
 
            break;
        case '/':
            ++*idx;
 
            div = factor(str, idx);
 
            if (div != 0.0)
            {
                result /= div;
            }
            else
            {
                printf("Division by zero!\n");
                exit(-1);
            }
 
            break;
        }
    }
 
    return result;
}
 
double factor(char *str, unsigned *idx)
{
    double result;
    int sign = 1;
 
    if (str[*idx] == '-')
    {
        sign = -1;
 
        ++*idx;
    }
 
    if (str[*idx] == '(')
    {
        ++*idx;
 
        result = expr(str, idx);
 
        if (str[*idx] != ')')
        {
            printf("Brackets unbalanced!\n");
            exit(-2);
        }
 
        ++*idx;
    }
    else
        result = number(str, idx);

    return sign * result;
}
