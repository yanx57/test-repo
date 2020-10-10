//
//  User.hpp
//  agenda
//
//  Created by 严旭 on 2020/8/3.
//  Copyright © 2020 严旭. All rights reserved.
//
#ifndef USER_H
#define USER_H

#include <initializer_list>
#include <string>
class User {
 public:
 
  User() = default;

  
  User(const std::string &t_userName, const std::string &t_userPassword,
       const std::string &t_userEmail, const std::string &t_userPhone);

 
  User(const User &t_user);

 
  std::string getName() const;

  
  void setName(const std::string &t_name);

 
  std::string getPassword() const;

 
  void setPassword(const std::string &t_password);

  
  std::string getEmail() const;

 
  void setEmail(const std::string &t_email);

  
  std::string getPhone() const;

 
  void setPhone(const std::string &t_phone);

 private:
  std::string m_name;
  std::string m_password;
  std::string m_email;
  std::string m_phone;
};

#endif
