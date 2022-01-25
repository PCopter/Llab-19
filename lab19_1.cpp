#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
using namespace std;



char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names, vector<int> &scores,vector<char> &grades){
    ifstream sources(filename);
    string textline;
    char format[] ="%[^:]: %d %d %d";
    
    while(getline(sources,textline))
    {
        char name[100];
        int score1,score2,score3;
        sscanf(textline.c_str(),format,name,&score1,&score2,&score3);
        names.push_back(name);
        scores.push_back(score1+score2+score3);
        grades.push_back(score2grade(score1+score2+score3));
    }

}

void getCommand(string &command,string &key){
    string cmdline;
    char cmdch[100];
    char keych[100];
    char format[]="%s %[^\n] ";
    cout << "Please input your command: ";
    getline(cin,cmdline);
    sscanf(cmdline.c_str(),format,cmdch,keych);
    command = cmdch;
    key = keych;

}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key)
{
cout << "---------------------------------\n";
int result = -1;
for(unsigned int i= 0;i<names.size();i++)
{
    if(toUpperStr(names.at(i))==key)result =i;
}
if(result != -1)
{
    cout << names.at(result) << "'s score = " << scores.at(result) << "\n";
    cout << names.at(result) << "'s grade = " << grades.at(result) << "\n";
}
    else cout << "Cannot found." << "\n";
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------\n";
    for(unsigned int i= 0;i<names.size();i++){
        if(grades.at(i)==*key.c_str()){
            cout << names.at(i) << " (" << scores.at(i) << ") " << "\n";
        }
    }
cout << "---------------------------------\n";

}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
