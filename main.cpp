#include <string>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include "constant.h"

using namespace std;
string to_convert = "./to_convert/";
string converted = "./converted/";
int main() {
    vector<string> files;
    for(const auto & entry : filesystem::directory_iterator(to_convert)) {
        filesystem::path filepath = entry.path();
        string filename_str = filepath.string();
        filename_str.erase(filename_str.begin(), filename_str.begin() + 13);

        if(filename_str.substr(filename_str.size() - 4) != ".txt") {
            files.push_back(filename_str);
        }

        set<string> s(files.begin(), files.end());
        files.assign(s.begin(), s.end());
    }

    int current = 0;
    string command;
    while(current != files.size()) {
        // Check if files exist, if so proceed
        command = files.at(current);
        command.erase(command.end() - 4, command.end());
        string total = to_convert + command + ".jpg";
        cout << total << endl;
        cv::Mat image = cv::imread(total, 1);
        cv::Mat resize;
        cv::resize(image, resize, cv::Size(width, height), cv::INTER_LINEAR);
        cv::imwrite(converted + command + ".jpg", resize);
        current++;
    }
}