//
//  AgendaService.hpp
//  agenda
//
//  Created by 严旭 on 2020/8/5.
//  Copyright © 2020 严旭. All rights reserved.
//
#ifndef AGENDASERVICE_H
#define AGENDASERVICE_H

#include <list>
#include <string>
#include "Storage.hpp"

class AgendaService {
 public:

  AgendaService();

 
 
  ~AgendaService();

 
  bool userLogIn(const std::string &userName, const std::string &password);

  bool userRegister(const std::string &userName, const std::string &password,
                    const std::string &email, const std::string &phone);


  bool deleteUser(const std::string &userName, const std::string &password);

  std::list<User> listAllUsers(void) const;


  bool createMeeting(const std::string &userName, const std::string &title,
                     const std::string &startDate, const std::string &endDate,
                     const std::vector<std::string> &participator);


  bool addMeetingParticipator(const std::string &userName,
                              const std::string &title,
                              const std::string &participator);

 
  bool removeMeetingParticipator(const std::string &userName,
                                 const std::string &title,
                                 const std::string &participator);

  bool quitMeeting(const std::string &userName, const std::string &title);


  std::list<Meeting> meetingQuery(const std::string &userName,
                                  const std::string &title) const;
 
  std::list<Meeting> meetingQuery(const std::string &userName,
                                  const std::string &startDate,
                                  const std::string &endDate) const;

 
  std::list<Meeting> listAllMeetings(const std::string &userName) const;

  
  std::list<Meeting> listAllSponsorMeetings(const std::string &userName) const;


  std::list<Meeting> listAllParticipateMeetings(
      const std::string &userName) const;

  
  bool deleteMeeting(const std::string &userName, const std::string &title);


  bool deleteAllMeetings(const std::string &userName);


  void startAgenda(void);

  
  void quitAgenda(void);

 private:
  std::shared_ptr<Storage> m_storage;
};
struct err{
    int num;
    std::list<std::string> user;
    err(){
        user.clear();
        num=0;
    }
    err(err &other){
        num=other.num;
        user.clear();
        auto it = other.user.begin();
        for(;it!=other.user.end();it++)
        {
            user.push_back(*it);
        }
    }
};
#endif
