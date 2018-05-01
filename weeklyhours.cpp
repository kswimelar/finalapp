//Final App
//Name: Kari Swimelar
//Date: 03/12/2018
/**************************************************************
 * Program to input employees id number, hours worked and     *
 * hourly rate. When finished with the input, the program     *
 * will display the gross, overtime, taxes, and netpay.       *
 * 
 * ***********************************************************/
#include <iostream>
#include <fstream>//file input output stream
#include <string>
using namespace std; 
// create class weeklyHours

class weeklyHours{
  public:
  string id;
  string hoursworked;
  string hourlyrate;
  void getData() // get data for class
  {
    id = "";
    hoursworked = "";
    hourlyrate= "";
    cout<< "Enter Employee ID: ";
    getline(cin,id);
    cout<< "Enter Hours Worked: ";
    getline(cin,hoursworked);
    cout<< "Enter Hourly Rate: ";
    getline(cin,hourlyrate);
  }
};

//function prototypes
int readalldata(long int[],int[],float[],const int);
void findovertimehours(int[],int[],int);
void findovertimepay(int[],float[],float[],int);
void findregularhours(int[],int[],int);
void findregularpay(int[],float[],float[],int);
void findgrosspay(float[],float[],float[],int);
void findtaxrate(float[],float[],int);
void findtaxamount(float[],float[],float[],int);
void findnetpay(float[],float[],float[],int);
void printalldata(long int[],int[],float[],float[],float[],float[],float[],int);

int main()
{
  const int MAXSIZE=50;   //for maximum of 50 employees
  string next = "Y";
  weeklyHours emp;
     // create employee.txt file for employee data.
    ofstream file("employee.txt", std::ios_base::app);
     if(!file){
        cout<<"Error creating file..";
        return 0;
    }
 while (next != "n" && next != "N"){
    
    // while loop to writeline to the file.
    
    emp.getData();    //read from user input
     string writeline = emp.id + " " + emp.hoursworked+ " " + emp.hourlyrate;
    file<<writeline<<endl;    //write into file
    cout<<"Continue? Y or N:";
    cin>>next;
    cout<<"\n";
    cin.ignore();
    
 }
    file.close();   //close the file employee.txt
  
  // begin reading and calculatiing from file.  
  //decleration of variables
  int n;
  long int id[MAXSIZE];
  int hoursworked[MAXSIZE];
  int overtimehours[MAXSIZE];
  int regularhours[MAXSIZE];
  float hourlyrate[MAXSIZE];
  float regularpay[MAXSIZE];
  float overtimepay[MAXSIZE];
  float grosspay[MAXSIZE];
  float taxrate[MAXSIZE];
  float taxamount[MAXSIZE];
  float netpay[MAXSIZE];
     
  //function calls
  n=readalldata(id,hoursworked,hourlyrate,MAXSIZE); //get all data
  findovertimehours(hoursworked,overtimehours,n);
  findovertimepay(overtimehours,hourlyrate,overtimepay,n);
  findregularhours(hoursworked,regularhours,n);
  findregularpay(regularhours,regularpay,hourlyrate,n);
  findgrosspay(regularpay,overtimepay,grosspay,n);
  findtaxrate(grosspay,taxrate,n);
  findtaxamount(grosspay,taxamount,taxrate,n);
  findnetpay(grosspay,netpay,taxamount,n);
  printalldata(id,hoursworked,hourlyrate,overtimepay,grosspay,taxamount,netpay,n);
  //cin.get();
  return 0;
}//End Main

//function definitions
int readalldata(long int id[], int hoursworked[], float hourlyrate[], int n)
{
  ifstream fin("employee.txt");
  n=0;
    
  while(fin>>id[n]>>hoursworked[n]>>hourlyrate[n]) n++;
    
  fin.close();
  //system("PAUSE");
  return n;
}// End Read all data

void findovertimehours(int hoursworked[],int overtimehours[],int n)
{
  for(int i=0; i<n; i++)
  {
    if(hoursworked[i]>40) overtimehours[i]=hoursworked[i]-40;
    else overtimehours[i]=0;
  }
}// End Find overtime hours

void findovertimepay(int overtimehours[], float hourlyrate[],
  float overtimepay[], int n)
{
  for(int i=0; i<n; i++)
  {
    overtimepay[i]=overtimehours[i]*hourlyrate[i]*1.5;
  }
}// End Find overtime pay

void findregularhours(int hoursworked[],int regularhours[],int n)
{
  for(int i=0; i<n; i++)
  {
    if(hoursworked[i]>40) regularhours[i]=40;
    else regularhours[i]=hoursworked[i];
  }
}// End Find regular hours

void findregularpay(int regularhours[],float regularpay[],
  float hourlyrate[],int n)
{
  for(int i=0; i<n; i++)
  {
    regularpay[i] = regularhours[i]*hourlyrate[i];
  }
}// End Find regular pay
void findgrosspay(float regularpay[],float overtimepay[],float grosspay[],int n)
{
  for(int i=0; i<n; i++)
  {
    grosspay[i]=regularpay[i]+overtimepay[i];
  }
}//End Find gross pay

void findtaxrate(float grosspay[],float taxrate[],int n)
{
  for(int i=0; i<n; i++)
  {
    if(grosspay[i]>4000.00) taxrate[i]=0.40;
    else if(grosspay[i]>3000.00) taxrate[i]=0.30;
    else if(grosspay[i]>1000.00) taxrate[i]=0.20;
    else taxrate[i]=0.10;
  }
}//End Find tax rate
void findtaxamount(float grosspay[],float taxamount[],float taxrate[],int n)
{
  for(int i=0; i<n; i++)
  {
    taxamount[i]=grosspay[i]*taxrate[i];
  }
}//End Find tax amount

void findnetpay(float grosspay[],float netpay[],float taxamount[],int n)
{
  for(int i=0; i<n; i++)
  {
    netpay[i]=grosspay[i]-taxamount[i];
  }
}// End Find net pay

void printalldata(long int id[], int hoursworked[], float hourlyrate[],
  float overtimepay[],float grosspay[],float taxamount[],float netpay[],int n)
{
  cout<<"Printing employee data from employee.txt file."<<endl;
  cout<<"\n";
  cout<<"EMP ID"<<"\t"<<"HOURS"<<"\t"<<"RATE"<<"\t"
  <<"OVERPAY"<<"\t"<<"GROSSPAY"<<"\t"<<"TAX"<<"\t"
  <<"NETPAY"<<endl;
  
  for(int i=0; i<n; i++)
  {
    cout<<""<<id[i]<<"\t"<<hoursworked[i]<<"\t"<<hourlyrate[i]
    <<"\t"<<overtimepay[i]<<"\t"<<grosspay[i]<<"\t\t"
    <<taxamount[i]<<"\t"<<netpay[i]<<endl;
  } // end for
}// End Print all data
