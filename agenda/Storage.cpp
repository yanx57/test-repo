//
//  Storage.cpp
//  agenda
//
//  Created by 严旭 on 2020/8/4.
//  Copyright © 2020 严旭. All rights reserved.
//

#include "Storage.hpp"
#include "Path.hpp"
#include <fstream>
using namespace std;
std::shared_ptr<Storage> Storage::m_instance = nullptr;
Storage::Storage() {
    m_dirty = false;
    readFromFile();
};
bool Storage::readFromFile(void) {
    ifstream fusers(Path::userPath);
    ifstream fmeetings(Path::meetingPath);
    if (!(fusers.is_open() && fmeetings.is_open())){
        return false;
    }
    string str1;
    while (getline(fusers, str1)) {
        string name, password, email, phone;
        if(str1.size() == 0) {
            continue;
        }
        int len=str1.size();
        vector<int>pos;
        for(int i = 0; i < len ; i++){
            if(str1[i] == '"')
            pos.push_back(i);
          }
        for(int i = pos[0]+1 ; i < pos[1] ; i++){
            name.push_back(str1[i]);
        }
           for(int i = pos[2]+1 ; i < pos[3] ; i++){
               password.push_back(str1[i]);
        }
           for(int i = pos[4]+1 ; i < pos[5] ; i++){
               email.push_back(str1[i]);
        }
           for(int i = pos[6]+1 ; i < pos[7] ; i++){
               phone.push_back(str1[i]);
        }
        User u(name, password, email, phone);
        m_userList.push_back(u);
    }
    fusers.close();
    string str2;
    while (getline(fmeetings, str2)) {
        string sponsor, participators, startDate, endDate, title;
        if(str2.size() == 0) {
                continue;
        }
        int len=str2.size();
        vector<int> pos;
        for(int i = 0; i < len ; i++){
            if(str2[i] == '"')
            pos.push_back(i);
          }
              for(int i = pos[0]+1 ; i < pos[1] ; i++){
                sponsor.push_back(str2[i]);
            }
            for(int i = pos[2]+1 ; i < pos[3] ; i++){
                participators.push_back(str2[i]);
            }
            for(int i = pos[4]+1 ; i < pos[5] ; i++){
                startDate.push_back(str2[i]);
            }
            for(int i = pos[6]+1 ; i < pos[7] ; i++){
                endDate.push_back(str2[i]);
            }
            for(int i = pos[8]+1 ; i < pos[9] ; i++){
                title.push_back(str2[i]);
            }
        vector<string> v_participators;
        int len2=participators.size();
        string parti;
        for(int i=0;i<len2;i++){
            if(participators[i]!='&'){
                parti.push_back(participators[i]);
            }
            else{
                string temp=parti;
                v_participators.push_back(temp);
                parti.clear();
            }
        }
        v_participators.push_back(parti);
        Date start(startDate);
        Date end(endDate);
        Meeting meeting(sponsor, v_participators, start, end, title);
        m_meetingList.push_back(meeting);
    }
    fmeetings.close();
    return true;
};
bool Storage::writeToFile(void) {
    ofstream fusers(Path::userPath);
    ofstream fmeetings(Path::meetingPath);
    if (!(fusers.is_open() && fmeetings.is_open())){
        return false;
    }
    for (auto it = m_userList.begin();it != m_userList.end();it++) {
        fusers<<'"'<<(*it).getName()<<'"'<<','<<'"'<<(*it).getPassword()<<'"'<<','<<'"'<<(*it).getEmail()<<'"'<<','<<'"'<<(*it).getPhone()<<'"';
        fusers<<"\n";
    }
    fusers.close();
       for(auto it = m_meetingList.begin();it != m_meetingList.end();it++)  {
       fmeetings<<'"'<<(*it).getSponsor()<<'"'<<','<<'"';
       vector<string> tmp = (*it).getParticipator();
       int len = tmp.size();
       for(int i = 0 ; i < len-1 ; i++){
             fmeetings<<tmp[i]<<'&';
       }
       fmeetings<<tmp[len-1];
       fmeetings<<'"'<<','<<'"'<<(*it).getStartDate().dateToString((*it).getStartDate())<<'"'<<','<<'"'<<(*it).getEndDate().dateToString((*it).getEndDate())<<'"'<<','<<'"'<<(*it).getTitle()<<'"';
         fmeetings<<"\n";
     }
    fmeetings.close();
    return true;
};
std::shared_ptr<Storage> Storage::getInstance(void) {
    if (m_instance == nullptr) {
        m_instance = shared_ptr<Storage>(new Storage());
    }
    return m_instance;
};
Storage::~Storage() {
    sync();
};
void Storage::createUser(const User &t_user) {
    m_userList.push_back(t_user);
    m_dirty = true;
};
std::list<User> Storage::queryUser(std::function<bool(const User &)> filter) const {
    std::list<User> result;
    for (auto it = m_userList.begin();it != m_userList.end();it++) {
        if (filter(*it)){
            result.push_back(*it);
        }
    }
    return result;
};
int Storage::updateUser(std::function<bool(const User &)> filter,
             std::function<void(User &)> switcher) {
    int num = 0;
    for (auto it = m_userList.begin();it != m_userList.end();it++) {
        if (filter(*it)) {
            switcher(*it);
            num++;
        }
    }
    if(num > 0){
        m_dirty = true;
    }
    return num;
};
int Storage::deleteUser(std::function<bool(const User &)> filter) {
    int num = 0;
    for (auto it = m_userList.begin();it != m_userList.end();) {
        if (filter(*it)) {
            it = m_userList.erase(it);
            num++;
        }
        else{
            it++;
        }
    }
    if (num > 0){
        m_dirty = true;
    }
    return num;
};
void Storage::createMeeting(const Meeting &t_meeting) {
    m_meetingList.push_back(t_meeting);
    m_dirty = true;
};
std::list<Meeting> Storage::queryMeeting(
  std::function<bool(const Meeting &)> filter) const {
    list<Meeting> meeting;
    for (auto it = m_meetingList.begin();it != m_meetingList.end();it++) {
        if (filter(*it))
            meeting.push_back(*it);
    }
    return meeting;
};
int Storage::updateMeeting(std::function<bool(const Meeting &)> filter,
                std::function<void(Meeting &)> switcher) {
    int num = 0;
    for (auto it = m_meetingList.begin();it != m_meetingList.end();it++) {
        if (filter(*it)) {
            switcher(*it);
            num++;
        }
    }
    if (num > 0){
        m_dirty = true;
    }
    return num;
};
int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter) {
    int num = 0;
    for (auto it = m_meetingList.begin();it != m_meetingList.end();) {
        if (filter(*it)) {
            it = m_meetingList.erase(it);
            num++;
        }
        else
            it++;
    }
    if (num > 0){
        m_dirty = true;
    }
    return num;
};
bool Storage::sync(void) {
    m_dirty = false;
    return writeToFile();
};

