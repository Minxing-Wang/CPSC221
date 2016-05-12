

#include <iostream>
#include <string>
#include "CDate.h"

CDate::CDate(void){
	m_year = m_month = m_day = 0;
}

CDate::CDate(int year, int month, int day){
	setDate( year, month, day );        
}

CDate::CDate(int year, std::string month, int day){
	setDate(year, month, day) ; 
}

bool CDate::isValidDate(int year, int month, int day){	
	if( (month<1) || (month>13) || (year< 0) || !isValidDay(year, month,day)){
	return false;} else 
	{return true; } 
}

bool CDate::isValidDate(int year, std::string month, int day){
	int monthint = monthStr2Num(month); 
	//return isValidDate(year,monthin,day);	
	if( (monthint < 1) || (monthint > 13)|| (year < 0) || !isValidDay(year,monthint,day)){
	return false;} else 
	{return false;}
}

int CDate::monthStr2Num(std::string month){

	if(month.compare("January")== 0 ){
	return 1 ;} else 
	if(month.compare("February") == 0){
	return 2; } else 
	if(month.compare("March") == 0) {
	return 3; } else 
	if(month.compare("April") == 0) {
	return 4; } else 
	if(month.compare("May") == 0) {
	return 5; } else 
	if(month.compare("June") == 0) {
	return 6; } else 
	if(month.compare("July") == 0) {
	return 7; } else 
	if(month.compare("August") == 0) {
	return 8; } else 
	if(month.compare("September") == 0) {
	return 9; } else 
	if(month.compare("October") == 0) {
	return 10; } else 
	if(month.compare("November") == 0) {
	return 11; } else 
	if(month.compare("December") == 0) {
	return 12; }

	return -1;
}

bool CDate::isValidDay(int year, int month, int day){
	if ((day < 1) || (day > 31)) return false;

	bool valid = false;
	switch (month) {
		case 1: if(day <= 31) { valid = true;} break;
		case 3: if(day <= 31) { valid = true;} break;
		case 5: if(day <= 31) { valid = true;} break; 
		case 7: if(day <= 31) { valid = true;} break; 
		case 8: if(day <= 31) { valid = true;} break;
		case 10:if(day <= 31) { valid = true;} break;
		case 12:if(day <= 31) { valid = true;} break;
			
		case 2:
			
			if ((year % 4) != 0) {
				valid = (day <=28);
			} else if ((year % 400) == 0) {
				valid = (day <= 29);
			} else if ((year % 100) == 0) {
				valid = (day <= 28);
			} else {
				valid = (day <= 29);
			}
			break;
		case 4: if(day < 31) { valid = true;} break;
		case 6: if(day < 31) { valid = true;} break;
		case 9: if(day < 31) { valid = true;} break;
		case 11:if(day < 31) { valid = true;} break;
			
		default: return false; 
			 
	}
	return valid;
}

void CDate::setDate(int year, int month, int day){
	if(isValidDate(year, month, day)){    
		m_year = year;
		m_month = month;
		m_day = day;
	}
	else {
		m_year = m_month = m_day = 0;
	}
}


void CDate::setDate(int year, std::string month, int day){
 

	int monthInt = monthStr2Num(month); 
	if(isValidDate(year,monthInt,day)){
		m_year = year; 
		m_month = monthInt; 
		m_day = day; 
	} 
	else { m_year = m_month = m_day = 0; 
	} 
}

void CDate::print(void){
	std::cout << m_year << "/" << m_month << "/" << m_day << std::endl;
}

int CDate::getDate(void){
	return (m_year * 10000) + (m_month * 100) + m_day;
}
