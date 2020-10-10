//
//  Meeting.hpp
//  agenda
//
//  Created by 严旭 on 2020/8/4.
//  Copyright © 2020 严旭. All rights reserved.
//
#ifndef MEETING_H
#define MEETING_H

#include <vector>
#include "Date.hpp"
#include<iostream>
class Meeting {
 public:

  Meeting() = default;


  Meeting(const std::string &t_sponsor,const std::vector<std::string> &t_participator,const Date &t_startTime, const Date &t_endTime,const std::string &t_title);

  Meeting(const Meeting &t_meeting);


  std::string getSponsor(void) const;

 
  void setSponsor(const std::string &t_sponsor);

 
  std::vector<std::string> getParticipator(void) const;

  
  void setParticipator(const std::vector<std::string> &t_participators);


  void addParticipator(const std::string &t_participator);


  void removeParticipator(const std::string &t_participator);


  Date getStartDate(void) const;

  
  void setStartDate(const Date &t_startTime);

 
  Date getEndDate(void) const;


  void setEndDate(const Date &t_endTime);


  std::string getTitle(void) const;

 
  void setTitle(const std::string &t_title);


  bool isParticipator(const std::string &t_username) const;

 private:
  std::string m_sponsor;
  std::vector<std::string> m_participators;
  Date m_startDate;
  Date m_endDate;
  std::string m_title;
};

#endif
