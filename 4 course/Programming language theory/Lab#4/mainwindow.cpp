#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <sstream>

#define pb push_back
#define ERROR1 "Cannot start up\n"
#define ERROR2 "Cannot end up\n"
#define ERROR3 "Unknown symbol in string\n"
#define ERROR4 "Has no right staitment to go\n"

using namespace std;

struct o {
    string a,b,d;
    int c;
};

struct e {
    string stait,str,st;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
     ui->textEdit->setText(QString::fromStdString(" "));
    vector <vector<o>> v(RAND_MAX);
    stack <char> st;
    ifstream fin("C:\\Users\\argon\\Desktop\\TYAP\\lab_4\\gram.txt");
    int m=0;
    int StartState, LastState;
    fin >> StartState >> LastState;
    vector <char> alphabet;
    char c;
    fin >> c;
    while (c != ';') {
        alphabet.pb(c);
        fin >> c;
    }
    while (!fin.eof()) {
        int i;
        string a, b;
        fin >> i >> a >> b;
        o tmp;
        tmp.a = a;
        tmp.b = b;
        int c;
        fin >> a >> c >> b;
        tmp.c = c;
        tmp.d = b;
        v[i].pb(tmp);
        m++;
    }
    fin.close();
    if (v[StartState].empty()) {
        ui->label->setText(ERROR1);
        return;
    }
    QString text = ui->lineEdit->text();
    string str = text.toStdString();
    vector <e> ans;
    for (int i = 0; i < str.size(); ++i) {
        bool f = 0;
        for (int j = 0; j < alphabet.size(); ++j) {
            if (str[i] == alphabet[j]) {
                f = 1;
                break;
            }
        }
        if (f) continue;
        else {
            ui->label->setText(ERROR3);
            return;
        }
    }
    int state = 0;
    for (int i = 0; i < str.size()+1; ++i) {
        bool f = 0;
        for (auto& j : v[state]) {
            if (((j.a == "L" && i==str.size()) || j.a[0] == str[i]) && ((j.b == "Z" && st.empty()) || j.b[0] == (st.empty()?-999:st.top()))) {
                e t;
                stringstream ss;
                if (i!=str.size()){
                    ss<<state;
                    ss>>t.stait;
                }
                if (state != j.c) {
                    state = j.c;
                }
                if (i==str.size()){
                    ss<<state;
                    ss>>t.stait;
                }
                if (j.d.size() == 2) {
                    st.push(j.d[0]);
                }
                else {
                    if (j.d == "E" && !st.empty())
                        st.pop();
                }
                if(i<str.size())
                    t.str = str.substr(i, str.size());
                else t.str = "L";
                if (st.empty())
                    t.st = "Z";
                else{
                    string s;
                    stack <char> tmp = st;
                    while(!st.empty()){
                        stringstream sss;
                        sss<<st.top();
                        sss>>s;
                        t.st+=s;
                        st.pop();
                    }
                    st = tmp;

                }
                reverse(t.st.begin(),t.st.end());
                ans.pb(t);
                f = 1;
                break;
            }
        }
        if (f) continue;
        else {
            ui->label->setText(ERROR4);
            return;
        }
    }
    if (LastState != state) {
        ui->label->setText(ERROR2);
        return;
    }
    string graf;
    for (auto&i:ans){
      graf+=("(q"+i.stait + ", " + i.str + ", " + i.st+") |- ");
   }
    graf= graf.substr(0, graf.size() - 3);
    ui->textEdit->setText(QString::fromStdString(graf));
    ui->label->setText("OK");
}

