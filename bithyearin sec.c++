#include <iostream>
#include <ctime>

using namespace std;

int getTheYear();
int getTheMonth();
int getTheDay();
int getTheHour();
int getTheMinute();
int getTheSecond();
int countLeapYears(int, int);
int welcome();
int calcAgeInSeconds(int, int, int);
int calcOffset(int, int);
int calcDaysRemainingThisYear(int, int);
int calcDaysSinceBDay(int, int);

int main(int argc, char** argv) 
{

    welcome();
    return 0;
}

int getTheYear( ) //Retrieve current year
{
   // current date/time based on current system
   time_t now = time(0);

   tm *ltm = localtime(&now);

   return (1900+ltm->tm_year); // print various components of tm structure.
   /*cout << "Year: "<< 1900 + ltm->tm_year << endl;*/
}

int getTheMonth() //Retrieve current month
{
    // current date/time based on current system
   time_t now = time(0);

   tm *ltm = localtime(&now);

   return (1+ltm->tm_mon); // print various components of tm structure.
   /*cout << "Month: "<< 1 + ltm->tm_mon<< endl;*/
}

int getTheDay() //Retrieve current day of month
{
    // current date/time based on current system
   time_t now = time(0);

   tm *ltm = localtime(&now);

   return (ltm->tm_mday); // print various components of tm structure.
   /*cout << "Day: "<<  ltm->tm_mday << endl;*/
}

int getTheHour() //Retrieve current hour
{
    // current date/time based on current system
   time_t now = time(0);

   tm *ltm = localtime(&now);

   return (1+ltm->tm_hour); // print various components of tm structure.
   /*cout << "Time: "<< 1 + ltm->tm_hour << ":";*/
}

int getTheMinute() //Retrieve current minute
{
    // current date/time based on current system
   time_t now = time(0);

   tm *ltm = localtime(&now);

   return (1+ltm->tm_min); // print various components of tm structure.
   /*cout << 1 + ltm->tm_min << ":";*/
}

int getTheSecond() //Retrieve current second
{
    // current date/time based on current system
   time_t now = time(0);

   tm *ltm = localtime(&now);

   return (1+ltm->tm_sec); // print various components of tm structure.
   /*cout << 1 + ltm->tm_sec << endl;*/
}

int welcome() //Get birthday input from user.  Pass info to appropriate functions. Output age in seconds.
{
    std::cout << "Welcome to the Age Calculator!\n";
    std::cout << "January \t-- 1\t|\tFebruary \t-- 2\nMarch \t\t-- 3\t|\tApril \t\t-- 4\n";
    std::cout << "May \t\t-- 5\t|\tJune \t\t-- 6\nJuly \t\t-- 7\t|\tAugust \t\t-- 8\n";
    std::cout << "September \t-- 9\t|\tOctober \t-- 10\nNovember \t-- 11\t|\tDecember \t-- 12";
    std::cout << "\n\nWhat month were you born in: ";

    int monthBorn=0;
    std::cin >> monthBorn;

    int dayOfMonthBorn=0;
    std::cout << "Enter the day of the month you were born: ";
    std::cin >> dayOfMonthBorn;

    int yearBorn=0;
    std::cout << "Enter the year you were born: ";
    std::cin >> yearBorn;
    std::cout << "\nThank you.  One moment.\nCalculating...\n\n";

    int ageInSeconds=0;
    ageInSeconds=calcAgeInSeconds(monthBorn,dayOfMonthBorn,yearBorn);

    std::cout << "You are " << ageInSeconds << " seconds old! Congratulations!\n\n";
    std::cout << "Enter \"0\" to end. ";

    char endPrg = ' ';
    std::cin >> endPrg;

    return 0;
}

int calcAgeInSeconds(int month, int day, int year)
{
   int curYear  =   getTheYear();
   int curMon   =   getTheMonth();
   int curDay   =   getTheDay();
   int curHour  =   getTheHour();
   int curMin   =   getTheMinute();
   int curSec   =   getTheSecond();
   int leapCount=   countLeapYears(curYear, year);
   int yearsOld =   curYear - year;

   //If person has not had their birthday yet, they are a year younger.
   if (curMon < month || (curMon == month && curDay < day))
       yearsOld--;

   //If this is a leap year, but before leap day, then subtract one leap day.
   if (((curYear / 4) * 4 == curYear) && (curMon < 2 || (curMon == 2 && curDay <= 28)))
       leapCount--;

   //If person born on leap year, but after leap day, subtract one leap day.
   if (((year / 4) * 4 == year) && (month > 2))
       leapCount--;

   int secondsOld   = 0;
   int dayOffset    = 0;
   dayOffset        = calcOffset(month, day); //Account for days since birthday or until birthday
   secondsOld       = yearsOld * 365 + leapCount + dayOffset; //Add up total number of days
   secondsOld       = secondsOld * 24 + curHour; //Convert to hours and add today's hours.
   secondsOld       = secondsOld * 60 + curMin; //Convert to minutes and add today's minutes.
   secondsOld       = secondsOld * 60 + curSec; //Convert to seconds and add today's seconds.

   return secondsOld; 
}

int calcOffset(int theirMon, int theirDay)
{
   int curYear  =   getTheYear();
   int curMon   =   getTheMonth();
   int curDay   =   getTheDay();
   int curHour  =   getTheHour();
   int curMin   =   getTheMinute();
   int curSec   =   getTheSecond(); 
   int dayOff   =   0;

   //If they have not yet had their birthday...
   if ((curMon < theirMon) || ((curMon == theirMon) && (curDay < theirDay)))
       dayOff = 365 - calcDaysRemainingThisYear(theirMon, theirDay);
   //If they have had their birthday...
   else if ((curMon == theirMon) && (curDay == theirDay))
       dayOff = 0;
   else
       dayOff = calcDaysSinceBDay(theirMon, theirDay);

   return dayOff;
}

int calcDaysRemainingThisYear(int theirMon, int theirDay)
{
    int curYear     = getTheYear();
    int curDay      = getTheDay();
    int curMon      = getTheMonth();
    int dayOffset   = 0;

    while (curMon < theirMon)
    {
        if (curMon == 1)
            dayOffset += 31;
        else if (curMon == 2)
        {
            if ((curYear / 4) * 4 == curYear)
                dayOffset += 29;
            else dayOffset += 28;
        }
        else if (curMon == 3)
            dayOffset += 31;
        else if (curMon == 4)
            dayOffset += 30;
        else if (curMon == 5)
            dayOffset += 31;
        else if (curMon == 6)
            dayOffset += 30;
        else if (curMon == 7)
            dayOffset += 31;
        else if (curMon == 8)
            dayOffset += 31;
        else if (curMon == 9)
            dayOffset += 30;
        else if (curMon == 10)
            dayOffset += 31;
        else if (curMon == 11)
            dayOffset += 30;
        else if (curMon == 12)
        {
            dayOffset += 31;
            curMon = 0;
        }

        curMon ++;
    }

    dayOffset -= curDay;
    dayOffset += theirDay;

    return dayOffset;
}

int calcDaysSinceBDay(int theirMon, int theirDay)
{
    int curYear     = getTheYear();
    int curDay      = getTheDay();
    int curMon      = getTheMonth();
    int dayOffset   = 0;

    while (theirMon < curMon)
    {
        if (theirMon == 1)
            dayOffset += 31;
        else if (theirMon==2)
        {
            if (((curYear - 1) / 4) * 4 == (curYear - 1))
                dayOffset += 29;
            else dayOffset += 28;
        }
        else if (theirMon == 3)
            dayOffset += 31;
        else if (theirMon == 4)
            dayOffset += 30;
        else if (theirMon == 5)
            dayOffset += 31;
        else if (theirMon == 6)
            dayOffset += 30;
        else if (theirMon == 7)
            dayOffset += 31;
        else if (theirMon == 8)
            dayOffset += 31;
        else if (theirMon == 9)
            dayOffset += 30;
        else if (theirMon == 10)
            dayOffset += 31;
        else if (theirMon == 11)
            dayOffset += 30;
        else if (theirMon == 12)
        {
            dayOffset += 31;
            theirMon = 0;
        }

        theirMon ++;
    }

    dayOffset -= theirDay;
    dayOffset += curDay;

    return dayOffset;
}

int countLeapYears(int curYear, int theirYear)
{
    //Find nearest year divisible by 4 beginning at or prior to the start count,
    //then begin subtracting 4 from the start count until we get to the finish count
    int leapYears   =   0;
    int modYears    =   0;

    //Found a better way than the comment under this code.
    //No If statements required, just find the mod, take it out, calculate leaps.
    modYears = curYear % 4;
    curYear -= modYears;
    while (curYear >= theirYear)
    {
        curYear -= 4;
        leapYears++;
    }

    return leapYears;
    /* Found a better way than this.  See above.
    if ((curYear / 4) * 4 == curYear) //This year is a leap year.
    {

    }
    else if (((curYear - 1) / 4) * 4 == curYear) //Last year was a leap year.
    {
        while ((curYear - 1) >= theirYear)
        {
            curYear -= 4;
            leapYears++;
        }
    }
    else if (((curYear - 2) / 4) * 4 == curYear) //Year before last was a leap year.
    {
        while ((curYear - 2) >= theirYear)
        {
            curYear -= 4;
            leapYears++;
        }
    }
    else //Next year is a leap year.
    {
        while ((curYear - 3) >= theirYear)
        {
            curYear -= 4;
            leapYears++;
        }
    }

    return leapYears;*/
}
