//
//  AgendaService.cpp
//  agenda
//
//  Created by 严旭 on 2020/8/5.
//  Copyright © 2020 严旭. All rights reserved.
//

#include<iostream>
#include<string>
#include<list>
#include<algorithm>
#include<vector>
#include"User.hpp"
#include"Date.hpp"
#include"Meeting.hpp"
#include"Storage.hpp"
#include"AgendaService.hpp"
using namespace std;
AgendaService::AgendaService(){
    startAgenda();
}

AgendaService::~AgendaService(){
    quitAgenda();
}

bool AgendaService::userLogIn(const std::string &userName, const std::string &password){
    auto filter=[userName, password](const User &user) {
        if(userName==user.getName() && password==user.getPassword()){
            return true;
        }
        else{
            return false;
        }
    };
    list<User>temp=m_storage->queryUser(filter);
    int size=temp.size();
    if(size>0){
        return true;
    }
    else{
        return false;
    }
}

bool AgendaService::userRegister(const std::string &userName, const std::string &password,const std::string &email, const std::string &phone){
    User U(userName, password, email, phone);
    auto filter=[userName](const User &user) {
       if(user.getName()==userName){
               return true;
       }
       else{
           return false;
       }
    };
    list<User> tmp=m_storage->queryUser(filter);
    if(tmp.empty()){
        m_storage->createUser(U);
        return true;
    }
    else{
        return false;
    }
}

bool AgendaService::deleteUser(const std::string &userName, const std::string &password){
    auto filter=[userName, password](const User &user) {
        if(userName==user.getName()&&password==user.getPassword()){
            return true;
        }
        else{
            return false;
        }
    };
    deleteAllMeetings(userName);
     auto parlist=listAllParticipateMeetings(userName);
     for(auto it=parlist.begin();it!=parlist.end();it++){
         quitMeeting(userName, it->getTitle());
     }
    int num=m_storage->deleteUser(filter);
       if(num>0){
           return true;
    }
    else{
        return false;
    }
}
std::list<User> AgendaService::listAllUsers(void) const{
    auto filter=[](const User &user) {return true;};
    list<User>temp=m_storage->queryUser(filter);
    return temp;
}

bool AgendaService::createMeeting(const std::string &userName, const std::string &title,const std::string &startDate, const std::string &endDate,const std::vector<std::string> &participator){
    err er;
    Date start(startDate);
    Date end(endDate);
    Meeting meeting(userName,participator,start,end,title);
    if(participator.empty()){
        
        return false;
    }
    try{if(start.isValid(start)==false||end.isValid(end)==false||start>=end){
        er.num=1;
        throw er;
        return false;
    }}
    catch(err x){
        throw ;
    }
    bool have=false;
    list<User>temp=listAllUsers();
    for(auto it=temp.begin();it!=temp.end();it++){
        if(userName==it->getName()){
            have=true;
            break;
        }
    }
    try{if(have==false){
        er.num=2;
        throw er;
        return false;
    }}
    catch(err x)
    {
        throw ;
    }
    try{if (participator.empty()){
        er.num=4;
        throw er;
        return false;
    }
    }
    catch(err x)
    {
        throw ;
    }
    auto filter=[title](const Meeting &meeting) {
        if(meeting.getTitle()==title){
            return true;
        }
        else{
            return false;
        }
    };
    list<Meeting>tmp1=m_storage->queryMeeting(filter);
    try{if(tmp1.empty()==false){
        er.num=5;
        throw er;
        return false;
    }}
    catch(err x){
        throw ;
    }
    auto filter1=[userName](const Meeting &meeting) {
        if(userName==meeting.getSponsor()){
            return true;
        }
        else{
            return false;
        }
    };
    bool flag=0;
    list<Meeting>m=listAllMeetings(userName);
    for(auto it=m.begin();it!=m.end();it++){
        if(!((*it).getEndDate()<=start || (*it).getStartDate()>= end)){
            flag=1;;
            break;
        }
        
    }
    try{
        if(flag==1)
        {
            er.num=3;
            throw er;
            return false;
        }
    }
    catch(err x){
        throw;
    }
    vector<string>tmp;
    Meeting meet(userName,tmp,start,end,title);
    m_storage->createMeeting(meet);
    for (auto it=participator.begin();it!=participator.end();it++){
        bool ff;
        ff=addMeetingParticipator(userName, title, *it);
        if(ff==true){
            tmp.push_back(*it);
        }
        else{
            m_storage->deleteMeeting(filter);
            return false;
        }
    }
    return true;
}

bool AgendaService::addMeetingParticipator(const std::string &userName,const std::string &title,const std::string &participator){
    auto filter = [participator](const User& user) {
        if(user.getName()==participator){
           return true;
        }
        return false;
    };
    std::list<User>U=m_storage->queryUser(filter);
    if(U.size()!=1){
           return false;
    }
    auto filter1=[&](const Meeting & meeting){
        if(meeting.getSponsor()==userName&&meeting.getTitle()==title){
            std::list<Meeting>tmpp=m_storage->queryMeeting( [&](const Meeting&meeting1){
            if(meeting1.getSponsor()==participator||meeting1.isParticipator(participator)){
                if(meeting.getStartDate()>=meeting1.getEndDate()||meeting.getEndDate()<=meeting1.getStartDate()){
                       return false;
                   }
                   else{
                       return true;
                }
                }
              return false;
            });
            if(tmpp.empty()){
               return true;
               }
               return false;
        }
        return false;
    };
    auto switcher=[participator](Meeting &meeting) {
        meeting.addParticipator(participator);
    };
    int num=m_storage->updateMeeting(filter1, switcher);
    if(num>0){
         return true;
    }
    else{
         return false;
    }
}
bool AgendaService::removeMeetingParticipator(const std::string &userName,const std::string &title,const std::string &participator){
     if(userName==participator){
        return false;
    }
    auto filter=[userName](const User &u){
        if(u.getName()==userName){
            return true;
        }
        else{
            return false;
        }
    };
    auto filter1=[participator](const User &u){
        if(u.getName()==participator){
            return true;
        }
        else{
            return false;
        }
    };
    list<User>u1=m_storage->queryUser(filter);
    list<User>u2=m_storage->queryUser(filter1);
    if(u1.empty()||u2.empty()){
        return false;
    }
    auto filter2 = [userName, title](const Meeting &meeting) {
        if (meeting.getSponsor()==userName&&meeting.getTitle()==title){
            return true;
        }
        else{
            return false;
        }
    };
    list<Meeting>l=m_storage->queryMeeting(filter2);
    if(l.size()!=1){
        return false;
    }
    Meeting m=*(l.begin());
    if(!m.isParticipator(participator)){
        return false;
    }
    auto switcher=[participator](Meeting &meeting) {
        meeting.removeParticipator(participator);
    };
    
    int num=m_storage->updateMeeting(filter2, switcher);
    m_storage->deleteMeeting([](const Meeting &meeting){
        return meeting.getParticipator().empty();
    });
    if(num>0){
           return true;
    }
    else{
           return false;
    }
}
bool AgendaService::quitMeeting(const std::string &userName, const std::string &title){
    auto filter=[userName, title](const Meeting &meeting){
         if(meeting.isParticipator(userName)&&meeting.getTitle()==title){
             return true;
         }
         else{
             return false;
         }
    };
    auto switcher=[userName](Meeting &meeting) {
        meeting.removeParticipator(userName);
    };
    int num=m_storage->updateMeeting(filter, switcher);
    auto filter1=[](const Meeting &meeting) {
        if(meeting.getParticipator().empty()){
            return true;
        }
        else{
            return false;
        }
    };
    m_storage->deleteMeeting(filter1);
    if(num>0){
        return true;
    }
    else{
        return false;
    }
}
std::list<Meeting> AgendaService::meetingQuery(const std::string &userName,const std::string &title) const{
    list<Meeting>tmp;
    list<User>U=m_storage->queryUser([userName](const User&u){
        if(u.getName()==userName){
            return true;
        }
        else{
            return false;
        }
    });
    if(U.empty()){
        return tmp;
    }
    auto filter=[userName, title](const Meeting &meeting){
        if((userName==meeting.getSponsor()||meeting.isParticipator(userName))&&title==meeting.getTitle()){
            return true;
        }
        else{
            return false;
        }
    };
    list<Meeting>temp=m_storage->queryMeeting(filter);
    return temp;
}
std::list<Meeting> AgendaService::meetingQuery(const std::string &userName,const std::string &startDate,const std::string &endDate) const{
    Date start(startDate);
    Date end(endDate);
    list<Meeting> temp;
    list<Meeting>l;
    if(start.isValid(start)==false||end.isValid(end)==false||start>end){
        return temp;
    }
    list<User>U=m_storage->queryUser([userName](const User&u){
        if(u.getName()==userName){
            return true;
        }
        else{
            return false;
        }
    });
    if(U.empty()){
        return l;
    }
    auto filter=[userName, start, end](const Meeting &meeting){
        if((meeting.getSponsor()==userName||meeting.isParticipator(userName))&&meeting.getEndDate()>=start&&meeting.getStartDate()<=end){
            return true;
        }
         else{
             return false;
         }
    };
    temp=m_storage->queryMeeting(filter);
    return temp;
}

std::list<Meeting> AgendaService::listAllMeetings(const std::string &userName) const{
    auto filter = [userName](const Meeting &meeting) {
        if(userName==meeting.getSponsor()||meeting.isParticipator(userName)){
            return true;
        }
        else{
            return false;
        }
    };
    list<Meeting>temp=m_storage->queryMeeting(filter);
    return temp;
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(const std::string &userName) const{
     auto filter=[userName](const Meeting &meeting) {
             if(userName==meeting.getSponsor()){
                 return true;
            }
            else{
                 return false;
            }
    };
    list<Meeting>temp=m_storage->queryMeeting(filter);
    return temp;
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(const std::string &userName) const{
    auto filter=[userName](const Meeting &meeting){
        if(meeting.isParticipator(userName)){
            return true;
        }
        else{
            return false;
        }
    };
    list<Meeting>temp=m_storage->queryMeeting(filter);
    return temp;
}

bool AgendaService::deleteMeeting(const std::string &userName, const std::string &title){
    auto filter=[userName, title](const Meeting &meeting) {
       if(userName==meeting.getSponsor()&&title==meeting.getTitle()){
               return true;
           }
           else{
               return false;
        }
    };
    int num=m_storage->deleteMeeting(filter);
    if(num>0){
        return true;
    }
    else{
        return false;
    }
}

bool AgendaService::deleteAllMeetings(const std::string &userName){
    auto filter=[userName](const Meeting &meeting) {
        if(userName==meeting.getSponsor()){
            return true;
        }
        else{
            return false;
        }
    };
    int num=m_storage->deleteMeeting(filter);
    if(num>0){
        return true;
    }
    else{
        return false;
    }
}

void AgendaService::startAgenda(void){
    m_storage=Storage::getInstance();
}

void AgendaService::quitAgenda(void){
    m_storage->sync();
}


