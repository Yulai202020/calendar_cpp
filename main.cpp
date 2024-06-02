#include <ctime>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

std::string red = "\033[31m";
std::string reset = "\033[0m";
std::string yellow = "\033[33m";
std::string white = "\033[30;47m";

std::vector<std::vector<int>> all_holidays = {{1, 2, 3}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
std::vector<std::string> months = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

int find(std::vector<int> list, int item) {
    auto it = std::find(list.begin(), list.end(), item);
    if (it != list.end()) {
        return *it;
    } else {
        return -1;
    }
}

void print_cal(int weekday, int days, int day, std::vector<int> holidays) {
    std::cout << std::string(3 * weekday, ' ');

    for (int i = weekday; i < days + weekday; i++) {
        int day_num = i + 1 - weekday;
        int it = find(holidays, day_num);

        if ((day_num)/10 < 1) {
            if (day_num == day) {
                std::cout << white << day_num << reset << "  ";
            } else if ((i+1) % 7 == 0 || (i+1) % 7 == 6 ) {
                std::cout << red << day_num << reset << "  ";
            } else if (day_num == it) {
                std::cout << red << day_num << reset << "  ";
            } else {
                std::cout << day_num << "  ";
            }
        } else {
            if (day_num == day) {
                std::cout << white << day_num << reset << " ";
            } else if ((i+1) % 7 == 0 || (i+1) % 7 == 6 ) {
                std::cout << red << day_num << reset << " ";
            } else if ((i+1) == it) {
                std::cout << red << day_num << reset << " ";
            } else {
                std::cout << day_num << " ";
            }
        }

        if ((i+1) % 7 == 0 && i != days + weekday - 1){
            std::cout << std::endl;
        }
    }

    std::cout << std::endl;
}

int get_month() {
    std::time_t t = std::time(nullptr);
    std::tm* localTime = std::localtime(&t);
    int month = localTime->tm_mon + 1;
    return month;
}

int get_day() {
    std::time_t t = std::time(nullptr);
    std::tm* localTime = std::localtime(&t);
    int day = localTime->tm_mday;
    return day;
}

int get_year() {
    std::time_t t = std::time(nullptr);
    std::tm* localTime = std::localtime(&t);
    int year = localTime->tm_year + 1900;
    return year;
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int getDaysInMonth(int month, int year) {
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (month == 2 && isLeapYear(year)) {
        return 29;
    }

    return daysInMonth[month - 1];
}

int getWeekdayStartOfMonth(int year, int month) {
    struct std::tm time_in = { 0, 0, 0, 1, month - 1, year - 1900 };
    std::mktime(&time_in);
    int weekday = time_in.tm_wday;

    if (weekday == 0) {
        weekday = 6;
    } else {
        weekday--;
    }

    return weekday;
}

int main(int argc, char* argv[]) {
    int year, month, day;

    if (argc > 1){
        year = std::stoi(argv[1]);
        month = std::stoi(argv[2]);
        day = -1;
    } else {
        year = get_year();
        month = get_month();
        day = get_day();
    }

    int days_in_month = getDaysInMonth(month, year);

    std::cout << "\n    " << yellow << months[month-1] << " " << year << reset << "\n" << std::endl;
    std::cout << "Mo Tu We Th Fr Sa Su" << std::endl;

    int weekday = getWeekdayStartOfMonth(year, month);

    std::vector<int> all_holidays_month = all_holidays[month-1];

    print_cal(weekday, days_in_month, day, all_holidays_month);

    std::cout << "\n";

    return 0;
}