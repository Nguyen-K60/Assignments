#include <iostream> // std::cout
#include <string> // std::string
#include <vector> // std::vector
#include <fstream> // std::fstream
#include <stdlib.h> // atoi
// filename: tên file cần đọc
// arr: mảng dùng để lưu dữ liệu đọc được
void ReadData(std::string filename, std::vector< std::vector<int> > &arr)// 2 dimentions array
{
	std::vector<std::string> output;// lưu nội dung file, mỗi phần tử là 1 dòng của file, output[0] là dòng đầu tiên của file
	std::string line1;
	std::ifstream myfile(filename.c_str());
	if(myfile.is_open())
	{
		while(getline(myfile, line1)) // đọc từng dòng của file và lưu vào line1
		{
			int size = line1.size();
			if(line1.size() == 0)
			{
				continue;
			}
			output.push_back(line1);
		}
		myfile.close();
		// hiển thị nội dung đọc được
		int size = output.size(); // size là số dòng đọc được
		for(int k = 0; k < size; k++)
		{
			std::cout<<output[k]<<std::endl;
		}
		// yêu cầu: trong mỗi dòng, tách ra từng số rồi lưu lại	vào mảng arr
		// gợi ý: 	hai số trong 1 dòng ngăn cách bởi dấu cách
		// 			duyệt từng phần tử của dòng, khi gặp ký tự dấu cách hoặc ký tự cuối cùng của dòng thì lưu số đọc được
		// Do số dòng và số phần tử trong mỗi dòng không biết trước nên không thể dùng mảng tĩnh, do đó cần phải dùng mảng động std::vector< std::vector<int> >
		// sinh viên có thể tự làm theo cách của riêng mình, không nhất thiết phải làm theo gợi ý này, miễn là kết quả đúng.
		// hoàn thành dòng code 47, 48, 52, 53 theo gợi ý được ghi tại mỗi dòng dưới đây để thực hiện yêu cầu trên
		// for(int k = 0; k < size; k++)
		// {
		// 	std::string line = output[k]; // dòng thứ k
		// 	std::string temp; // dùng để lưu số đọc được
		// 	std::vector<int> row;// dùng để lưu các số trong 1 dòng
		// 	int num = line.size(); // số ký tự trong dòng
		// 	for(int i = 0; i < num; i++)
		// 	{
		// 		if(line[i] == ' ') // gặp ký tự dấu cách --> lưu số đọc được vào row
		// 		{
		// 			// lưu temp vào row
		// 			// xóa temp để đọc số tiếp theo
		// 		}
		// 		else if(i == num-1) // gặp ký tự cuối cùng của dòng --> lưu số đọc được vào row
		// 		{
		// 			 // lưu số cuối cùng vào temp
		// 			 // lưu temp vào row
		// 		}
		// 		else // gặp số --> lưu số này vào biến temp
		// 		{
		// 			temp.push_back(line[i]); // lưu số vào temp
		// 		}
		// 	}
		// 	arr.push_back(row); // lưu hàng 
		// }
		// sau khi đọc xong thì nội dung file sẽ được lưu trong mảng 2 chiều arr
	}
	else
	{
		std::cout<<"cannot open file "<<filename<<std::endl;
	}
}

int main()
{
	std::vector< std::vector<int> > arr;
	std::string filename = "input.txt";
	ReadData(filename, arr);
	// bỏ comment đoạn code dưới đây để hiển thị kết quả đọc được
	// for(int i = 0; i < (int)arr.size(); i++)
	// {
	// 	std::vector<int> v = arr[i];
	// 	int s = v.size();
	// 	for(int j = 0; j < s; j++)
	// 	{
	// 		std::cout<<v[j]<<" ";
	// 	}
	// 	std::cout<<std::endl;
	// }
	return 0;
}