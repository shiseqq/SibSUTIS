#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#define pb push_back
#define ERROR1 "Cannot start up\n"
#define ERROR2 "Cannot end up\n"
#define ERROR3 "Unknown symbol in string\n"
#define ERROR4 "Has no right staitment to go\n"

typedef long long ll;

using namespace std;

struct MP {
    string fsym, fque, ssym, sque;
    int num ,goTo;
};

struct RES {
    int q,num;
    string str, que, inp;
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
    vector <vector<MP>> v(RAND_MAX);
    string q;
    ifstream fin("C:\\Users\\argon\\Desktop\\TYAP\\lab_6\\gram.txt");
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
        MP tmp;
        int n, i;
        fin >> n >> i;
        tmp.num = n;
        string a, b;
        fin >> a >> b;
        tmp.fsym = a;
        tmp.fque = b;
        fin >> a >> n;
        tmp.goTo = n;
        fin >> a >> b;
        tmp.ssym = a;
        tmp.sque = b;
        v[i].pb(tmp);
    }
    fin.close();
    if (v[StartState].empty()) {
        ui->label->setText(ERROR1);
        return;
    }
    QString text = ui->lineEdit->text();
    string str = text.toStdString();
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
    string input;
    int state = StartState;
    int i = 0;
    vector <RES> ans;
    while (i < str.size() || !(q.empty())) {
        bool f = 0;
        for (auto& j : v[state]) {
            if ((j.fsym[0] == str[i]  || (i==str.size() && j.fsym == "E")) && (j.fque[0] == q[0] || (q.empty() && j.fque=="E"))) {
                RES t;
                t.q = state;
                t.str = str.substr(i, str.size());
                if (t.str.empty()) {
                    t.str = "L";
                }
                t.num = j.num;
                if (q.empty()) {
                    t.que = "Eps";
                }
                else {
                    t.que = q;
                }
                if (input.empty()) {
                    t.inp = "Eps";
                }
                else
                {
                    t.inp = input;
                }
                if (state != j.goTo) {
                    state = j.goTo;
                }
                if (j.ssym == "E") {
                    q.erase(0, 1);
                }
                else {
                    q += j.ssym;
                }
                if (j.sque != "E") {
                    input += j.sque;
                }
                f = 1;
                ans.pb(t);
                break;
            }
        }
        if (i < str.size()) ++i;
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
        graf+=("(q"+to_string(i.q) + ", " + i.str + ", " + i.que + ", " + i.inp + ") -" + to_string(i.num) + "-> ");
    }
    graf+=("(q"+to_string(LastState)+", L, Eps, " + input + ")");
    ui->textEdit->setText(QString::fromStdString(graf));
    ui->label->setText("OK");
//    for (auto& i : ans) {
//        cout << i.num << " " << i.q << " " << i.str << " " << i.que <<" " << i.inp << endl;
//    }
//    cout << input;
}
