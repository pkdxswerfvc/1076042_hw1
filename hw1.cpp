#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#pragma warning(disable : 4996)

using namespace std;

bool predictor(string state, string seq);	// 預測 function
vector<string> predictor_state;

int main() {
	cout << "  1076042 -- 2-bit Simple Predictor --  " << endl << endl;
	char file_name[100] = "test_case.txt";
	char filename_output[100] = "";
	string line;
	vector<string> input_sequence;
	vector<string> miss;
	vector<string> prediction;

	predictor_state.push_back("00");	// 初始 state 狀態
	double misprediction_rate = 0;
	int miss_count = 0;

	cout << "File name: ";
	cin >> file_name;
	cout << endl;

	// creat output file name
	int j = 0;
	while (file_name[j] != '.' && j != strlen(file_name)) {
		filename_output[j] = file_name[j];
		j++;
	}
	strncat(filename_output, "_result.txt", 100);
	
	// open file
	ifstream infile(file_name);
	ofstream write_file;
	if (!infile) {    // Can not open file
		std::cout << "Open file error..." << endl << endl;
		system("pause");
		exit(0);
	}
	else {    // Open file success
		write_file.open(filename_output);

		while (getline(infile, line)) {

			istringstream iss(line);
			for (std::string s; iss >> s; )	// 切割輸入序列 存入vector中
				input_sequence.push_back(s);

			for (int i = 0; i < input_sequence.size(); i++) {
				// 接收 prediction 結果
				if (predictor(predictor_state[i], input_sequence[i]) == 0) {
					prediction.push_back("N");
				}
				else {
					prediction.push_back("T");
				}
				// 判斷是否 miss
				if (input_sequence[i] == "T") {
					if (prediction[i] == "T") {
						miss.push_back("V");
					}
					else {	// prediction == N
						miss.push_back("X");
						miss_count++;
					}
				}
				else {	// input == N
					if (prediction[i] == "T") {
						miss.push_back("X");
						miss_count++;
					}
					else {	// prediction == N
						miss.push_back("V");
					}
				}
			}
			misprediction_rate = ((double)miss_count / (double)input_sequence.size()) * 100.0;	// 計算 miss prediction 比例(%)
																					// 輸出結果
			cout << "Predictor state\t";
			write_file << "Predictor state\t";
			for (int i = 0; i < predictor_state.size() - 1; i++) {
				cout << predictor_state[i] << "\t";
				write_file << predictor_state[i] << "\t";
			}
			cout << endl;
			write_file << endl;
			cout << "Actual outcome\t";
			write_file << "Actual outcome\t";
			for (int i = 0; i < input_sequence.size(); i++) {
				cout << input_sequence[i] << "\t";
				write_file << input_sequence[i] << "\t";
			}
			cout << endl;
			write_file << endl;
			cout << "Prediction\t";
			write_file << "Prediction\t";
			for (int i = 0; i < prediction.size(); i++) {
				cout << prediction[i] << "\t";
				write_file << prediction[i] << "\t";
			}
			cout << endl;
			write_file << endl;
			cout << "Miss\t\t";
			write_file << "Miss\t\t";
			for (int i = 0; i < miss.size(); i++) {
				cout << miss[i] << "\t";
				write_file << miss[i] << "\t";
			}
			cout << endl;
			write_file << endl;
			cout << "Misprediction rate: " << fixed << setprecision(1) << misprediction_rate << "%" << endl << endl;
			write_file << "Misprediction rate: " << fixed << setprecision(1) << misprediction_rate << "%" << endl << endl;
			
			// 初始化
			input_sequence.clear();
			predictor_state.clear();
			prediction.clear();
			miss.clear();
			miss_count = 0;
			predictor_state.push_back("00");
		}
	}
	system("pause");
	return 0;
}


bool predictor(string state, string seq) {
	bool prediction_result = 0; // 預測結果，0為N 1為T
	if (state == "00") {
		prediction_result = 0;
		if (seq == "T") {
			predictor_state.push_back("01");
		}
		else {	// NT
			predictor_state.push_back("00");
		}
	}
	else if(state == "01") {
		prediction_result = 0;
		if (seq == "T") {
			predictor_state.push_back("10");
		}
		else {	// NT
			predictor_state.push_back("00");
		}
	}
	else if (state == "10") {
		prediction_result = 1;
		if (seq == "T") {
			predictor_state.push_back("11");
		}
		else {	// NT
			predictor_state.push_back("01");
		}
	}
	else if (state == "11") {
		prediction_result = 1;
		if (seq == "T") {
			predictor_state.push_back("11");
		}
		else {	// NT
			predictor_state.push_back("10");
		}
	}
	return prediction_result;
}

