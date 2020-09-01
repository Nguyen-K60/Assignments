Đây là bài tập dành cho sinh viên làm quen với C++ và phần mềm NS-3, bài tập về C++ làm trước.
1. Lập trình C++ trên Ubuntu:
   - Mở terminal bằng tổ hợp phím Ctrl+Alt+t và chạy lệnh sau để cài đặt các gói cần thiết:

		sudo apt install build-essential g++
   - Biên dịch file mã nguồn:

    	g++ tên-file-đầu-vào -o tên-file-đầu-ra

     Ví dụ: g++ example.cc -o example
   - Chạy file vừa biên dịch:

   		./tên-file-đầu-ra

   	 Ví dụ: ./example
2. Bài tập C++: đọc nội dung từ file
   - Cho file input.txt, file này bao gồm nhiều dòng, mỗi dòng bao gồm nhiều số, mỗi số phân biệt bởi ký tự space (dấu cách).
   - Ví dụ ReadData.cc đọc nội dung file này theo từng dòng và hiển thị nội dung đọc được ra màn hình.
   - Bài tập 1: đọc tất cả các số của file input.txt và lưu vào mảng 2 chiều std::vector< std::vector<int> >. Chi tiết yêu cầu và gợi ý ghi trong dòng 31 của file ReadData.cc
3. Cài đặt và biên dịch NS-3
	- Tải về phiên bản NS-3 tại địa chỉ: https://www.nsnam.org/releases/
		Trong mục này, phiên bản sử dụng là ns-3.27
	- Giải nén file vừa tải về, thư-mục-chứa-waf có đường dẫn là: thư-mục-tải-ns3/ns-allinone-3.27/ns-3.27
	- Cài đặt các gói cần thiết và biên dịch NS3

		sudo apt-get install gcc g++ python python3

		cd thư-mục-chứa-waf
		
		./waf configure --disable-tests --disable-examples --disable-python

		./waf
	- Các file chương trình NS-3 cần được đặt tại thư-mục-chứa-waf/scratch
	- Cách chạy chương trình

		./waf --run scratch/tên-file-không-có-phần-mở-rộng

	 Ví dụ, để chạy file example.cc trong thư mục scratch, ta chạy lệnh sau:

	  	./waf --run scratch/example
	- Hướng dẫn sử dụng cho người mới bắt đầu: https://www.nsnam.org/docs/release/3.31/tutorial/ns-3-tutorial.pdf
	- Tổng quan về các module: https://www.nsnam.org/docs/release/3.31/models/singlehtml/index.html

		Chú ý mục: Internet Models (IP, TCP, Routing, UDP, Internet Applications)   

	- Quy tắc viết code trong NS-3: https://www.nsnam.org/develop/contributing-code/coding-style/

	- Group ns-3-users để đặt câu hỏi khi có thắc mắc: https://groups.google.com/g/ns-3-users 

	- Hướng dẫn đặt câu hỏi trong group ns-3-users: https://www.nsnam.org/wiki/Ns-3-users-guidelines-for-posting 
	- Slide mạng máy tính: https://sites.google.com/site/setnguyenhuuthanh/home/mang-may-tinh
4. Bài tập NS-3

   Trong NS-3, mọi đối tượng (người, vật, xe cộ, ...) đều được mô phỏng bởi Node (nút)

   So với C++, NS-3 có 3 cải thiện là:
   + Lập lịch cho sự kiện (phương thức Schedule)
   + Khả năng di chuyển của các Node (mobility)
   + Truyền thông giữa các Node (communication)

	a. Mobility

	   - Ví dụ square.cc mô phỏng một node di chuyển theo hình vuông.
	    Sinh viên đọc kỹ file này để biết cách đặt vị trí và vận tốc cho một node.

	   - Ví dụ follow_waypoints.cc: một node đi theo quỹ đạo định trước.

	   - Bài tập 2: viết chương trình mô phỏng 1 node di chuyển theo quỹ đạo được cho trong file trajectory.txt, tốc độ di chuyển là 10 m/s, gợi ý như sau:

	   	 + Trong file trajectory.txt, mỗi dòng bao gồm 2 số, tương ứng với tọa độ x, y.
	   	  Các tọa độ này được đọc và lưu vào mảng 2 chiều giống như ví dụ C++ bên trên. 
	   	  Node sẽ di chuyển lần lượt tới các vị trí này cho tới khi đi hết các điểm.
	   	  Có thể sử dụng WaypointMobilityModel như ví dụ follow_waypoints.cc

	   - Trực quan hóa bằng NetAnim: 

	   		+ NetAnim là công cụ giúp ta quan sát quá trình mô phỏng, được tích hợp sẵn trong NS-3

	   		+ Cách cài đặt NetAnim có tại địa chỉ: https://www.nsnam.org/wiki/NetAnim_3.108

	   			Mở terminal và chạy các lệnh sau: (thay 3.27 bằng phiên bản phù hợp)

	   			cd đường-dẫn-tới-NS-3/ns-allinone-3.27/netanim-3.108

	   			sudo apt-get install mercurial

	   			sudo apt-get install qt5-default

	   			qmake NetAnim.pro

	   			make

	   		+ Mở NetAnim bằng lệnh

	   			./NetAnim

	   		+ Sau khi chạy xong file square.cc, file square.xml sẽ được tạo ra tại thư mục đường-dẫn-tới-NS-3/ns-allinone-3.27/ns-3.27

	   		+ Nạp file square.xml cho NetAnim và bấm nút Play để quan sát quá trình mô phỏng.

	b. Communication

	   - Ví dụ UAV_sensor.cc: mô phỏng thu thập dữ liệu trong mạng cảm biến không dây. 
	   File này bao gồm cách thiết lập truyền thông WIFI cho các nút mạng, cách gửi và nhận gói tin. 
	   Kịch bản mô phỏng bao gồm một UAV (Unmanned aircraft vehicle - máy bay không người lái) đứng yên
	   Mỗi nút cảm biến (sensor) gửi 1 gói tin cho UAV nhờ định tuyến đa chặng OLSR
	   Nội dung gói tin bao gồm id và tọa độ của sensor.

	   - Bài tập 3: hoàn thành yêu cầu được ghi trong dòng 45 của file UAV_sensor.cc 

	c. Mobility + Communication:

	   - Bài tập 4: chỉnh sửa file UAV_sensor.cc như sau

	   		+ Bỏ giao thức định tuyến OLSR trong file UAV_sensor.cc bằng cách xóa dòng 212 đến 217 và dòng 221 

	   		+ Cho UAV di chuyển tới vị trí của từng sensor để thực hiện việc thu thập dữ liệu. 
	   		Khi UAV đi đến vị trí của một sensor thì sensor này sẽ gửi 1 gói tin cho UAV (coi như sensor biết sự có mặt của UAV)
	   		Nội dung gói tin bao gồm id và tọa độ của sensor. UAV làm như vậy cho đến khi thu thập dữ liệu của tất cả sensor.

5. Lưu ý khi sử dụng NS-3
	- Tất cả mã nguồn của các module nằm tại thư mục đường-dẫn-tới-NS-3/ns-allinone-3.27/ns-3.27/src
	- Trong mỗi module có 3 thư mục quan trọng là:
		+ model: chứa tất cả thiết kế của module này
		+ helper: chứa các helper để sử dụng module thuận tiện và dễ dàng hơn. Ví dụ, để cài Internet Stack cho các node, ta cần thực hiện nhiều thủ tục, các thủ tục này đã được viết sẵn trong InternetStackHelper (xem file UAV_sensor bên trên), do đó nếu sử dụng InternetStackHelper thì sẽ nhanh hơn.
		+ examples: thư mục này chứa các ví dụ liên quan tới module
	- Cách tìm kiếm nội dung của một phương thức:

		Xét 2 dòng lệnh sau:

			InternetStackHelper internet;

  			internet.Install (allNodes);

  		Để biết phương thức Install() có nội dung gì, ta làm như sau:

  		+ Install() là phương thức của class InternetStackHelper, do đó ta sẽ tìm tới class này.

  			Tên class: InternetStackHelper (viết hoa chữ cái đầu của mỗi từ)
  			
  		--> Tên file chứa định nghĩa của class: internet-stack-helper.cc (không viết hoa chữ cái đầu, giữa 2 từ có dấu gạch ngang)
  		+ Truy cập vào thư mục đường-dẫn-tới-NS-3/ns-allinone-3.27/ns-3.27/src, tìm kiếm file internet-stack-helper.cc, mở file ra và tìm kiếm class InternetStackHelper và phương thức Install của class này.