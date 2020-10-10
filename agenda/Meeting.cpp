//
//  Meeting.cpp
//  agenda
//
//  Created by 严旭 on 2020/8/4.
//  Copyright © 2020 严旭. All rights reserved.
//

#include "Meeting.hpp"
#include <vector>
#include "Date.hpp"
#include<iostream>
using namespace std;

  Meeting::Meeting(const std::string &t_sponsor,const std::vector<std::string> &t_participator,const Date &t_startTime, const Date &t_endTime,const std::string &t_title)
{
     m_sponsor=t_sponsor;
     m_title=t_title;
     m_startDate=t_startTime;
     m_endDate=t_endTime;
     for(int cnt=0; cnt< t_participator.size();cnt++)
         m_participators.push_back(t_participator[cnt]);
 }


    Meeting:: Meeting(const Meeting &t_meeting){
       m_sponsor=t_meeting.getSponsor();
       m_title=t_meeting.getTitle();
       m_startDate=t_meeting.getStartDate();
       m_endDate=t_meeting.getEndDate();
       for(int cnt=0;cnt < t_meeting.getParticipator().size(); cnt++)
           m_participators.push_back(t_meeting.getParticipator()[cnt]);
   }


   std::string  Meeting::getSponsor(void) const{
       return m_sponsor;
   }


   void  Meeting::setSponsor(const std::string &t_sponsor){
       m_sponsor=t_sponsor;
   }


   std::vector<std::string> Meeting::getParticipator(void) const{
       return m_participators;
   }

 
   void Meeting::setParticipator(const std::vector<std::string> &t_participators)
{
       m_participators.clear();
       for(int cnt=0; cnt < t_participators.size(); cnt++)
           m_participators.push_back(t_participators[cnt]);
   }


   void  Meeting::addParticipator(const std::string &t_participator){
       m_participators.push_back(t_participator);
   }


   void  Meeting::removeParticipator(const std::string &t_participator){
       vector<string>::iterator p,q;
       for(p=m_participators.begin(); p!=m_participators.end(); )
           if(*p == t_participator){
               q=p;
               p=m_participators.erase(q);
           }
           else p++;
   }


   Date  Meeting::getStartDate(void) const{
       return m_startDate;
   }


   void  Meeting::setStartDate(const Date &t_startTime){
       m_startDate=t_startTime;
   }


   Date  Meeting::getEndDate(void) const{
       return m_endDate;
   }


   void  Meeting::setEndDate(const Date &t_endTime){
       m_endDate=t_endTime;
   }


   std::string Meeting:: getTitle(void) const{
       return m_title;
   }


   void  Meeting::setTitle(const std::string &t_title){
       m_title=t_title;
   }


   bool  Meeting::isParticipator(const std::string &t_username) const{
       for(int cnt=0; cnt<m_participators.size(); cnt++)
           if(m_participators[cnt] == t_username) return true;
       return false;
   }
