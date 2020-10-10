//
//  Date.cpp
//  agenda
//
//  Created by 严旭 on 2020/8/3.
//  Copyright © 2020 严旭. All rights reserved.
//

#include "Date.hpp"
#include <string>
#include <iostream>
#include<cstring>
#include<sstream>
using namespace std;
 Date::Date(){m_year=m_month=m_day=m_hour=m_minute=0; }
   Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute){
       m_year=t_year;
       m_month=t_month;
       m_day=t_day;
       m_hour=t_hour;
       m_minute=t_minute;
   }
   Date::Date(const std::string &dateString){
      Date tmp=stringToDate(dateString);
       m_year=tmp.getYear();
       m_month=tmp.getMonth();
       m_day=tmp.getDay();
       m_hour=tmp.getHour();
       m_minute=tmp.getMinute();
   }

   int Date::getYear(void) const{return m_year;}


   void Date::setYear(const int t_year){m_year=t_year;}


   int Date::getMonth(void) const{return m_month;}


   void Date::setMonth(const int t_month){m_month=t_month;}


   int Date::getDay(void) const{return m_day;}


   void Date::setDay(const int t_day){m_day=t_day;}


   int Date::getHour(void) const{return m_hour;}


   void Date::setHour(const int t_hour){m_hour=t_hour;}


   int Date::getMinute(void) const{return m_minute;}

   void Date::setMinute(const int t_minute){m_minute=t_minute;}
 bool isleapyear(int year){
         if(year%400==0||(year%4==0&&year%100!=0)) return true;
         return false;
     }
 bool Date::isValid(const Date &a){
     if(a.getYear()<1000||a.getYear()>9999) return false;
     if(a.getMonth()<1||a.getMonth()>12) return false;
     int day1[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
     int day2[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};
     if(isleapyear(a.getYear()))
     {
         if(a.getDay()<1||a.getDay()>day2[a.getMonth()]) return false;
     }
     if(!isleapyear(a.getYear()))
     {
         if(a.getDay()<1||a.getDay()>day1[a.getMonth()]) return false;
     }
     if(a.getHour()<0||a.getHour()>23) return false;
     if(a.getMinute()<0||a.getMinute()>59) return false;
     return true;
 }
 bool valid_str(const std::string& str)
   {
     int len = (int)str.length();
      if(len != 16)
       return false;
     if(str[4] != '-')
       return false;
     if(str[7] != '-')
       return false;
     if(str[10] != '/')
       return false;
       if(str[13] != ':')
         return false;
       for(int index = 0 ; index < 4 ; index++)
        {
          if(str[index] < '0' || str[index] > '9')
          return false;
        }
       for(int index = 5 ; index < 7 ; index++)
       {
         if(str[index] < '0' || str[index] > '9')
         return false;
       }
       for(int index = 8 ; index < 10 ; index++)
       {
         if(str[index] < '0' || str[index] > '9')
         return false;
       }
       for(int index = 11 ; index < 13 ; index++)
        {
          if(str[index] < '0' || str[index] > '9')
          return false;
        }
       for(int index = 14 ; index < 16 ; index++)
       {
         if(str[index] < '0' || str[index] > '9')
         return false;
       }
       return true;
   }
 Date Date::stringToDate(const std::string &s)
   {
     if(!valid_str(s))
           return Date(0,0,0,0,0);
       int y,m,d,h,minu;
       char tmp;
       stringstream ss;
       ss << s;
       ss >> y >> tmp >> m >> tmp >> d >> tmp >> h >>tmp >> minu;
      return Date(y,m,d,h,minu);
      
   }
 string AddZero(int n)
   {
       stringstream s;
       if(n<10) s << "0" << n;
       else s << n;
       return s.str();
   }
 std::string Date::dateToString(const Date &a){
     stringstream s;
     if(!isValid(a)){
         s << "0000-00-00/00:00";
         return s.str();
     }
     
     s<<a.getYear();
     s  << "-" << AddZero(a.getMonth()) << "-" <<  AddZero(a.getDay()) << "/" << AddZero(a.getHour())  << ":" << AddZero(a.getMinute());
     return s.str();
 }

   Date &Date::operator = (const Date& other)
   {
       int y=other.getYear();
       int m=other.getMonth();
       int d=other.getDay();
       int h=other.getHour();
       int minu=other.getMinute();
       setYear(y);
       setMonth(m);
       setDay(d);
       setHour(h);
       setMinute(minu);
       return *this;
   }
  bool Date::operator==(const Date& other) const
    {
        return (m_year==other.getYear()&&m_month==other.getMonth()&&m_day==other.getDay()&&m_hour==other.getHour()&&m_minute==other.getMinute());
    }

   bool Date::operator>(const Date& other) const{
       if(m_year>other.getYear()) return true;
              else if(m_year==other.getYear()){
                  if(m_month>other.getMonth()) return true;
                  else if(m_month == other.getMonth())
                  {
                      if(m_day>other.getDay()) return true;
                      else if(m_day==other.getDay())
                      {
                          if(m_hour>other.getHour()) return true;
                          else if(m_hour == other.getHour()) {
                              if(m_minute>other.getMinute()) return true;
                          }
                      }
                  }
              }
              return false;
   }

   bool Date::operator<(const Date& other) const
   {
       if(m_year<other.getYear()) return true;
       else if(m_year==other.getYear()){
           if(m_month<other.getMonth()) return true;
           else if(m_month == other.getMonth())
           {
               if(m_day<other.getDay()) return true;
               else if(m_day==other.getDay())
               {
                   if(m_hour<other.getHour()) return true;
                   else if(m_hour == other.getHour()) {
                       if(m_minute<other.getMinute()) return true;
                   }
               }
           }
       }
       return false;
   }

 bool Date::operator>=(const Date& other) const{
     return !(*this<other);
 }

  bool Date::operator<=(const Date& other)const{
        return !(*this>other);
    }
