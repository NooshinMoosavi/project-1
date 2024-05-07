#include <iostream>
#include <string>
using namespace std;
class trim
{
    public:
    string trim1(const string &u)
    {
        int start = 0;
        int end = u.length() - 1;
        while (start <= end && (u[start] == ' ' || u[start] == '\t' || u[start] == '\n' || u[start] ==  '\r'))
        {
            start++;
        }
        while (end >= start && (u[end] == ' ' || u[end] == '\t' || u[end] == '\n' || u[end] ==  '\r'))
        {
            end--;
        }
        return u.substr(start, end-start + 1);
    }
};
class login
{
    private:
    string userName;
    string password;
    public:
    login(const string &u, const string &p) : userName(u), password(p){}
    bool isTeacher()
    {
        if(userName.find("teacher.") != string::npos)
        {
            return true;
        }
        return false;
    }   
};
class teacher
{
    public:
    trim tr;
    int num;
    string *question;
    bool Q;
    string optionA, optionB, optionC, optionD, *correctOption;
    string *options;
    string *grade;
    void askQuestions()
    {
        cout << "Do you want to ask multiple-choice(1) question or a descriptive(2) question ? ";
        string choiceType;
        cin >> choiceType;
        if (choiceType == "1") 
        {
            Q = true;
        }
        else if (choiceType == "2")
        {
            Q = false;
        }
        cout << "How many questions do you want to ask ? ";
        cin >> num;
        question = new string[num];
        grade = new string[num];
        options = new string[num];
        correctOption = new string[num];
        for (int i = 0; i < num; ++i)
        {
            cout << "question " << i + 1 <<" :";
            getline(cin >> ws, question[i]);
            cout << " How many points does this question have ? ";
            getline(cin >> ws, grade[i]);
            if(Q)
            {
                cout << "enert option A : ";
                getline(cin, optionA);
                optionA = tr.trim1(optionA);
                cout << "enert option B : ";
                getline(cin, optionB);
                optionB = tr.trim1(optionB);
                cout << "enert option C : ";
                getline(cin, optionC);
                optionC = tr.trim1(optionC);
                cout << "enert option D : ";
                getline(cin, optionD);
                optionD = tr.trim1(optionD);
                options[i] += "A)" + optionA + " " + "B)" + optionB + " " + "C)" + optionC + " " + "D)" + optionD;
                cout << "Enter the correct option (A, B, C, D) : ";
                getline(cin, correctOption[i]);
                correctOption[i] = tr.trim1(correctOption[i]);                     
            }
        }
    }
    bool isTest()
    {
        if(Q)
        {
            return true;
        }
        return false;
    }
    int getNum()
    {
        return num;
    }
    string getQuestions(int index)
    {
        if(index >= 0 && index < num)
        {
            return question[index];
        }
        return "";
    }
    string getGrade(int index)
    {
        if(index >= 0 && index < num)
        {
            return grade[index];
        }
        return "";
    }
    string getOptions(int index)
    {
        if (Q)
        {
            if(index >= 0 && index < num)
            {
                return options[index];  
            }
            return "";
        }
        return "";
    }
    string getCorrectOption(int index)
    {
        if(index >= 0 && index < num)
        {
            return correctOption[index];
        }
        return "";
    }
};
int main()
{
    trim tr;
    while(true)
    {
        cout << "Welcome dear teacher !" << endl;
        string userName, passWord;
        cout << "Enter userName: ";
        getline(cin, userName);
        userName = tr.trim1(userName);
        cout << "Enter passWord: ";
        getline(cin, passWord);
        passWord = tr.trim1(passWord);
    }
    return 0;
}