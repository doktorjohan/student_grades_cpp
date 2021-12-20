#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
/* parem stiil oleks ehk main lõppu jätta, muidu otsi teist taga
 *
 */

// class for data storage
class student {
    int rollno;
    char name[50];
    int eng_marks, math_marks, sci_marks, lang2_marks, cs_marks;
    double average;
    char grade;

public:
    void getdata();
    void showdata() const;
    void calculate();
    int retrollno() const;
};

void student::calculate()
{
    average = (eng_marks + math_marks + sci_marks + lang2_marks + cs_marks)/5.0;

    if (average >= 90)
        grade = 'A';
    else if (average >= 75)
        grade = 'B';
    else if (average >= 50)
        grade = 'C';
    else
        grade = 'F';
}

void student::getdata()
{
    cout << "\nSisesta matrikli number: "; cin  >> rollno;
    cout << "\nsisesta tudengi nimi: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nKõik hinded peavad olema 100 punkti skaalas";
    cout << "\nInglise keele hinded: "; cin >> eng_marks;
    cout << "\nMatemaatika hinded: "; cin >> math_marks;
    cout << "\nLoodusõpetuse hinded: "; cin >> sci_marks;
    cout << "\nVõõrkeele hinded: "; cin >> lang2_marks;
    cout << "\nInformaatika hinded: "; cin >> cs_marks;
    calculate();
}

void student::showdata() const
{
    cout << "\nTudengi matrikli number: " << rollno;
    cout << "\nTudengi nimi: " << name;
    cout << "\nInglise keel: " << eng_marks;
    cout << "\nMatemaatika: " << math_marks;
    cout << "\nLoodusõpetus: " << sci_marks;
    cout << "\nVõõrkeel: " << lang2_marks;
    cout << "\nInformaatika: " << cs_marks;
    cout << "\nKeskmine hinne: " << average;
    cout << "\nHinne (täht): " << grade;
}

int student::retrollno() const
{
    return rollno;
}

// function declaration
void create_student();
void display_sp(int);  //väljasta kindla tudengi hinded
void display_all();  //väljasta kõigi hinded
void delete_student(int);  //kustuta kindel tudeng
void change_student(int);  //editi kindla tudengi andmeid

//LESGO MAIN
int main() {
    char ch;
    cout << setprecision(2);
    do
    {
        int num;
        system("clear");
        cout << "\n\n\tMENU";
        cout << "\n\t1. Lisa tudeng";
        cout << "\n\t2. Otsi tudengit";
        cout << "\n\t3. Näita kõiki tudengeid";
        cout << "\n\t4. Kustuta tudeng";
        cout << "\n\t5. Muuda tudengi andmeid";
        cout << "\n\t6. Välju\n" << endl;
        cin >> ch;

        // meelega kasutada char type muutujat et switchi proovida
        switch(ch)
        {
            case '1': create_student(); break;
            case '2': cout << "Sisesta matrikli number: "; cin >> num; display_sp(num); break;
            case '3': display_all(); break;
            case '4': cout << "Sisesta atrikli number: "; cin >> num; delete_student(num); break;
            case '5': cout << "Sisesta matrikli number: "; cin >> num; change_student(num); break;
            case '6': cout << "Väljumine..."; exit(0);
            default: cout << "Invalid number";
        }
    }while(ch!='6');
    return 0;
}

// kirjutame tudengid faili nagu mingid koerad
void create_student()
{
    student stud;
    ofstream oFile;
    oFile.open("student.dat", ios::binary|ios::app);
    stud.getdata();
    oFile.write(reinterpret_cast<char *>(&stud), sizeof(student));
    oFile.close();
    cout << "\n\nTudengi andmed faili lisatud!";
    cin.ignore();
    cin.get();
}

//  loe tudengi andmeid nagu facebook
void display_all()
{
    student stud;
    ifstream inFile;
    inFile.open("Student.dat", ios::binary);

    if(!inFile)
    {
        cout << "Faili ei saa avada mine putsi !! prESs Ani kEi Tuu cOntInUe";
        cin.ignore();
        cin.get();
        return;
    }

    cout << "\n\nKÕIGI TUDENGITE ANDMED PAREM OLEKS ET SA NEID KUHUGI EI MÜÜ\n";
    while (inFile.read(reinterpret_cast<char *> (&stud), sizeof(student)))
    {
        stud.showdata();
        cout << "\n===========================\n";
    }
    inFile.close();
    cin.ignore();
    cin.get();
}

// loe kindla tudengi andmeid sa pervo
void display_sp(int n)
{
    student stud;
    ifstream iFile;
    iFile.open("student,.dat", ios::binary);

    if(!iFile)
    {
        cout << "Faili ei saa avada. Tead küll protokolli.";
        cin.ignore();
        cin.get();
        return;
    }

    bool flag = false;
    while(iFile.read(reinterpret_cast<char *> (&stud), sizeof(student)))
    {
        if (stud.retrollno()==n) {
            stud.showdata();
            flag = true;
        }
    }

    iFile.close();
    if (!flag) {
        cout << "\n\ntudengit ei leitud. teda ilmselt poel olemas.";
        cin.ignore();
        cin.get();
    }
}

// muuda kindla tudengi andmeid. parem oleks et sa ei valeta.
void change_student(int n)
{
    bool found = false;
    student stud;
    fstream fl;
    fl.open("student.dat", ios::binary|ios::in|ios::out);
    if(!fl)
    {
        cout << "Faili ei saanud avada. Tead küll protokolli";
        cin.ignore();
        cin.get();
        return;
    }

    while(!fl.eof() && !found)
    {
        fl.read(reinterpret_cast<char *> (&stud), sizeof(student));
        if(stud.retrollno()==n) {
            stud.showdata();
            cout << "Sisesta uued tudengi andmed" << endl;
            stud.getdata();
            int pos=(-1)*static_cast<int>(sizeof(stud));
            fl.seekp(pos, ios::cur);
            fl.write(reinterpret_cast<char *> (&stud), sizeof(student));
            cout << "\n\nTudengi andmed salvestatud";
            found = true;
        }
    }
    fl.close();
    if (!found) {
        cout << "\nTudengit pole ilmselt olemas";
        cin.ignore();
        cin.get();
    }
}

// kustuta kindel tudeng. said eksmatti bitch
void delete_student(int n)
{
    student stud;
    ifstream iFile;
    iFile.open("student.dat", ios::binary);
    if (!iFile)
    {
        cout << "Faili ei saanud avada. Tead küll protokolli.";
        cin.ignore();
        cin.get();
        return;
    }

    ofstream oFile;
    oFile.open("Temp.dat", ios::out);
    iFile.seekg(0, ios::beg);

    while (iFile.read(reinterpret_cast <char *> (&stud), sizeof(student)))
    {
        if (stud.retrollno() != n) {
            oFile.write(reinterpret_cast <char *> (&stud), sizeof(student));
        }
    }
    oFile.close();
    iFile.close();
    remove("student.dat");
    rename("Temp.dat", "student.dat");
    cout << "\n\nTudeng eemaldatud...";
    cin.ignore();
    cin.get();
}
