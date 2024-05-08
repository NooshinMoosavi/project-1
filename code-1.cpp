#include <iostream>
#include <string>
#include <thread>
#include <chrono>
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
    int time;
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
        cout << "How many seconds does this exam take? ";
        cin >> time;
        question = new string[num];
        grade = new string[num];
        options = new string[num];
        correctOption = new string[num];
        for (int i = 0; i < num; ++i)
        {
            cout << "question " << i + 1 <<" :";
            getline(cin >> ws, question[i]);
            cout << "How many points does this question have ? ";
            getline(cin >> ws, grade[i]);
            if(Q)
            {
                cout << "enter option A : ";
                getline(cin, optionA);
                optionA = tr.trim1(optionA);
                cout << "enter option B : ";
                getline(cin, optionB);
                optionB = tr.trim1(optionB);
                cout << "enter option C : ";
                getline(cin, optionC);
                optionC = tr.trim1(optionC);
                cout << "enter option D : ";
                getline(cin, optionD);
                optionD = tr.trim1(optionD);
                options[i] += "A)" + optionA + " " + "B)" + optionB + " " + "C)" + optionC + " " + "D)" + optionD;
                cout << "Enter the correct option (A, B, C, D) : ";
                getline(cin, correctOption[i]);
                correctOption[i] = tr.trim1(correctOption[i]);                     
            }
        }
        delete [] question;
        delete [] options;
        delete [] grade;
        delete [] correctOption;
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
    float totalScore()
    {
        float *total = new float [getNum()];
        float total1 = 0;
        for (int i = 0; i < getNum(); i++) 
        {
            total[i] = stof(grade[i]);
        }
        for (int i = 0; i < getNum(); i++)
        {
            total1 += total[i];
        }  
        return total1;
        delete [] total;
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
    int examTime()
    {
        return time;
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
class student : public teacher
{
    string userName, passWord;
    string *answer;
    string *sum;
    float *sum1;
    float sum2;
    string userNames = "";
    public:
    void studentLogin(int i)
    {
        cout << "Hello, Welcome dear student " << i+1 << ": " << endl;
        cout << "Enter your userName: ";
        getline(cin >> ws, userName);
        userNames += userName + " ";
        cout<<"Enter your passWord: ";
        getline(cin >> ws, passWord);
    }
    string getUserNames()
    {
        return userNames;
    }
    void answerQuestions()
    {
        cout << "Read the questions carefully and answer them. " << endl;
        answer = new string[getNum()];
        for (int i = 0; i < getNum(); i++)
        {
            cout << "question " << i + 1 << ") " << getQuestions(i) << " (score: " << getGrade(i) << ")" << endl;
            cout << getOptions(i) << ": ";
            auto start = chrono::steady_clock::now();
            getline(cin, answer[i]);
            answer[i] = tr.trim1(answer[i]);
            auto end = chrono::steady_clock::now();
            auto elapsed_seconds = chrono::duration_cast<chrono::seconds>(end - start);
            if (elapsed_seconds.count() > examTime())
            {
                cout << "Time's up !";
                break;
            }
        }
        delete [] answer;
    }
    float grades()
    {
        sum2 = 0;
        sum = new string[getNum()];
        sum1 = new float[getNum()];
        for (int i = 0; i < getNum(); i++)
        {
            if (answer[i] == getCorrectOption(i))
            {
                sum[i] += getGrade(i);
            }
            else
            {
                sum[i] += '0';
            }
        }
        for (int i = 0; i < getNum(); i++)
        {
            sum1[i] = stof(sum[i]);
        }
        for (int i = 0; i < getNum(); i++)
        {
            sum2 += sum1[i];
        }
        return sum2;
        delete [] sum;
        delete [] sum1;
    }
    string getAnswers(int index)
    {
        return answer[index];
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
        login lo(userName, passWord);
        if(lo.isTeacher())
        {
            student stu;
            stu.askQuestions();
            int number;
            cout << "How many students are allowed to enter? ";
            cin >> number;
            string *answers = new string[number];
            float *grades = new float[number];
            for (int i = 0; i < number; i++)
            {
                stu.studentLogin(i);
                stu.answerQuestions();
                grades[i] = stu.grades();
                for (int j = 0 ; j < stu.getNum(); j++)
                {
                    answers[i] += stu.getAnswers(j) + "//";
                }
                cout << endl;
                delete [] answers;
                delete [] gradess;
            }
           int command;
           cout << " How many commands do you want to be executed ? ";
           cin >> command;
           while (command > 0)
           {
            cout << "select the order you want : (1:exam-section | 2:students-list | 3:grades-section | 4:exit)";
            int n;
            cin >> n;
            command--;
            switch(n)
            {
                case 1:
                {
                    for (int i = 0; i < stu.getNum(); i++)
                    {
                        cout << "question" << i + 1 << ": " << stu.getQuestions(i) << endl << stu.getOptions(i) << endl;
                    }
                    cout << "totalScore : " << stu.totalScore() << endl;
                    string answer;
                    cout << "Do you want to plan a new exam ? (yes/no)";
                    getline(cin >> ws, answer);
                    if(answer == "yes")
                    {
                        stu.askQuestions();
                    }
                    else
                        break;
                    break;  
                }
                case 2:
                {
                    cout << "List: " << stu.getUserNames() << endl;
                    string answer;
                    cout << "Are new students allowed to enter? (yes/no) ";
                    getline(cin >> ws, answer);
                    if (answer == "yes")
                    {
                        int number1;
                        cout << "How many are they? ";
                        cin >> number1;
                        for (int i = 0; i < number1; i++)
                        {
                            stu.studentLogin(i);
                        }
                        cout << "New list: " << stu.getUserNames();
                    }
                    break;
                }
                case 3:
                {
                    string descriptions;
                    for (int i = 0; i < number; i++)
                    {
                        cout << "Answer of student " << i+1 << " : " << answers[i] << endl;
                        if(stu.isTest())
                        {
                            cout << "Student grade " << i+1 << " : " << grades[i]<< endl << "Descriptions: ";
                            getline(cin >> ws, descriptions);
                            cout << endl;
                        }
                        else
                        {
                            string grade;
                            cout << "Enter the student grade " << i+1 << " : ";
                            getline(cin >> ws, grade);
                            cout << "Descriptions: ";
                            getline(cin >> ws, descriptions);
                        }
                    }
                    break;
                }
                case 4:
                {
                    cout << "Getting out..." << endl;
                    break;
                }
            }
        }
    } 
        else
        {
            cout << "Incorrect userName ! ";
            break;
        }
    }
    return 0;
}