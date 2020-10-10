//
//  AgendaUI.cpp
//  agenda
//
//  Created by 严旭 on 2020/8/30.
//  Copyright © 2020 严旭. All rights reserved.
//
#include <iomanip>
#include "AgendaUI.hpp"
#include"AgendaService.hpp"
using namespace std;
void AgendaUI:: printMeetings(const list<Meeting> & m_list)
{
    cout<<endl;
    if(m_list.size()==0)
    {cout<<"there is no meeting\n";return;}
    cout<<fixed<<left;
    cout<<setw(30)<<"title"<<setw(30)<<"sponsor"<<setw(30)<<"start time"<<setw(30)<<"end time"<<"participators\n";
    for(auto iter=m_list.begin();iter!=m_list.end();iter++)
    {
        cout<<setw(30)<<iter->getTitle()<<setw(30)<<iter->getSponsor()<<setw(30)<<Date:: dateToString(iter->getStartDate())<<setw(30)<<Date:: dateToString(iter->getEndDate());
        auto m_ulist=iter->getParticipator();
        auto it=m_ulist.begin();
        cout<<*it;
        for(it++;it!=m_ulist.end();it++)
        {
            cout<<","<<*it;
        }
        cout<<endl;
    }
}

AgendaUI:: AgendaUI(){
    m_userName="";
    m_userPassword="";
    startAgenda();
}

void AgendaUI:: startAgenda(){
    for(int i=0;i<37;i++)cout<<"_ ";
    cout<<"Agenda ";
    for(int i=0;i<37;i++)cout<<"_ ";
    cout<<endl;
    cout<<"Action :\n";
    cout<<"l    - log in Agenda by user name and password\n";
    cout<<"r    - register an Agenda account\n";
    cout<<"q    - quit Agenda\n";
    for(int i=0;i<79;i++)cout<<"_ ";
    cout<<endl<<endl;
    cout<<"Agenda :~$ ";
    string &&cmd=getOperation();
    while(!executeOperation(cmd))
    {
        cout<<"Agenda : ERROR! "<<cmd<<" is not a right command,please type in again\n";
        cout<<"Agenda :~$ ";
        cmd=getOperation();
    }
}

std::string AgendaUI:: getOperation(){
    string cmd;
    cin>>cmd;
    return cmd;
}

bool AgendaUI:: executeOperation(const std::string &t_operation){
    if(m_userName==""){
    if(t_operation=="l"){
        if(this->userLogIn()){
            this->OperationLoop();
        }
        else{
            startAgenda();
        }
    }
    else if(t_operation=="r"){
        if(this->userRegister()){
            this->OperationLoop();
        }
        else{
            startAgenda();
        }
        
    }
        else if(t_operation=="q") this->quitAgenda();
        else
            return false;
    }
    else if(m_userName!="")
    {
        if(t_operation=="o")userLogOut();
        else if(t_operation=="dc")deleteUser();
        else if(t_operation=="lu"){listAllUsers();getchar();getchar();}
        else if(t_operation=="cm")createMeeting();
        else if(t_operation=="amp")addMeetingParticipator();
        else if(t_operation=="rmp")removeMeetingParticipator();
        else if(t_operation=="rqm")quitMeeting();
        else if(t_operation=="la"){listAllMeetings();getchar();getchar();}
        else if(t_operation=="las"){listAllSponsorMeetings();getchar();getchar();}
        else if(t_operation=="lap"){listAllParticipateMeetings();getchar();getchar();}
        else if(t_operation=="qm"){queryMeetingByTitle();getchar();getchar();}
        else if(t_operation=="qt"){queryMeetingByTimeInterval();getchar();getchar();}
        else if(t_operation=="dm")deleteMeetingByTitle();
        else if(t_operation=="da")deleteAllMeetings();
        else if(t_operation=="\n"){
            executeOperation(getOperation());
        }
        else
            return false;
    }
    else
        return false;
    return true;
}

bool AgendaUI:: userLogIn(){
    string username,password;
    cout<<"[log in] [username] [password]\n";
    cout<<"[log in] ";
    cin>>username>>password;
    if(m_agendaService.userLogIn(username, password)){
        cout<<"[log in] succeed!\n";
        m_userName=username;
        m_userPassword=password;
        cout<<endl;
        return true;
    }
    else
    {
        cout<<"[log in] Password error or user doesn't exist";
        cout<<endl;
        return false;
    }
}

void AgendaUI:: quitAgenda(){
    cout<<"Have a nice day!\n";
    m_userPassword="";
    m_userName="";
    m_agendaService.quitAgenda();
}

bool AgendaUI:: userRegister(){
    cout<<endl;
    cout<<"[register] [username] [password] [email] [phone]\n[register] ";
    string username,password,email,phone;
    cin>>username>>password>>email>>phone;
    if(m_agendaService.userRegister(username,password,email,phone))
    {
        cout<<"[register] succeed!"<<endl<<endl;
        m_userName=username;
        m_userPassword=password;
    }
    else
    {
        cout<<"[register] This username has been register!\n";
        return false;
    }
    return true;
}

void AgendaUI:: OperationLoop(){
    string cmd;
    while (m_userName!=""){
        for(int i=0;i<37;i++)cout<<"_ ";
        cout<<"Agenda ";
        for(int i=0;i<37;i++)cout<<"_ ";
        cout<<endl;
        cout<<"Action :\n";
        cout<<"o    - log out Agenda\n";
        cout<<"dc   - delete Agenda account\n";
        cout<<"lu   - list all Agenda user\n";
        cout<<"cm   - create a meeting\n";
        cout<<"amp  - add meeting participator\n";
        cout<<"rmp  - remove meeting participator\n";
        cout<<"rqm  - request to quit meeting\n";
        cout<<"la   - list all meetings\n";
        cout<<"las  - list all sponsor meetings\n";
        cout<<"lap  - list all participator meetings\n";
        cout<<"qm   - query meeting by title\n";
        cout<<"qt   - qurey meeting by time interval\n";
        cout<<"dm   - delete meeting by title\n";
        cout<<"da   - delete all meeting\n";
        for(int i=0;i<79;i++)cout<<"_ ";
        cout<<endl<<endl;
        cout<<"Agenda@"<<m_userName<<" :~# ";
        cmd=getOperation();
        while(!this->executeOperation(cmd)){
            cout<<"Agenda@"<<m_userName<<" : ERROR! "<<cmd<<"is not a right command\n";
            cout<<"Agenda@"<<m_userName<<" :~# ";
            cmd=getOperation();
        }
    }
    this->startAgenda();
}

void AgendaUI:: userLogOut(){
    m_userName="";
    m_userPassword="";
    cout<<endl<<endl;
}

void AgendaUI:: deleteUser(){
    cout<<endl;
    if(m_agendaService.deleteUser(m_userName, m_userPassword))
    {
        cout<<"[delete agenda account] succeed!";
        m_userName="";
        m_userPassword="";
    }
    else
        cout<<"[delete agenda account] ERROR!";
    cout<<endl;
}

void AgendaUI:: listAllUsers(){
    list<User> m_list=m_agendaService.listAllUsers();
    cout<<endl<<"[list all users]\n"<<endl;
    for(auto iter=m_list.begin();iter!=m_list.end();iter++)
    {
        cout<<iter->getName()<<"\t"<<iter->getEmail()<<"\t"<<iter->getPhone()<<"\t\n";
    }
}

void AgendaUI:: createMeeting(){
    int numpar;
    string title,startdate,enddate;
    vector<string> m_list;
    cout<<endl;
    cout<<"[create meeting] [the number of participators]"<<endl;
    cout<<"[create meeting] ";
    cin>>numpar;
    for(int i=1;i<=numpar;i++){
        cout<<"[create meeting] [please enter the participator "<<i<<" ]\n";
        string *p=new string;
        cout<<"[create meeting] ";
        cin>>*p;
        m_list.push_back(*p);
    }
    cout<<"[create meeting] [title][start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]\n";
    cout<<"[create meeting] ";
    cin>>title>>startdate>>enddate;
    bool flag;
    try{flag=m_agendaService.createMeeting(m_userName, title, startdate, enddate, m_list);}
    catch(err x){
        if(x.num==1){
                cout<<"[create meeting] "<<"\""<<title<<"\" has been used,please try another meeting title(if you do not want to creat this meeting please type in 0)\n";
                cout<<"[create meeting] ";
                cin>>title;
                if(title!="0")
                {
                    try{flag=m_agendaService.createMeeting(m_userName, title, startdate, enddate, m_list);}
                    catch(...){cout<<"[create meeting] still have invalid items\n";}
                }
        }
        else if(x.num==2)
        {
            cout<<"[create meeting] "<<"your date is invalid,please type in your start time and end time again(if you do not want to creat this meeting please type in 0)\n";
            cout<<"[create meeting] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]\n";
            cout<<"[create meeting] ";
            cin>>startdate;
            if(startdate!="0")
            {
                cin>>enddate;
                try{flag=m_agendaService.createMeeting(m_userName, title, startdate, enddate, m_list);}
                catch(...){cout<<"[create meeting] still have invalid items\n";}
            }
        }
        else if(x.num==3)
        {
            cout<<"[create meeting] "<<"\"";
            auto iter=x.user.begin();
            cout<<*iter;
            for(iter++;iter!=x.user.end();iter++)
            {
                cout<<*iter<<"&";
            }
            cout<<"\" ";
            if(x.user.size()>1)cout<<"have not registered. Please try again after he/she registered account";
            else cout<<"has not registed. Please try again after they registered accounts.\n";
        }
        else if(x.num==4)
        {
            cout<<"[create meeting] you are not available at that time.\n";
            cout<<"[create meeting] this is your meeting list.Please choose a free time after check it out.(if you do not want to creat this meeting please type in 0)\n";
            listAllMeetings();
            cout<<"[create meeting] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]\n";
            cout<<"[create meeting] ";
            cin>>startdate;
            if(startdate!="0")
            {
                cin>>enddate;
                try{flag=m_agendaService.createMeeting(m_userName, title, startdate, enddate, m_list);}
                catch(...){cout<<"[create meeting] still have invalid items\n";}
            }
        }
        else if(x.num==5)
        {
            cout<<"[create meeting] "<<"\"";
            auto iter=x.user.begin();
            cout<<*iter;
            for(iter++;iter!=x.user.end();iter++)
            {
                cout<<"&"<<*iter;
            }
            cout<<"\" ";
            if(x.user.size()>1)cout<<"are not available. \n";
            else cout<<"is not available.\n";
        }
    }
    if(flag)
        cout<<"[create meeting] succeed!\n";
    else
        cout<<"[create meeting] error!\n";
}

void AgendaUI:: addMeetingParticipator(){
    string title,participator;
    cout<<endl;
    cout<<"[add participator] [meeting title] [participator username]\n";
    cout<<"[add participator] ";
    cin>>title>>participator;
    if(m_agendaService.addMeetingParticipator(m_userName, title, participator))
        cout<<"[add participator] succeed!\n";
    else
        cout<<"[add participator] error!\n";
}

void AgendaUI:: removeMeetingParticipator(){
    string title,participator;
    cout<<endl;
    cout<<"[remove participator] [meeting title] [participator username]\n";
    cout<<"[remove participator] ";
    cin>>title>>participator;
    if(m_agendaService.removeMeetingParticipator(m_userName, title, participator))
        cout<<"[remove participator] succeed!\n";
    else
        cout<<"[remove participator] error!\n";
}

void AgendaUI:: quitMeeting(){
    string title;
    cout<<endl;
    cout<<"[quit meeting] [meeting title]\n";
    cout<<"[quit meeting] ";
    cin>>title;
    if(m_agendaService.quitMeeting(m_userName, title))
        cout<<"[quit meeting] succeed!\n";
    else
        cout<<"[quit meeting] error!\n";
}

void AgendaUI:: listAllMeetings(){
    list<Meeting> m_list;
    cout<<endl;
    cout<<"[list all meeting]\n";
    m_list=m_agendaService.listAllMeetings(m_userName);
    printMeetings(m_list);
}

void AgendaUI:: listAllSponsorMeetings(){
   list<Meeting> m_list;
    cout<<endl;
    cout<<"[list all sponsor meeting]\n";
    m_list=m_agendaService.listAllSponsorMeetings(m_userName);
    printMeetings(m_list);
}

void AgendaUI:: listAllParticipateMeetings(){
   list<Meeting> m_list;
    cout<<endl;
    cout<<"[list all participator meeting]\n";
    m_list=m_agendaService.listAllParticipateMeetings(m_userName);
    printMeetings(m_list);
}

void AgendaUI:: queryMeetingByTitle(){
    cout<<endl;
    string title;
    cout<<"[query meeting] [title]\n";
    cout<<"[query meeting] ";
    cin>>title;
    list<Meeting> m_list;
    m_list=m_agendaService.meetingQuery(m_userName, title);
    printMeetings(m_list);
}

void AgendaUI:: queryMeetingByTimeInterval(){
    cout<<endl;
    string startdate,enddate;
    list<Meeting> m_list;
    cout<<"[query meetings] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]\n";
    cout<<"[query meetings] ";
    cin>>startdate>>enddate;
    m_list=m_agendaService.meetingQuery(m_userName, startdate, enddate);
    cout<<"[query meetings]\n";
    printMeetings(m_list);
}

void AgendaUI:: deleteMeetingByTitle(){
    cout<<endl;
    string title;
    cout<<"[delete meeting] [title]\n";
    cout<<"[delete meeting] ";
    cin>>title;
    if(m_agendaService.deleteMeeting(m_userName, title))
        cout<<"[delete meeting] succeed!\n";
    else
        cout<<"[error] delete meeting fail\n";
}

void AgendaUI:: deleteAllMeetings(){
    cout<<endl;
    m_agendaService.deleteAllMeetings(m_userName);
    cout<<"[delete all meeting] succeed!\n";
}
