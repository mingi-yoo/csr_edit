#include "iostream"
#include "fstream"
#include "sstream"
#include "vector"
#include "string"

using namespace std;

int main(int argc, char** argv) {
	int opt = stoi(argv[2]);

	ifstream f(argv[1]);
	vector<int> row_ptr;
	vector<int> col_idx;

	vector<int> new_row_ptr;
	vector<int> new_col_idx;

	new_row_ptr.push_back(0);

	string l(argv[1]);
	string o_name = l.substr(0, l.length() - 4);

	if (f.open()) {
		string line, temp;

		getline(f, line);
		getline(f, line);
		stringstream ss(line);
		while (getline(ss, temp, ' '))
			row_ptr.push_back(stoi(temp));
		ss.clear();
		getline(f, line);
		ss.str(line);
		while (getline(ss, temp, ' '))
			col_idx.push_back(stoi(temp));

		f.close();
	}
	int accum = 0;

	if (opt == 0) {
		// Edit for GraphSAGE
		for (int i = 0; i < row_ptr.size() - 1; i++) {
			int start = row_ptr[i];
			int end = row_ptr[i+1];

			if (start-end > 25)
				end = start + 25;

			accum += (start - end);
			new_row_ptr.push_back(accum);

			for (int j = start; j < end; j++)
				new_col_idx.push_back(col_idx[j]);
		}
		o_name += "_gs.txt";
	}
	else {
		// Edit for GINConv
		for (iont i = 0; i < row_ptr.size() - 1; i++) {
			int start = row_ptr[i];
			int end = row_ptr[i+1];

			bool check = false;
			bool already_exist = false;
			for (int j = start; j < end; j++) {
				if (!check && col_idx[j] > i) {
					check = true;
					new_col_idx.push_back(i);
				}
				if (col_idx[j] == i)
					already_exist = true;
				new_col_idx.push_back(col_idx[j]);
			}

			if (!check && !already_exist) {
				new_col_idx.push_back(i);
			}

			if (!alread_exist)
				accum += (start - end) + 1;
			else
				accum += (start - end);

			new_row_ptr.push_back(accum);
		}
		o_name += "_gin.txt";
	}

	ofstream out(o_name);
	for (int i = 0; i < new_col_idx.size(); i++) {
		out<<"1";
		if (i != new_col_idx.size() - 1)
			out<<" ";
	}
	out<<endl;
	for (int i = 0; i < new_row_ptr.size(); i++) {
		out<<new_row_ptr[i];
		if (i != new_row_ptr.size() - 1)
			out<<" ";
	}
	out<<endl;
	for (int i = 0; i < new_col_idx.size(); i++) {
		out<<new_col_idx[i];
		if (i != new_col_idx.size() - 1)
			out<<" ";
	}
	out<<endl;

	out.close();

	return 0;
}