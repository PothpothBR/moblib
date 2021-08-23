/*----------------------------------------------------
  |               Programa feito por                 |
  |     [Bruno Dalagnol] [2018] [versao: sei la]     |
  ----------------------------------------------------
  |                                                  |
  |			    /\         /\       ___              |
  |			   /--\_______/--\     /  _|             |
  |			   |  Y       Y  |    / /                |
  |			   |    ==T==    |   / /                 |
  |			   \_____________/  / /                  |
  |				  |  _____   \ / /                   |
  |				  |           \ /                    |
  |				  |  |--|  |\  |                     |
  |				  |__||_|__||__|                     |
  ----------------------------------------------------
*/

#ifndef DEBUGLOG_H
#define DEBUGLOG_H

#define SPRITEDEBUG
//#define SPRITEFILTERDEBUG

#include <iostream>
#include <string>
#include <fstream>
using namespace std;
ofstream cache_log("moblib/moblibDebug.log", ios::trunc);


#ifdef SPRITEDEBUG

		#ifdef SPRITEFILTERDEBUG

		char arrow[8] = { '=' , '=' , '=' , '=' , '=' , '>',' ', '\0' };

		void debugLog(std::string valueString1) {

			std::cout << std::endl << arrow + valueString1 << std::endl;
			cache_log << std::endl << arrow + valueString1 << std::endl;
		}


		void debugLog(std::string valueString1, short int valuenumber1, std::string valueString2="", short int valuenumber2=0) {

		}

		#else

		char arrow[8] = { '=' , '=' , '#' , '=' , '=' , '>',' ', '\0' };
		char contarw[6] = { ' ' , ' ' , '#' , '>', ' ', '\0' };
		void debugLog(std::string valueString1) {

			std::cout << std::endl << arrow + valueString1  << std::endl;
			cache_log << std::endl << arrow + valueString1 << std::endl;
		}

		void debugLog(std::string valueString1, short int valuenumber1) {

			std::cout << contarw + valueString1+' ' << valuenumber1  << std::endl;
			cache_log << contarw + valueString1 + ' ' << valuenumber1 << std::endl;
		}

		void debugLog(std::string valueString1, short int valuenumber1, std::string valueString2) {

			std::cout << contarw + valueString1+' ' << valuenumber1 << " # " + valueString2  << std::endl;
			cache_log << contarw + valueString1 + ' ' << valuenumber1 << " # " + valueString2 << std::endl;
		}

		void debugLog(std::string valueString1, short int valuenumber1, std::string valueString2, short int valuenumber2) {

			std::cout << contarw + valueString1+' ' << valuenumber1 << " # " + valueString2+' ' << valuenumber2 << std::endl;
			cache_log << contarw + valueString1 + ' ' << valuenumber1 << " # " + valueString2 + ' ' << valuenumber2 << std::endl;
		}
		#endif

	#else

	#define debugLog(a,b,c,d)

#endif // DEBUG


#endif
