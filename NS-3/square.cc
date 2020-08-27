// file này để cài đặt một node đi theo quỹ đạo hình vuông
#include "ns3/core-module.h"
#include "ns3/mobility-module.h"
#include "ns3/netanim-module.h"
using namespace ns3;
// các hàm về tọa độ và vận tốc
// để sử dụng các hàm này cần phải Install MobilityModel trước
// lấy vị trí của 1 node
Vector GetPosition(Ptr<Node> node)
{
  return node -> GetObject<MobilityModel>()->GetPosition();
}
// đặt vị trí cho 1 nút
void SetPosition(Ptr<Node> node, Vector pos)
{
  node -> GetObject<MobilityModel>()->SetPosition(pos);
}
// đặt vận tốc 
void SetVelocity(Ptr<Node> node, Vector vel)
{
  node -> GetObject<ConstantVelocityMobilityModel>()->SetVelocity(vel);
}
// lấy vận tốc
Vector GetVelocity(Ptr<Node> node)
{
  return node -> GetObject<ConstantVelocityMobilityModel>()->GetVelocity();
}
//Kết thúc các hàm về tọa độ và vận tốc


//Hàm cài đặt một node đi theo quỹ đạo hình vuông 
// các tham số: node: node cần cài đặt
//				newVel: vận tốc của node
//				edge: độ dài cạnh hình vuông

void SquareTrajectory(Ptr<Node> node, Vector vel, double edge)
{
	// coi node chuyển động trong không gian 2 chiều, tức là z không đổi
	double now = Simulator::Now().GetSeconds();// lấy thời gian mô phỏng hiện tại
	Vector pos = GetPosition(node); // lấy vị trí hiện tại
	std::cout<<now<<": "<<pos<<std::endl;// hiển thị vị trí hiện tại ra màn hình
	SetVelocity(node, vel); // Đặt vận tốc
	//Khi đi đến đỉnh hình vuông ta sẽ xoay vector vận tốc góc 90 độ 
	//Khi xoay vector (x, y) 90 độ theo chiều kim đồng hồ ta được vector(y, -x)
	double velLength = vel.GetLength();// tốc độ chuyển động 
	double time = edge/velLength; //thời gian đi hết một cạnh
	double x = vel.x;
	double y = vel.y;
	double z = vel.z;
	Vector nextVel = Vector(y, -x, z);
	Simulator::Schedule(Seconds(time), &SquareTrajectory, node, nextVel, edge);
	// Schedule là phương thức quan trọng trong ns3, chỉ áp dụng cho các hàm có kiểu trả về là void
	// chú ý cú pháp sử dụng phương thức Schedule
}
void Stop()
{
	Simulator::Stop();
}
int main()
{
	//tạo node
	NodeContainer n;
	n.Create(1);
	// install mobility model
	MobilityHelper m;
	m.SetMobilityModel("ns3::ConstantVelocityMobilityModel");
	m.Install(n);
	//đặt tọa độ ban đầu
	SetPosition(n.Get(0), Vector(0, 0, 0));
	//đi theo hình vuông
	SquareTrajectory(n.Get(0), Vector(0, 10, 0), 100);
	Simulator::Schedule(Seconds(1000), &Stop);//dừng mô phỏng
	AnimationInterface anim("square.xml");// trực quan hóa quá trình mô phỏng với netanim
	Simulator::Run();
	Simulator::Destroy();
}
